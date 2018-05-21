/*
The MIT License (MIT)

Copyright (c) 2015 Jae Yang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
    ATBarHistoryType toATBarHistoryType( std::string barHistoryType );
    
private:
    std::map<std::string, ATExchangeType> m_strToExchange;
    std::map<std::string, ATCountryType> m_strToCountry;
    std::map<std::string, ATStreamRequestType> m_strToStreamRequest;
    std::map<std::string, ATQuoteFieldType> m_strToQuoteField;
    std::map<std::string, ATCursorType> m_strToCursor;
    std::map<std::string, ATConstituentListType> m_strToConstituentList;
    std::map<std::string, ATBarHistoryType> m_strToBarHistoryType;

};