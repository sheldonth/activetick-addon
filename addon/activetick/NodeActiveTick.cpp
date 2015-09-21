#include <cstring>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <node.h>
#include <node_buffer.h>
#include <nan.h>
#include "NodeActiveTick.h"
// #include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Persistent<Function> NodeActiveTick::constructor;

// Persistent<Function> NodeActiveTick::p_callback;
// Handle<Function> cb = Handle<Function>::Cast(args[0]);
// p_callback.Reset(isolate, cb);
// obj->p_dataCallback = Persistent<Function>::Persistent(isolate, args[0].As<Function>());
// obj->p_dataCallback = Persistent<Function>::New(isolate, cb);
// obj->p_dataCallback = Persistent<Function>::Persistent(isolate, cb);
// obj->p_dataCallback = Persistent<Function>::Persistent(cb);
// obj->p_dataCallback = Persistent<Function>::New(cb);
// obj->p_dataCallback = Persistent<Function>::New(Isolate::GetCurrent(), obj)
// obj->p_dataCallback = Persistent<Function, CopyablePersistentTraits<Function> >::New(isolate, args[0]);
// obj->p_dataCallback = Persistent<Function, CopyablePersistentTraits<Function> >::New(isolate, Handle<Function>::Cast(args[0]));
// obj->dataCallback = Persistent<Function>::New(Handle<Function>::Cast(args[0]));
// obj->dataCallback = Persistent<Function>::New(cb);
// obj->dataCallback = Persistent<Function>::Cast(args[0]);


NodeActiveTick::NodeActiveTick() {
  
}
  
NodeActiveTick::~NodeActiveTick() {
  
}

void NodeActiveTick::Init( Handle<Object> exports ) {
    Isolate* isolate = Isolate::GetCurrent();

    ATInitAPI();
    Local<FunctionTemplate> tpl = FunctionTemplate::New( isolate, New );
    tpl->SetClassName( String::NewFromUtf8( isolate, "NodeActiveTick" ) );
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD( tpl, "fireCallback" , FireCallback );
    
    constructor.Reset( isolate, tpl->GetFunction() );
    exports->Set( String::NewFromUtf8( isolate, "NodeActiveTick" ),
                  tpl->GetFunction() );
}
  
void NodeActiveTick::New( const FunctionCallbackInfo<Value> &args ) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope( isolate );

    if (args.IsConstructCall()) {
        NodeActiveTick* obj = new NodeActiveTick();
        // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        if (!args[0]->IsFunction()) {
          isolate->ThrowException(Exception::TypeError(
                  String::NewFromUtf8(isolate, "NodeActiveTick requires a callback parameter in first position")));
        }
        Local<Function> cb = Local<Function>::Cast(args[0]);
        obj->p_dataCallback.Reset(isolate, cb);
        obj->Wrap( args.This() );
        args.GetReturnValue().Set( args.This() );
  }
}
  
void NodeActiveTick::FireCallback(const FunctionCallbackInfo<Value> &args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope( isolate );
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>( args.Holder() );
  
  // !!!!!!!!!!!!!!!!!!!!!!!!!  CALLING FUNCTION PASSING BUFFER IN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  const char *data = "Hello World FOOBAR!";
  int data_length = strlen(data);
  Local<Object> buffer = node::Buffer::New(data_length);
  std::memcpy(node::Buffer::Data(buffer), data, data_length);
  // get handle to the global object
  Local<Context> globalContext = isolate->GetCurrentContext();
  Local<Object> globalObject = globalContext->Global();
  // Retrieve the buffer constructor function
  Local<Function> bufferConstructor = Local<Function>::Cast(globalObject->Get(String::NewFromUtf8(isolate, "Buffer")));
  // use buffer constructors with 3 arguments: 
  //   (1) handle of buffer 
  //   (2) length of buffer 
  //   (3) offset in buffer (where to start)
  Handle<Value> constructorArgs[3] = { buffer,
                           Integer::New(isolate, data_length),
                           Integer::New(isolate, 0) };
  // call the buffer-constructor
  Local<Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);
  Local<Function> func = Local<Function>::New(isolate, obj->p_dataCallback);
  const unsigned argc = 1;
  Local<Value> argv[1] = { actualBuffer };
  func->Call(Null(isolate), argc, argv);
  
  // !!!!!!!!!!!!!!!!!!!!!!!!!  CALLING FUNCTION PASSING STRING IN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  const unsigned argcc = 1;
  Local<Value> argvv[argcc] = { String::NewFromUtf8(isolate, "hello world") };  
  // Local<Function> func = Local<Function>::New(isolate, obj->p_dataCallback);
  func->Call(Null(isolate), argcc, argvv);
}















