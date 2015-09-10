var addon = require('../activetick');
var messageIds = addon.messageIds;
var colors = require('colors');

var api = new addon.NodeActivetick();

Number.prototype.round = function(places) {
  return +(Math.round(this + "e+" + places)  + "e-" + places);
}

var activetickCb = function (data) {
  console.log(JSON.stringify(data,null,2));
};

Object.keys(messageIds).forEach(function (messageId) {
  api.handlers[messageId] = activetickCb;
});

var printQuote = function ( record ) {
  var res = "[QUOTE] ";
  res += colors.gray(record.quoteBidSize.toString());
  res += colors.gray(" | ");
  res += colors.gray(record.quoteBidPrice.price.round(
           record.quoteBidPrice.precision).toString());
  res += colors.gray(" - ");
  res += colors.gray(record.quoteAskPrice.price.round(
           record.quoteAskPrice.precision).toString());
  res += colors.gray(" | ");
  res += colors.gray(record.quoteAskSize.toString());
  return res;
};

var printTrade = function ( record ) {
  var res = "[TRADE] ";
  res += colors.gray(record.tradeLastSize.toString());
  res += colors.gray(" @ ");
  res += colors.gray(record.tradeLastPrice.price.round(
           record.tradeLastPrice.precision).toString());
  return res;
};

var printTime = function ( atTime ) {
  var res = "";
  var padding = "";
  if (atTime.milliseconds < 100)
    padding = " ";
  else if (atTime.milliseconds < 10)
    padding = "  ";
  res += colors.gray( atTime.year + "-" + atTime.month + "-" + 
                      atTime.day + " " + atTime.hour + ":" +
                      atTime.minute + ":" + atTime.second + ":" +
                      atTime.milliseconds + padding );
  return res;
};

api.handlers["ATTickHistoryDb"] = function ( data ) {
  var records = data.data.ATTickHistory.records;
  for ( var recordId in records ) {
    var record = records[recordId]
    var atTime = record.time;
    var recData = "";
    if (record.tradeLastPrice) {
      recData = printTrade( record );
    } else if (record.quoteBidPrice) {
      recData = printQuote( record );
    }
    console.log( printTime(atTime) + " " + recData );
  }
  process.exit(0);
};

api.handlers["ATLoginResponse"] = function ( data ) {
  console.log( JSON.stringify(data, null, 2) );
  var req1 = {};
  req1.symbol = ".WMT   160115P00047500";
  req1.selectTrades = true;
  req1.selectQuotes = true;
  req1.beginDateTime = "20150428093000"
  req1.endDateTime = "20150511093000"
  var reqNum = api.sendATTickHistoryDbRequest(req1);
  console.log(reqNum);
  
};

var connected = api.connect( process.env.ATAPIKEY,
                             "activetick1.activetick.com",
                             5000,
                             process.env.ATUID,
                             process.env.ATPWD );

if (connected) {

  api.beginProcessing();
}
