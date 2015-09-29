{NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
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
      readyCb()

  beginQuoteStream: (symbols, ATStreamRequestTypeIndex, @quoteCb, requestCb) =>
    _quoteDecode = (quote_buffer) =>
      quote = @ATQuote.decode quote_buffer
      @quoteCb quote
    if typeof symbols is 'object'
      symbolParam = symbols.join ','
      symbolCount = symbols.length
    else if typeof symbols is 'string'
      symbolParam = symbols
      symbolCount = 1
    request_id = @api.beginQuoteStream symbols, ATStreamRequestTypes[ATStreamRequestTypeIndex], symbolCount, _quoteDecode
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
  # a.listRequest listType, key
  await a.listRequest ATConstituentRequestTypes[2], 'YANG',  defer(yang)
  await a.listRequest ATConstituentRequestTypes[2], 'FB', defer(fb)
  console.log yang.symbols.length
  console.log fb.symbols.length
  getQuote = (quote) ->
    console.log 'got quote'
    console.log quote
  # await a.beginQuoteStream ['AAPL', 'CSIQ', 'fb', 'baba'], 4, 3000, defer(result)
  
main() if not module.parent
