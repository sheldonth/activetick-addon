// Copyright 2015 Sheldon Thomas

#include "Requestor.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <node.h>
#include "NodeActiveTick.h"
#include "protobuf/messages.pb.h"
#include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Streamor::Streamor(const uint64_t session) : ActiveTickStreamListener(session), Requestor(session) {
  session_handle = session;
}

Streamor::~Streamor() {
  
}

void Streamor::OnATStreamTradeUpdate (LPATQUOTESTREAM_TRADE_UPDATE pUpdate) {
  
}

void Streamor::OnATStreamQuoteUpdate (LPATQUOTESTREAM_QUOTE_UPDATE pUpdate) {
  
}

void Streamor::OnATStreamRefreshUpdate (LPATQUOTESTREAM_REFRESH_UPDATE pUpdate) {
  
}

void Streamor::OnATStreamTopMarketMoversUpdate (LPATMARKET_MOVERS_STREAM_UPDATE pUpdate) {
  
}
