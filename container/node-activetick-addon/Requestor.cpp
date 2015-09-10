#include "StdAfx.h"
#include "Requestor.h"
#include <ActiveTickServerAPI/ATBarHistoryDbResponseParser.h>
#include <ActiveTickServerAPI/ATMarketMoversDbResponseParser.h>
#include <ActiveTickServerAPI/ATQuoteDbResponseParser.h>
#include <ActiveTickServerAPI/ATQuoteStreamResponseParser.h>
#include <ActiveTickServerAPI/ATTickHistoryDbResponseParser.h>

#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>

#include <node.h>
#include "import/atfeed-cppsdk/example/Helper.h"
#include "import/libjson/libjson.h"

using namespace std;

Requestor::Requestor( const APISession& session,
                      std::queue< JSONNode > *pInboundMsgs)
: ActiveTickServerRequestor(session.GetSessionHandle())
{
    m_pInboundMsgs = pInboundMsgs;
}

Requestor::~Requestor(void)
{
}

/*virtual*/ void Requestor::OnATBarHistoryDbResponse(
                                    uint64_t origRequest,
                                    ATBarHistoryResponseType responseType,
                                    LPATBARHISTORY_RESPONSE pResponse) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATBarHistoryDb" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );

    string strResponseType;
    switch(responseType)
    {
    case BarHistoryResponseSuccess: strResponseType = "BarHistoryResponseSuccess"; break;
    case BarHistoryResponseInvalidRequest: strResponseType = "BarHistoryResponseInvalidRequest"; break;
    case BarHistoryResponseMaxLimitReached: strResponseType = "BarHistoryResponseMaxLimitReached"; break;
    case BarHistoryResponseDenied: strResponseType = "BarHistoryResponseDenied"; break;
    default: break;
    }

    JSONNode resp( JSON_NODE );
    resp.set_name( "response" );
    resp.push_back( JSONNode( "name", "ATBarHistoryResponseType" ) );
    resp.push_back( JSONNode( "enum", responseType ) );
    resp.push_back( JSONNode( "type", strResponseType ) );
    n.push_back( resp );

    JSONNode data( JSON_NODE );
    data.set_name( "data" );
    data.push_back( jsonifyAtBarHistory( pResponse ) );
    n.push_back( data );

    m_pInboundMsgs->push( n );
}

JSONNode Requestor::jsonifyAtBarHistory( LPATBARHISTORY_RESPONSE pResponse ) {
    ATBarHistoryDbResponseParser parser(pResponse);

    JSONNode n( JSON_NODE );
    n.set_name( "ATBarHistory" );
    n.push_back( m_jsonifier.jsonifyAtSymbol( parser.GetSymbol() ) );
    n.push_back( JSONNode( "count", parser.GetRecordCount() ) );

    if( parser.MoveToFirstRecord() ) {
        JSONNode c( JSON_ARRAY );
        c.set_name( "records");
        while( true ) {
            JSONNode bar( JSON_NODE );
            bar.set_name( "tick" );

            ATTIME recordDateTime = parser.GetDateTime();

            bar.push_back( m_jsonifier.jsonifyAtTime( "time",
                                                    &recordDateTime ) );
            
            JSONNode open( JSON_NODE );
            open.set_name( "open" );
            open.push_back( JSONNode( "precision",
                                      parser.GetOpen().precision ) );
            open.push_back( JSONNode( "price", parser.GetOpen().price ) );
            bar.push_back( open );

            JSONNode high( JSON_NODE );
            high.set_name( "high" );
            high.push_back( JSONNode( "precision",
                                      parser.GetHigh().precision ) );
            high.push_back( JSONNode( "price", parser.GetHigh().price ) );
            bar.push_back( high );

            JSONNode low( JSON_NODE );
            low.set_name( "low" );
            low.push_back( JSONNode( "precision", parser.GetLow().precision ) );
            low.push_back( JSONNode( "price", parser.GetLow().price ) );
            bar.push_back( low );

            JSONNode close( JSON_NODE );
            close.set_name( "close" );
            close.push_back( JSONNode( "precision",
                                       parser.GetClose().precision ) );
            close.push_back( JSONNode( "price", parser.GetClose().price ) );
            bar.push_back( close );

            bar.push_back( JSONNode( "volume", parser.GetVolume() ) );
            c.push_back( bar );

            if(parser.MoveToNextRecord() == false)
                break;
        }
        n.push_back( c );
    }

    return n;
}

