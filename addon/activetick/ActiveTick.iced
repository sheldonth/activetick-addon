{NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
async = require 'async'
_ = require 'underscore'
config = require './config'

noisy = yes

class ActiveTick
  constructor:() ->
    @api = new NodeActiveTick(@handleProtoMsg)
    # @api.fireCallback()
    @api.connect config.url, config.port, config.api_key, config.username, config.password
    setTimeout () ->
          console.log 'End'
        , 5000
    
  handleProtoMsg:(msgType, msgData) =>
    console.log "handleProtoMsg"
    console.log msgType
    if typeof msgData is 'object'
      console.log 'data'
      console.log msgData
    else if typeof msgData is 'string'
      console.log 'string'
      console.log msgData

main = () ->
  a = new ActiveTick()

main() if not module.parent
