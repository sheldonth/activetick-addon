#include <cstring>
#include <locale>
#include <sstream>
#include <node.h>
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
  const unsigned argc = 1;
  Local<Value> argv[1] = { String::NewFromUtf8(isolate, "hello world") };  
  Local<Function> func = Local<Function>::New(isolate, obj->p_dataCallback);
  func->Call(Null(isolate), argc, argv);
}