/*virtual*/ void Requestor::OnATSectorListResponse(
                                    uint64_t origRequest,
                                    LPATSECTORLIST_RECORD pRecords,
                                    uint32_t recordsCount ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATSectorList" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );
    n.push_back( JSONNode( "count", recordsCount ) );

    JSONNode list( JSON_ARRAY );
    list.set_name( "list" );
    for(uint32_t i = 0; i < recordsCount; ++i) {
        JSONNode item( JSON_NODE );
        item.set_name( "data" );
        item.push_back( JSONNode( "sector", Helper::ConvertString(
                pRecords[i].sector, ATSectorNameMaxLength).c_str() ) );
        item.push_back( JSONNode( "industry", Helper::ConvertString(
                pRecords[i].industry, ATIndustryNameMaxLength).c_str() ) );
        list.push_back(item);
    }
    n.push_back( list );
    m_pInboundMsgs->push( n );
}

/*virtual*/ void Requestor::OnATConstituentListResponse(
                                    uint64_t origRequest,
                                    LPATSYMBOL pSymbols,
                                    uint32_t symbolsCount ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATConstituentList" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );
    n.push_back( JSONNode( "count", symbolsCount ) );
    
    JSONNode list( JSON_ARRAY );
    list.set_name( "dataItems" );
    for(uint32_t i = 0; i < symbolsCount; ++i) {
        JSONNode symbol( JSON_NODE );
        symbol.set_name( "ATSymbol" );
        symbol.push_back( JSONNode( "symbolStr", Helper::ConvertString(
                pSymbols[i].symbol, _countof(pSymbols[i].symbol)).c_str() ) );
        symbol.push_back( JSONNode( "symbolType", m_jsonifier.getSymbolType(pSymbols[i].symbolType) ) );
        symbol.push_back( JSONNode( "exchangeType", m_jsonifier.getExchangeType(pSymbols[i].exchangeType) ));
        symbol.push_back( JSONNode( "countryType", m_jsonifier.getCountryType(pSymbols[i].countryType) ) );

        list.push_back( symbol );
    }
    n.push_back( list );
    m_pInboundMsgs->push( n );
}


/*virtual*/ void Requestor::OnATTickHistoryDbResponse(
                                    uint64_t origRequest,
                                    ATTickHistoryResponseType responseType,
                                    LPATTICKHISTORY_RESPONSE pResponse ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATTickHistoryDb" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );

    string strResponseType;
    switch(responseType)
    {
    case TickHistoryResponseSuccess: strResponseType = "TickHistoryResponseSuccess"; break;
    case TickHistoryResponseInvalidRequest: strResponseType = "TickHistoryResponseInvalidRequest"; break;
    case TickHistoryResponseMaxLimitReached: strResponseType = "TickHistoryResponseMaxLimitReached"; break;
    case TickHistoryResponseDenied: strResponseType = "TickHistoryResponseDenied"; break;
    default: break;
    }
    JSONNode resp( JSON_NODE );
    resp.set_name( "response" );
    resp.push_back( JSONNode( "name", "ATTickHistoryResponseType" ) );
    resp.push_back( JSONNode( "enum", responseType ) );
    resp.push_back( JSONNode( "type", strResponseType ) );
    n.push_back( resp );

    JSONNode data( JSON_NODE );
    data.set_name( "data" );
    data.push_back( jsonifyAtTickHistory( pResponse ) );
    n.push_back( data );

    m_pInboundMsgs->push( n );

    if( pResponse->nextOffset != 0xffffffffffffffffULL &&
        pResponse->nextOffset != 0xfffffffffffffff0ULL &&
        pResponse->nextOffset != 0 )
        SendATTickHistoryDbRequest( pResponse->symbol, true, true, 10,
                                    pResponse->nextOffset,
                                    pResponse->offsetDatabaseDate,
                                    DEFAULT_REQUEST_TIMEOUT);

}

