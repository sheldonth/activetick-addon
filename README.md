## Node.js Bindings for activetick.com C++ SDK
- Uses protocol buffers internally between C++ and Javascript
- Node.js portion is written in IcedCoffeeScript in `/iced` compiled js in `/js` 
- Requires Node 0.12.7 - OS X or Ubuntu Linux (almost version independent w/ Node-NaN)

### Usage OS X
- Install dependencies:
  - `npm install -g node-gyp`
  - `brew install protobuf pkg-config`

### Usage Ubuntu
- sudo apt-get install libprotobuf-dev protobuf-compiler pkg-config

### To-Do
  - Support every API method (a few are missing)
  - Memory Management
    - CPP: delete *pointer;
  - Finish NaN abstractions

