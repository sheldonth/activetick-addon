#import "ProtobufHelper.h"
#include "example/Helper.h"

// parse ATSYMBOL into NodeActiveTickProto::ATSymbol
void ProtobufHelper::atsymbol_insert(ATSYMBOL* s, NodeActiveTickProto::ATSymbol *symbol) {
  std::string str_symbol_long = Helper::ConvertString(s->symbol, ATSymbolMaxLength);
  std::string str_symbol_short = std::string(str_symbol_long.c_str());
  symbol->set_symbol(str_symbol_short);
  symbol->set_symboltype(s->symbolType);
  symbol->set_exchangetype(s->exchangeType);
  symbol->set_countrytype(s->countryType);
}

// parse ATPRICE into NodeActiveTickProto::ATPrice
void ProtobufHelper::atprice_insert(ATPRICE* p, NodeActiveTickProto::ATPrice *price) {
  price->set_price(p->price);
  price->set_precision(p->precision);
}
// parse ATTIME into NodeActiveTickProto::ATTime
void ProtobufHelper::attime_insert(ATTIME* t, NodeActiveTickProto::ATTime *time) {
  time->set_year(t->year);
  time->set_month(t->month);
  time->set_dayofweek(t->dayOfWeek);
  time->set_day(t->day);
  time->set_hour(t->hour);
  time->set_minute(t->minute);
  time->set_second(t->second);
  time->set_milliseconds(t->milliseconds);
}

void ProtobufHelper::AtQuoteStream_InsertMarketMover(ATMARKET_MOVERS_STREAM_UPDATE u, 
                                                     NodeActiveTickProto::ATMarketMoversStreamUpdate* stream_update) {
  attime_insert(&u.lastUpdateTime, stream_update->mutable_lastupdatedtime());
  NodeActiveTickProto::ATMarketMoversRecord *marketMovers = stream_update->mutable_marketmovers();
  ATMARKET_MOVERS_RECORD record = u.marketMovers;
  atsymbol_insert(&record.symbol, marketMovers->mutable_symbol());
  marketMovers->set_status(atsymbolstatus_string(record.status));
  for (int i=0; i < ATMarketMoversMaxRecords; i++) {
    ATMARKET_MOVERS_ITEM item = record.items[i];
    NodeActiveTickProto::ATMarketMoversItem *it = marketMovers->add_item();
    atsymbol_insert(&item.symbol, it->mutable_symbol());
    // TODO (sheldonth): fix including Helper::ConvertString
    // std::string str_symbol_long = Helper::ConvertString(item.symbol, ATSymbolMaxLength);
    // it->set_name(str_symbol_long);
    atprice_insert(&item.lastPrice, it->mutable_lastprice());
    atprice_insert(&item.closePrice, it->mutable_closeprice());
    it->set_volume(item.volume);
    attime_insert(&item.lastDateTime, it->mutable_lastdatetime());    
  }
}

void ProtobufHelper::ATQuoteStream_InsertRefresh(ATQUOTESTREAM_REFRESH_UPDATE src, NodeActiveTickProto::ATQuoteStreamRefreshUpdate* target) {
  NodeActiveTickProto::ATSymbol *symbol = target->mutable_symbol();
  atsymbol_insert(&src.symbol, symbol);
  NodeActiveTickProto::ATPrice* lastPrice = target->mutable_lastprice();
  NodeActiveTickProto::ATPrice* openPrice = target->mutable_openprice();
  NodeActiveTickProto::ATPrice* highPrice = target->mutable_highprice();
  NodeActiveTickProto::ATPrice* lowPrice = target->mutable_lowprice();
  NodeActiveTickProto::ATPrice* closePrice = target->mutable_closeprice();
  NodeActiveTickProto::ATPrice* prevClosePrice = target->mutable_prevcloseprice();
  NodeActiveTickProto::ATPrice* afterMarketClosePrice = target->mutable_aftermarketcloseprice();
  NodeActiveTickProto::ATPrice* bidPrice = target->mutable_bidprice();
  NodeActiveTickProto::ATPrice* askPrice = target->mutable_askprice();
  atprice_insert(&src.lastPrice, lastPrice);
  atprice_insert(&src.openPrice, openPrice);
  atprice_insert(&src.highPrice, highPrice);
  atprice_insert(&src.lowPrice, lowPrice);
  atprice_insert(&src.closePrice, closePrice);
  atprice_insert(&src.prevClosePrice, prevClosePrice);
  atprice_insert(&src.afterMarketClosePrice, afterMarketClosePrice);
  atprice_insert(&src.bidPrice, bidPrice);
  atprice_insert(&src.askPrice, askPrice);
  target->set_bidsize(src.bidSize);
  target->set_asksize(src.askSize);
  target->set_lastsize(src.lastSize);
  target->set_volume(src.volume);
}

void ProtobufHelper::ATQuoteStream_InsertQuote(ATQUOTESTREAM_QUOTE_UPDATE src, NodeActiveTickProto::ATQuoteStreamQuoteUpdate* target) {
  NodeActiveTickProto::ATSymbol* symbol = target->mutable_quotesymbol();
  atsymbol_insert(&src.symbol, symbol);
  target->set_quotecondition(atquoteconditiontype_string(src.condition));
  NodeActiveTickProto::ATPrice* bid_price = target->mutable_quotebidprice();
  atprice_insert(&src.bidPrice, bid_price);
  NodeActiveTickProto::ATPrice *ask_price = target->mutable_quoteaskprice();
  atprice_insert(&src.askPrice, ask_price);
  target->set_quoteasksize(src.askSize);
  target->set_quotebidsize(src.bidSize);
  NodeActiveTickProto::ATTime *t = target->mutable_quotetime();
  attime_insert(&src.quoteDateTime, t);
}

void ProtobufHelper::ATQuoteStream_InsertTrade(ATQUOTESTREAM_TRADE_UPDATE src, NodeActiveTickProto::ATQuoteStreamTradeUpdate* target) {
  NodeActiveTickProto::ATSymbol *symbol = target->mutable_tradesymbol();
  atsymbol_insert(&src.symbol, symbol);
  target->set_trademessageflags(src.flags);
  for (int i = 0; i < ATTradeConditionsCount; i++) {
      target->add_tradeconditiontype(attradeconditiontype_string(src.condition[i]));
  }
  NodeActiveTickProto::ATPrice *price = target->mutable_tradeprice();
  atprice_insert(&src.lastPrice, price);
  target->set_tradesize(src.lastSize);
  NodeActiveTickProto::ATTime *timePtr = target->mutable_tradetime();
  attime_insert(&src.lastDateTime, timePtr);
  // q->set_tradeexchange(a); TODO
}

std::string ProtobufHelper::attradeconditiontype_string(ATTradeConditionType t) {
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

std::string ProtobufHelper::atsymbolstatus_string(ATSymbolStatus symbolStatus) {
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

std::string ProtobufHelper::atquoteconditiontype_string(ATQuoteConditionType t) {
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



