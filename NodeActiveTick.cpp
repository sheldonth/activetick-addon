// Copyright 2015-present Sheldon Thomas
#include <cstring>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <node.h>
#include <node_buffer.h>
#include <nan.h>
#include <uv.h>
#include "NodeActiveTick.h"
#include "import/atfeed-cppsdk/example/Helper.h"

#define debug 0

using namespace v8;

NodeActiveTick* NodeActiveTick::s_pInstance = NULL;

NodeActiveTick::NodeActiveTick() {
  ATInitAPI();
  session_handle = ATCreateSession();
  requestor = new Requestor(session_handle);
  enumConverter = new AtEnumConverter();
  ATSetStreamUpdateCallback(session_handle, &NodeActiveTick::ATStreamUpdateCallback);
  uv_async_init(uv_default_loop(), &handle, DumpData);
  GOOGLE_PROTOBUF_VERIFY_VERSION;
}
  
NodeActiveTick::~NodeActiveTick() {
  ATDestroySession(session_handle);
}

NAN_MODULE_INIT(NodeActiveTick::Init) {
    // Isolate* isolate = Isolate::GetCurrent();

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    // v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    // tpl->SetClassName( String::NewFromUtf8(isolate, "NodeActiveTick"));
    tpl->SetClassName(Nan::New("NodeActiveTick").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    // NODE_SET_PROTOTYPE_METHOD(tpl, "fireCallback", FireCallback);
    Nan::SetPrototypeMethod(tpl, "fireCallback", FireCallback);
    Nan::SetPrototypeMethod(tpl, "connect", Connect);
    Nan::SetPrototypeMethod(tpl, "listRequest", ListRequest);
    Nan::SetPrototypeMethod(tpl, "quoteStreamRequest", QuoteStreamRequest);
    Nan::SetPrototypeMethod(tpl, "barHistoryDbRequest", BarHistoryDbRequest);
    Nan::SetPrototypeMethod(tpl, "quoteDbRequest", QuoteDbRequest);
    Nan::SetPrototypeMethod(tpl, "quoteStreamRequestForSymbolData", QuoteStreamRequestForSymbolData);
    
    // constructor.Reset(isolate, tpl->GetFunction());
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    // exports->Set(String::NewFromUtf8(isolate, "NodeActiveTick"), tpl->GetFunction());
    Nan::Set(target, Nan::New("NodeActiveTick").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(NodeActiveTick::New) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    if (info.IsConstructCall()) {
        NodeActiveTick* obj = new NodeActiveTick();
        NodeActiveTick::s_pInstance = obj;
        if (!info[0]->IsFunction()) {
          isolate->ThrowException(Exception::TypeError(
                  String::NewFromUtf8(isolate, "NodeActiveTick requires a callback parameter in first argument position")));
        }
        Local<Function> cb = Local<Function>::Cast(info[0]);
        obj->p_dataCallback.Reset(isolate, cb);
        
        // Experimental Nan::Callback structure
        obj->nan_cb = new Nan::Callback(cb);
        
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
  }
  else {
    isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "NodeActiveTick cannot be allocated without javascript new keyword")));
  }
}
  
// void NodeActiveTick::FireCallback(const FunctionCallbackInfo<Value> &args) {
NAN_METHOD(NodeActiveTick::FireCallback) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
  
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

// void NodeActiveTick::Connect(const FunctionCallbackInfo<Value> &args) {
NAN_METHOD(NodeActiveTick::Connect) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
  
  uint32_t api_port = 443;
  
  Local<String> str_api_key = info[0]->ToString();
  char cstr_api_key[str_api_key->Utf8Length()];
  str_api_key->WriteUtf8(cstr_api_key);
  
  ATGUID at_guid = Helper::StringToATGuid(cstr_api_key);
  
  Local<String> str_user_id = info[1]->ToString();
  char cstr_api_user_id[str_user_id->Utf8Length()];
  str_user_id->WriteUtf8(cstr_api_user_id);
  
  Local<String> str_api_password = info[2]->ToString();
  char cstr_api_password[str_api_password->Utf8Length()];
  str_api_password->WriteUtf8(cstr_api_password);
  
  bool r = ATSetAPIUserId(obj->session_handle, &at_guid);
  if (!r) {
    isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Unable to call ATSetAPIUserId in SDK. Aborting. Check credentials.")));
    return;
  }

  if (debug) {
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
  ATInitSession(obj->session_handle,
                "activetick1.activetick.com",
                "activetick2.activetick.com",
                api_port,
                ATSessionStatusChangeCallback,
                true);
  // hack: connect messages are always ID 1
  info.GetReturnValue().Set(Number::New(isolate, 1));
}

