**Node package for millisecond-precision streaming financial data & historical data using activetick.com**

-- **C++ node extension that links against CppSDK. Uses Google Protobuf to structure data interchange between languages. As such it has a very small node footprint and is extremely flexible. Protocol Buffer could be used to interchange to any language or protocol. Also fast.**

-- **Uses libuv async_send() to interrupt Node.js runtime only as needed and immediately on message frames**

-- **Requires activetick.com subscription**

-- **Requires Node 0.12.7 - OS X or Ubuntu Linux**  

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
  

