#pragma once
#include <stdio.h>
#include <cstring>
#include "import/atfeed-cppsdk/include/ActiveTickServerAPI/ActiveTickServerAPI.h"
#include "import/libjson/libjson.h"

// The reason why Jsonifier has static functions is that they are called
//  from within Session.h static functions 
class Jsonifier
{
public:
    Jsonifier( void );
    virtual ~Jsonifier( void );

public:
    static JSONNode jsonifyAtTime( std::string name, LPATTIME pServerTime );
    static JSONNode jsonifyAtSymbol( LPATSYMBOL pSymbol );

    static std::string getSymbolType( uint8_t symbolType );
    static std::string getExchangeType( uint8_t exchangeType );
    static std::string getCountryType( uint8_t countryType );
    static std::string getFieldStatus( uint8_t fieldStatus );
    static std::string getQuoteFieldType( uint8_t quoteFieldType );

};
