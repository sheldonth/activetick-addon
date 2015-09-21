#pragma once
#include <queue>
#include <node.h>
#include <node_object_wrap.h>

// #include "Requestor.h"
// #include "Session.h"
// #include "Streamer.h"
// #include "AtJsonParser.h"
// #include "AtEnumConverter.h"

#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include "import/atfeed-cppsdk/example/Helper.h"

// #include "import/libjson/_internal/Source/JSONNode.h"

using namespace v8;

class NodeActiveTick : public node::ObjectWrap {
public:
    static void Init( Handle<Object> exports );
    Persistent<Function> p_dataCallback;

private:
    explicit NodeActiveTick();
    ~NodeActiveTick();
    
    static void New( const FunctionCallbackInfo<Value> &args );
    static Persistent<Function> constructor;
    
    static void FireCallback(
            const FunctionCallbackInfo<Value> &args );
    
  };