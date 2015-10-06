# {NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
{NodeActiveTick} = require './build/Debug/NodeActiveTickAddon'
async = require 'async'
_ = require 'underscore'
config = require './config'
ProtoBuf = require 'protobufjs'
path = require 'path'

noisy = yes

ATConstituentRequestTypes = [
  'ATConstituentListIndex',
  'ATConstituentListSector',
  'ATConstituentListOptionChain'
]

ATStreamRequestTypes = [
  'StreamRequestSubscribe',
  'StreamRequestUnsubscribe',
  'StreamRequestSubscribeQuotesOnly',
  'StreamRequestUnsubscribeQuotesOnly',
  'StreamRequestSubscribeTradesOnly',
  'StreamRequestUnsubscribeTradesOnly'
]

standard_timeout = 3000

class ActiveTick
  constructor:(readyCb) ->
    ProtoBuf.loadProtoFile path.join(__dirname, "protobuf", "messages.proto"), (err, builder) =>
      return console.error err if err
      @api = new NodeActiveTick(@handleProtoMsg)
      @callbacks = {}
      @messages_builder = builder;
      @ATLoginResponse = @messages_builder.build "NodeActiveTickProto.ATLoginResponse"
      @ATConstituentResponse = @messages_builder.build "NodeActiveTickProto.ATConstituentResponse"
      @ATQuote = @messages_builder.build "NodeActiveTickProto.ATQuote"
      @ATQuoteStreamResponse = @messages_builder.build "NodeActiveTickProto.ATQuoteStreamResponse"
      readyCb()

  beginQuoteStream: (symbols, ATStreamRequestTypeIndex, @quoteCb, requestCb) =>
    _quoteDecode = (quote_buffer) =>
      console.log 'hurro'
      console.log quote_buffer
      quote = @ATQuote.decode quote_buffer
      @quoteCb quote
    if typeof symbols is 'object'
      symbolParam = symbols.join ','
      symbolCount = symbols.length
    else if typeof symbols is 'string'
      symbolParam = symbols
      symbolCount = 1
    console.log 'symbolParam'
    console.log symbolParam, symbolCount
    request_id = @api.beginQuoteStream symbolParam, symbolCount, ATStreamRequestTypes[ATStreamRequestTypeIndex], _quoteDecode
    @callbacks[request_id] = requestCb if requestCb?
    
  listRequest: (listType, key, cb) ->
    request_id = @api.listRequest listType, key
    @callbacks[request_id] = cb
  
  connect:(url, port, apiKey, username, password, cb) =>
      request_id = @api.connect url, port, apiKey, username, password
      @callbacks[request_id] = cb
    
  handleProtoMsg:(msgType, msgID, msgData) =>
    if msgType is 'ATLoginResponse'
      msg = @ATLoginResponse.decode msgData
      return console.error msg if msg.loginResponseString isnt 'Success'
    else if msgType is 'ATConstituentResponse'
      msg = @ATConstituentResponse.decode msgData
    else if msgType is 'ATQuoteStreamResponse'
      msg = @ATQuoteStreamResponse.decode msgData 
    if (c = @callbacks[msgID])?
      c(msg)

main = () ->
  await a = new ActiveTick(defer())
  await a.connect config.url, config.port, config.api_key, config.username, config.password, defer(result)
  await a.listRequest ATConstituentRequestTypes[2], 'fb',  defer(yang)
  console.log yang.symbols.length + ' options.'
  getQuote = (quote) ->
    console.log 'getQuote'
    console.log quote
  # a.beginQuoteStream ['WFM'], ATStreamRequestTypes[0], getQuote, (result) ->
  #   console.log result
  sym1 = yang.symbols[22].symbol
  sym2 = yang.symbols[4].symbol
  sym3 = yang.symbols[188].symbol
  sym4 = yang.symbols[588].symbol
  console.log sym1, sym2, sym3, sym4
  # a.beginQuoteStream [sym1, sym2, sym3, sym4], ATStreamRequestTypes[0], getQuote, (result) ->
  #   console.log result
  #   for i in result.quoteStreamItems
  #     console.log i.symbol
  a.beginQuoteStream sym1, ATStreamRequestTypes[0], getQuote, (result) ->
    for i in result.quoteStreamItems
      console.log i.symbol

main() if not module.parent
