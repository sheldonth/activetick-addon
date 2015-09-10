#pragma once
#include <queue>

#include <ActiveTickServerAPI/ActiveTickStreamListener.h>
#include "Requestor.h"
#include "Session.h"

#include <node.h>
#include "import/libjson/_internal/Source/JSONNode.h"

using namespace v8;

class Streamer: public ActiveTickStreamListener,
                public Requestor
{
public:
    Streamer( const APISession &session, std::queue< JSONNode > *pInboundMsgs );
    virtual ~Streamer(void);

private:
    virtual void OnATStreamTradeUpdate( LPATQUOTESTREAM_TRADE_UPDATE pUpdate );
    virtual void OnATStreamQuoteUpdate( LPATQUOTESTREAM_QUOTE_UPDATE pUpdate );
    virtual void OnATStreamRefreshUpdate(
                        LPATQUOTESTREAM_REFRESH_UPDATE pUpdate);
    virtual void OnATStreamTopMarketMoversUpdate(
                        LPATMARKET_MOVERS_STREAM_UPDATE pUpdate);

    JSONNode jsonifyAtQuoteStreamTradeUpdate( LPATQUOTESTREAM_TRADE_UPDATE pUpdate );
    JSONNode jsonifyAtQuoteStreamQuoteUpdate( LPATQUOTESTREAM_QUOTE_UPDATE pUpdate );
    JSONNode jsonifyAtMarketMoversStreamUpdate( LPATMARKET_MOVERS_STREAM_UPDATE pUpdate );
    JSONNode jsonifyAtStreamRefreshUpdate( LPATQUOTESTREAM_REFRESH_UPDATE pUpdate );

private:
    const APISession &m_session;
    static Jsonifier m_jsonifier;
    std::queue< JSONNode > *m_pInboundMsgs;
};