JSONNode Requestor::jsonifyAtTickHistory( LPATTICKHISTORY_RESPONSE pResponse ) {
    ATTickHistoryDBResponseParser parser(pResponse);

    JSONNode n( JSON_NODE );
    n.set_name( "ATTickHistory" );
    n.push_back( m_jsonifier.jsonifyAtSymbol( parser.GetSymbol() ) );
    n.push_back( jsonifyAtSymbolStatus( parser.GetSymbolStatus() ) );
    n.push_back( JSONNode( "count", parser.GetRecordCount() ) );
    n.push_back( JSONNode( "nextOffset", parser.GetNextOffset() ) );
    ATTIME offsetDatabaseDate = parser.GetOffsetDbDate();
    n.push_back( m_jsonifier.jsonifyAtTime( "offsetDatabaseDate",
                                            &offsetDatabaseDate ) );

    if( parser.MoveToFirstRecord() ) {
        JSONNode c( JSON_ARRAY );
        c.set_name( "records" );
        while( true ) {
            JSONNode tick( JSON_NODE );
            tick.set_name( "tick" );

            ATTIME recordDateTime = parser.GetRecordDateTime();
            tick.push_back( m_jsonifier.jsonifyAtTime( "time",
                                                    &recordDateTime ) );
            switch( parser.GetRecordType() )
            {
            case TickHistoryRecordTrade:
                {
                JSONNode last( JSON_NODE );
                last.set_name( "tradeLastPrice" );
                last.push_back( JSONNode( "precision",
                                    parser.GetTradeLastPrice().precision ) );
                last.push_back( JSONNode( "price",
                                    parser.GetTradeLastPrice().price ) );
                tick.push_back( last );
                tick.push_back( JSONNode( "tradeLastSize", parser.GetTradeLastSize() ) );
                tick.push_back( JSONNode( "tradeLastExchange", m_jsonifier.getExchangeType(parser.GetTradeLastExchange()) ) );
                tick.push_back( JSONNode( "tradeCondition", parser.GetTradeCondition(0) ) );
                }
                break;
            case TickHistoryRecordQuote:
                {
                JSONNode bid( JSON_NODE );
                bid.set_name( "quoteBidPrice" );
                bid.push_back( JSONNode( "precision",
                                   parser.GetQuoteBidPrice().precision ) );
                bid.push_back( JSONNode( "price",
                                   parser.GetQuoteBidPrice().price ) );
                tick.push_back( bid );
                JSONNode ask( JSON_NODE );
                ask.set_name( "quoteAskPrice" );
                ask.push_back( JSONNode( "precision",
                                   parser.GetQuoteAskPrice().precision ) );
                ask.push_back( JSONNode( "price",
                                   parser.GetQuoteAskPrice().price ) );
                tick.push_back( ask );
                tick.push_back( JSONNode( "quoteBidSize", parser.GetQuoteBidSize() ) );
                tick.push_back( JSONNode( "quoteAskSize", parser.GetQuoteAskSize() ) );
                tick.push_back( JSONNode( "quoteBidExchange", m_jsonifier.getExchangeType(parser.GetQuoteBidExchange()) ) );
                tick.push_back( JSONNode( "quoteAskExchange", m_jsonifier.getExchangeType(parser.GetQuoteAskExchange()) ) );
                tick.push_back( JSONNode( "quoteCondition", parser.GetQuoteCondition() ) );
                }
                break;
            default:
                break;
            }
            c.push_back( tick );
            if(parser.MoveToNextRecord() == false)
                break;
            
        }
        n.push_back( c );
    }
    return n;
}

JSONNode Requestor::jsonifyAtSymbolStatus( ATSymbolStatus status ) {
    string strStatusType;
    switch(status)
    {
    case SymbolStatusSuccess: strStatusType = "SymbolStatusSuccess"; break;
    case SymbolStatusInvalid: strStatusType = "SymbolStatusInvalid"; break;
    case SymbolStatusUnavailable: strStatusType = "SymbolStatusUnavailable"; break;
    case SymbolStatusNoPermission: strStatusType = "SymbolStatusNoPermission"; break;
    default: break;
    }
    JSONNode n( JSON_NODE );
    n.set_name( "data" );
    n.push_back( JSONNode( "name", "ATSymbolStatus" ) );
    n.push_back( JSONNode( "enum", status ) );
    n.push_back( JSONNode( "type", strStatusType ) );
    return n;
}


/*virtual*/ void Requestor::OnATMarketMoversDbResponse(
                                    uint64_t origRequest,
                                    ATMarketMoversDbResponseType responseType,
                                    LPATMARKET_MOVERSDB_RESPONSE pResponse ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATMarketMoversDb" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );

    string strResponseType;
    switch(responseType)
    {
    case MarketMoversDbResponseSuccess: strResponseType = "MarketMoversDbResponseSuccess"; break;
    case MarketMoversDbResponseInvalidRequest: strResponseType = "MarketMoversDbResponseInvalidRequest"; break;
    case MarketMoversDbResponseDenied: strResponseType = "MarketMoversDbResponseDenied"; break;
    default: break;
    }

    JSONNode resp( JSON_NODE );
    resp.set_name( "response" );
    resp.push_back( JSONNode( "name", "ATMarketMoversDbResponseType" ) );
    resp.push_back( JSONNode( "enum", responseType ) );
    resp.push_back( JSONNode( "type", strResponseType ) );
    n.push_back( resp );

    JSONNode data( JSON_NODE );
    data.set_name( "data" );
    data.push_back( jsonifyAtMarketMoversDb( pResponse ) );
    n.push_back( data );

    m_pInboundMsgs->push( n );
}

