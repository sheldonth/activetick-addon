{NodeActivetick} = require './node-activetick-addon/build/Release/NodeActivetickAddon'
async = require 'async'
config = require './config'

class ActiveTick
  constructor: () ->
    @api = new NodeActivetick()
    if @connect()
      @beginProcessing()
    
  beginProcessing:() =>
    async.forever (next) =>
      @readNextMessage(next)
    
  readNextMessage:(done) ->
    msg = @api.getMsg()
    console.log msg if msg
    done()
    
  connect: () ->
    return @api.sessionInit config.api_key, config.ip, config.port, config.username, config.password

main = () ->
  a = new ActiveTick()
  a.connect()

main() if not module.parent
