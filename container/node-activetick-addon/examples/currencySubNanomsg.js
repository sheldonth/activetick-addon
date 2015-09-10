var nano = require('nanomsg');
var colors = require('colors/safe');

var sub = nano.socket('sub');
var addr = 'tcp://127.0.0.1:7789';
// blessed dashboard
//

var blessed = require('blessed');
var contrib = require('blessed-contrib');
var screen = blessed.screen();
var grid = new contrib.grid({rows: 12, cols: 12, screen: screen});

var tradeline = grid.set(0,0,4,4, contrib.line, 
      { style: 
        { line: "yellow"
        , text: "green"
        , baseline: "black"}
      , xLabelPadding: 3
      , xPadding: 10
      , label: 'Last Trade'});

var quoteline = grid.set(4,0,4,4, contrib.line, 
      { style: 
        { line: "yellow"
        , text: "green"
        , baseline: "black"}
      , xLabelPadding: 3
      , xPadding: 10
      , label: 'Spread'});
var eurusddata = {
  title: "EURUSD",
  x: ['01','02','03','04','05','06','07','08','09','10','11','12','13','14',
      '15','16','17','18','19','20'],
  y: [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ]
};
var eurusdspread = {
  title: "Spread",
  style: {line: 'red'},
  x: ['01','02','03','04','05','06','07','08','09','10','11','12','13','14',
      '15','16','17','18','19','20'],
  y: [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ]
};
screen.append(tradeline); //must append before setting data
screen.append(quoteline); //must append before setting data
tradeline.setData([eurusddata]);
quoteline.setData([eurusdspread]);

// table
//
var tabledata = 
         [
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ], 
           [ "0", "EURUSD", "0" ]
         ];
var quotedata = 
         [
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ], 
           [ "00:00:00", "EUR/USD", "0.00000", "0.00000" ]
         ];

var tradetable = grid.set(0, 4, 4, 3, contrib.table,
     { keys: true
     , fg: 'white'
     , selectedFg: 'white'
     , selectedBg: 'blue'
     , interactive: true
     , label: 'Last Trade'
     , width: '30%'
     , height: '30%'
     , border: {type: "line", fg: "cyan"}
     , columnSpacing: 2 //in chars
     , columnWidth: [9, 8, 13] /*in chars*/ });

var quotetable = grid.set(4, 4, 4, 3, contrib.table,
     { keys: true
     , fg: 'white'
     , selectedFg: 'white'
     , selectedBg: 'blue'
     , interactive: true
     , label: 'Quotes'
     , width: '30%'
     , height: '30%'
     , border: {type: "line", fg: "cyan"}
     , columnSpacing: 2 //in chars
     , columnWidth: [9, 8, 13, 13] /*in chars*/ });
   //allow control the table with the keyboard
tradetable.focus();
tradetable.setData({ headers: ['time', 'symbol', 'lastPrice'], data: tabledata });
quotetable.setData({ headers: ['time', 'symbol', 'bid', 'ask'], data: quotedata });
screen.append(tradetable);
screen.append(quotetable);

screen.key(['escape', 'q', 'C-c'], function(ch, key) {
  return process.exit(0);
});

screen.render();

// sub binding
sub.connect(addr);
sub.on('message', function (buf) {
  var msg = JSON.parse(buf.toString());

  if (msg.messageId === "ATStreamQuoteUpdate" )
    ATStreamQuoteUpdate(msg);
  else if (msg.messageId === "ATStreamTradeUpdate")
    ATStreamTradeUpdate(msg);
});

Number.prototype.round = function(places) {
  return +(Math.round(this + "e+" + places)  + "e-" + places);
}

var lastBid = {};
var lastAsk = {};
var lastTrade = {};

var ATStreamQuoteUpdate = function ( msg ) {
  var atTime = msg.data.time;
  var bidText = "";
  var askText = "";
  var bidPrice = msg.data.bidPrice.price.round(msg.data.bidPrice.precision).toPrecision(6);
  var askPrice = msg.data.askPrice.price.round(msg.data.askPrice.precision).toPrecision(6);
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

  if ( msg.data.ATSymbol.symbolStr == "EUR/USD" ) {
  eurusdspread.y.push(askPrice-bidPrice);
  eurusdspread.y.shift();
  quoteline.setData([eurusdspread]);

  var tradetime = atTime.hour + ":" + atTime.minute + ":" + atTime.second + ":" +
              atTime.milliseconds;
  var tablebuf = [ tradetime, msg.data.ATSymbol.symbolStr, bidText, askText];
  quotedata.push(tablebuf);
  quotedata.shift();
  quotetable.setData(
     { headers: ['time', 'symbol', 'bid', 'ask']
       , data: quotedata });
  screen.render();
  }
};


var ATStreamTradeUpdate = function ( msg ) {
  var atTime = msg.data.time;
  var lastText = "";
  var lastPrice = msg.data.lastPrice.price.round(msg.data.lastPrice.precision).toPrecision(6);
  if ( lastTrade[msg.data.ATSymbol.symbolStr] < lastPrice ) {
    lastText = colors.green(lastPrice.toString());
  } else if ( lastTrade[msg.data.ATSymbol.symbolStr] > lastPrice ) {
    lastText = colors.red(lastPrice.toString());
  } else {
    lastText = colors.gray(lastPrice.toString());
  }
  lastTrade[msg.data.ATSymbol.symbolStr] = lastPrice;

  if ( msg.data.ATSymbol.symbolStr == "EUR/USD" ) {
  eurusddata.y.push(lastPrice);
  eurusddata.y.shift();
  tradeline.setData([eurusddata]);

  var tradetime = atTime.hour + ":" + atTime.minute + ":" + atTime.second + ":" +
              atTime.milliseconds;
  var tablebuf = [ tradetime, msg.data.ATSymbol.symbolStr, lastText ];
  tabledata.push(tablebuf);
  tabledata.shift();
  tradetable.setData(
     { headers: ['time', 'symbol', 'lastPrice']
       , data: tabledata });
  screen.render();
  }
};
