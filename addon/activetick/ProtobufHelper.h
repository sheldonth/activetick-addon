#pragma once
#import "protobuf/messages.pb.h"
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <Shared/ATServerAPIDefines.h>
#include "import/atfeed-cppsdk/example/Helper.h"
#include <node.h>

using namespace v8;

class ProtobufHelper {
public:
  static void atsymbol_insert(ATSYMBOL* s, NodeActiveTickProto::ATSymbol *symbol) {
    std::string str_symbol_long = Helper::ConvertString(s->symbol, ATSymbolMaxLength);
    std::string str_symbol_short = std::string(str_symbol_long.c_str());
    symbol->set_symbol(str_symbol_short);
    symbol->set_symbol_long(str_symbol_long);
    symbol->set_symboltype(s->symbolType);
    symbol->set_exchangetype(s->exchangeType);
    symbol->set_countrytype(s->countryType);
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