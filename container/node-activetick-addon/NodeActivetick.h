#pragma once
#include <queue>
#include <node.h>
#include <node_object_wrap.h>

#include "Requestor.h"
#include "Session.h"
#include "Streamer.h"
#include "AtJsonParser.h"
#include "AtEnumConverter.h"

#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include "import/atfeed-cppsdk/example/Helper.h"
#include "import/libjson/_internal/Source/JSONNode.h"

using namespace v8;

class NodeActivetick : public node::ObjectWrap {
public:
    static void Init( Handle<Object> exports );

private:
    explicit NodeActivetick();
    ~NodeActivetick();

    static void New( const FunctionCallbackInfo<Value> &args );
    static Persistent<Function> constructor;

    // -- session --
    static void SessionInit( const FunctionCallbackInfo<Value> &args );
    static void GetSessionHandle( const FunctionCallbackInfo<Value> &args );

    // -- requestor --
    static void CloseAllATRequests( const FunctionCallbackInfo<Value> &args );
    static void CloseATRequest( const FunctionCallbackInfo<Value> &args );
    static void SendATBarHistoryDbRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATLoginRequest( const FunctionCallbackInfo<Value> &args );
    static void SendATMarketHolidaysRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATMarketMoversDbRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATMarketMoversStreamRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATQuoteDbRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATQuoteStreamRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATTickHistoryDbRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATSectorListRequest(
            const FunctionCallbackInfo<Value> &args );
    static void SendATConstituentListRequest(
            const FunctionCallbackInfo<Value> &args );

    // -- streamer --


    static void GetMsg( const FunctionCallbackInfo<Value> &args );

private:
    JSONNode getInboundMsg();
    double testDouble;

private:
    APISession m_session;
    Requestor m_requestor;
    Streamer m_streamer;

    AtJsonParser m_parser;
    std::queue< JSONNode > m_inboundMsgs;
    AtEnumConverter m_enumMap;
};
