{NodeActivetick} = require './node-activetick-addon/build/Release/NodeActivetickAddon'
async = require 'async'
config = require './config'
_ = require 'underscore'

# .getSessionHandle()
# .closeAllATRequests()
# .closeATRequest()
# .sendATBarHistoryDbRequest( request )
# .sendATLoginRequest( request )
# .sendATMarketHolidaysRequest( request )
# .sendATMarketMoversDbRequest( request )
# .sendATMarketMoversStreamRequest( request )
# .sendATQuoteDbRequest( request )
# .sendATQuoteStreamRequest( request )
# .sendATTickHistoryDbRequest( request )
# .sendATSectorListRequest( request )
# .sendATConstituentListRequest( request )
# .connect( apiKey, serverAddr, port, userid, passwd )

noisy = yes

class ActiveTick
  constructor:() ->
    @api = new NodeActivetick()
    if @connect()
      @beginProcessing()
    
  beginProcessing:() =>
    @processing = yes
    async.forever (next) =>
      @readNextMessage(next)
    
  readNextMessage:(done) ->
    msg = @api.getMsg()
    console.log msg if _.size(msg) isnt 0 and noisy
    if not @processing
      done(1)
    else
      @handleMsg msg
      setTimeout done, 1
    
  stopProcessing:() =>
    @processing = no
    
  connect: (@connection_cb) ->
    return @api.sessionInit config.api_key, config.url, config.port, config.username, config.password

main = () ->
  a = new ActiveTick()
  a.connect()

main() if not module.parent