NAN_METHOD(NodeActiveTick::QuoteDbRequest) {
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
  // Local<String> symbol_string = info[0]->ToString();
  Nan::Utf8String ticker_string(info[0]->ToString());
  std::string ticker = std::string(*ticker_string);
  std::vector<ATSYMBOL> symbols = Helper::StringToSymbols(ticker);
  Nan::Utf8String field_string(info[1]->ToString());
  std::string field = std::string(*field_string);
  std::vector<ATQuoteFieldType> fields;
  std::size_t pos = 0;
  std::size_t prevpos = 0;  
  while((pos=field.find(",", pos)) != std::string::npos) {
    std::string fieldStr = field.substr(prevpos, pos - prevpos);
    fields.push_back(obj->enumConverter->toAtQuoteField(fieldStr));
    ++pos;
    prevpos = pos;
  }
  fields.push_back(obj->enumConverter->toAtQuoteField(field.substr(prevpos)));
  s_pInstance->m_hLastRequest = obj->requestor->SendATQuoteDbRequest(symbols.data(), symbols.size(), fields.data(), fields.size(), DEFAULT_REQUEST_TIMEOUT);
  info.GetReturnValue().Set(Nan::New<Number>(s_pInstance->m_hLastRequest));
}

NAN_METHOD(NodeActiveTick::BarHistoryDbRequest) {
  Isolate* isolate = Isolate::GetCurrent();
  if (isolate) {
    HandleScope scope(isolate);
    NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
    Local<String> symbol_string = info[0]->ToString();
    char cstr_symbol[symbol_string->Utf8Length()];
    symbol_string->WriteUtf8(cstr_symbol);
    ATSYMBOL s = Helper::StringToSymbol(std::string(cstr_symbol));
    Local<String> barhistorytype_string = info[1]->ToString();
    char cstr_barhistorytype[barhistorytype_string->Utf8Length()];
    barhistorytype_string->WriteUtf8(cstr_barhistorytype);
    ATBarHistoryType barHistoryType = obj->enumConverter->toATBarHistoryType(std::string(cstr_barhistorytype));
    Local<Uint32> ca = info[2]->ToUint32();
    uint32_t c = ca->Value();
    uint8_t compression = c;
    Local<String> start_time = info[3]->ToString();
    char cstr_start_time[start_time->Utf8Length()];
    start_time->WriteUtf8(cstr_start_time);
    Local<String> end_time = info[4]->ToString();
    char cstr_end_time[end_time->Utf8Length()];
    end_time->WriteUtf8(cstr_end_time);
    ATTIME sTime = Helper::StringToATTime(std::string(cstr_start_time));
    ATTIME eTime = Helper::StringToATTime(std::string(cstr_end_time));    
    s_pInstance->m_hLastRequest = obj->requestor->SendATBarHistoryDbRequest(s, barHistoryType, compression, sTime, eTime, DEFAULT_REQUEST_TIMEOUT);
    info.GetReturnValue().Set(Number::New(isolate, s_pInstance->m_hLastRequest));
  }
}

NAN_METHOD(NodeActiveTick::ListRequest) {
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
  Nan::Utf8String list_type(info[0]->ToString());
  std::string str_list_type = std::string(*list_type);
  Nan::Utf8String symbol(info[1]->ToString());
  std::string str_symbol = std::string(*symbol);
  wchar16_t wchar_symbol[50];
  Helper::ConvertString(str_symbol.c_str(), wchar_symbol, sizeof(wchar_symbol));    
  ATConstituentListType type = obj->enumConverter->toAtConstituentList(str_list_type);
  s_pInstance->m_hLastRequest = s_pInstance->requestor->SendATConstituentListRequest(type, wchar_symbol, DEFAULT_REQUEST_TIMEOUT);
  info.GetReturnValue().Set(Nan::New<Number>(s_pInstance->m_hLastRequest));
}

