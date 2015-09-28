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

Requestor::Requestor(const uint64_t session):ActiveTickServerRequestor(session) {
    session_handle = session;
}

Requestor::~Requestor() {
  
}

void Requestor::OnATConstituentListResponse(uint64_t origRequest, LPATSYMBOL pSymbols, uint32_t symbolsCount) {
  NodeActiveTickProto::ATConstituentResponse *msg = new NodeActiveTickProto::ATConstituentResponse;
  for (uint32_t i = 0; i < symbolsCount; i++) {
    NodeActiveTickProto::ATSymbol *symbol = msg->add_symbols();
    ATSYMBOL s = pSymbols[i];
    wchar16_t* wchar_symbol = s.symbol;
    std::string str_symbol = Helper::ConvertString(wchar_symbol, ATSymbolMaxLength);
    symbol->set_symbol(str_symbol);
    symbol->set_symboltype(s.symbolType);
    symbol->set_exchangetype(s.exchangeType);
    symbol->set_countrytype(s.countryType);
  }
  int size = msg->ByteSize(); 
  void *buffer = new char[size];
  msg->SerializeToArray(buffer, size);
  MessageStruct* m = new MessageStruct();
  m->data_sz = size;
  m->c_str_data = buffer;
  m->message_id = origRequest;
  std::strcpy(m->messageType, "ATConstituentResponse");
  (&NodeActiveTick::s_pInstance->handle)->data = m;
  uv_async_send(&NodeActiveTick::s_pInstance->handle);
}

// Response that tells you whether your stream request was accepted
// Actual stream callbacks are sent are in ActiveTickStreamListener::OnATStream*
void Requestor::OnATQuoteStreamResponse (uint64_t origRequest,
                                        ATStreamResponseType responseType,
                                        LPATQUOTESTREAM_RESPONSE pResponse,
                                        uint32_t responseCount)
{
  

}
