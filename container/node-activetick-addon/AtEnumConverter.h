#pragma once
#include <string>
#include <map>
#include "./import/atfeed-cppsdk/include/Shared/ATServerAPIDefines.h"

class AtEnumConverter {

public:
    AtEnumConverter();
    ~AtEnumConverter();

    ATExchangeType toAtExchange( std::string exchangeType );
    ATCountryType toAtCountry( std::string countryType );
    ATStreamRequestType toAtStreamRequest( std::string requestType );
    ATQuoteFieldType toAtQuoteField( std::string quoteFieldType );
    ATCursorType toAtCursor( std::string cursorType );
    ATConstituentListType toAtConstituentList( std::string constituentListType );

private:
    std::map<std::string, ATExchangeType> m_strToExchange;
    std::map<std::string, ATCountryType> m_strToCountry;
    std::map<std::string, ATStreamRequestType> m_strToStreamRequest;
    std::map<std::string, ATQuoteFieldType> m_strToQuoteField;
    std::map<std::string, ATCursorType> m_strToCursor;
    std::map<std::string, ATConstituentListType> m_strToConstituentList;

};