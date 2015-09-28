#pragma once
#include "Requestor.h"
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <ActiveTickServerAPI/ActiveTickServerRequestor.h>
#include <node.h>

using namespace v8;

class Streamer : public ActiveTickStreamListener, public Requestor
{
  virtual ACTIVETICKSERVERAPI_API void ActiveTickStreamListener::OnATStreamTradeUpdate (LPATQUOTESTREAM_TRADE_UPDATE pUpdate);
  virtual ACTIVETICKSERVERAPI_API void ActiveTickStreamListener::OnATStreamQuoteUpdate (LPATQUOTESTREAM_QUOTE_UPDATE pUpdate);
  virtual ACTIVETICKSERVERAPI_API void ActiveTickStreamListener::OnATStreamRefreshUpdate (LPATQUOTESTREAM_REFRESH_UPDATE pUpdate);
  virtual ACTIVETICKSERVERAPI_API void ActiveTickStreamListener::OnATStreamTopMarketMoversUpdate (LPATMARKET_MOVERS_STREAM_UPDATE pUpdate);
}