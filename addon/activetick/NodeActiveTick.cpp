#include <cstring>
#include <locale>
#include <sstream>
#include <node.h>
#include "NodeActiveTick.h"
// #include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Persistent<Function> NodeActiveTick::constructor;

NodeActiveTick::NodeActiveTick() {
  
}
  
NodeActiveTick::~NodeActiveTick() {
  
}

void NodeActiveTick::Init( Handle<Object> exports ) {
    Isolate* isolate = Isolate::GetCurrent();

    ATInitAPI();
    Local<FunctionTemplate> tpl = FunctionTemplate::New( isolate, New );
    tpl->SetClassName( String::NewFromUtf8( isolate, "NodeActiveTick" ) );
    // tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD( tpl, "fireCallback" , FireCallback );
    
    constructor.Reset( isolate, tpl->GetFunction() );
    exports->Set( String::NewFromUtf8( isolate, "NodeActiveTick" ),
                  tpl->GetFunction() );
}
  
void NodeActiveTick::New( const FunctionCallbackInfo<Value> &args ) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope( isolate );

    // if (args.IsConstructCall()) {
        NodeActiveTick* obj = new NodeActiveTick();
        
        // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        obj->dataCallback = Local<Function>::Cast(args[0]);
        obj->Wrap( args.This() );
        args.GetReturnValue().Set( args.This() );
  // }
}
  
void NodeActiveTick::FireCallback(const FunctionCallbackInfo<Value> &args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope( isolate );
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>( args.Holder() );
  
  const unsigned argc = 1;
  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
  obj->dataCallback->Call(Null(isolate), argc, argv);
}
  
  

