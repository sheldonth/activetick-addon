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

#define debug 0

using namespace v8;

Persistent<Function> NodeActiveTick::constructor;
NodeActiveTick* NodeActiveTick::s_pInstance = NULL;

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
        NodeActiveTick::s_pInstance = obj;
        obj->iso = isolate;
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
  char cstr_url_address[str_url_address->Utf8Length()];
  str_url_address->WriteUtf8(cstr_url_address);
  
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

  if (debug) {
    printf("A: %s \n", cstr_url_address);
    printf("B: %i \n", api_port);
    printf("C: %s \n", cstr_api_key);
    printf("D: %s \n", cstr_api_user_id);
    printf("E: %s \n", cstr_api_password);
  }

  std::strcpy(obj->m_userid, cstr_api_user_id);
  std::strcpy(obj->m_password, cstr_api_password);
  std::strcpy(obj->api_token, cstr_api_key);
  
  Helper::ConvertString(obj->m_userid, obj->wchar_userid, sizeof(obj->wchar_userid));
  Helper::ConvertString(obj->m_password, obj->wchar_password, sizeof(obj->wchar_password));
  Helper::ConvertString(obj->api_token, obj->wchar_api_token, sizeof(obj->wchar_api_token));
  

  // todo: activetick2.activetick.com
  bool r2 = ATInitSession(obj->session_handle,
                          "activetick1.activetick.com",
                          "activetick2.activetick.com",
                          api_port,
                          ATSessionStatusChangeCallback,
                          true);
                          
  args.GetReturnValue().Set(Boolean::New(isolate, r2));
}

// Callbacks
void NodeActiveTick::ATSessionStatusChangeCallback(uint64_t hSession, ATSessionStatusType statusType) {
  std::string strStatusType;
  switch(statusType)
  {
    case SessionStatusConnected: strStatusType = "Connected"; break;
    case SessionStatusDisconnected: strStatusType = "Disconnected"; break;
    case SessionStatusDisconnectedDuplicateLogin: strStatusType = "DuplicateLogin"; break;
    default: strStatusType = "None"; break;
  }
  std::printf("ATSessionStatusChangeCallback: %s \n", strStatusType.c_str());
  
  if (statusType == SessionStatusConnected) {
    s_pInstance->m_hLastRequest = ATCreateLoginRequest( hSession,
                                                        s_pInstance->wchar_userid,
                                                        s_pInstance->wchar_password,
                                                        ATLoginResponseCallback );
    bool r = ATSendRequest( s_pInstance->session_handle,
                            s_pInstance->m_hLastRequest,
                            DEFAULT_REQUEST_TIMEOUT,
                            ATRequestTimeoutCallback );
    if (!r) {
      std::cerr << "ATSendRequest Failed";
    }
  }
}

void NodeActiveTick::ATLoginResponseCallback(uint64_t hSession, uint64_t hRequest, LPATLOGIN_RESPONSE pResponse) {
  ATLoginResponseType p = pResponse->loginResponse;
  uint8_t perm = pResponse->permissions[0];
  ATTIME time = pResponse->serverTime;
  
  std::string strLoginResponseType;
  switch(p)
  {
    case LoginResponseSuccess: strLoginResponseType = "Success"; break;
    case LoginResponseInvalidUserid: strLoginResponseType = "InvalidUserid"; break;
    case LoginResponseInvalidPassword: strLoginResponseType = "InvalidPassword"; break;
    case LoginResponseInvalidRequest: strLoginResponseType = "InvalidRequest"; break;
    case LoginResponseLoginDenied: strLoginResponseType = "LoginDenied"; break;
    case LoginResponseServerError: strLoginResponseType = "ServerError"; break;
    default: strLoginResponseType = "Default Case"; break;
  }
  std::printf("Login: %s\n", strLoginResponseType.c_str());
  Isolate* isolate = Isolate::GetCurrent();
  if (!isolate) {
    isolate = s_pInstance->iso;
    if (isolate) {
      Locker locker(isolate);
      Isolate::Scope isolate_scope(isolate);
      HandleScope handle_scope(isolate);
      Local<Context> context = Context::New(isolate);
      context->Enter();
      Local<Object> globalObject = context->Global();
      // if (!globalObject) {
      //   printf("No globalObject");
      // }
      const unsigned argcc = 1;
      Local<Value> argvv[argcc] = { String::NewFromUtf8(isolate, "hello world") };  
      Local<Function> func = Local<Function>::New(isolate, s_pInstance->p_dataCallback);
      
      func->Call(globalObject, argcc, argvv);
      
      // isolate->Enter();
      
    }
  }
  // HandleScope scope(isolate);
}

void NodeActiveTick::ATRequestTimeoutCallback( uint64_t hOrigRequest ) {
  std::printf("ATRequestTimeoutCallback");
}













