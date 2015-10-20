// Copyright 2015-present Sheldon Thomas
#include "Requestor.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <node.h>
#include <Shared/ATServerAPIDefines.h>
#include <ActiveTickServerAPI/ATQuoteStreamResponseParser.h>
#include <ActiveTickServerAPI/ATBarHistoryDbResponseParser.h>
#include "NodeActiveTick.h"
#include "protobuf/messages.pb.h"
#include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Requestor::Requestor(const uint64_t session):ActiveTickServerRequestor(session) {
  // session_handle = session;
}

Requestor::~Requestor() {
  
}

void Requestor::OnATBarHistoryDbResponse (  uint64_t origRequest,
                                            ATBarHistoryResponseType responseType,
                                            LPATBARHISTORY_RESPONSE pResponse)
{
  ATBarHistoryDbResponseParser *parser = new ATBarHistoryDbResponseParser(pResponse);
  NodeActiveTickProto::ATBarHistoryDbResponse *dbResponse = new NodeActiveTickProto::ATBarHistoryDbResponse();
  if (parser->MoveToFirstRecord()) {
    for (uint32_t i=0; i<parser->GetRecordCount(); i++) {
      NodeActiveTickProto::ATBarHistoryValue *value = dbResponse->add_value();
      NodeActiveTickProto::ATPrice *open = new NodeActiveTickProto::ATPrice();
      ATPRICE o = parser->GetOpen();
      ProtobufHelper::atprice_insert(&o, open);
      NodeActiveTickProto::ATPrice *high = new NodeActiveTickProto::ATPrice();
      ATPRICE h = parser->GetHigh();
      ProtobufHelper::atprice_insert(&h, high);
      NodeActiveTickProto::ATPrice *low = new NodeActiveTickProto::ATPrice();
      ATPRICE l = parser->GetLow();
      ProtobufHelper::atprice_insert(&l, low);
      NodeActiveTickProto::ATPrice *close = new NodeActiveTickProto::ATPrice();
      ATPRICE c = parser->GetClose();
      ProtobufHelper::atprice_insert(&c, close);
      value->set_allocated_open(open);
      value->set_allocated_high(high);
      value->set_allocated_low(low);
      value->set_allocated_close(close);
      value->set_volume(parser->GetVolume());
      NodeActiveTickProto::ATSymbol *symbol = new NodeActiveTickProto::ATSymbol();
      ATSYMBOL *s = parser->GetSymbol();
      ProtobufHelper::atsymbol_insert(s, symbol);
      value->set_allocated_symbol(symbol);
      ATSymbolStatus status = parser->GetSymbolStatus();
      std::string status_string;
      switch (status) {
        case SymbolStatusSuccess: status_string = "SymbolStatusSuccess"; break;
        case SymbolStatusInvalid: status_string = "SymbolStatusInvalid"; break;
        case SymbolStatusUnavailable: status_string = "SymbolStatusUnavailable"; break;
        case SymbolStatusNoPermission: status_string = "SymbolStatusNoPermission"; break;
        default: status_string = ""; break;
      }
      value->set_status(status_string);
      parser->MoveToNextRecord();
    }
    int bin_size = dbResponse->ByteSize();
    void *buffer = new char[bin_size];
    dbResponse->SerializeToArray(buffer, bin_size);
    MessageStruct* m = new MessageStruct();
    m->data_sz = bin_size;
    m->c_str_data = buffer;
    m->message_id = origRequest;
    std::strcpy(m->messageType, "ATBarHistoryDbResponse");
    (&NodeActiveTick::s_pInstance->handle)->data = m;
    uv_async_send(&NodeActiveTick::s_pInstance->handle);
  }
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
  NodeActiveTickProto::ATQuoteStreamResponse *msg = new NodeActiveTickProto::ATQuoteStreamResponse;
  ATQuoteStreamResponseParser parser = ATQuoteStreamResponseParser(pResponse);
  std::string response = ProtobufHelper::atresponsetype_string(responseType);
  msg->set_quotestreamresponsetype(response);
  msg->set_quoteresponsecount(responseCount);

  parser.MoveToBeginning();
  if (parser.MoveToFirstDataItem()) {
    // parse the first item
    NodeActiveTickProto::ATQuoteStreamResponseItem *item = msg->add_quotestreamitems();
    item->set_responsetype(ProtobufHelper::atresponsetype_string(parser.GetResponseType()));
    NodeActiveTickProto::ATSymbol *symbol = new NodeActiveTickProto::ATSymbol();
    ProtobufHelper::atsymbol_insert(parser.GetSymbol(), symbol);
    item->set_allocated_symbol(symbol);
    item->set_symbolstatus(ProtobufHelper::atsymbolstatus_string(parser.GetSymbolStatus()));
    while (parser.MoveToNextDataItem()) {
      // parse all subsequent items
      NodeActiveTickProto::ATQuoteStreamResponseItem *item = msg->add_quotestreamitems();
      item->set_responsetype(ProtobufHelper::atresponsetype_string(parser.GetResponseType()));
      NodeActiveTickProto::ATSymbol *symbol = new NodeActiveTickProto::ATSymbol();
      ProtobufHelper::atsymbol_insert(parser.GetSymbol(), symbol);
      item->set_allocated_symbol(symbol);
      item->set_symbolstatus(ProtobufHelper::atsymbolstatus_string(parser.GetSymbolStatus()));
    }
  }
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