NAN_METHOD(NodeActiveTick::QuoteStreamRequestForSymbolData) {
  uint64_t quote_stream_request = 0;
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
  // void* buf = (void*) node::Buffer::Data(info[0]->ToObject());
  // Nan::Utf8String p_data(info[2]->ToString());
  // std::string data_string = std::string(*p_data);
  char* buf = node::Buffer::Data(info[0]->ToObject());

  unsigned int size = info[1]->Uint32Value();
  Nan::Utf8String request_type(info[2]->ToString());
  std::string str_request_type = std::string(*request_type);

  ATStreamRequestType requestType = obj->enumConverter->toAtStreamRequest(str_request_type);  
  NodeActiveTickProto::ATSymbol s = NodeActiveTickProto::ATSymbol();

  s.ParseFromArray(buf, size);
  ATSYMBOL atSymbol;
  // atSymbol.symbol = s.symbol();
  Helper::ConvertString(s.symbol().c_str(), atSymbol.symbol, ATSymbolMaxLength);
  atSymbol.symbolType = s.symboltype();
  atSymbol.exchangeType = s.exchangetype();
  atSymbol.countryType = s.countrytype();
  std::vector<ATSYMBOL> out;
  out.push_back(atSymbol);
  quote_stream_request = obj->requestor->SendATQuoteStreamRequest(out.data(), 1, requestType, DEFAULT_REQUEST_TIMEOUT);
  info.GetReturnValue().Set(Nan::New<Number>(quote_stream_request));
}

NAN_METHOD(NodeActiveTick::QuoteStreamRequest) {
  uint64_t quote_stream_request = 0;
  NodeActiveTick *obj = ObjectWrap::Unwrap<NodeActiveTick>(info.Holder());
  Nan::Utf8String symbols(info[0]->ToString());
  std::string str_symbols = std::string(*symbols);
  std::vector<ATSYMBOL> v_symbols = Helper::StringToSymbols(str_symbols);
  uint32_t symbol_count = info[1]->Uint32Value();      
  Nan::Utf8String request_type(info[2]->ToString());
  std::string str_request_type = std::string(*request_type);
  ATStreamRequestType requestType = obj->enumConverter->toAtStreamRequest(str_request_type);
  quote_stream_request = obj->requestor->SendATQuoteStreamRequest(v_symbols.data(), symbol_count, requestType, DEFAULT_REQUEST_TIMEOUT);
  info.GetReturnValue().Set(Nan::New<Number>(quote_stream_request));
}


// AT Callbacks
void NodeActiveTick::ATStreamUpdateCallback(LPATSTREAM_UPDATE pUpdate) {
  MessageStruct* m = new MessageStruct();
  switch (pUpdate->updateType) {
    case StreamUpdateTrade: {
      ATQUOTESTREAM_TRADE_UPDATE trade = pUpdate->trade;
      NodeActiveTickProto::ATQuoteStreamTradeUpdate* msg = ProtobufHelper::atquotestreamtradeupdate(trade);
      std::strcpy(m->messageType, "ATQuoteStreamTradeUpdate");
      int size = msg->ByteSize();
      void *buffer = new char[size];
      msg->SerializeToArray(buffer, size);
      m->data_sz = size;
      m->c_str_data = buffer;
      break;
    }
    case StreamUpdateQuote:{
      ATQUOTESTREAM_QUOTE_UPDATE quote = pUpdate->quote;
      NodeActiveTickProto::ATQuoteStreamQuoteUpdate* msg = ProtobufHelper::atquotestreamquoteupdate(quote);
      std::strcpy(m->messageType, "ATQuoteStreamQuoteUpdate");
      int size = msg->ByteSize(); 
      void *buffer = new char[size];
      msg->SerializeToArray(buffer, size);
      m->data_sz = size;
      m->c_str_data = buffer;
      break;
    }
    case StreamUpdateRefresh: {
      ATQUOTESTREAM_REFRESH_UPDATE refresh = pUpdate->refresh;
      NodeActiveTickProto::ATQuoteStreamRefreshUpdate* msg = ProtobufHelper::atquotestreamrefreshquote(refresh);
      std::strcpy(m->messageType, "ATQuoteStreamRefreshUpdate");
      int size = msg->ByteSize();
      void *buffer = new char[size];
      msg->SerializeToArray(buffer, size);
      m->data_sz = size;
      m->c_str_data = buffer;
      break;
    }
    case StreamUpdateTopMarketMovers: {
      ATMARKET_MOVERS_STREAM_UPDATE movers = pUpdate->marketMovers;
      NodeActiveTickProto::ATMarketMoversStreamUpdate* msg = ProtobufHelper::atmarketmoversstreamupdate(movers);
      std::strcpy(m->messageType, "ATMarketMoversStreamUpdate");
      int size = msg->ByteSize();
      void *buffer = new char[size];
      msg->SerializeToArray(buffer, size);
      m->data_sz = size;
      m->c_str_data = buffer;
      break;
    }
    default: break;
  }
  (&s_pInstance->handle)->data = m;
  uv_async_send(&s_pInstance->handle);
}

