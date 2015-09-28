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

void ActiveTickStreamListener::OnATStreamTradeUpdate (LPATQUOTESTREAM_TRADE_UPDATE pUpdate) {
  
}

void ActiveTickStreamListener::OnATStreamQuoteUpdate (LPATQUOTESTREAM_QUOTE_UPDATE pUpdate) {
  
}

void ActiveTickStreamListener::OnATStreamRefreshUpdate (LPATQUOTESTREAM_REFRESH_UPDATE pUpdate) {
  
}

void ActiveTickStreamListener::OnATStreamTopMarketMoversUpdate (LPATMARKET_MOVERS_STREAM_UPDATE pUpdate) {
  
}