JSONNode Requestor::jsonifyAtMarketMoversDb( LPATMARKET_MOVERSDB_RESPONSE pResponse ) {

    ATMarketMoversDbResponseParser parser(pResponse);

    JSONNode n( JSON_NODE );
    n.set_name( "ATMarketMoversDb" );

    if( parser.MoveToFirstRecord() == true ) {
        JSONNode c( JSON_ARRAY );
        c.set_name( "records" );
        while( true ) {
            JSONNode rec( JSON_NODE );
            rec.push_back( JSONNode( "recordSymbol", parser.GetRecordSymbol()->symbol ) );

            if(parser.MoveToFirstItem() == true) {
                JSONNode items( JSON_ARRAY );
                items.set_name( "items" );
                while( true ) {
                    JSONNode item( JSON_NODE );
                    item.push_back( JSONNode( "itemSymbol", parser.GetItemSymbol()->symbol ) );

                    JSONNode lastPrice( JSON_NODE );
                    lastPrice.set_name( "itemLastPrice" );
                    lastPrice.push_back( JSONNode( "precision", parser.GetItemSymbol()->symbol ) );
                    lastPrice.push_back( JSONNode( "price", parser.GetItemLastPrice().price ) );
                    item.push_back( lastPrice );

                    item.push_back( JSONNode( "itemVolume", parser.GetItemVolume() ) );
                    items.push_back( item );
                    if(parser.MoveToNextItem() == false)
                        break;
                }
                rec.push_back( items );

                c.push_back( rec );
                if(parser.MoveToNextRecord() == false)
                    break;
            }
        }
    }
    return n;
}

/*virtual*/ void Requestor::OnATQuoteDbResponse(
                                    uint64_t origRequest,
                                    ATQuoteDbResponseType responseType,
                                    LPATQUOTEDB_RESPONSE pResponse,
                                    uint32_t responseCount ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATQuoteDb" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );

    string strResponseType;
    switch(responseType)
    {
    case QuoteDbResponseSuccess: strResponseType = "QuoteDbResponseSuccess"; break;
    case QuoteDbResponseInvalidRequest: strResponseType = "QuoteDbResponseInvalidRequest"; break;
    case QuoteDbResponseDenied: strResponseType = "QuoteDbResponseDenied"; break;
    default: break;
    }

    JSONNode resp( JSON_NODE );
    resp.set_name( "response" );
    resp.push_back( JSONNode( "name", "ATQuoteDbResponseType" ) );
    resp.push_back( JSONNode( "enum", responseType ) );
    resp.push_back( JSONNode( "type", strResponseType ) );
    n.push_back( resp );

    JSONNode data( JSON_NODE );
    data.set_name( "data" );
    data.push_back( jsonifyAtQuoteDb( pResponse, responseCount ) );
    n.push_back( data );

    m_pInboundMsgs->push( n );
}

