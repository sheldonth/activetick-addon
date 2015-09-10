var addon = require('../activetick');
var messageIds = addon.messageIds;
var api = new addon.NodeActivetick();

var activetickCb = function (data) {
  console.log(JSON.stringify(data,null,2));
};

// See messageId.js for message types to be tracked
Object.keys(messageIds).forEach(function (messageId) {
  api.handlers[messageId] = activetickCb;
});

// Don't put credentials in your scripts. Make sure you export
//   them as environment variables
var connected = api.connect( process.env.ATAPIKEY,
                             "activetick1.activetick.com",
                             5000,
                             process.env.ATUID,
                             process.env.ATPWD );

if (connected) {
  api.beginProcessing();
}
