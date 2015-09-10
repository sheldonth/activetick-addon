#pragma once
#include <queue>
#include <node.h>

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
    NodeActivetick();
    ~NodeActivetick();

    static Handle<Value> New( const Arguments &args );

    // -- session --
    static Handle<Value> SessionInit( const Arguments &args );
    static Handle<Value> GetSessionHandle( const Arguments &args );

    // -- requestor --
    static Handle<Value> CloseAllATRequests ( const Arguments &args );
    static Handle<Value> CloseATRequest ( const Arguments &args );
    static Handle<Value> SendATBarHistoryDbRequest ( const Arguments &args );
    static Handle<Value> SendATLoginRequest ( const Arguments &args );
    static Handle<Value> SendATMarketHolidaysRequest ( const Arguments &args );
    static Handle<Value> SendATMarketMoversDbRequest ( const Arguments &args );
    static Handle<Value> SendATMarketMoversStreamRequest ( const Arguments &args );
    static Handle<Value> SendATQuoteDbRequest ( const Arguments &args );
    static Handle<Value> SendATQuoteStreamRequest ( const Arguments &args );
    static Handle<Value> SendATTickHistoryDbRequest ( const Arguments &args );
    static Handle<Value> SendATSectorListRequest ( const Arguments &args );
    static Handle<Value> SendATConstituentListRequest ( const Arguments &args );

    // -- streamer --


    static Handle<Value> GetMsg( const Arguments &args );

private:
    JSONNode getInboundMsg();

private:
    APISession m_session;
    Requestor m_requestor;
    Streamer m_streamer;

    AtJsonParser m_parser;
    std::queue< JSONNode > m_inboundMsgs;
    AtEnumConverter m_enumMap;
};
