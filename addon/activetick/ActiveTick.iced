{NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
async = require 'async'
_ = require 'underscore'
config = require './config'
ProtoBuf = require "protobufjs"
path = require 'path'

noisy = yes

ATConstituentRequestTypes = [
  'ATConstituentListIndex',
  'ATConstituentListSector',
  'ATConstituentListOptionChain'
]

class ActiveTick
  constructor:(readyCb) ->
    ProtoBuf.loadProtoFile path.join(__dirname, "protobuf", "messages.proto"), (err, builder) =>
      return console.error err if err
      @api = new NodeActiveTick(@handleProtoMsg)
      @callbacks = {}
      @messages_builder = builder;
      @ATLoginResponse = @messages_builder.build "NodeActiveTickProto.ATLoginResponse"
      @ATConstituentResponse = @messages_builder.build "NodeActiveTickProto.ATConstituentResponse"
      readyCb()
  
  listRequest: (listType, key, cb) ->
    request_id = @api.listRequest listType, key
    @callbacks[request_id] = cb
  
  connect:(url, port, api_key, username, password, cb) =>
      request_id = @api.connect url, port, api_key, username, password
      @callbacks[request_id] = cb
    
  handleProtoMsg:(msgType, msgID, msgData) =>
    if msgType is 'ATLoginResponse'
      msg = @ATLoginResponse.decode msgData
      return console.error msg if msg.loginResponseString isnt 'Success'
    else if msgType is 'ATConstituentResponse'
      msg = @ATConstituentResponse.decode msgData
    if (c = @callbacks[msgID])?
      c(msg)

main = () ->
  await a = new ActiveTick(defer())
  await a.connect config.url, config.port, config.api_key, config.username, config.password, defer(result)
  # a.listRequest listType, key
  await a.listRequest ATConstituentRequestTypes[2], 'YANG',  defer(yang)
  await a.listRequest ATConstituentRequestTypes[2], 'FB', defer(fb)
  console.log yang
  console.log fb
  
main() if not module.parent
