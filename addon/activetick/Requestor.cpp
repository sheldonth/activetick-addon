#include "Requestor.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <node.h>
#include <Shared/ATServerAPIDefines.h>
#include <ActiveTickServerAPI/ATQuoteStreamResponseParser.h>
#include "NodeActiveTick.h"
#include "protobuf/messages.pb.h"
#include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Requestor::Requestor(const uint64_t session):ActiveTickServerRequestor(session) {
  std::printf("Can you hear me");
  // session_handle = session;
}

Requestor::~Requestor() {
  
}

void Requestor::OnATConstituentListResponse(uint64_t origRequest, LPATSYMBOL pSymbols, uint32_t symbolsCount) {
  NodeActiveTickProto::ATConstituentResponse *msg = new NodeActiveTickProto::ATConstituentResponse;
  for (uint32_t i = 0; i < symbolsCount; i++) {
    NodeActiveTickProto::ATSymbol *symbol = msg->add_symbols();
    ATSYMBOL s = pSymbols[i];
    ProtobufHelper::atsymbol_insert(&s, symbol);
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
// Either all success or all failure. We pass back responseType
// ATStreamResponseType responseType
// uint16_t dataItemCount
void Requestor::OnATQuoteStreamResponse (uint64_t origRequest,
                                        ATStreamResponseType responseType,
                                        LPATQUOTESTREAM_RESPONSE pResponse,
                                        uint32_t responseCount)
{ 
  // ATQuoteStreamResponseParser parser(pResponse);
  ATQuoteStreamResponseParser parser = ATQuoteStreamResponseParser(pResponse);
  parser.MoveToBeginning();
  if (parser.MoveToFirstDataItem()) {
    // parse the first item
    
    while (parser.MoveToNextDataItem()) {
      // parse all subsequent items
    }
  }
  
  std::string response;
  switch(responseType) {
    case StreamResponseSuccess: response = "StreamResponseSuccess"; break;
    case StreamResponseInvalidRequest: response = "StreamResponseInvalidRequest"; break;
    case StreamResponseDenied: response = "StreamResponseDenied"; break;
    default: response = "Default Error"; break;
  }
  NodeActiveTickProto::ATQuoteStreamResponse *msg = new NodeActiveTickProto::ATQuoteStreamResponse;
  msg->set_quotestreamresponsetype(response);
  msg->set_quoteresponsecount(responseCount);
  int size = msg->ByteSize(); 
  void *buffer = new char[size];
  msg->SerializeToArray(buffer, size);
  MessageStruct* m = new MessageStruct();
  m->data_sz = size;
  m->c_str_data = buffer;
  m->message_id = origRequest;
  std::strcpy(m->messageType, "ATQuoteStreamResponse");
  (&NodeActiveTick::s_pInstance->handle)->data = m;
  uv_async_send(&NodeActiveTick::s_pInstance->handle);
}
