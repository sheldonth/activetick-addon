#include <cstring>
#include <locale>
#include <sstream>
#include <node.h>
#include "NodeActivetick.h"
// #include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Persistent<Function> NodeActivetick::constructor;

NodeActivetick::NodeActivetick() {
        
  }
  
NodeActivetick::~NodeActivetick() {
    
  }

void NodeActivetick::Init( Handle<Object> exports ) {
    Isolate* isolate = Isolate::GetCurrent();

    ATInitAPI();
    Local<FunctionTemplate> tpl = FunctionTemplate::New( isolate, New );
    tpl->SetClassName( String::NewFromUtf8( isolate, "NodeActivetick" ) );
    constructor.Reset( isolate, tpl->GetFunction() );
    exports->Set( String::NewFromUtf8( isolate, "NodeActivetick" ),
                  tpl->GetFunction() );
  }
  
  void NodeActivetick::New( const FunctionCallbackInfo<Value> &args ) {
      Isolate* isolate = Isolate::GetCurrent();
      HandleScope scope( isolate );

      if (args.IsConstructCall()) {
          // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
          NodeActivetick* obj = new NodeActivetick();
          obj->Wrap( args.This() );
          args.GetReturnValue().Set( args.This() );
    }
  }

