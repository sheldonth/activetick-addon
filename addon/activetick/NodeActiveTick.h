#pragma once
#include <queue>
#include <node.h>
#include <node_object_wrap.h>
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>

#include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

class NodeActiveTick : public node::ObjectWrap {
public:
    static void Init(Handle<Object> exports);
    Persistent<Function> p_dataCallback;
    Persistent<Function> connectionCallback;
    
    uint64_t    m_hLastRequest;
    char        m_userid[50];
    char        m_password[50];
    
private:
    explicit NodeActiveTick();
    ~NodeActiveTick();
    
    uint64_t session_handle;
    static NodeActiveTick* s_pInstance;
    
private:  
    static void ATSessionStatusChangeCallback(
                  uint64_t hSession,
                  ATSessionStatusType statusType);
    static void ATLoginResponseCallback(
                  uint64_t hSession,
                  uint64_t hRequest,
                  LPATLOGIN_RESPONSE pResponse);
    
    static void New (const FunctionCallbackInfo<Value> &args);
    static Persistent<Function> constructor;
    
    static void FireCallback(
            const FunctionCallbackInfo<Value> &args);
    static void Connect(
            const FunctionCallbackInfo<Value> &args);
  };