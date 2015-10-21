**Node package for millisecond-precision streaming financial data & historical data using activetick.com
**Requires activetick.com subscription**
**Requires Node 0.12.7 - OS X or Ubuntu Linux**  

###### OS X
- brew install protobuf

###### UBUNTU LINUX
- sudo apt-get install libprotobuf-dev protobuf-compiler

###### To-Do
  - Support every API method
  - Pass a callback for streaming updates, and the response to begin streaming updates
    - keep the streaming update callback alive for the duration
    - keep a separate libuv interrupter around
  - Memory Management
    - CPP: delete *pointer;
  - Usage documentation
  - Make node-version independent (using nan)
  

