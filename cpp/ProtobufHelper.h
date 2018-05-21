// Copyright 2015-present Sheldon Thomas
#pragma once
#include <node.h>
#include <type_traits>
#include "protobuf/messages.pb.h"
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <Shared/ATServerAPIDefines.h>


class ProtobufHelper {
public:
  static void atsymbol_insert(ATSYMBOL* s, NodeActiveTickProto::ATSymbol *symbol);
  static void atprice_insert(ATPRICE* p, NodeActiveTickProto::ATPrice *price);
  static void attime_insert(ATTIME* t, NodeActiveTickProto::ATTime *time);
  
  static void ATQuoteStream_InsertQuote(ATQUOTESTREAM_QUOTE_UPDATE src,
                                        NodeActiveTickProto::ATQuoteStreamQuoteUpdate* target);
                                        
  static void ATQuoteStream_InsertTrade(ATQUOTESTREAM_TRADE_UPDATE src, 
                                        NodeActiveTickProto::ATQuoteStreamTradeUpdate* target);
                                        
  static void ATQuoteStream_InsertRefresh(ATQUOTESTREAM_REFRESH_UPDATE src,
                                          NodeActiveTickProto::ATQuoteStreamRefreshUpdate* target);
  
  static void AtQuoteStream_InsertMarketMover(ATMARKET_MOVERS_STREAM_UPDATE u, 
                                              NodeActiveTickProto::ATMarketMoversStreamUpdate* stream_update);

  static std::string attradeconditiontype_string(ATTradeConditionType t);
  static std::string atsymbolstatus_string(ATSymbolStatus symbolStatus);
  static std::string atquoteconditiontype_string(ATQuoteConditionType t);
    
};