void NodeActiveTick::ATSessionStatusChangeCallback(uint64_t hSession, ATSessionStatusType statusType) {
  std::string strStatusType;
  switch(statusType)
  {
    case SessionStatusConnected: strStatusType = "Connected"; break;
    case SessionStatusDisconnected: strStatusType = "Disconnected"; break;
    case SessionStatusDisconnectedDuplicateLogin: strStatusType = "DuplicateLogin"; break;
    default: strStatusType = "None"; break;
  }
  if (debug) {
    std::printf("ATSessionStatusChangeCallback: %s \n", strStatusType.c_str());
  }
  
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
  // TODO serialize ATTIME
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
  if (debug) {
    std::printf("Login: %s\n", strLoginResponseType.c_str());
  }
  NodeActiveTickProto::ATLoginResponse *msg = new NodeActiveTickProto::ATLoginResponse;
  msg->set_loginresponsetype((int32_t)p);
  msg->set_loginresponsestring(strLoginResponseType);
  int size = msg->ByteSize(); 
  void *buffer = new char[size];
  msg->SerializeToArray(buffer, size);
  MessageStruct* m = new MessageStruct();
  m->data_sz = size;
  m->c_str_data = buffer;
  m->message_id = hRequest;
  std::strcpy(m->messageType, "ATLoginResponse");
  (&s_pInstance->handle)->data = m;
  uv_async_send(&s_pInstance->handle);
}

void NodeActiveTick::ATRequestTimeoutCallback( uint64_t hOrigRequest ) {
  std::printf("ATRequestTimeoutCallback"); // TODO Make this an event
}

// Threading Helper
void NodeActiveTick::DumpData(uv_async_t *handle) {
  Isolate* isolate = Isolate::GetCurrent();
  if (isolate) {
    HandleScope scope(isolate);
    MessageStruct* m = static_cast<MessageStruct*>(handle->data);
    Local<Object> buffer = node::Buffer::New(m->data_sz);
    std::memcpy(node::Buffer::Data(buffer), m->c_str_data, m->data_sz);
    Local<Context> globalContext = isolate->GetCurrentContext();
    Local<Object> globalObject = globalContext->Global();
    Local<Function> bufferConstructor = Local<Function>::Cast(globalObject->Get(String::NewFromUtf8(isolate, "Buffer")));
    Handle<Value> constructorArgs[3] = {buffer,
                             Integer::New(isolate, m->data_sz),
                             Integer::New(isolate, 0)};
    Local<Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);
    Local<Function> func = Local<Function>::New(isolate, s_pInstance->p_dataCallback);
    Local<Value> str = String::NewFromUtf8(isolate, m->messageType);  
    Local<Number> request_id = Number::New(isolate, m->message_id);
    const unsigned argc = 3;
    Local<Value> argv[argc] = {str, request_id, actualBuffer};
    func->Call(Null(isolate), argc, argv);
    // delete m;
  }
  // TODO: Memory Management
  // uv_close((uv_handle_t*) &s_pInstance->handle, NULL);
}











