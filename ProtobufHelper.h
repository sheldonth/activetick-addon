// Copyright 2015-present Sheldon Thomas
#pragma once
#include <node.h>
#include <type_traits>
#import "protobuf/messages.pb.h"
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <Shared/ATServerAPIDefines.h>
#include "import/atfeed-cppsdk/example/Helper.h"


using namespace v8;

class ProtobufHelper {
public:
  // parse ATSYMBOL into NodeActiveTickProto::ATSymbol
  static void atsymbol_insert(ATSYMBOL* s, NodeActiveTickProto::ATSymbol *symbol) {
    std::string str_symbol_long = Helper::ConvertString(s->symbol, ATSymbolMaxLength);
    std::string str_symbol_short = std::string(str_symbol_long.c_str());
    symbol->set_symbol(str_symbol_short);
    symbol->set_symbol_long(str_symbol_long);
    symbol->set_symboltype(s->symbolType);
    symbol->set_exchangetype(s->exchangeType);
    symbol->set_countrytype(s->countryType);
  }
  // parse ATPRICE into NodeActiveTickProto::ATPrice
  static void atprice_insert(ATPRICE* p, NodeActiveTickProto::ATPrice *price) {
    price->set_price(p->price);
    price->set_precision(p->precision);
  }
  // parse ATTIME into NodeActiveTickProto::ATTime
  static void attime_insert(ATTIME* t, NodeActiveTickProto::ATTime *time) {
    time->set_year(t->year);
    time->set_month(t->month);
    time->set_dayofweek(t->dayOfWeek);
    time->set_day(t->day);
    time->set_hour(t->hour);
    time->set_minute(t->minute);
    time->set_second(t->second);
    time->set_milliseconds(t->milliseconds);
  }
  
  // return NodeActiveTickProto::ATQuoteStreamTradeUpdate from ATQUOTESTREAM_TRADE_UPDATE
  static NodeActiveTickProto::ATQuoteStreamTradeUpdate* quotestreamtradeupdate(ATQUOTESTREAM_TRADE_UPDATE u) {
    NodeActiveTickProto::ATQuoteStreamTradeUpdate *q = new NodeActiveTickProto::ATQuoteStreamTradeUpdate();
    NodeActiveTickProto::ATSymbol *symbol = new NodeActiveTickProto::ATSymbol();
    atsymbol_insert(&u.symbol, symbol);
    q->set_allocated_tradesymbol(symbol);
    q->set_trademessageflags(u.flags);
    for (int i = 0; i < ATTradeConditionsCount; i++) {
        q->add_tradeconditiontype(attradeconditiontype_string(u.condition[i]));
    }
    NodeActiveTickProto::ATPrice *price = new NodeActiveTickProto::ATPrice();
    atprice_insert(&u.lastPrice, price);
    q->set_allocated_tradeprice(price);
    q->set_tradesize(u.lastSize);
    NodeActiveTickProto::ATTime *timePtr = new NodeActiveTickProto::ATTime();
    attime_insert(&u.lastDateTime, timePtr);
    q->set_allocated_tradetime(timePtr);
    // q->set_tradeexchange(a); TODO
    return q;
  }
  
  static std::string attradeconditiontype_string(ATTradeConditionType t) {
    std::string response;
    switch(t) {
      case TradeConditionRegular: response = "TradeConditionRegular"; break;
      case TradeConditionAcquisition: response = "TradeConditionAcquisition"; break;
      case TradeConditionAveragePrice: response = "TradeConditionAveragePrice"; break;
      case TradeConditionAutomaticExecution: response = "TradeConditionAutomaticExecution"; break;
      case TradeConditionBunched: response = "TradeConditionBunched"; break;
      case TradeConditionBunchSold: response = "TradeConditionBunchSold"; break;
      case TradeConditionCAPElection: response = "TradeConditionCAPElection"; break;
      case TradeConditionCash: response = "TradeConditionCash"; break;
      case TradeConditionClosing: response = "TradeConditionClosing"; break;
      case TradeConditionCross: response = "TradeConditionCross"; break;
      case TradeConditionDerivativelyPriced: response = "TradeConditionDerivativelyPriced"; break;
      case TradeConditionDistribution: response = "TradeConditionDistribution"; break;
      case TradeConditionFormT: response = "TradeConditionFormT"; break;
      case TradeConditionFormTOutOfSequence: response = "TradeConditionFormTOutOfSequence"; break;
      case TradeConditionInterMarketSweep: response = "TradeConditionInterMarketSweep"; break;
      case TradeConditionMarketCenterOfficialClose: response = "TradeConditionMarketCenterOfficialClose"; break;
      case TradeConditionMarketCenterOfficialOpen: response = "TradeConditionMarketCenterOfficialOpen"; break;
      case TradeConditionMarketCenterOpening: response = "TradeConditionMarketCenterOpening"; break;
      case TradeConditionMarketCenterReOpenning: response = "TradeConditionMarketCenterReOpenning"; break;
      case TradeConditionMarketCenterClosing: response = "TradeConditionMarketCenterClosing"; break;
      case TradeConditionNextDay: response = "TradeConditionNextDay"; break;
      case TradeConditionPriceVariation: response = "TradeConditionPriceVariation"; break;
      case TradeConditionPriorReferencePrice: response = "TradeConditionPriorReferencePrice"; break;
      case TradeConditionRule155Amex: response = "TradeConditionRule155Amex"; break;
      case TradeConditionRule127Nyse: response = "TradeConditionRule127Nyse"; break;
      case TradeConditionOpening: response = "TradeConditionOpening"; break;
      case TradeConditionOpened: response = "TradeConditionOpened"; break;
      case TradeConditionRegularStoppedStock: response = "TradeConditionRegularStoppedStock"; break;
      case TradeConditionReOpening: response = "TradeConditionReOpening"; break;
      case TradeConditionSeller: response = "TradeConditionSeller"; break;
      case TradeConditionSoldLast: response = "TradeConditionSoldLast"; break;
      case TradeConditionSoldLastStoppedStock: response = "TradeConditionSoldLastStoppedStock"; break;
      case TradeConditionSoldOutOfSequence: response = "TradeConditionSoldOutOfSequence"; break;
      case TradeConditionSoldOutOfSequenceStoppedStock: response = "TradeConditionSoldOutOfSequenceStoppedStock"; break;
      case TradeConditionSplit: response = "TradeConditionSplit"; break;
      case TradeConditionStockOption: response = "TradeConditionStockOption"; break;
      case TradeConditionYellowFlag: response = "TradeConditionYellowFlag"; break;
      default: response = ""; break;
    }
    return response;
  }
  
  static std::string atresponsetype_string(ATStreamResponseType responseType) {
    std::string response;
    switch(responseType) {
      case StreamResponseSuccess: response = "StreamResponseSuccess"; break;
      case StreamResponseInvalidRequest: response = "StreamResponseInvalidRequest"; break;
      case StreamResponseDenied: response = "StreamResponseDenied"; break;
      default: response = "Default Error"; break;
    }
    return response;
  }
  
  static std::string atsymbolstatus_string(ATSymbolStatus symbolStatus) {
    std::string response;
    switch(symbolStatus) {
      case SymbolStatusSuccess: response = "SymbolStatusSuccess"; break;
      case SymbolStatusInvalid: response = "SymbolStatusInvalid"; break;
      case SymbolStatusUnavailable: response = "SymbolStatusUnavailable"; break;
      case SymbolStatusNoPermission: response = "SymbolStatusNoPermission"; break;
      default: response = "Default Error"; break;
    }
    return response;
  }
  
};