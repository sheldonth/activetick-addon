#### Node.js Bindings for activetick.com C++ SDK
- Uses protocol buffers internally to serialize between C++ and Javascript
- Node.js portion is written in IcedCoffeeScript in `/iced` compiled js in `/js` 
- Uses Nan for node.js version abstraction. Should work on all versions of Node.js

##### Usage Mac OSX
- Install dependencies:
  - `npm install -g node-gyp`
  - `brew install protobuf pkg-config`

##### Usage Ubuntu
- sudo apt-get install libprotobuf-dev protobuf-compiler pkg-config

##### Example
- Create `/example/config.js` with your username, password, and apikey
- Run either `iced example.iced` or `node example.js` to see a stream of trades and quote ticks in real time.

### To-Do
  - Support every API method (a few are missing)
  - Memory Management *Not Production Ready*
