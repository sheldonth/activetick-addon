// Copyright 2015-present Sheldon Thomas
#pragma once
#include <queue>
#include <node.h>
#include <node_object_wrap.h>
#include <nan.h>
#include <uv.h>
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include "protobuf/messages.pb.h"
#include "import/atfeed-cppsdk/example/Helper.h"
#include "Requestor.h"
#include "AtEnumConverter.h"

using namespace v8;

struct MessageStruct {
  uint64_t message_id;
  int32_t data_sz;
  void *c_str_data;
  char messageType[60];
};

class NodeActiveTick : public node::ObjectWrap {
public:
    static void Init(Handle<Object> exports);
    static void New (const FunctionCallbackInfo<Value> &args);
    Persistent<Function> p_dataCallback;
    uint64_t    session_handle;
    uint64_t    m_hLastRequest;
    char        m_userid[50];
    char        m_password[50];
    char        api_token[100];
    wchar16_t   wchar_userid[50];
    wchar16_t   wchar_password[50];
    wchar16_t   wchar_api_token[100];
    
    AtEnumConverter *enumConverter;
    Nan::Callback *nan_cb;
    uv_async_t handle;
    Requestor* requestor;
    static NodeActiveTick* s_pInstance;
    
private:
    explicit NodeActiveTick();
    ~NodeActiveTick();
    
private:
    static Persistent<Function> constructor;
    // Javascript Methods
    static void FireCallback(
                  const FunctionCallbackInfo<Value> &args);
    static void Connect(
                  const FunctionCallbackInfo<Value> &args);
    static void ListRequest(
                  const FunctionCallbackInfo<Value> &args);
    static void BeginQuoteStream(
                  const FunctionCallbackInfo<Value> &args);
    
    // AT Callbacks
    static void ATStreamUpdateCallback(LPATSTREAM_UPDATE pUpdate);
    static void ATSessionStatusChangeCallback(
                  uint64_t hSession,
                  ATSessionStatusType statusType);
    static void ATLoginResponseCallback(
                  uint64_t hSession,
                  uint64_t hRequest,
                  LPATLOGIN_RESPONSE pResponse);
    // Threading Helper
    static void DumpData(
                  uv_async_t *handle);

                  
    static void ATRequestTimeoutCallback(
                  uint64_t hOrigRequest);
  };