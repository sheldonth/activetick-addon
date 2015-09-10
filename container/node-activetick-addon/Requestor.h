#pragma once
#include <queue>

#include "Session.h"
#include <ActiveTickServerAPI/ActiveTickServerRequestor.h>

#include <node.h>
#include "import/libjson/_internal/Source/JSONNode.h"

using namespace v8;

class Requestor : public ActiveTickServerRequestor
{
public:
    Requestor( const APISession &session,
               std::queue< JSONNode > *pInboundMsgs );
    virtual ~Requestor(void);

private:
    virtual void OnATBarHistoryDbResponse(
                        uint64_t origRequest,
                        ATBarHistoryResponseType responseType,
                        LPATBARHISTORY_RESPONSE pResponse);
    virtual void OnATLoginResponse(
                        uint64_t origRequest,
                        LPATLOGIN_RESPONSE pResponse);
    virtual void OnAtMarketHolidaysResponse(
                        uint64_t origRequest,
                        LPATMARKET_HOLIDAYSLIST_ITEM pItems,
                        uint32_t itemsCount);
    virtual void OnATMarketMoversDbResponse(
                        uint64_t origRequest,
                        ATMarketMoversDbResponseType responseType,
                        LPATMARKET_MOVERSDB_RESPONSE pResponse);
    virtual void OnATMarketMoversStreamResponse(
                        uint64_t origRequest,
                        ATStreamResponseType responseType,
                        LPATMARKET_MOVERS_STREAM_RESPONSE pResponse);
    virtual void OnATQuoteDbResponse(
                        uint64_t origRequest,
                        ATQuoteDbResponseType responseType,
                        LPATQUOTEDB_RESPONSE pResponse,
                        uint32_t responseCount);
    virtual void OnATQuoteStreamResponse(
                        uint64_t origRequest,
                        ATStreamResponseType responseType,
                        LPATQUOTESTREAM_RESPONSE pResponse,
                        uint32_t responseCount);
    virtual void OnATRequestTimeout(uint64_t origRequest);
    virtual void OnATTickHistoryDbResponse(
                        uint64_t origRequest,
                        ATTickHistoryResponseType responseType,
                        LPATTICKHISTORY_RESPONSE pResponse);
    virtual void OnATSectorListResponse(
                        uint64_t origRequest,
                        LPATSECTORLIST_RECORD pRecords,
                        uint32_t recordsCount);
    virtual void OnATConstituentListResponse(
                        uint64_t origRequest,
                        LPATSYMBOL pSymbols,
                        uint32_t symbolsCount);

    JSONNode jsonifyAtBarHistory( LPATBARHISTORY_RESPONSE pResponse );
    JSONNode jsonifyAtTickHistory( LPATTICKHISTORY_RESPONSE pResponse );
    JSONNode jsonifyAtSymbolStatus( ATSymbolStatus status );
    JSONNode jsonifyAtMarketMoversDb( LPATMARKET_MOVERSDB_RESPONSE pResponse );
    JSONNode jsonifyAtQuoteDb( LPATQUOTEDB_RESPONSE pResponse, uint32_t responseCount );
    JSONNode jsonifyStreamResponseType( ATStreamResponseType responseType );
    JSONNode jsonifyAtQuoteStream( LPATQUOTESTREAM_RESPONSE pResponse,
                                   ATStreamResponseType responseType );
    JSONNode jsonifyAtMarketHolidays( LPATMARKET_HOLIDAYSLIST_ITEM pItems, uint32_t itemsCount );

private:
    static Jsonifier m_jsonifier;
    std::queue< JSONNode > *m_pInboundMsgs;
};
