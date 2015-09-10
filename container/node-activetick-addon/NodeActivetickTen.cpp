#include <cstring>
#include <node.h>
#include "NodeActivetickTen.h"
#include "import/libjson/libjson.h"
#include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

NodeActivetick::NodeActivetick()
    : m_session( &this->m_inboundMsgs ),
      m_requestor( this->m_session, &this->m_inboundMsgs ),
      m_streamer( this->m_session, &this->m_inboundMsgs ) {
}
NodeActivetick::~NodeActivetick() {
    ATShutdownAPI();
}

void NodeActivetick::Init( Handle<Object> exports ) {
    ATInitAPI();
    Local<FunctionTemplate> tpl = FunctionTemplate::New( New );
    tpl->SetClassName( String::NewSymbol( "NodeActivetick" ) );
    tpl->InstanceTemplate()->SetInternalFieldCount( 1 );

    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sessionInit" ),
        FunctionTemplate::New( SessionInit )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getSessionHandle" ),
        FunctionTemplate::New( GetSessionHandle )->GetFunction() );
    
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "closeAllATRequests" ),
        FunctionTemplate::New( CloseAllATRequests )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "closeATRequest" ),
        FunctionTemplate::New( CloseATRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATBarHistoryDbRequest" ),
        FunctionTemplate::New( SendATBarHistoryDbRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATLoginRequest" ),
        FunctionTemplate::New( SendATLoginRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATMarketHolidaysRequest" ),
        FunctionTemplate::New( SendATMarketHolidaysRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATMarketMoversDbRequest" ),
        FunctionTemplate::New( SendATMarketMoversDbRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATMarketMoversStreamRequest" ),
        FunctionTemplate::New( SendATMarketMoversStreamRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATQuoteDbRequest" ),
        FunctionTemplate::New( SendATQuoteDbRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATQuoteStreamRequest" ),
        FunctionTemplate::New( SendATQuoteStreamRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATTickHistoryDbRequest" ),
        FunctionTemplate::New( SendATTickHistoryDbRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATSectorListRequest" ),
        FunctionTemplate::New( SendATSectorListRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "sendATConstituentListRequest" ),
        FunctionTemplate::New( SendATConstituentListRequest )->GetFunction() );

    // message queue
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getMsg" ),
        FunctionTemplate::New( GetMsg )->GetFunction() );


    Persistent<Function> constructor =
        Persistent<Function>::New( tpl->GetFunction() );
    exports->Set( String::NewSymbol( "NodeActivetick" ), constructor );
}

Handle<Value> NodeActivetick::New( const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = new NodeActivetick();
    obj->Wrap( args.This() );
    return args.This();
}

Handle<Value> NodeActivetick::SessionInit( const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.This() );

    std::string serverIpAddress, apiUserid, userid, password;
    uint32_t serverPort = 0;

    apiUserid = *v8::String::Utf8Value( args[0]->ToString() );
    serverIpAddress = *String::Utf8Value( args[1]->ToString() );
    serverPort = args[2]->Int32Value();
    userid = *String::Utf8Value( args[3]->ToString() );
    password = *String::Utf8Value( args[4]->ToString() );
    
    ATGUID guidApiUserid = Helper::StringToATGuid(apiUserid);
    bool rc = obj->m_session.Init(guidApiUserid, serverIpAddress, serverPort,
                                    &Helper::ConvertString(userid).front(),
                                    &Helper::ConvertString(password).front());

    return scope.Close( Boolean::New( rc ) );
}
Handle<Value> NodeActivetick::GetSessionHandle( const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.This() );
    return scope.Close( Integer::New( obj->m_session.GetSessionHandle() ) );
}

// -- requestor --
Handle<Value> NodeActivetick::CloseAllATRequests(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );
    obj->m_requestor.CloseAllATRequests();
    return scope.Close( Undefined() );
}

Handle<Value> NodeActivetick::CloseATRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    // TODO: incorrect type assignment
    uint64_t request = args[0]->IntegerValue();

    obj->m_requestor.CloseATRequest( request );
    return scope.Close( Undefined() );
}

Handle<Value> NodeActivetick::SendATBarHistoryDbRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string symbol( *String::Utf8Value( args[0]->ToString() ) );
    ATSYMBOL atSymbol = Helper::StringToSymbol(symbol);

    ATBarHistoryType type;
    std::string historyType( *String::Utf8Value( args[1]->ToString() ) );
    if ( historyType == "BarHistoryIntraday" )
        type = BarHistoryIntraday;
    else if ( historyType == "BarHistoryDaily" )
        type = BarHistoryDaily;
    else if ( historyType == "BarHistoryWeekly" )
        type = BarHistoryWeekly;
    else {
        type = BarHistoryIntraday;
    }
    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    uint64_t request = 0;

    uint32_t minutes = args[2]->Uint32Value();

    if ( args[3]->IsString() && args[4]->IsString() ) {
        std::string beginTime( *String::Utf8Value( args[3]->ToString() ) );
        std::string endTime( *String::Utf8Value( args[4]->ToString() ) );

        ATTIME atBeginTime = Helper::StringToATTime(beginTime);
        ATTIME atEndTime = Helper::StringToATTime(endTime);

        if ( args.Length() == 6 && args[5]->IsUint32() )
            timeout = args[5]->Uint32Value();
        request = obj->m_requestor.SendATBarHistoryDbRequest(
                       atSymbol, type, (uint8_t)minutes, atBeginTime,
                       atEndTime, timeout );
    } else if ( args[3]->IsUint32() ) {
        uint32_t recordsWanted = args[3]->Uint32Value();

        if ( args.Length() == 5 && args[4]->IsUint32() )
            timeout = args[4]->Uint32Value();

        request = obj->m_requestor.SendATBarHistoryDbRequest(
                       atSymbol, type, (uint8_t)minutes, recordsWanted,
                       timeout );
    } else if ( args[3]->IsString() && args[4]->IsUint32() &&
                args[5]->IsString() ) {
        std::string beginTime( *String::Utf8Value( args[3]->ToString() ) );
        ATTIME atBeginTime = Helper::StringToATTime(beginTime);

        uint32_t recordsWanted = args[4]->Uint32Value();

        std::string cursorStr( *String::Utf8Value( args[5]->ToString() ) );
        ATCursorType cursorType = obj->m_enumMap.toAtCursor( cursorStr );

        if ( args.Length() == 7 && args[6]->IsUint32() )
            timeout = args[6]->Uint32Value();
        request = obj->m_requestor.SendATBarHistoryDbRequest(
                       atSymbol, type, (uint8_t)minutes, atBeginTime,
                       recordsWanted, cursorType, timeout );
    }

    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATLoginRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string userid = *String::Utf8Value( args[0]->ToString() );
    std::string passwd = *String::Utf8Value( args[1]->ToString() );
    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 3 && args[2]->IsUint32() )
        timeout = args[2]->Uint32Value();

    uint64_t request = obj->m_requestor.SendATLoginRequest(
                            &Helper::ConvertString(userid).front(),
                            &Helper::ConvertString(passwd).front(), timeout );
    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATMarketHolidaysRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    uint8_t yearsGoingBack = (uint8_t)args[0]->Uint32Value();
    uint8_t yearsGoingFwd = (uint8_t)args[1]->Uint32Value();

    
    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 5 && args[4]->IsUint32() )
        timeout = args[4]->Uint32Value();


    std::string exchangeStr( *String::Utf8Value( args[2]->ToString() ) );
    std::string countryStr( *String::Utf8Value( args[3]->ToString() ) );

    ATExchangeType exchangeType = obj->m_enumMap.toAtExchange( exchangeStr );
    ATCountryType countryType = obj->m_enumMap.toAtCountry( countryStr );

    uint64_t request = obj->m_requestor.SendATMarketHolidaysRequest(
                           yearsGoingBack, yearsGoingFwd, exchangeType,
                           countryType, timeout );
    
    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATMarketMoversDbRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    // QUESTION is atSymbol.symbolType = SymbolTopMarketMovers; necessary?
    std::string symbols( *String::Utf8Value( args[0]->ToString() ) );
    std::vector<ATSYMBOL> atSymbols = Helper::StringToSymbols( symbols );

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 2 && args[1]->IsUint32() )
        timeout = args[1]->Uint32Value();

    uint64_t request = obj->m_requestor.SendATMarketMoversDbRequest(
                            atSymbols.data(), (uint16_t)symbols.size(),
                            timeout );

    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATMarketMoversStreamRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string symbol( *String::Utf8Value( args[0]->ToString() ) );
    ATSYMBOL atSymbol = Helper::StringToSymbol(symbol);

    std::string requestStr( *String::Utf8Value( args[1]->ToString() ) );
    ATStreamRequestType requestType =
            obj->m_enumMap.toAtStreamRequest( requestStr );

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 3 && args[2]->IsUint32() )
        timeout = args[2]->Uint32Value();

    uint64_t request = obj->m_streamer.SendATMarketMoversStreamRequest(
                            atSymbol, requestType, timeout );

    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATQuoteDbRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string symbols( *String::Utf8Value( args[0]->ToString() ) );
    std::vector<ATSYMBOL> atSymbols = Helper::StringToSymbols( symbols );

    std::string quoteFieldStr( *String::Utf8Value( args[1]->ToString() ) );
    //
    std::vector<ATQuoteFieldType> fields;
    std::size_t pos = 0;
    std::size_t prevpos = 0;

    while( ( pos = quoteFieldStr.find( ",", pos ) ) != std::string::npos )
    {
        std::string field = quoteFieldStr.substr( prevpos, pos - prevpos );
        fields.push_back( obj->m_enumMap.toAtQuoteField( field ) );
        
        ++pos;
        prevpos = pos;              
    }   

    fields.push_back(
            obj->m_enumMap.toAtQuoteField( quoteFieldStr.substr( prevpos ) ) );

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 3 && args[2]->IsUint32() )
        timeout = args[2]->Uint32Value();

    uint64_t request = obj->m_requestor.SendATQuoteDbRequest(
                            atSymbols.data(), (uint16_t)atSymbols.size(),
                            fields.data(), (uint16_t)fields.size(), timeout );

    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATQuoteStreamRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string symbols( *String::Utf8Value( args[0]->ToString() ) );
    std::vector<ATSYMBOL> atSymbols = Helper::StringToSymbols( symbols );

    std::string requestStr( *String::Utf8Value( args[1]->ToString() ) );
    ATStreamRequestType requestType =
            obj->m_enumMap.toAtStreamRequest( requestStr );

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 3 && args[2]->IsUint32() )
        timeout = args[2]->Uint32Value();

    uint64_t request = obj->m_streamer.SendATQuoteStreamRequest(
                            atSymbols.data(), (uint16_t)atSymbols.size(),
                            requestType, timeout);

    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATTickHistoryDbRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string symbol( *String::Utf8Value( args[0]->ToString() ) );
    ATSYMBOL atSymbol = Helper::StringToSymbol( symbol );

    bool selectTrades = args[1]->BooleanValue();
    bool selectQuotes = args[2]->BooleanValue();

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    uint64_t request = 0;

    if ( args[3]->IsString() && args[4]->IsString() ) {
        std::string beginTime( *String::Utf8Value( args[3]->ToString() ) );
        std::string endTime( *String::Utf8Value( args[4]->ToString() ) );

        ATTIME atBeginTime = Helper::StringToATTime( beginTime );
        ATTIME atEndTime = Helper::StringToATTime( endTime );

        if ( args.Length() == 6 && args[5]->IsUint32() )
            timeout = args[5]->Uint32Value();

        request = obj->m_requestor.SendATTickHistoryDbRequest(
                       atSymbol, selectTrades, selectQuotes, atBeginTime,
                       atEndTime, timeout );
    } else if ( args[3]->IsUint32() &&
                ( args.Length() == 5 || args.Length() == 4 ) ) {
        uint32_t recordsWanted = args[3]->Uint32Value();

        if ( args.Length() == 5 && args[4]->IsUint32() )
            timeout = args[4]->Uint32Value();

        request = obj->m_requestor.SendATTickHistoryDbRequest(
                       atSymbol, selectTrades, selectQuotes, recordsWanted,
                       timeout );
    } else if ( args[3]->IsString() && args[4]->IsUint32() &&
                args[5]->IsString() ) {
        std::string beginTime( *String::Utf8Value( args[3]->ToString() ) );
        ATTIME atBeginTime = Helper::StringToATTime( beginTime );

        uint32_t recordsWanted = args[4]->Uint32Value();

        std::string cursorStr( *String::Utf8Value( args[5]->ToString() ) );
        ATCursorType cursorType = obj->m_enumMap.toAtCursor( cursorStr );

        if ( args.Length() == 7 && args[6]->IsUint32() )
            timeout = args[6]->Uint32Value();

        request = obj->m_requestor.SendATTickHistoryDbRequest(
                       atSymbol, selectTrades, selectQuotes, atBeginTime,
                       recordsWanted, cursorType, timeout );
    } else if ( args[3]->IsUint32() && args[5]->IsString() &&
                ( args.Length() == 7 || args.Length() == 6 ) ) {
        uint32_t pagesWanted = args[3]->Uint32Value();

        uint64_t offset = args[4]->IntegerValue();

        std::string dbdateStr( *String::Utf8Value( args[5]->ToString() ) );
        ATTIME dbdate = Helper::StringToATTime( dbdateStr );

        if ( args.Length() == 7 && args[6]->IsUint32() )
            timeout = args[6]->Uint32Value();

        request = obj->m_requestor.SendATTickHistoryDbRequest(
                       atSymbol, selectTrades, selectQuotes, pagesWanted,
                       offset, dbdate, timeout );
    }

    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATSectorListRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 1 && args[0]->IsUint32() )
        timeout = args[0]->Uint32Value();

    uint64_t request = obj->m_requestor.SendATSectorListRequest( timeout );
    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::SendATConstituentListRequest(
        const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    std::string constituentList( *String::Utf8Value( args[0]->ToString() ) );
    ATConstituentListType atConstituentList =
            obj->m_enumMap.toAtConstituentList( constituentList );

    uint32_t timeout = DEFAULT_REQUEST_TIMEOUT;
    if ( args.Length() == 3 && args[2]->IsUint32() )
            timeout = args[2]->Uint32Value();

    uint64_t request = 0;

    std::string asciikey( *String::Utf8Value( args[1]->ToString() ) );

    if ( atConstituentList == ATConstituentListSector ) {
        std::string asciikey( *String::Utf8Value( args[1]->ToString() ) );

        for(std::string::size_type i = 0; i < asciikey.length(); ++i) {
            if(asciikey[i] == '_')
                asciikey[i] = ' ';
        }

        wchar16_t key[ATSymbolMaxLength];
        Helper::ConvertString( asciikey.c_str(), key, ATSymbolMaxLength );

        request = obj->m_requestor.SendATConstituentListRequest(
                       atConstituentList, key, timeout );
    } else if ( atConstituentList == ATConstituentListOptionChain || 
                atConstituentList == ATConstituentListIndex ) {
        wchar16_t symbol[ATSymbolMaxLength];
        Helper::ConvertString( asciikey.c_str(), symbol, ATSymbolMaxLength );

        request = obj->m_requestor.SendATConstituentListRequest(
                       ATConstituentListOptionChain, symbol, timeout );
    }
    return scope.Close( Integer::New( request ) );
}

Handle<Value> NodeActivetick::GetMsg( const Arguments &args ) {
    HandleScope scope;
    NodeActivetick *obj = ObjectWrap::Unwrap<NodeActivetick>( args.Holder() );

    JSONNode newMsg;
    newMsg = obj->getInboundMsg();

    Handle<Object> retData = Object::New( );
    retData = obj->m_parser.parse( newMsg );

    return scope.Close( retData );
}

///////////////////////////////////////////////////////////////////////////////
// Helper methods
///////////////////////////////////////////////////////////////////////////////

JSONNode NodeActivetick::getInboundMsg() {
    JSONNode popped;
    if ( !this->m_inboundMsgs.empty() ) {
        popped = this->m_inboundMsgs.front();
        this->m_inboundMsgs.pop();
        return popped;
    }
    return popped;
}