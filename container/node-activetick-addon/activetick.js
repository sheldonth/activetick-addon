var addon = require('./build/Release/NodeActivetickAddon');
var async = require('async');
var messageIds = require('./messageIds');
var RateLimiter = require("limiter").RateLimiter;

/**
  * Constructor.
  * @constructor
  */
function NodeActivetick() {
  this.client = new addon.NodeActivetick();
  this.limiter = new RateLimiter(1000,'second');
  this.handlers = {};
  this.isProcessing = false;
}

NodeActivetick.prototype = {
  _consumeMessages: function () {
    async.forever( this._processMessage.bind( this ),
      function( err ) {
        console.error( err );
        throw err;
      }
    );
  },
  _processMessage: function (next) {
    var message = this.client.getMsg();
    if (message.messageId in this.handlers) {
      var handler = this.handlers[message.messageId];
      handler(message);
    }
    setTimeout(next,0);
  },
  beginProcessing: function () {
    if (!this.isProcessing) {
      this._consumeMessages();
      this.isProcessing = true;
    }
  },

  /**
    * Returns connected session handle
    * @memberof NodeActivetick
    */
  getSessionHandle: function () {
    this.doAction( function () {
      return this.client.getSessionHandle();
    });
  },

  /**
    * Closes all outstanding requests
    * @memberof NodeActivetick
    */
  closeAllATRequests: function () {
    this.doAction( function () {
      this.client.closeAllATRequests();
    });
  },

  /**
    * Closes specific request, given an request handle
    * @memberof NodeActivetick
    * @param {int} reqId - Request handle
    */
  closeATRequest: function (reqId) {
    this.doAction( function () {
      this.client.closeATRequest(reqId);
    });
  },

  /**
    * Call this function to request bar history data
    * See import/inclde/ActiveTickServerAPI/ActiveTickServerRequestor.h
    * You must pass an object of one of three types. 'timeout' parameter within
    * the object req is optional.
    * @memberof NodeActivetick
    * @function sendATBarHistoryDbRequest
    * @param {Object[]} req -
    * @param {string} req[].symbol - Symbol name
    * @param {string} req[].barHistoryType - History type can be either
    *   "BarHistoryIntraday", "BarHistoryDaily", or "BarHistoryWeekly"
    * @param {int} req[].intradayMinuteCompression - Size of the bars in
    *   minutes
    * @param {string} req[].beginDateTime - Date formatted in "YYYYMMDDHHMMSS"
    * @param {string} req[].endDateTime - Date formatted in "YYYYMMDDHHMMSS"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  /**
    * @memberof NodeActivetick
    * @function sendATBarHistoryDbRequest
    * @param {Object[]} req -
    * @param {string} req[].symbol - Symbol name
    * @param {string} req[].barHistoryType - History type can be either
    *   "BarHistoryIntraday", "BarHistoryDaily", or "BarHistoryWeekly"
    * @param {int} req[].intradayMinuteCompression - Size of the bars in
    *   minutes
    * @param {int} req[].recordsWanted - Number of records wanted from the
    *   query
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  /**
    * @memberof NodeActivetick
    * @function sendATBarHistoryDbRequest
    * @param {Object[]} req -
    * @param {string} req[].symbol - Symbol name
    * @param {string} req[].barHistoryType - History type can be either
    *   "BarHistoryIntraday", "BarHistoryDaily", or "BarHistoryWeekly"
    * @param {int} req[].intradayMinuteCompression - Size of the bars in
    *   minutes
    * @param {string} req[].beginDateTime - Date formatted in "YYYYMMDDHHMMSS"
    * @param {int} req[].recordsWanted - Number of records wanted from the
    *   query
    * @param {string} req[].cursorType - Cursor type can be "CursorForward" or
    *   "CursorBackward"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATBarHistoryDbRequest: function ( req ) {
    this.doAction( function () {
      if ( 'beginDateTime' in req && 'endDateTime' in req ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATBarHistoryRequest( req.symbol,
                                               req.barHistoryType,
                                               req.intradayMinuteCompression,
                                               req.beginDateTime,
                                               req.endDateTime );
        } else {
          return this.client.sendATBarHistoryRequest( req.symbol,
                                               req.barHistoryType,
                                               req.intradayMinuteCompression,
                                               req.beginDateTime,
                                               req.endDateTime,
                                               req.timeout );
        }
      } else if ( 'recordsWanted' in req && !('beginDateTime' in req) ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATBarHistoryRequest( req.symbol,
                                               req.barHistoryType,
                                               req.intradayMinuteCompression,
                                               req.recordsWanted );
        } else {
          return this.client.sendATBarHistoryRequest( req.symbol,
                                               req.barHistoryType,
                                               req.intradayMinuteCompression,
                                               req.recordsWanted,
                                               req.timeout );
        }
      } else if ( 'beginDateTime' in req && 'recordsWanted' in req ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATBarHistoryRequest( req.symbol,
                                               req.barHistoryType,
                                               req.intradayMinuteCompression,
                                               req.beginDateTime,
                                               req.recordsWanted,
                                               req.cursorType );
        } else {
          return this.client.sendATBarHistoryRequest( req.symbol,
                                               req.barHistoryType,
                                               req.intradayMinuteCompression,
                                               req.beginDateTime,
                                               req.recordsWanted,
                                               req.cursorType,
                                               req.timeout );
        }
      }
    });
  },

  /**
    * Sends login request with Activetick credentials
    * @memberof NodeActivetick
    * @param {Object[]} req -
    * @param {string} req[].userid - Activetick user ID
    * @param {string} req[].passwd - Activetick password
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATLoginRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATLoginRequest( req.userid, req.passwd );
      } else {
        return this.client.sendATLoginRequest( req.userid, req.passwd,
                                               req.timeout );
      }
    });
  },

  /**
    * Requests dates for market holidays
    * @memberof NodeActivetick
    * @param {Object[]} req -
    * @param {int} req[].yearsGoingBack - Number of years going back
    * @param {int} req[].yearsGoingForward - Number of years going forward
    * @param {string} req[].countryType - Can be either "CountryInternational",
    *   "CountryUnitedStates", or "CountryCanada"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATMarketHolidaysRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATMarketHolidaysRequest( req.yearsGoingBack,
                                                        req.yearsGoingForward,
                                                        req.countryType );
      } else {
        return this.client.sendATMarketHolidaysRequest( req.yearsGoingBack,
                                                        req.yearsGoingForward,
                                                        req.countryType,
                                                        req.timeout );
      }
    });
  },

  /**
    * Send market movers snapshot request
    * @memberof NodeActivetick
    * @param {Object[]} req -
    * @param {string} req[].symbols - String of symbols, comma separated
    *   symbol1,symbol2,...
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATMarketMoversDbRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATMarketMoversDbRequest( req.symbols );
      } else {
        return this.client.sendATMarketMoversDbRequest( req.symbols,
                                                        req.timeout );
      }
    });
  },

  /**
    * Send market movers stream request.
    * @memberof NodeActivetick
    * @param {Object[]} req -
    * @param {string} req[].symbol - Symbol
    * @param {string} req[].requestType - can be either
    *   "StreamRequestSubscribe", "StreamRequestUnsubscribe",
    *   "StreamRequestSubscribeQuotesOnly",
    *   "StreamRequestUnsubscribeQuotesOnly",
    *   "StreamRequestSubscribeTradesOnly",
    *   "StreamRequestUnsubscribeTradesOnly"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATMarketMoversStreamRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATMarketMoversStreamRequest( req.symbols );
      } else {
        return this.client.sendATMarketMoversStreamRequest( req.symbols,
                                                            req.timeout );
      }
    });
  },

  /**
    * Send quote snapshot request.
    * @memberof NodeActivetick
    * @param {Object[]} req -
    * @param {string} req[].symbols - String of symbols, comma separated
    *   symbol1,symbol2,...
    * @param {string} req[].fields - String of fields, comma separated
    *   see import/include/Shared/ATServerAPIDefines.h for ATQuoteFieldType
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATQuoteDbRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATQuoteDbRequest( req.symbols, req.fields );
      } else {
        return this.client.sendATQuoteDbRequest( req.symbols, req.fields,
                                                 req.timeout );
      }
    });
  },

  /**
    * Send quote stream request.
    * @memberof NodeActivetick
    * @param {Object[]} req -
    * @param {string} req[].symbols - String of symbols, comma separated
    *   symbol1,symbol2,...
    * @param {string} req[].requestType - can be either
    *   "StreamRequestSubscribe", "StreamRequestUnsubscribe",
    *   "StreamRequestSubscribeQuotesOnly",
    *   "StreamRequestUnsubscribeQuotesOnly",
    *   "StreamRequestSubscribeTradesOnly",
    *   "StreamRequestUnsubscribeTradesOnly"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATQuoteStreamRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATQuoteStreamRequest( req.symbols,
                                                     req.requestType );
      } else {
        return this.client.sendATQuoteStreamRequest( req.symbols,
                                                     req.requestType,
                                                     req.timeout );
      }
    });
  },

  /**
    * Send tick history data request. Takes in begining and end dates. Will
    *  output only a week's worth, truncated at the start of the weekend.
    * @memberof NodeActivetick
    * @function sendATTickHistoryDbRequest
    * @param {Object[]} req - 
    * @param {string} req[].symbol - String of symbol
    * @param {bool} req[].selectTrades -
    * @param {bool} req[].selectQuotes -
    * @param {string} req[].beginDateTime - Date formatted in "YYYYMMDDHHMMSS"
    * @param {string} req[].endDateTime - Date formatted in "YYYYMMDDHHMMSS"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  /**
    * Send tick history data request. Takes in number of records wanted.
    * @memberof NodeActivetick
    * @function sendATTickHistoryDbRequest
    * @param {Object[]} req - 
    * @param {string} req[].symbol - String of symbol
    * @param {bool} req[].selectTrades -
    * @param {bool} req[].selectQuotes -
    * @param {int} req[].recordsWanted - Number of records wanted
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  /**
    * Send tick history data request. Takes in begining date, number of
    *  records and direction of records.
    * @memberof NodeActivetick
    * @function sendATTickHistoryDbRequest
    * @param {Object[]} req - 
    * @param {string} req[].symbol - String of symbol
    * @param {bool} req[].selectTrades -
    * @param {bool} req[].selectQuotes -
    * @param {string} req[].beginDateTime - Date formatted in "YYYYMMDDHHMMSS"
    * @param {int} req[].recordsWanted - Number of records wanted
    * @param {string} req[].cursorType - Cursor type can be "CursorForward" or
    *   "CursorBackward"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  /**
    * Send tick history data request. Takes in number of pages wanted.
    * @memberof NodeActivetick
    * @function sendATTickHistoryDbRequest
    * @param {Object[]} req - 
    * @param {string} req[].symbol - String of symbol
    * @param {bool} req[].selectTrades -
    * @param {bool} req[].selectQuotes -
    * @param {int} req[].pagesWanted - Number of pages wanted
    * @param {int} req[].offset- Page offset
    * @param {string} req[].dbdate - Date formatted in "YYYYMMDDHHMMSS"
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATTickHistoryDbRequest: function ( req ) {
    this.doAction( function () {
      if ( 'beginDateTime' in req && 'endDateTime' in req ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.beginDateTime,
                                                         req.endDateTime );
        } else {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.beginDateTime,
                                                         req.endDateTime,
                                                         req.timeout );
        }
      } else if ( 'recordsWanted' in req && !( 'beginDateTime' in req ) ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.recordsWanted );
        } else {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.recordsWanted,
                                                         req.timeout );
        }
      } else if ( 'recordsWanted' in req && 'beginDateTime' in req ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.beginDateTime,
                                                         req.recordsWanted,
                                                         req.cursorType );
        } else {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.beginDateTime,
                                                         req.recordsWanted,
                                                         req.cursorType,
                                                         req.timeout );
        }
      } else if ( 'pagesWanted' in req ) {
        if ( !('timeout' in req) ) {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.pagesWanted,
                                                         req.offset,
                                                         req.dbdate );
        } else {
          return this.client.sendATTickHistoryDbRequest( req.symbol,
                                                         req.selectTrades,
                                                         req.selectQuotes,
                                                         req.pagesWanted,
                                                         req.offset,
                                                         req.dbdate,
                                                         req.timeout );
        }
      }
    });
  },

  /**
    * Send sector list request. The response will contain sector/industry pairs
    *   for all defined sectors.
    * @memberof NodeActivetick
    * @param {Object[]} req - 
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATSectorListRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATSectorListRequest();
      } else {
        return this.client.sendATSectorListRequest( req.timeout );
      }
    });
  },

  /**
    * Send constituent list request. The response will contain a list of
    *   symbols for key.
    * @memberof NodeActivetick
    * @param {Object[]} req - 
    * @param {string} req[].constituentListType - Either 
    *   "ATConstituentListIndex", "ATConstituentListSector", or
    *   "ATConstituentListOptionChain".
    * @param {string} req[].key - Specifies the key for which to retrieve the
    *   list. If constituentListType is sector, the key should contain
    *   SectorName IndustryName with 0x10 character between the names, 
    *   * for example: "Services" 0x10 "Restaurants". If listType is index,
    *   then key should contain an index symbol, for example $DJI. For
    *   options, the key should be the underlying symbol.
    * @param {int} [req[].timeout] - Timeout in milliseconds
    */
  sendATConstituentListRequest: function ( req ) {
    this.doAction( function () {
      if ( !('timeout' in req) ) {
        return this.client.sendATConstituentListRequest(
                           req.constituentListType, req.key );
      } else {
        return this.client.sendATConstituentListRequest(
                           req.constituentListType, req.key, req.timeout );
      }
    });
  },

  /**
    * Connects to Activetick server.
    * @memberof NodeActivetick
    * @param {string} apiKey - API key supplied with Activetick subscription
    * @param {string} serverAddr - Server address, e.g. 
    *   activetick1.activetick.com
    * @param {int} port - Port number, e.g. 5000
    * @param {string} userid - Username
    * @param {string} passwd - Password
    */
  connect: function (apiKey, serverAddr, port, userid, passwd) {
    return this.client.sessionInit( apiKey, serverAddr, port, userid, passwd );
  },

  doAction: function (action) {
    this.limiter.removeTokens(1, function (err, remainingRequests) {
      action.bind(this)();
    }.bind(this));
  }
}

exports = module.exports = {
  "NodeActivetick": NodeActivetick,
  "messageIds": messageIds
};
