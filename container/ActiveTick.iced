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

class ActiveTick
  constructor:() ->
    @api = new NodeActivetick()
    if @connect()
      @beginProcessing()
    
  beginProcessing:() =>
    async.forever (next) =>
      @readNextMessage(next)
    
  readNextMessage:(done) ->
    msg = @api.getMsg()
    console.log msg if _.size(msg) isnt 0
    setTimeout done(), 500 # grab data twice a second
    
  connect: () ->
    return @api.sessionInit config.api_key, config.ip, config.port, config.username, config.password

main = () ->
  a = new ActiveTick()
  a.connect()

main() if not module.parent
