### USAGE (OS-X Node 0.12.7 ONLY):
- Place 'atfeed-cppsdk' folder from ActiveTick in the repository root
- Place 'libActiveTickServerAPI.dylib' from 'atfeed-cppsdk' inside /container
- run '/container/node-active-addon/preinstall.sh'
- Copy config.js.example to config.js with your values and place in /container
- 'node-gyp rebuild' from inside /container
- 'iced container/ActiveTick.iced' to test connection and download sample quote

#### To-Do
- Remove json queue polling as inter-language communication mechanism
  - 0MQ
  - Support every API method
  - Pass a callback for streaming updates, and the response to begin streaming updates
    - keep the streaming update callback alive for the duration
    - keep a separate libuv interrupter around
  - Memory Management
    - CPP: delete *pointer;
  - Usage documentation

#### Notes
- What if it crawled?

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