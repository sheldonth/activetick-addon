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
    @api = new NodeActivetick(@dataCb)
    if @connect()
      @beginProcessing()
    
  dataCb:() =>
    console.log 'YAYAYO'
    
  beginProcessing:() =>
    @processing = yes
    async.forever (next) =>
      @readNextMessage(next)
    
  readNextMessage:(done) =>
    msg = @api.getMsg()
    console.log msg if _.size(msg) isnt 0 and noisy
    if not @processing
      done(1)
    else
      @handleMsg msg if _.size(msg) isnt 0
      setTimeout done, 1
    
  handleMsg:(msg) =>
    switch msg.messageId
      when 'ATSessionStatus' then @handleStatus msg
      when 'ATLoginResponse' then @handleLoginResponse msg
    
  handleStatus: (obj) =>
    
  handleLoginResponse: (obj) =>
    if obj.ATLoginResponse.loginResponseString is 'LoginResponseSuccess'
      if @connection_cb
        @connection_cb()
        @connection_cb = null # only do the callback the first time.
        # c++ api layer remembers subscriptions between reconnects
    
  stopProcessing:() =>
    @processing = no
    
  connect: (@connection_cb) ->
    return @api.sessionInit config.api_key, config.url, config.port, config.username, config.password

main = () ->
  a = new ActiveTick()
  await a.connect defer()
  

main() if not module.parent
