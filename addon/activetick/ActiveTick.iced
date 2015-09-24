{NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
async = require 'async'
_ = require 'underscore'
config = require './config'
ProtoBuf = require "protobufjs"
path = require 'path'
    
noisy = yes

class ActiveTick
  constructor:() ->
    ProtoBuf.loadProtoFile path.join(__dirname, "protobuf", "messages.proto"), (err, builder) =>
      return console.error err if err
      @api = new NodeActiveTick(@handleProtoMsg)
      @messages_builder = builder;
      @ATLoginResponse = @messages_builder.build "NodeActiveTickProto.ATLoginResponse"
      console.log @ATLoginResponse
      @api.connect config.url, config.port, config.api_key, config.username, config.password
    
  handleProtoMsg:(msgType, msgData) =>
    if msgType is 'ATLoginResponse'
      msg = @ATLoginResponse.decode msgData
    console.log msg

main = () ->
  a = new ActiveTick()

main() if not module.parent
