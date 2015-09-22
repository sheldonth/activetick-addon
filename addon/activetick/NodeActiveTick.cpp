#include <cstring>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <node.h>
#include <node_buffer.h>
#include <nan.h>
#include "NodeActiveTick.h"
#include "import/atfeed-cppsdk/example/Helper.h"

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

// NodeActiveTick
NodeActiveTick::NodeActiveTick() {
  ATInitAPI();
  session_handle = ATCreateSession();
}
  
NodeActiveTick::~NodeActiveTick() {
  ATDestroySession(session_handle);
}

void NodeActiveTick::Init( Handle<Object> exports ) {
    Isolate* isolate = Isolate::GetCurrent();

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName( String::NewFromUtf8(isolate, "NodeActiveTick"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD(tpl, "fireCallback", FireCallback);
    NODE_SET_PROTOTYPE_METHOD(tpl, "connect", Connect);
    
    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "NodeActiveTick"), tpl->GetFunction());
}
  
void NodeActiveTick::New( const FunctionCallbackInfo<Value> &args ) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    if (args.IsConstructCall()) {
        NodeActiveTick* obj = new NodeActiveTick();
        // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        if (!args[0]->IsFunction()) {
          isolate->ThrowException(Exception::TypeError(
                  String::NewFromUtf8(isolate, "NodeActiveTick requires a callback parameter in first argument position")));
        }
        Local<Function> cb = Local<Function>::Cast(args[0]);
        obj->p_dataCallback.Reset(isolate, cb);
        obj->Wrap( args.This() );
        args.GetReturnValue().Set( args.This() );
  }
  else {
    isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "NodeActiveTick cannot be allocated without javascript new")));
  }
}
  
void NodeActiveTick::FireCallback(const FunctionCallbackInfo<Value> &args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(args.Holder());
  
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
  Handle<Value> constructorArgs[3] = {buffer,
                           Integer::New(isolate, data_length),
                           Integer::New(isolate, 0)};
  // call the buffer-constructor
  Local<Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);
  // Create Local Function with obj->Persistent<Function>
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

void NodeActiveTick::Connect(const FunctionCallbackInfo<Value> &args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(args.Holder());

  Local<String> str_url_address = args[0]->ToString();
  printf("L: %i \n", str_url_address->Utf8Length());
  printf("%s", str_url_address);
  char cstr_url_address[str_url_address->Utf8Length()];
  str_url_address->WriteUtf8(cstr_url_address);
  
  // isolate->ThrowException(Exception::TypeError(
  //         String::NewFromUtf8(isolate, "cstr_url_address")));
  
  uint32_t api_port = args[1]->Uint32Value();
  
  Local<String> str_api_key = args[2]->ToString();
  char cstr_api_key[str_api_key->Utf8Length()];
  str_api_key->WriteUtf8(cstr_api_key);
  
  ATGUID at_guid = Helper::StringToATGuid(cstr_api_key);
  
  Local<String> str_user_id = args[3]->ToString();
  char cstr_api_user_id[str_user_id->Utf8Length()];
  str_user_id->WriteUtf8(cstr_api_user_id);
  
  Local<String> str_api_password = args[4]->ToString();
  char cstr_api_password[str_api_password->Utf8Length()];
  str_api_password->WriteUtf8(cstr_api_password);
  
  bool r = ATSetAPIUserId(obj->session_handle, &at_guid);
  if (!r) {
    isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Unable to call ATSetAPIUserId in SDK. Aborting. Check credentials.")));
    return;
  }
  
  if (args[5]->IsFunction()) {
    Local<Function> c_callback = Local<Function>::Cast(args[5]);
    obj->connectionCallback.Reset(isolate, c_callback);
  }

  // std::cout << obj->session_handle;
  // std::cout << static_cast<const void*>(cstr_url_address) << std::endl;
  printf("A: %s \n", cstr_url_address);
  printf("B: %i \n", api_port);
  printf("C: %s \n", cstr_api_key);
  printf("D: %s \n", cstr_api_user_id);
  printf("E: %s \n", cstr_api_password);
  
  // todo: activetick2.activetick.com
  bool r2 = ATInitSession(obj->session_handle,
                          cstr_url_address,
                          cstr_url_address,
                          api_port,
                          ATSessionStatusChangeCallback,
                          true);
                          
  // bool r2 = ATInitSession(obj->session_handle,
  //                         cstr_url_address,
  //                         cstr_url_address,
  //                         api_port,
  //                         &NodeActiveTick::ATSessionStatusChangeCallback,
  //                         true);  
                
  args.GetReturnValue().Set(Boolean::New(isolate, r2));
}

// Callbacks
void NodeActiveTick::ATSessionStatusChangeCallback(uint64_t hSession, ATSessionStatusType statusType) {
  std::cout << "Got it!";
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Foo to the bar")));
}

void NodeActiveTick::ATLoginResponseCallback(uint64_t hSession, uint64_t hRequest, LPATLOGIN_RESPONSE pResponse) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Foo to the bar")));
  
}












