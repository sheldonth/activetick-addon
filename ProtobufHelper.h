// Copyright 2015-present Sheldon Thomas
#pragma once
#include <node.h>
#include <type_traits>
#include "protobuf/messages.pb.h"
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
  
  static NodeActiveTickProto::ATMarketMoversStreamUpdate *atmarketmoversstreamupdate(ATMARKET_MOVERS_STREAM_UPDATE u) {
    NodeActiveTickProto::ATMarketMoversStreamUpdate *m = new NodeActiveTickProto::ATMarketMoversStreamUpdate();
    // todo
    return m;
  }
  
  static NodeActiveTickProto::ATQuoteStreamRefreshUpdate* atquotestreamrefreshquote(ATQUOTESTREAM_REFRESH_UPDATE u) {
    NodeActiveTickProto::ATQuoteStreamRefreshUpdate *r = new NodeActiveTickProto::ATQuoteStreamRefreshUpdate();
    NodeActiveTickProto::ATSymbol *symbol = new NodeActiveTickProto::ATSymbol();
    atsymbol_insert(&u.symbol, symbol);
    r->set_allocated_symbol(symbol);
    NodeActiveTickProto::ATPrice *lastPrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *openPrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *highPrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *lowPrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *closePrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *prevClosePrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *afterMarketClosePrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *bidPrice = new NodeActiveTickProto::ATPrice();
    NodeActiveTickProto::ATPrice *askPrice =  new NodeActiveTickProto::ATPrice();
    atprice_insert(&u.lastPrice, lastPrice);
    atprice_insert(&u.openPrice, openPrice);
    atprice_insert(&u.highPrice, highPrice);
    atprice_insert(&u.lowPrice, lowPrice);
    atprice_insert(&u.closePrice, closePrice);
    atprice_insert(&u.prevClosePrice, prevClosePrice);
    atprice_insert(&u.afterMarketClosePrice, afterMarketClosePrice);
    atprice_insert(&u.bidPrice, bidPrice);
    atprice_insert(&u.askPrice, askPrice);
    r->set_allocated_openprice(openPrice);
    r->set_allocated_lastprice(lastPrice);
    r->set_allocated_highprice(highPrice);
    r->set_allocated_lowprice(lowPrice);
    r->set_allocated_closeprice(closePrice);
    r->set_allocated_prevcloseprice(prevClosePrice);
    r->set_allocated_aftermarketcloseprice(afterMarketClosePrice);
    r->set_allocated_bidprice(bidPrice);
    r->set_allocated_askprice(askPrice);
    r->set_bidsize(u.bidSize);
    r->set_asksize(u.askSize);
    r->set_lastsize(u.lastSize);
    r->set_volume(u.volume);
    return r;
  }
  
  // return NodeActiveTickProto::ATQuoteStreamTradeUpdate from ATQUOTESTREAM_TRADE_UPDATE
  static NodeActiveTickProto::ATQuoteStreamTradeUpdate* atquotestreamtradeupdate(ATQUOTESTREAM_TRADE_UPDATE u) {
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
  
  static NodeActiveTickProto::ATQuoteStreamQuoteUpdate* atquotestreamquoteupdate(ATQUOTESTREAM_QUOTE_UPDATE u) {
    NodeActiveTickProto::ATQuoteStreamQuoteUpdate *quoteUpdate = new NodeActiveTickProto::ATQuoteStreamQuoteUpdate();
    NodeActiveTickProto::ATSymbol *symbol = new NodeActiveTickProto::ATSymbol();
    atsymbol_insert(&u.symbol, symbol);
    quoteUpdate->set_allocated_quotesymbol(symbol);
    quoteUpdate->set_quotecondition(atquoteconditiontype_string(u.condition));
    NodeActiveTickProto::ATPrice *bid_price = new NodeActiveTickProto::ATPrice();
    atprice_insert(&u.bidPrice, bid_price);
    quoteUpdate->set_allocated_quotebidprice(bid_price);
    quoteUpdate->set_quotebidsize(u.bidSize);
    NodeActiveTickProto::ATPrice *ask_price = new NodeActiveTickProto::ATPrice();
    atprice_insert(&u.askPrice, ask_price);
    quoteUpdate->set_allocated_quoteaskprice(ask_price);
    quoteUpdate->set_quoteasksize(u.askSize);
    NodeActiveTickProto::ATTime *tim = new NodeActiveTickProto::ATTime();
    attime_insert(&u.quoteDateTime, tim);
    quoteUpdate->set_allocated_quotetime(tim);
    return quoteUpdate;
  }
  
  static std::string atquoteconditiontype_string(ATQuoteConditionType t) {
    std::string response;
    switch (t) {
      case QuoteConditionRegular: response = "QuoteConditionRegular"; break;
        case QuoteConditionRegularTwoSidedOpen: response = "QuoteConditionRegularTwoSidedOpen"; break;
        case QuoteConditionRegularOneSidedOpen: response = "QuoteConditionRegularOneSidedOpen"; break;
        case QuoteConditionSlowAsk: response = "QuoteConditionSlowAsk"; break;
        case QuoteConditionSlowBid: response = "QuoteConditionSlowBid"; break;
        case QuoteConditionSlowBidAsk: response = "QuoteConditionSlowBidAsk"; break;
        case QuoteConditionSlowDueLRPBid: response = "QuoteConditionSlowDueLRPBid"; break;
        case QuoteConditionSlowDueLRPAsk: response = "QuoteConditionSlowDueLRPAsk"; break;
        case QuoteConditionSlowDueNYSELRP: response = "QuoteConditionSlowDueNYSELRP"; break;
        case QuoteConditionSlowDueSetSlowListBidAsk: response = "QuoteConditionSlowDueSetSlowListBidAsk"; break;
        case QuoteConditionManualAskAutomaticBid: response = "QuoteConditionManualAskAutomaticBid"; break;
        case QuoteConditionManualBidAutomaticAsk: response = "QuoteConditionManualBidAutomaticAsk"; break;
        case QuoteConditionManualBidAndAsk: response = "QuoteConditionManualBidAndAsk"; break;
        case QuoteConditionOpening: response = "QuoteConditionOpening"; break;
        case QuoteConditionClosing: response = "QuoteConditionClosing"; break;
        case QuoteConditionClosed: response = "QuoteConditionClosed"; break;
        case QuoteConditionResume: response = "QuoteConditionResume"; break;
        case QuoteConditionFastTrading: response = "QuoteConditionFastTrading"; break;
        case QuoteConditionTradingRangeIndication: response = "QuoteConditionTradingRangeIndication"; break;
        case QuoteConditionMarketMakerQuotesClosed: response = "QuoteConditionMarketMakerQuotesClosed"; break;
        case QuoteConditionNonFirm: response = "QuoteConditionNonFirm"; break;
        case QuoteConditionNewsDissemination: response = "QuoteConditionNewsDissemination"; break;
        case QuoteConditionOrderInflux: response = "QuoteConditionOrderInflux"; break;
        case QuoteConditionOrderImbalance: response = "QuoteConditionOrderImbalance"; break;
        case QuoteConditionDueToRelatedSecurityNewsDissemination: response = "QuoteConditionDueToRelatedSecurityNewsDissemination"; break;
        case QuoteConditionDueToRelatedSecurityNewsPending: response = "QuoteConditionDueToRelatedSecurityNewsPending"; break;
        case QuoteConditionAdditionalInformation: response = "QuoteConditionAdditionalInformation"; break;
        case QuoteConditionNewsPending: response = "QuoteConditionNewsPending"; break;
        case QuoteConditionAdditionalInformationDueToRelatedSecurity: response = "QuoteConditionAdditionalInformationDueToRelatedSecurity"; break;
        case QuoteConditionDueToRelatedSecurity: response = "QuoteConditionDueToRelatedSecurity"; break;
        case QuoteConditionInViewOfCommon: response = "QuoteConditionInViewOfCommon"; break;
        case QuoteConditionEquipmentChangeover: response = "QuoteConditionEquipmentChangeover"; break;
        case QuoteConditionNoOpenNoResume: response = "QuoteConditionNoOpenNoResume"; break;
        case QuoteConditionSubPennyTrading: response = "QuoteConditionSubPennyTrading"; break;
        case QuoteConditionAutomatedBidNoOfferNoBid: response = "QuoteConditionAutomatedBidNoOfferNoBid"; break;
        default: response = ""; break;
    }
    return response;
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