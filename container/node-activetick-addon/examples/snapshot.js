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


api.handlers["ATLoginResponse"] = function ( data ) {
  console.log( JSON.stringify(data, null, 2) );
  var req1 = {};

  //req1.symbols = "WMT";
  req1.symbols = ".WMT   160115P00047500";
  //req1.fields  = "QuoteFieldLastPrice,QuoteFieldProfileLongName";
  req1.fields = "QuoteFieldLastPrice,QuoteFieldOptionOpenInterest";
  var reqNum = api.sendATQuoteDbRequest(req1);
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
