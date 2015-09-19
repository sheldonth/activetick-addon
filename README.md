### USAGE (OSX Node 0.12.7 ONLY):
- Place 'atfeed-cppsdk' folder from ActiveTick in the repository root
- Place 'libActiveTickServerAPI.dylib' from 'atfeed-cppsdk' inside /container
- run '/container/node-active-addon/preinstall.sh'
- Copy config.js.example to config.js with your values and place in /container
- 'node-gyp rebuild' from inside /container
- 'iced container/ActiveTick.iced' to test connection and download sample quote

#### Milestone
- Remove json queue polling as inter-language communication mechanism
  - Google protobufs
  - 0MQ
