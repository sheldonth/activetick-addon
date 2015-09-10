var addon = require('../activetick');
var messageIds = addon.messageIds;

var nano = require('nanomsg');
var colors = require('colors/safe');

var api = new addon.NodeActivetick();
var pub = nano.socket('pub');
var addr = 'tcp://127.0.0.1:7789';

Number.prototype.round = function(places) {
  return +(Math.round(this + "e+" + places)  + "e-" + places);
}

var activetickCb = function (data) {
  pub.send(JSON.stringify(data));
};

Object.keys(messageIds).forEach(function (messageId) {
  api.handlers[messageId] = activetickCb;
});

api.handlers["ATLoginResponse"] = function ( data ) {
  console.log( JSON.stringify(data, null, 2) );
  var req = {};
  req.symbols = "#USD/CHF,#USD/JPY,#EUR/USD,#EUR/GBP";
  req.requestType = "StreamRequestSubscribe";
  var reqNum = api.sendATQuoteStreamRequest(req);
};

var connected = api.connect( process.env.ATAPIKEY,
                             "activetick1.activetick.com",
                             5000,
                             process.env.ATUID,
                             process.env.ATPWD );

if (connected) {
  pub.bind(addr);
  api.beginProcessing();
}
