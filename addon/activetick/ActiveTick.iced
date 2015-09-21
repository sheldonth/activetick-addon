{NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
async = require 'async'
_ = require 'underscore'
config = require './config'

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
    @api = new NodeActiveTick(@handleData)
    # @api.fireCallback()
    result = @api.connect config.url, config.port, config.api_key, config.username, config.password
    
  handleData:(data) =>
    if typeof data is 'object'
      console.log data.toString 'utf8'
    else if typeof data is 'string'
      console.log data

main = () ->
  a = new ActiveTick()
  # a.api.fireCallback()
  # a.fireCallback()

main() if not module.parent
