## Node.js Bindings for C++ activetick.com SDK

- Uses protocol buffers internally between C++ and javascript
- Node.js portion is written in IcedCoffeeScript
- Requires Node 0.12.7 - OS X or Ubuntu Linux (almost Node-NaN ready)


### Usage OSX
- brew install protobuf pkg-config

### Usage Ubuntu
- sudo apt-get install libprotobuf-dev protobuf-compiler pkg-config

### To-Do
  - Support every API method (a few are missing)
  - Memory Management
    - CPP: delete *pointer;
  - Finish NaN abstractions

