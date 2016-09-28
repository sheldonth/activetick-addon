# Copyright 2015-present Sheldon Thomas
fs = require 'fs'
release_path = __dirname + '/../build/Release/NodeActiveTickAddon.node'
debug_path = __dirname + '/../build/Debug/NodeActiveTickAddon.node'
debug_exists = fs.existsSync debug_path
if debug_exists # prefer debug
  {NodeActiveTick} = require(debug_path)
else
  {NodeActiveTick} = require(release_path)

async = require 'async'
_ = require 'underscore'
ProtoBuf = require 'protobufjs'
path = require 'path'
EventEmitter = require 'events'

noisy = yes

standard_timeout = 3000

class ActiveTick extends EventEmitter
  constructor: (readyCb) ->
    ProtoBuf.loadProtoFile path.join(__dirname, "../protobuf", "messages.proto"), (err, builder) =>
      return console.error err if err
      @api = new NodeActiveTick(@handleProtoMsg)
      @callbacks = {}
      @stream_callbacks = {}
      @messages_builder = builder
      @ATLoginResponse = @messages_builder.build 'NodeActiveTickProto.ATLoginResponse'
      @ATConstituentResponse = @messages_builder.build 'NodeActiveTickProto.ATConstituentResponse'
      @ATQuote = @messages_builder.build 'NodeActiveTickProto.ATQuote'
      @ATQuoteStreamResponse = @messages_builder.build 'NodeActiveTickProto.ATQuoteStreamResponse'
      @ATQuoteStreamTradeUpdate = @messages_builder.build 'NodeActiveTickProto.ATQuoteStreamTradeUpdate'
      @ATQuoteStreamQuoteUpdate = @messages_builder.build 'NodeActiveTickProto.ATQuoteStreamQuoteUpdate'
      @ATQuoteStreamRefreshUpdate = @messages_builder.build 'NodeActiveTickProto.ATQuoteStreamRefreshUpdate'
      @ATQuoteStreamMarketMoversUpdate = @messages_builder.build 'NodeActiveTickProto.ATMarketMoversStreamUpdate'
      @ATBarHistoryDbResponse = @messages_builder.build 'NodeActiveTickProto.ATBarHistoryDbResponse'
      @ATQuoteDbResponse = @messages_builder.build 'NodeActiveTickProto.ATQuoteDbResponse'
      @ATSymbol = @messages_builder.build 'NodeActiveTickProto.ATSymbol'
      
      @timer = setInterval () =>
        noop = {}
      , 2000
      
      # enums
      @ATQuoteFieldTypes = @messages_builder.build 'NodeActiveTickProto.ATQuoteFieldType'
      @ATFieldStatus = @messages_builder.build 'NodeActiveTickProto.ATQuoteDbResponseSymbolFieldData.ATFieldStatus'
      @ATDataType = @messages_builder.build 'NodeActiveTickProto.ATQuoteDbResponseSymbolFieldData.ATDataType'
      @ATQuoteDbResponseType = _.invert @messages_builder.build 'NodeActiveTickProto.ATQuoteDbResponse.ATQuoteDbResponseType'
      @ATSymbolStatus = @messages_builder.build 'NodeActiveTickProto.ATSymbolStatus'
      @ATQuoteFieldType = @messages_builder.build 'NodeActiveTickProto.ATQuoteFieldType'
      @ATStreamRequestTypes = @messages_builder.build 'NodeActiveTickProto.ATStreamRequestTypes'
      
      @stream_symbols = {}
      readyCb()

  barHistoryDBRequest: (symbol, barhistorytype, intradayminutecompression, startime, endtime, requestCb) =>
    request_id = @api.barHistoryDbRequest symbol, barhistorytype, intradayminutecompression, startime, endtime
    @callbacks[request_id] = requestCb if requestCb?

  quoteDBRequest: (symbol, fields, requestCb) =>
    request_id = @api.quoteDbRequest symbol, fields
    @callbacks[request_id] = requestCb if requestCb?

  # subscribe/unsubscribe prevent duplicating server requests if many clients subscribe to similar symbols
  subscribe: (symbol, cb) =>
    return if not symbol?
    streamKey = symbol.symbol if typeof symbol is 'object'
    streamKey = symbol if typeof symbol is 'string'
    @stream_symbols[streamKey] = 0 if not @stream_symbols[streamKey]?
    if @stream_symbols[streamKey] is 0
      @quoteStreamRequest symbol, 'StreamRequestSubscribe', (msg) =>
        # TODO check payload body for failure
        @stream_symbols[streamKey] += 1
        cb yes
    else if @stream_symbols[streamKey] > 0 # we're already getting this quote stream
      @stream_symbols[streamKey] += 1
      cb yes
    
  unsubscribe: (symbol, cb) =>
    return if not symbol?
    streamKey = symbol.symbol if typeof symbol is 'object'
    streamKey = symbol if typeof symbol is 'string'
    if @stream_symbols[streamKey] is 0 or not @stream_symbols[streamKey]?
      return console.error "Unsubscribe sent for symbol we aren't subscribed to #{streamKey}"
    else
      @stream_symbols[streamKey] = @stream_symbols[streamKey] - 1
      if @stream_symbols[streamKey] <= 0
        @quoteStreamRequest symbol, 'StreamRequestUnsubscribe', (msg) =>
          cb yes
      else
        cb yes
        
  quoteStreamRequest: (symbol, reqAction, requestCb) =>
    if typeof symbol is 'object'
      q = new @ATSymbol
      q.symbol = symbol.symbol.toString('utf8')
      q.symbolType = symbol.symbolType
      q.exchangeType = symbol.exchangeType
      q.countryType = symbol.countryType
      r = q.encode()
      request_id = @api.quoteStreamRequestForSymbolData r.buffer, r.buffer.length, reqAction
      @callbacks[request_id] = requestCb if requestCb?
    else if typeof symbol is 'string'
      symbolParam = symbol
      symbolCount = 1
      request_id = @api.quoteStreamRequest symbolParam, symbolCount, reqAction
      @callbacks[request_id] = requestCb if requestCb?
    else
      console.error 'Bad request parameter type quoteStreamRequest'
  
  # "ATConstituentListIndex"
  # "ATConstituentListSector"
  # "ATConstituentListOptionChain"
  listRequest: (listType, key, cb) ->
    request_id = @api.listRequest listType, key
    @callbacks[request_id] = cb
  
  connect: (apiKey, username, password, cb) =>
    request_id = @api.connect apiKey, username, password
    @callbacks[request_id] = cb
    
  handleProtoMsg: (msgType, msgID, msgData) =>
    if msgType is 'ATLoginResponse'
      msg = @ATLoginResponse.decode msgData
      return console.error msg if msg.loginResponseString isnt 'Success'
    else if msgType is 'ATConstituentResponse'
      msg = @ATConstituentResponse.decode msgData
    else if msgType is 'ATQuoteStreamResponse'
      msg = @ATQuoteStreamResponse.decode msgData
    else if msgType is 'ATBarHistoryDbResponse'
      msg = @ATBarHistoryDbResponse.decode msgData
    else if msgType is 'ATQuoteStreamTradeUpdate'
      msg = @ATQuoteStreamTradeUpdate.decode msgData
      @emit 'trade', msg
      # @emit 'trade' + msg.tradeSymbol.symbol, msg
    else if msgType is 'ATQuoteStreamQuoteUpdate'
      msg = @ATQuoteStreamQuoteUpdate.decode msgData
      @emit 'quote', msg
      # @emit 'quote' + msg.quoteSymbol.symbol, msg
    else if msgType is 'ATQuoteStreamRefreshUpdate'
      msg = @ATQuoteStreamRefreshUpdate.decode msg
      @emit 'refresh', msg
      # @emit 'refresh' + msg.symbol.symbol, msg
    else if msgType is 'ATQuoteStreamMarketMoversUpdate'
      msg = @ATQuoteStreamMarketMoversUpdate.decode msg
      @emit 'marketmovers', msg
    else if msgType is 'ATQuoteDbResponse'
      msg = @ATQuoteDbResponse.decode msgData
    if (c = @callbacks[msgID])?
      c(msg)

module.exports = {ActiveTick}


