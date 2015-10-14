### USAGE (OS-X Node 0.12.7 ONLY):
- Place 'atfeed-cppsdk' folder from ActiveTick in the repository root
- Place 'libActiveTickServerAPI.dylib' from 'atfeed-cppsdk' inside /container
- run '/container/node-active-addon/preinstall.sh'
- Copy config.js.example to config.js with your values and place in /container
- 'node-gyp rebuild' from inside /container
- 'iced container/ActiveTick.iced' to test connection and download sample quote

### USAGE UBUNTU LINUX
- sudo apt-get install libprotobuf-dev protobuf-compiler

#### To-Do
  - npm install script, {wget, unzip, move} {libraries, headers}
    - For Linux and OS X
  - Support every API method
  - Pass a callback for streaming updates, and the response to begin streaming updates
    - keep the streaming update callback alive for the duration
    - keep a separate libuv interrupter around
  - Memory Management
    - CPP: delete *pointer;
  - Usage documentation
  - 1), you can create a debug build of your addon by adding the --debug switch when running node-gyp (note that it will be built into build/Debug instead of build/Release).
  - Make node-version independent (using nan)
  - Make username, password, etc allocation parameters rather than config.js 