JSONNode Requestor::jsonifyAtQuoteDb( LPATQUOTEDB_RESPONSE pResponse,
                                      uint32_t responseCount ) {
    ATQuoteDbResponseParser parser( pResponse, responseCount );
    JSONNode n( JSON_NODE );
    n.set_name( "ATQuoteDb" );

    if( parser.MoveToFirstResponse() == true ) {
        JSONNode recs( JSON_ARRAY );
        recs.set_name( "records" );

        while( true ) {
            JSONNode rec( JSON_NODE );

            rec.push_back( jsonifyAtSymbolStatus( parser.GetSymbolStatus() ) );
            JSONNode items( JSON_ARRAY );
            items.set_name( "dataItems" );

            if(parser.GetSymbolStatus() == SymbolStatusSuccess && parser.MoveToFirstDataItem() == true) {
                while(true) {
                    JSONNode item( JSON_NODE );

                    char data[512] = {0};
                    ATDataType dataType = parser.GetDataItemDataType();
                    JSONNode dContent( JSON_NODE );
                    dContent.set_name( "data" );
                    dContent.push_back( JSONNode( "enum", dataType ) );

                    switch( dataType )
                    {
                    case DataByte:
                        {
                        dContent.push_back( JSONNode( "byte", *(char*)parser.GetDataItemData() ) );
                        }
                        break;
                    case DataByteArray:
                        {
                        // TODO handle byteArray
                        dContent.push_back( JSONNode( "byteArray", data ) );
                        }
                        break;
                    case DataUInteger32:
                        {
                        dContent.push_back( JSONNode( "uint32", *(uint32_t*)parser.GetDataItemData() ) );
                        }
                        break;
                    case DataUInteger64:
                        {
                        dContent.push_back( JSONNode( "uint64", *(uint64_t*)parser.GetDataItemData() ) );
                        }
                        break;
                    case DataInteger32:
                        {
                        dContent.push_back( JSONNode( "int32", *(int32_t*)parser.GetDataItemData() ) );
                        }
                        break;
                    case DataInteger64:
                        {
                        dContent.push_back( JSONNode( "int64", *(int64_t*)parser.GetDataItemData() ) );
                        }
                        break;
                    case DataPrice:
                        {
                        ATPRICE price = *(LPATPRICE)parser.GetDataItemData();
                        JSONNode dat( JSON_NODE );
                        dat.set_name( "priceData" );
                        dat.push_back( JSONNode( "precision", price.precision ) );
                        dat.push_back( JSONNode( "price", price.price ) );
                        dContent.push_back( dat );
                        }
                        break;
                    case DataString:
                        {
                        char* pString = (char*)parser.GetDataItemData();
                        strncpy(data, pString, sizeof(data) - 1);
                        dContent.push_back( JSONNode( "string", data ) );
                        }
                        break;
                    case DataUnicodeString:
                        {
                        wchar16_t* pString = (wchar16_t*)parser.GetDataItemData();
                        std::string s = Helper::ConvertString(pString, Helper::StringLength(pString));
                        strncpy(data, s.c_str(), sizeof(data));
                        dContent.push_back( JSONNode( "unicodeString", data ) );
                        }
                        break;
                    case DataDateTime:
                        {
                        LPATTIME pst = (LPATTIME)parser.GetDataItemData();
                        dContent.push_back( m_jsonifier.jsonifyAtTime( "dateTime", pst ) );
                        }
                        break;
                    default: break;
                    }
                    item.push_back( JSONNode( "dataItemQuoteFieldType", m_jsonifier.getQuoteFieldType( parser.GetDataItemQuoteFieldType() ) ) );
                    item.push_back( JSONNode( "dataItemFieldStatus", m_jsonifier.getFieldStatus( parser.GetDataItemFieldStatus() ) ) );
                    item.push_back( dContent );
                    items.push_back( item );
                    if(parser.MoveToNextDataItem() == false)
                        break;
                }
            }
            rec.push_back( items );
            recs.push_back( rec );
            if(parser.MoveToNextResponse() == false)
                break;
        }
        n.push_back( recs );
    }
    return n;
}


/*virtual*/ void Requestor::OnATMarketMoversStreamResponse(
                                uint64_t origRequest,
                                ATStreamResponseType responseType,
                                LPATMARKET_MOVERS_STREAM_RESPONSE pResponse ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATMarketMoversStream" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );
    n.push_back( jsonifyStreamResponseType( responseType ) );

    m_pInboundMsgs->push( n );
}

JSONNode Requestor::jsonifyStreamResponseType( ATStreamResponseType responseType ) {

    string strResponseType;
    switch(responseType)
    {
    case StreamResponseSuccess: strResponseType = "StreamResponseSuccess"; break;
    case StreamResponseInvalidRequest: strResponseType = "StreamResponseInvalidRequest"; break;
    case StreamResponseDenied: strResponseType = "StreamResponseDenied"; break;
    default: break;
    }
    JSONNode resp( JSON_NODE );
    resp.set_name( "response" );
    resp.push_back( JSONNode( "name", "ATStreamResponseType" ) );
    resp.push_back( JSONNode( "enum", responseType ) );
    resp.push_back( JSONNode( "type", strResponseType ) );
    return resp;
}

/*virtual*/ void Requestor::OnATQuoteStreamResponse(
                                    uint64_t origRequest,
                                    ATStreamResponseType responseType,
                                    LPATQUOTESTREAM_RESPONSE pResponse,
                                    uint32_t responseCount ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATQuoteStream" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );
    n.push_back( jsonifyStreamResponseType( responseType ) );

    JSONNode data( JSON_NODE );
    data.set_name( "data" );
    data.push_back( jsonifyAtQuoteStream( pResponse, responseType ) );
    n.push_back( data );

    m_pInboundMsgs->push( n );
}

