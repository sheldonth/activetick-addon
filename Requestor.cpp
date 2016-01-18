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
#include <ActiveTickServerAPI/ATQuoteDbResponseParser.h>
#include "NodeActiveTick.h"
#include "protobuf/messages.pb.h"
#include "import/atfeed-cppsdk/example/Helper.h"

using namespace v8;

Requestor::Requestor(const uint64_t session):ActiveTickServerRequestor(session) {
  // session_handle = session;
}

Requestor::~Requestor() {
  
}

void Requestor::OnATQuoteDbResponse ( uint64_t origRequest,
                                      ATQuoteDbResponseType responseType,
                                      LPATQUOTEDB_RESPONSE pResponse,
                                      uint32_t responseCount ) {
  ATQuoteDbResponseParser parser(pResponse, responseCount);
  NodeActiveTickProto::ATQuoteDbResponse quoteDbResponse; // = new NodeActiveTickProto::ATQuoteDbResponse();
  if (NodeActiveTickProto::ATQuoteDbResponse::ATQuoteDbResponseType_IsValid(static_cast<int>(responseType))) // Sample of using native protobuf enums
    quoteDbResponse.set_responsetype(NodeActiveTickProto::ATQuoteDbResponse::ATQuoteDbResponseType(static_cast<int>(responseType)));
  if (parser.MoveToFirstResponse()) {
    if (parser.MoveToFirstDataItem()) {
      for (int32_t response_index = 0; response_index < parser.GetSymbolCount(); response_index++) {
        NodeActiveTickProto::ATQuoteDbResponseData* responseData = quoteDbResponse.add_datum();
        ATSYMBOL currentSymbol = parser.GetSymbol()[0];
        NodeActiveTickProto::ATSymbol* sym = responseData->mutable_symbol();
        ProtobufHelper::atsymbol_insert(& currentSymbol, sym);        
        ATSymbolStatus symbolStatus = parser.GetSymbolStatus();
        responseData->set_symbolstatus(NodeActiveTickProto::ATSymbolStatus(symbolStatus));
        for (int32_t data_index = 0; data_index < parser.GetDataItemCount(); data_index++) {
          NodeActiveTickProto::ATQuoteDbResponseSymbolFieldData* fieldData = responseData->add_symbolfielddata();
          fieldData->set_fieldtype(NodeActiveTickProto::ATQuoteFieldType(parser.GetDataItemQuoteFieldType())); // could be wrong
          fieldData->set_fieldstatus(NodeActiveTickProto::ATQuoteDbResponseSymbolFieldData::ATFieldStatus(parser.GetDataItemFieldStatus()));
          fieldData->set_datatype(NodeActiveTickProto::ATQuoteDbResponseSymbolFieldData::ATDataType(parser.GetDataItemDataType()));
          switch (parser.GetDataItemDataType()) {
            case DataByte: {
              // TODO
            }
            break;
            case DataByteArray: {
              // TODO
            }
            break;
            case DataUInteger32: {
              uint32_t val = *(uint32_t)parser.GetDataItemData();
              fieldData->set_datauinteger32pb(val);
            }
            break;
            case DataUInteger64: {
              uint64_t val = *(uint64_t*)parser.GetDataItemData();
              fieldData->set_datauinteger64pb(val);
            }
            break;
            case DataInteger32: {
              int32_t val = *(int32_t*)parser.GetDataItemData();
              fieldData->set_datainteger32pb(val);
            }
            break;
            case DataInteger64: {
              int64_t val = *(int64_t*)parser.GetDataItemData();
              fieldData->set_datainteger64pb(val);
            }
            break;
            case DataPrice: {
              NodeActiveTickProto::ATPrice* pricePB = fieldData->mutable_datapricepb();
              ATPRICE price = *(LPATPRICE)parser.GetDataItemData();
              ProtobufHelper::atprice_insert(&price, pricePB);
            }
            break;
            case DataString: {
              char* pString = (char*)parser.GetDataItemData();
              std::string s(pString);
              fieldData->set_datastringpb(s);
            }
            break;
            case DataUnicodeString: {
              wchar16_t* pString = (wchar16_t*)parser.GetDataItemData();
              std::string s = Helper::ConvertString(pString, Helper::StringLength(pString));
              fieldData->set_dataunicodestringpb(s);
            }
            break;
            case DataDateTime: {
              ATTIME pst = *(LPATTIME)parser.GetDataItemData();
              NodeActiveTickProto::ATTime* tpb = fieldData->mutable_datadatetimepb();
              ProtobufHelper::attime_insert(&pst, tpb);
            }
            break;
            case DataDouble: {
              // TO DO; Current solution does not work
              // char data[512] = {0};
              const void* r = parser.GetDataItemData();
              int s = sizeof(r);
              double d = -1; // negative one is sentinel value
              memcpy(&d, r, s);
              // sprintf(data, "%f", *(double*)parser.GetDataItemData());
              // const void * q = parser.GetDataItemData();
              // double a = static_cast<const char* const>(parser->GetDataItemData());
              // double d = *(double*);
              fieldData->set_datadoublepb(d);
            }
            break;
          }
          // const char* const ptr = static_cast<const char* const>(parser->GetDataItemData());
          parser.MoveToNextDataItem();
        }
        parser.MoveToNextResponse();
      }
    }
  }
  int bin_size = quoteDbResponse.ByteSize();
  void *buffer = new char[bin_size];
  quoteDbResponse.SerializeToArray(buffer, bin_size);
  MessageStruct* m = new MessageStruct();
  m->data_sz = bin_size;
  m->c_str_data = buffer;
  m->message_id = origRequest;
  std::strcpy(m->messageType, "ATQuoteDbResponse");
  (&NodeActiveTick::s_pInstance->handle)->data = m;
  uv_async_send(&NodeActiveTick::s_pInstance->handle);
  // delete parser;
}

void Requestor::OnATBarHistoryDbResponse (  uint64_t origRequest,
                                            ATBarHistoryResponseType responseType,
                                            LPATBARHISTORY_RESPONSE pResponse) {
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
                                        uint32_t responseCount) {
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
