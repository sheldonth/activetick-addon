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
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    constructor.Reset( isolate, tpl->GetFunction() );
    exports->Set( String::NewFromUtf8( isolate, "NodeActiveTick" ),
                  tpl->GetFunction() );
  }
  
  void NodeActiveTick::New( const FunctionCallbackInfo<Value> &args ) {
      Isolate* isolate = Isolate::GetCurrent();
      HandleScope scope( isolate );

      if (args.IsConstructCall()) {
          // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
          NodeActiveTick* obj = new NodeActiveTick();
          obj->Wrap( args.This() );
          args.GetReturnValue().Set( args.This() );
    }
  }

