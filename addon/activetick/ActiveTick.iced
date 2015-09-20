{NodeActiveTick} = require './build/Release/NodeActiveTickAddon'
async = require 'async'
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
    @api = new NodeActiveTick(@handleData)
    @api.fireCallback()
    
  handleData:(data) =>
    console.log 'got data'
    console.log data

main = () ->
  a = new ActiveTick()
  # a.api.fireCallback()
  # a.fireCallback()

main() if not module.parent