JSONNode Requestor::jsonifyAtQuoteStream( LPATQUOTESTREAM_RESPONSE pResponse,
                                          ATStreamResponseType responseType ) {
    JSONNode n( JSON_NODE );
    n.set_name( "ATQuoteStream" );

    if( responseType == StreamResponseSuccess ) {
        ATQuoteStreamResponseParser parser( pResponse );
        parser.MoveToBeginning();

        if(parser.MoveToFirstDataItem() == true) {
            JSONNode items( JSON_ARRAY );
            items.set_name( "dataItems" );
            while( true ) {
                JSONNode item( JSON_NODE );
                item.push_back( m_jsonifier.jsonifyAtSymbol( parser.GetSymbol() ) );
                item.push_back( jsonifyAtSymbolStatus( parser.GetSymbolStatus() ) );
                items.push_back( item );
                if(parser.MoveToNextDataItem() == false)
                    break;
            }
            n.push_back( items );
        }
    }
    return n;
}

/*virtual*/ void Requestor::OnATRequestTimeout( uint64_t origRequest ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATRequestTimeout" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );
    m_pInboundMsgs->push( n );
}

/*virtual*/ void Requestor::OnATLoginResponse( uint64_t origRequest,
                                               LPATLOGIN_RESPONSE pResponse ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATLoginResponse" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );

    // TODO add LPATLOGIN_RESPONSE permissions  parsing
    std::string strLoginResponseType;
    switch(pResponse->loginResponse)
    {
    case LoginResponseSuccess: strLoginResponseType = "LoginResponseSuccess"; break;
    case LoginResponseInvalidUserid: strLoginResponseType = "LoginResponseInvalidUserid"; break;
    case LoginResponseInvalidPassword: strLoginResponseType = "LoginResponseInvalidPassword"; break;
    case LoginResponseInvalidRequest: strLoginResponseType = "LoginResponseInvalidRequest"; break;
    case LoginResponseLoginDenied: strLoginResponseType = "LoginResponseLoginDenied"; break;
    case LoginResponseServerError: strLoginResponseType = "LoginResponseServerError"; break;
    default: strLoginResponseType = "unknown"; break;
    }
    JSONNode resp( JSON_NODE );
    resp.set_name( "response" );
    resp.push_back( JSONNode( "name", "ATQuoteDbResponseType" ) );
    resp.push_back( JSONNode( "enum", pResponse->loginResponse ) );
    resp.push_back( JSONNode( "type", strLoginResponseType ) );
    n.push_back( resp );

    m_pInboundMsgs->push( n );
}

/*virtual*/ void Requestor::OnAtMarketHolidaysResponse( uint64_t origRequest,
                                                        LPATMARKET_HOLIDAYSLIST_ITEM pItems,
                                                        uint32_t itemsCount ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "AtMarketHolidaysResponse" ) );
    n.push_back( JSONNode( "origRequest", origRequest ) );

    JSONNode data( JSON_NODE );
    data.set_name( "data" );
    data.push_back( jsonifyAtMarketHolidays( pItems, itemsCount ) );
    n.push_back( data );

    m_pInboundMsgs->push( n );
}

JSONNode Requestor::jsonifyAtMarketHolidays( LPATMARKET_HOLIDAYSLIST_ITEM pItems,
                                             uint32_t itemsCount ) {
    JSONNode n( JSON_ARRAY );
    n.set_name( "AtMarketHolidays" );

    for(uint32_t i = 0; i < itemsCount; ++i) {
        JSONNode holiday( JSON_NODE );
        holiday.set_name( "data" );
        holiday.push_back( JSONNode( "symbolType", m_jsonifier.getSymbolType(pItems[i].symbolType) ) );
        holiday.push_back( JSONNode( "exchangeType", m_jsonifier.getExchangeType(pItems[i].exchangeType) ));
        holiday.push_back( JSONNode( "countryType", m_jsonifier.getCountryType(pItems[i].countryType) ) );
        holiday.push_back( this->m_jsonifier.jsonifyAtTime( "beginDateTime", &pItems[i].beginDateTime ) );
        holiday.push_back( this->m_jsonifier.jsonifyAtTime( "endDateTime", &pItems[i].endDateTime ) );

        n.push_back( holiday );
    }

    return n;
}
