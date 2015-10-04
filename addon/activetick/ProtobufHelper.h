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
    wchar16_t* wchar_symbol = s->symbol;
    std::string str_symbol = Helper::ConvertString(wchar_symbol, ATSymbolMaxLength);
    symbol->set_symbol(str_symbol);
    symbol->set_symboltype(s->symbolType);
    symbol->set_exchangetype(s->exchangeType);
    symbol->set_countrytype(s->countryType);
  }
};