var addon = require('../activetick');
var messageIds = addon.messageIds;
var colors = require('colors/safe');

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

var lastBid = {};
var lastAsk = {};
var lastTrade = {};

api.handlers["ATLoginResponse"] = function ( data ) {
  console.log( JSON.stringify(data, null, 2) );
  var req = {};
  req.symbols = "AAPL,WMT,XOM";
  lastBid["AAPL"] = 0;
  lastBid["WMT"] = 0;
  lastBid["XOM"] = 0;
  lastAsk["AAPL"] = 0;
  lastAsk["WMT"] = 0;
  lastAsk["XOM"] = 0;
  lastTrade["AAPL"] = 0;
  lastTrade["WMT"] = 0;
  lastTrade["XOM"] = 0;
  req.requestType = "StreamRequestSubscribeQuotesOnly";
  var reqNum = api.sendATQuoteStreamRequest(req);

  console.log(reqNum);
  
};
/*
api.handlers["ATStreamQuoteUpdate"] = function ( msg ) {
  var atTime = msg.data.time;
  var bidText = "";
  var askText = "";
  var bidPrice = msg.data.bidPrice.price.round(msg.data.bidPrice.precision);
  var askPrice = msg.data.askPrice.price.round(msg.data.askPrice.precision);
  if ( lastBid[msg.data.ATSymbol.symbolStr] < bidPrice ) {
    bidText = colors.green(bidPrice.toString());
  } else if ( lastBid[msg.data.ATSymbol.symbolStr] > bidPrice ) {
    bidText = colors.red(bidPrice.toString());
  } else {
    bidText = colors.gray(bidPrice.toString());
  }
  lastBid[msg.data.ATSymbol.symbolStr] = bidPrice;
  if ( lastAsk[msg.data.ATSymbol.symbolStr] < askPrice ) {
    askText = colors.green(askPrice.toString());
  } else if ( lastAsk[msg.data.ATSymbol.symbolStr] > askPrice ) {
    askText = colors.red(askPrice.toString());
  } else {
    askText = colors.gray(askPrice.toString());
  }
  lastAsk[msg.data.ATSymbol.symbolStr] = askPrice;
  var padding = "";
  if (atTime.milliseconds < 100)
    padding = " ";
  else if (atTime.milliseconds < 10)
    padding = "  ";
  lastAsk[msg.data.ATSymbol.symbolStr] = askPrice;
  console.log(colors.gray(atTime.year + "-" + atTime.month + "-" + atTime.day + " " +
              atTime.hour + ":" + atTime.minute + ":" + atTime.second + ":" +
              atTime.milliseconds + padding + " [QUOTE] " +
              msg.data.ATSymbol.symbolStr + " ") +
              colors.gray(msg.data.bidSize) + " | " +
              bidText + " - " +
              askText + " | " +
              colors.gray(msg.data.askSize) );
};


api.handlers["ATStreamTradeUpdate"] = function ( msg ) {
  var atTime = msg.data.time;
  var lastText = "";
  var lastPrice = msg.data.lastPrice.price.round(msg.data.lastPrice.precision);
  if ( lastTrade[msg.data.ATSymbol.symbolStr] < lastPrice ) {
    lastText = colors.green(lastPrice.toString());
  } else if ( lastTrade[msg.data.ATSymbol.symbolStr] > lastPrice ) {
    lastText = colors.red(lastPrice.toString());
  } else {
    lastText = colors.gray(lastPrice.toString());
  }
  lastTrade[msg.data.ATSymbol.symbolStr] = lastPrice;
  var padding = "";
  if (atTime.milliseconds < 100)
    padding = " ";
  else if (atTime.milliseconds < 10)
    padding = "  ";
  console.log(colors.gray(atTime.year + "-" + atTime.month + "-" + atTime.day + " " +
              atTime.hour + ":" + atTime.minute + ":" + atTime.second + ":" +
              atTime.milliseconds + padding + " [TRADE] " +
              msg.data.ATSymbol.symbolStr + " " +
              msg.data.lastSize + " @ ") + 
              lastText );
};
*/
var connected = api.connect( process.env.ATAPIKEY,
                             "activetick1.activetick.com",
                             5000,
                             process.env.ATUID,
                             process.env.ATPWD );

if (connected) {
  api.beginProcessing();
}
