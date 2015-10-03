// Copyright 2015 Sheldon Thomas
// File Not currently active

#pragma once
#include "Requestor.h"
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <ActiveTickServerAPI/ActiveTickServerRequestor.h>
#include <ActiveTickServerAPI/ActiveTickStreamListener.h>
#include <node.h>

using namespace v8;

class Streamor : public ActiveTickStreamListener,
                 public Requestor
{
  public:
    Streamor();
    virtual ~Streamor(void);
  
  private:
    uint64_t session_handle;

  virtual ACTIVETICKSERVERAPI_API void OnATStreamTradeUpdate (LPATQUOTESTREAM_TRADE_UPDATE pUpdate);
  virtual ACTIVETICKSERVERAPI_API void OnATStreamQuoteUpdate (LPATQUOTESTREAM_QUOTE_UPDATE pUpdate);
  virtual ACTIVETICKSERVERAPI_API void OnATStreamRefreshUpdate (LPATQUOTESTREAM_REFRESH_UPDATE pUpdate);
  virtual ACTIVETICKSERVERAPI_API void OnATStreamTopMarketMoversUpdate (LPATMARKET_MOVERS_STREAM_UPDATE pUpdate);
};