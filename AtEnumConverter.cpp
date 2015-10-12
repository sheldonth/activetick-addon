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

#include "AtEnumConverter.h"
#include <utility>

AtEnumConverter::AtEnumConverter() {
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeAMEX",ExchangeAMEX) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNasdaqOmxBx",ExchangeNasdaqOmxBx) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNationalStockExchange",ExchangeNationalStockExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeFinraAdf",ExchangeFinraAdf) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeCQS",ExchangeCQS) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeForex",ExchangeForex) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeInternationalSecuritiesExchange",ExchangeInternationalSecuritiesExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeEdgaExchange",ExchangeEdgaExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeEdgxExchange",ExchangeEdgxExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeChicagoStockExchange",ExchangeChicagoStockExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNyseEuronext",ExchangeNyseEuronext) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNyseArcaExchange",ExchangeNyseArcaExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNasdaqOmx",ExchangeNasdaqOmx) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeCTS",ExchangeCTS) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeCTANasdaqOMX",ExchangeCTANasdaqOMX) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOTCBB",ExchangeOTCBB) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNNOTC",ExchangeNNOTC) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeChicagoBoardOptionsExchange",ExchangeChicagoBoardOptionsExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeNasdaqOmxPhlx",ExchangeNasdaqOmxPhlx) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeBatsYExchange",ExchangeBatsYExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeBatsExchange",ExchangeBatsExchange) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeCanadaToronto",ExchangeCanadaToronto) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeCanadaVenture",ExchangeCanadaVenture) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOpra",ExchangeOpra) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOptionBoston",ExchangeOptionBoston) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOptionCboe",ExchangeOptionCboe) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOptionNyseArca",ExchangeOptionNyseArca) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOptionC2",ExchangeOptionC2) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeOptionNasdaqOmxBx",ExchangeOptionNasdaqOmxBx) );
    this->m_strToExchange.insert( std::pair<std::string,ATExchangeType>("ExchangeComposite",ExchangeComposite) );

    this->m_strToCountry.insert( std::pair<std::string,ATCountryType>("CountryInternational",CountryInternational) );
    this->m_strToCountry.insert( std::pair<std::string,ATCountryType>("CountryUnitedStates",CountryUnitedStates) );
    this->m_strToCountry.insert( std::pair<std::string,ATCountryType>("CountryCanada",CountryCanada) );

    this->m_strToStreamRequest.insert( std::pair<std::string,ATStreamRequestType>("StreamRequestSubscribe",StreamRequestSubscribe) );
    this->m_strToStreamRequest.insert( std::pair<std::string,ATStreamRequestType>("StreamRequestUnsubscribe",StreamRequestUnsubscribe) );
    this->m_strToStreamRequest.insert( std::pair<std::string,ATStreamRequestType>("StreamRequestSubscribeQuotesOnly",StreamRequestSubscribeQuotesOnly) );
    this->m_strToStreamRequest.insert( std::pair<std::string,ATStreamRequestType>("StreamRequestUnsubscribeQuotesOnly",StreamRequestUnsubscribeQuotesOnly) );
    this->m_strToStreamRequest.insert( std::pair<std::string,ATStreamRequestType>("StreamRequestSubscribeTradesOnly",StreamRequestSubscribeTradesOnly) );
    this->m_strToStreamRequest.insert( std::pair<std::string,ATStreamRequestType>("StreamRequestUnsubscribeTradesOnly",StreamRequestUnsubscribeTradesOnly) );

    //Intraday fields
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldSymbol", QuoteFieldSymbol) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldOpenPrice", QuoteFieldOpenPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldPreviousClosePrice", QuoteFieldPreviousClosePrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldClosePrice", QuoteFieldClosePrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLastPrice", QuoteFieldLastPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBidPrice", QuoteFieldBidPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldAskPrice", QuoteFieldAskPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldHighPrice", QuoteFieldHighPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLowPrice", QuoteFieldLowPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldDayHighPrice", QuoteFieldDayHighPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldDayLowPrice", QuoteFieldDayLowPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldPreMarketOpenPrice", QuoteFieldPreMarketOpenPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldExtendedHoursLastPrice", QuoteFieldExtendedHoursLastPrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldAfterMarketClosePrice", QuoteFieldAfterMarketClosePrice) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBidExchange", QuoteFieldBidExchange) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldAskExchange", QuoteFieldAskExchange) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLastExchange", QuoteFieldLastExchange) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLastCondition", QuoteFieldLastCondition) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldQuoteCondition", QuoteFieldQuoteCondition) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLastTradeDateTime", QuoteFieldLastTradeDateTime) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLastQuoteDateTime", QuoteFieldLastQuoteDateTime) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldDayHighDateTime", QuoteFieldDayHighDateTime) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldDayLowDateTime", QuoteFieldDayLowDateTime) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldLastSize", QuoteFieldLastSize) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBidSize", QuoteFieldBidSize) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldAskSize", QuoteFieldAskSize) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldVolume", QuoteFieldVolume) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldPreMarketVolume", QuoteFieldPreMarketVolume) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldAfterMarketVolume", QuoteFieldAfterMarketVolume) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldTradeCount", QuoteFieldTradeCount) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldPreMarketTradeCount", QuoteFieldPreMarketTradeCount) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldAfterMarketTradeCount", QuoteFieldAfterMarketTradeCount) );

    //Profile fields
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldProfileShortName", QuoteFieldProfileShortName) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldProfilePrimaryExchange", QuoteFieldProfilePrimaryExchange) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldProfileLongName", QuoteFieldProfileLongName) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldProfileSector", QuoteFieldProfileSector) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldProfileIndustry", QuoteFieldProfileIndustry) );

    //Option fields
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldOptionOpenInterest", QuoteFieldOptionOpenInterest) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldOptionStrikePrice", QuoteFieldOptionStrikePrice) );

    //Financials - Income statement fields
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSFromContinuingOperations", QuoteFieldIncomeStatementBasicEPSFromContinuingOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSFromDiscontinuedOperations", QuoteFieldIncomeStatementBasicEPSFromDiscontinuedOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSFromTotalOperations", QuoteFieldIncomeStatementBasicEPSFromTotalOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSFromExtraordinaryIncome", QuoteFieldIncomeStatementBasicEPSFromExtraordinaryIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSFromCumEffectOfAccountingChange", QuoteFieldIncomeStatementBasicEPSFromCumEffectOfAccountingChange) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSFromOtherGains", QuoteFieldIncomeStatementBasicEPSFromOtherGains) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicEPSTotal", QuoteFieldIncomeStatementBasicEPSTotal) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementBasicNormalizedNetIncomePerShare", QuoteFieldIncomeStatementBasicNormalizedNetIncomePerShare) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedEPSFromContinuingOperations", QuoteFieldIncomeStatementDilutedEPSFromContinuingOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedEPSFromDiscontinuedOperations", QuoteFieldIncomeStatementDilutedEPSFromDiscontinuedOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedEPSFromTotalOperations", QuoteFieldIncomeStatementDilutedEPSFromTotalOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedEPSFromExtraordinaryIncome", QuoteFieldIncomeStatementDilutedEPSFromExtraordinaryIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedEPSFromOtherGains", QuoteFieldIncomeStatementDilutedEPSFromOtherGains) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedEPSTotal", QuoteFieldIncomeStatementDilutedEPSTotal) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDilutedNormalizedNetIncomePerShare", QuoteFieldIncomeStatementDilutedNormalizedNetIncomePerShare) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDividendsPaidPerShare", QuoteFieldIncomeStatementDividendsPaidPerShare) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementIncomeAcquiredInProcessRD", QuoteFieldIncomeStatementIncomeAcquiredInProcessRD) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementOtherSpecialCharges", QuoteFieldIncomeStatementOtherSpecialCharges) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementIncomeTaxes", QuoteFieldIncomeStatementIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementMinorityInterest", QuoteFieldIncomeStatementMinorityInterest) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementNetIncomeFromContinuingOperations", QuoteFieldIncomeStatementNetIncomeFromContinuingOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementNetIncomeFromDiscontinuedOperations", QuoteFieldIncomeStatementNetIncomeFromDiscontinuedOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementNetIncomeFromTotalOperations", QuoteFieldIncomeStatementNetIncomeFromTotalOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementIncomeFromTaxLossCarryforward", QuoteFieldIncomeStatementIncomeFromTaxLossCarryforward) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementOtherGainsLosses", QuoteFieldIncomeStatementOtherGainsLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementTotalNetIncome", QuoteFieldIncomeStatementTotalNetIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementNormalizedIncome", QuoteFieldIncomeStatementNormalizedIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementNetIncomeAvailableForCommon", QuoteFieldIncomeStatementNetIncomeAvailableForCommon) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementPreferredDividends", QuoteFieldIncomeStatementPreferredDividends) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardOperatingRevenue", QuoteFieldIncomeStatementStandardOperatingRevenue) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardTotalRevenue", QuoteFieldIncomeStatementStandardTotalRevenue) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardAdjustmentToRevenue", QuoteFieldIncomeStatementStandardAdjustmentToRevenue) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardCostOfSales", QuoteFieldIncomeStatementStandardCostOfSales) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardCostOfSalesWithDepreciation", QuoteFieldIncomeStatementStandardCostOfSalesWithDepreciation) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardGrossMargin", QuoteFieldIncomeStatementStandardGrossMargin) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardGrossOperatingProfit", QuoteFieldIncomeStatementStandardGrossOperatingProfit) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardResearchAndDevelopment", QuoteFieldIncomeStatementStandardResearchAndDevelopment) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardSellingGeneralAndAdminExpense", QuoteFieldIncomeStatementStandardSellingGeneralAndAdminExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardAdvertising", QuoteFieldIncomeStatementStandardAdvertising) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardOperatingProfit", QuoteFieldIncomeStatementStandardOperatingProfit) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardOperatingProfitBeforeDepreciation", QuoteFieldIncomeStatementStandardOperatingProfitBeforeDepreciation) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardDepreciation", QuoteFieldIncomeStatementStandardDepreciation) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardDepreciationUnreconciled", QuoteFieldIncomeStatementStandardDepreciationUnreconciled) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardAmortization", QuoteFieldIncomeStatementStandardAmortization) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardAmortizationOfIntangibles", QuoteFieldIncomeStatementStandardAmortizationOfIntangibles) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardOperatingIncomeAfterDepreciation", QuoteFieldIncomeStatementStandardOperatingIncomeAfterDepreciation) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardInterestIncome", QuoteFieldIncomeStatementStandardInterestIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardEarningsFromEquityInterest", QuoteFieldIncomeStatementStandardEarningsFromEquityInterest) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardOtherIncomeNet", QuoteFieldIncomeStatementStandardOtherIncomeNet) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardInterestRestructuringAndMA", QuoteFieldIncomeStatementStandardInterestRestructuringAndMA) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardTotalIncomeAvailForInterestExpense", QuoteFieldIncomeStatementStandardTotalIncomeAvailForInterestExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardInterestExpense", QuoteFieldIncomeStatementStandardInterestExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardIncomeBeforeTax", QuoteFieldIncomeStatementStandardIncomeBeforeTax) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardPreferredSecuritiesOfSubsidiaryTrust", QuoteFieldIncomeStatementStandardPreferredSecuritiesOfSubsidiaryTrust) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardExtraordinaryIncomeOrLosses", QuoteFieldIncomeStatementStandardExtraordinaryIncomeOrLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardIncomeFromCumEffectOfAccountChange", QuoteFieldIncomeStatementStandardIncomeFromCumEffectOfAccountChange) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementStandardExciseTaxes", QuoteFieldIncomeStatementStandardExciseTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialLoans", QuoteFieldIncomeStatementFinancialLoans) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialInvestmentSecurities", QuoteFieldIncomeStatementFinancialInvestmentSecurities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialLeaseFinancingIncome", QuoteFieldIncomeStatementFinancialLeaseFinancingIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialOtherInterestIncome", QuoteFieldIncomeStatementFinancialOtherInterestIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialFedFundsSoldPurchased", QuoteFieldIncomeStatementFinancialFedFundsSoldPurchased) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialInterestBearingDeposits", QuoteFieldIncomeStatementFinancialInterestBearingDeposits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialLoansHeldForResale", QuoteFieldIncomeStatementFinancialLoansHeldForResale) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTradingAccountSecurities", QuoteFieldIncomeStatementFinancialTradingAccountSecurities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTimeDepositsPlaced", QuoteFieldIncomeStatementFinancialTimeDepositsPlaced) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialOtherMoneyMarketInvestments", QuoteFieldIncomeStatementFinancialOtherMoneyMarketInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTotalMoneyMarketInvestments", QuoteFieldIncomeStatementFinancialTotalMoneyMarketInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTotalInterestIncome", QuoteFieldIncomeStatementFinancialTotalInterestIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialDeposits", QuoteFieldIncomeStatementFinancialDeposits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialFedFundsPurchasedSecSold", QuoteFieldIncomeStatementFinancialFedFundsPurchasedSecSold) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialCapitalizedLeaseObligations", QuoteFieldIncomeStatementFinancialCapitalizedLeaseObligations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialOtherInterestExpense", QuoteFieldIncomeStatementFinancialOtherInterestExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTotalInterestExpense", QuoteFieldIncomeStatementFinancialTotalInterestExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialNetInterestIncomeExpense", QuoteFieldIncomeStatementFinancialNetInterestIncomeExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialProvisionForLoanLoss", QuoteFieldIncomeStatementFinancialProvisionForLoanLoss) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTrustFeesByCommissions", QuoteFieldIncomeStatementFinancialTrustFeesByCommissions) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialServiceChargeOnDepositAccounts", QuoteFieldIncomeStatementFinancialServiceChargeOnDepositAccounts) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialOtherServiceCharges", QuoteFieldIncomeStatementFinancialOtherServiceCharges) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialSecurityTransactions", QuoteFieldIncomeStatementFinancialSecurityTransactions) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialPremiumsEarned", QuoteFieldIncomeStatementFinancialPremiumsEarned) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialNetRealizedCapitalGains", QuoteFieldIncomeStatementFinancialNetRealizedCapitalGains) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialInvestmentBankingProfit", QuoteFieldIncomeStatementFinancialInvestmentBankingProfit) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialOtherNonInterestIncome", QuoteFieldIncomeStatementFinancialOtherNonInterestIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTotalNonInterestIncome", QuoteFieldIncomeStatementFinancialTotalNonInterestIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialSalariesAndEmployeeBenefits", QuoteFieldIncomeStatementFinancialSalariesAndEmployeeBenefits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialNetOccupancyExpense", QuoteFieldIncomeStatementFinancialNetOccupancyExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialPromotionsAndAdvertising", QuoteFieldIncomeStatementFinancialPromotionsAndAdvertising) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialPropLiabInsuranceClaims", QuoteFieldIncomeStatementFinancialPropLiabInsuranceClaims) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialPolicyAcquisitionCosts", QuoteFieldIncomeStatementFinancialPolicyAcquisitionCosts) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialAmortDefPolicyAcqCost", QuoteFieldIncomeStatementFinancialAmortDefPolicyAcqCost) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialCurrentAndFutureBenefits", QuoteFieldIncomeStatementFinancialCurrentAndFutureBenefits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialOtherNonInterestExpense", QuoteFieldIncomeStatementFinancialOtherNonInterestExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialTotalNonInterestExpense", QuoteFieldIncomeStatementFinancialTotalNonInterestExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialPremiumTaxCredit", QuoteFieldIncomeStatementFinancialPremiumTaxCredit) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialIncomeRestructuringAndMA", QuoteFieldIncomeStatementFinancialIncomeRestructuringAndMA) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialSpecialIncomeCharges", QuoteFieldIncomeStatementFinancialSpecialIncomeCharges) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialExtraordinaryIncomeLosses", QuoteFieldIncomeStatementFinancialExtraordinaryIncomeLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementFinancialIncomeFromCumEffectOfAcctChg", QuoteFieldIncomeStatementFinancialIncomeFromCumEffectOfAcctChg) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldIncomeStatementDate", QuoteFieldIncomeStatementDate) );
    
    //Financials - Balance sheets fields
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsAssetsRestrictedCash", QuoteFieldBalanceSheetsAssetsRestrictedCash) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsAssetsOtherReceivable", QuoteFieldBalanceSheetsAssetsOtherReceivable) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsAssetsTotalAssets", QuoteFieldBalanceSheetsAssetsTotalAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsLiabilitiesShortTermDebt", QuoteFieldBalanceSheetsLiabilitiesShortTermDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsLiabilitiesLongTermDebt", QuoteFieldBalanceSheetsLiabilitiesLongTermDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsLiabilitiesCapitalLeaseObligations", QuoteFieldBalanceSheetsLiabilitiesCapitalLeaseObligations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsLiabilitiesMinorityInterest", QuoteFieldBalanceSheetsLiabilitiesMinorityInterest) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsLiabilitiesTotalLiabilities", QuoteFieldBalanceSheetsLiabilitiesTotalLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsShareDataSharesOutstandingCommonClassOnly", QuoteFieldBalanceSheetsShareDataSharesOutstandingCommonClassOnly) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsShareDataPreferredShares", QuoteFieldBalanceSheetsShareDataPreferredShares) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsShareDataTotalOrdinaryShares", QuoteFieldBalanceSheetsShareDataTotalOrdinaryShares) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsShareDataTotalCommonSharesOutstanding", QuoteFieldBalanceSheetsShareDataTotalCommonSharesOutstanding) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsShareDataTreasuryShares", QuoteFieldBalanceSheetsShareDataTreasuryShares) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityPreferredStockEquity", QuoteFieldBalanceSheetsEquityPreferredStockEquity) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityCommonStockEquity", QuoteFieldBalanceSheetsEquityCommonStockEquity) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityCommonPar", QuoteFieldBalanceSheetsEquityCommonPar) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityAdditionalPaidInCapital", QuoteFieldBalanceSheetsEquityAdditionalPaidInCapital) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityCumulativeTranslationAdjustment", QuoteFieldBalanceSheetsEquityCumulativeTranslationAdjustment) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityRetainedEarnings", QuoteFieldBalanceSheetsEquityRetainedEarnings) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityTreasuryStock", QuoteFieldBalanceSheetsEquityTreasuryStock) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityOtherEquityAdjustments", QuoteFieldBalanceSheetsEquityOtherEquityAdjustments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityTotalEquity", QuoteFieldBalanceSheetsEquityTotalEquity) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityTotalCapitalization", QuoteFieldBalanceSheetsEquityTotalCapitalization) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsEquityTotalLiabilitiesAndStockEquity", QuoteFieldBalanceSheetsEquityTotalLiabilitiesAndStockEquity) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsNumberOfEmployees", QuoteFieldBalanceSheetsNumberOfEmployees) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsNumberOfPartTimeEmployees", QuoteFieldBalanceSheetsNumberOfPartTimeEmployees) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsCashAndEquivalents", QuoteFieldBalanceSheetsStandardAssetsCashAndEquivalents) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsMarketableSecurities", QuoteFieldBalanceSheetsStandardAssetsMarketableSecurities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsAccountsReceivable", QuoteFieldBalanceSheetsStandardAssetsAccountsReceivable) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsLoansReceivable", QuoteFieldBalanceSheetsStandardAssetsLoansReceivable) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsReceivables", QuoteFieldBalanceSheetsStandardAssetsReceivables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsRawMaterials", QuoteFieldBalanceSheetsStandardAssetsRawMaterials) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsWorkInProgress", QuoteFieldBalanceSheetsStandardAssetsWorkInProgress) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsPurchasedComponents", QuoteFieldBalanceSheetsStandardAssetsPurchasedComponents) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsFinishedGoods", QuoteFieldBalanceSheetsStandardAssetsFinishedGoods) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsOtherInventories", QuoteFieldBalanceSheetsStandardAssetsOtherInventories) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsInventoriesAdjAllowances", QuoteFieldBalanceSheetsStandardAssetsInventoriesAdjAllowances) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsInventories", QuoteFieldBalanceSheetsStandardAssetsInventories) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsPrepaidExpenses", QuoteFieldBalanceSheetsStandardAssetsPrepaidExpenses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsCurrentDeferredIncomeTaxes", QuoteFieldBalanceSheetsStandardAssetsCurrentDeferredIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsOtherCurrentAssets", QuoteFieldBalanceSheetsStandardAssetsOtherCurrentAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsTotalCurrentAssets", QuoteFieldBalanceSheetsStandardAssetsTotalCurrentAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsGrossFixedAssets", QuoteFieldBalanceSheetsStandardAssetsGrossFixedAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsAccumulatedDepreciationAndDepletion", QuoteFieldBalanceSheetsStandardAssetsAccumulatedDepreciationAndDepletion) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsNetFixedAssets", QuoteFieldBalanceSheetsStandardAssetsNetFixedAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsIntangibles", QuoteFieldBalanceSheetsStandardAssetsIntangibles) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsCostInExcess", QuoteFieldBalanceSheetsStandardAssetsCostInExcess) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsNonCurrentDeferredIncomeTaxes", QuoteFieldBalanceSheetsStandardAssetsNonCurrentDeferredIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsOtherNonCurrentAssets", QuoteFieldBalanceSheetsStandardAssetsOtherNonCurrentAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardAssetsTotalNonCurrentAssets", QuoteFieldBalanceSheetsStandardAssetsTotalNonCurrentAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesAccountsPayable", QuoteFieldBalanceSheetsStandardLiabilitiesAccountsPayable) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesNotesPayable", QuoteFieldBalanceSheetsStandardLiabilitiesNotesPayable) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesAccruedExpenses", QuoteFieldBalanceSheetsStandardLiabilitiesAccruedExpenses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesAccruedLiabilities", QuoteFieldBalanceSheetsStandardLiabilitiesAccruedLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesDeferredRevenues", QuoteFieldBalanceSheetsStandardLiabilitiesDeferredRevenues) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesCurrentDeferredIncomeTaxes", QuoteFieldBalanceSheetsStandardLiabilitiesCurrentDeferredIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesOtherCurrentLiabilities", QuoteFieldBalanceSheetsStandardLiabilitiesOtherCurrentLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesTotalCurrentLiabilities", QuoteFieldBalanceSheetsStandardLiabilitiesTotalCurrentLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesDeferredIncomeTaxes", QuoteFieldBalanceSheetsStandardLiabilitiesDeferredIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesOtherNonCurrentLiabilities", QuoteFieldBalanceSheetsStandardLiabilitiesOtherNonCurrentLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesPreferredSecuritiesOfSubsidiaryTrust", QuoteFieldBalanceSheetsStandardLiabilitiesPreferredSecuritiesOfSubsidiaryTrust) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesPreferredEquityOutsideStockEquity", QuoteFieldBalanceSheetsStandardLiabilitiesPreferredEquityOutsideStockEquity) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardLiabilitiesTotalNonCurrentLiabilities", QuoteFieldBalanceSheetsStandardLiabilitiesTotalNonCurrentLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardCashFlow", QuoteFieldBalanceSheetsStandardCashFlow) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardWorkingCapital", QuoteFieldBalanceSheetsStandardWorkingCapital) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardFreeCashFlow", QuoteFieldBalanceSheetsStandardFreeCashFlow) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsStandardInvestedCapital", QuoteFieldBalanceSheetsStandardInvestedCapital) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsCashAndDueFromBanks", QuoteFieldBalanceSheetsFinancialAssetsCashAndDueFromBanks) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsFedFundsSoldSecuritiesPurchased", QuoteFieldBalanceSheetsFinancialAssetsFedFundsSoldSecuritiesPurchased) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsInterestBearingDepAtOtherBanks", QuoteFieldBalanceSheetsFinancialAssetsInterestBearingDepAtOtherBanks) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsInvestmentSecuritiesNet", QuoteFieldBalanceSheetsFinancialAssetsInvestmentSecuritiesNet) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsLoans", QuoteFieldBalanceSheetsFinancialAssetsLoans) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsUnearnedPremiums", QuoteFieldBalanceSheetsFinancialAssetsUnearnedPremiums) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsAllowanceForLoansAndLeaseLosses", QuoteFieldBalanceSheetsFinancialAssetsAllowanceForLoansAndLeaseLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsNetLoans", QuoteFieldBalanceSheetsFinancialAssetsNetLoans) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsPremisesAndEquipment", QuoteFieldBalanceSheetsFinancialAssetsPremisesAndEquipment) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsDueFromCustomersAcceptance", QuoteFieldBalanceSheetsFinancialAssetsDueFromCustomersAcceptance) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsTradingAccountSecurities", QuoteFieldBalanceSheetsFinancialAssetsTradingAccountSecurities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsAccruedInterest", QuoteFieldBalanceSheetsFinancialAssetsAccruedInterest) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsDeferredAcquisitionCost", QuoteFieldBalanceSheetsFinancialAssetsDeferredAcquisitionCost) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsAccruedInvestmentIncome", QuoteFieldBalanceSheetsFinancialAssetsAccruedInvestmentIncome) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsSeparateAccountBusiness", QuoteFieldBalanceSheetsFinancialAssetsSeparateAccountBusiness) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsTimeDepositsPlaced", QuoteFieldBalanceSheetsFinancialAssetsTimeDepositsPlaced) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsIntangibleAssets", QuoteFieldBalanceSheetsFinancialAssetsIntangibleAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialAssetsOtherAssets", QuoteFieldBalanceSheetsFinancialAssetsOtherAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesNonInterestBearingDeposits", QuoteFieldBalanceSheetsFinancialLiabilitiesNonInterestBearingDeposits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesInterestBearingDeposits", QuoteFieldBalanceSheetsFinancialLiabilitiesInterestBearingDeposits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesOtherLiabilities", QuoteFieldBalanceSheetsFinancialLiabilitiesOtherLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesBankersAcceptanceOutstanding", QuoteFieldBalanceSheetsFinancialLiabilitiesBankersAcceptanceOutstanding) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesFedFundsPurchasedSecuritiesSold", QuoteFieldBalanceSheetsFinancialLiabilitiesFedFundsPurchasedSecuritiesSold) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedTaxes", QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedInterestPayables", QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedInterestPayables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesOtherPayables", QuoteFieldBalanceSheetsFinancialLiabilitiesOtherPayables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesClaimsAndClaimExpense", QuoteFieldBalanceSheetsFinancialLiabilitiesClaimsAndClaimExpense) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesFuturePolicyBenefits", QuoteFieldBalanceSheetsFinancialLiabilitiesFuturePolicyBenefits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesUnearnedPremiums", QuoteFieldBalanceSheetsFinancialLiabilitiesUnearnedPremiums) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesPolicyHolderFunds", QuoteFieldBalanceSheetsFinancialLiabilitiesPolicyHolderFunds) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesParticipatingPolicyholderEquity", QuoteFieldBalanceSheetsFinancialLiabilitiesParticipatingPolicyholderEquity) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialLiabilitiesSeparateAccountsBusiness", QuoteFieldBalanceSheetsFinancialLiabilitiesSeparateAccountsBusiness) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialEquityForeignCurrencyAdjustments", QuoteFieldBalanceSheetsFinancialEquityForeignCurrencyAdjustments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnInvestments", QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnForeignCurrency", QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnForeignCurrency) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsFinancialEquityNetOtherUnearnedLossesGains", QuoteFieldBalanceSheetsFinancialEquityNetOtherUnearnedLossesGains) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldBalanceSheetsDate", QuoteFieldBalanceSheetsDate) );

    //Financials - Cash flow fields
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowOperatingActivitiesNetIncomeOrLoss", QuoteFieldCashFlowOperatingActivitiesNetIncomeOrLoss) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowOperatingActivitiesDeferredIncomeTaxes", QuoteFieldCashFlowOperatingActivitiesDeferredIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowOperatingActivitiesOtherNonCashItems", QuoteFieldCashFlowOperatingActivitiesOtherNonCashItems) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowInvestingActivitiesAcquisitions", QuoteFieldCashFlowInvestingActivitiesAcquisitions) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowInvestingActivitiesOtherInvestingChangesNet", QuoteFieldCashFlowInvestingActivitiesOtherInvestingChangesNet) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowInvestingActivitiesNetCashFromInvestingActivities", QuoteFieldCashFlowInvestingActivitiesNetCashFromInvestingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancingActivitiesNetCashFromFinancingActivities", QuoteFieldCashFlowFinancingActivitiesNetCashFromFinancingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancingActivitiesEffectOfExchangeRateChanges", QuoteFieldCashFlowFinancingActivitiesEffectOfExchangeRateChanges) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancingActivitiesCashAtBeginningOfPeriod", QuoteFieldCashFlowFinancingActivitiesCashAtBeginningOfPeriod) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancingActivitiesCashAtEndOfPeriod", QuoteFieldCashFlowFinancingActivitiesCashAtEndOfPeriod) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesDepreciation", QuoteFieldCashFlowStandardOperatingActivitiesDepreciation) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesAmortization", QuoteFieldCashFlowStandardOperatingActivitiesAmortization) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesAmortizationOfIntangibles", QuoteFieldCashFlowStandardOperatingActivitiesAmortizationOfIntangibles) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesOperatingGainsOrLosses", QuoteFieldCashFlowStandardOperatingActivitiesOperatingGainsOrLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesExtraordinaryGainsOrLosses", QuoteFieldCashFlowStandardOperatingActivitiesExtraordinaryGainsOrLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInReceivables", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInReceivables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInInventories", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInInventories) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPrepaidExpenses", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPrepaidExpenses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrentAssets", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrentAssets) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPayables", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPayables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrLiabilities", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrLiabilities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherWorkingCapital", QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherWorkingCapital) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromContinuingOperations", QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromContinuingOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromDiscontinuedOperations", QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromDiscontinuedOperations) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromOperatingActivities", QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromOperatingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesSaleOfPropertyPlantEquipment", QuoteFieldCashFlowStandardInvestingActivitiesSaleOfPropertyPlantEquipment) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesSaleOfLongTermInvestments", QuoteFieldCashFlowStandardInvestingActivitiesSaleOfLongTermInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesSaleOfShortTermInvestments", QuoteFieldCashFlowStandardInvestingActivitiesSaleOfShortTermInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfPropertyPlantEquipment", QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfPropertyPlantEquipment) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfLongTermInvestments", QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfLongTermInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfShortTermInvestments", QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfShortTermInvestments) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardInvestingActivitiesCashFromDiscInvestingActivities", QuoteFieldCashFlowStandardInvestingActivitiesCashFromDiscInvestingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfDebt", QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfCapitalStock", QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfCapitalStock) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesRepaymentOfDebt", QuoteFieldCashFlowStandardFinancingActivitiesRepaymentOfDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesRepurchaseOfCapitalStock", QuoteFieldCashFlowStandardFinancingActivitiesRepurchaseOfCapitalStock) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesPaymentOfCashDividends", QuoteFieldCashFlowStandardFinancingActivitiesPaymentOfCashDividends) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesOtherFinancingChargesNet", QuoteFieldCashFlowStandardFinancingActivitiesOtherFinancingChargesNet) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesCashFromDiscFinancingActivities", QuoteFieldCashFlowStandardFinancingActivitiesCashFromDiscFinancingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowStandardFinancingActivitiesNetChangeInCashAndCashEquivalents", QuoteFieldCashFlowStandardFinancingActivitiesNetChangeInCashAndCashEquivalents) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesProvisionForLoanLosses", QuoteFieldCashFlowFinancialOperatingActivitiesProvisionForLoanLosses) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesDepreciationandAmortization", QuoteFieldCashFlowFinancialOperatingActivitiesDepreciationandAmortization) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesChangeInAssetsReceivables", QuoteFieldCashFlowFinancialOperatingActivitiesChangeInAssetsReceivables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesChangeInLiabilitiesPayables", QuoteFieldCashFlowFinancialOperatingActivitiesChangeInLiabilitiesPayables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesInvestmentSecuritiesGain", QuoteFieldCashFlowFinancialOperatingActivitiesInvestmentSecuritiesGain) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesNetPolicyAcquisitionCosts", QuoteFieldCashFlowFinancialOperatingActivitiesNetPolicyAcquisitionCosts) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesRealizedInvestmentGains", QuoteFieldCashFlowFinancialOperatingActivitiesRealizedInvestmentGains) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesNetPremiumsReceivables", QuoteFieldCashFlowFinancialOperatingActivitiesNetPremiumsReceivables) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesChangeInIncomeTaxes", QuoteFieldCashFlowFinancialOperatingActivitiesChangeInIncomeTaxes) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialOperatingActivitiesNetCashFromOperatingActivities", QuoteFieldCashFlowFinancialOperatingActivitiesNetCashFromOperatingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialInvestingActivitiesProceedsFromSaleMatInv", QuoteFieldCashFlowFinancialInvestingActivitiesProceedsFromSaleMatInv) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfInvestmentSecurities", QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfInvestmentSecurities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialInvestingActivitiesNetIncreaseFedFundsSold", QuoteFieldCashFlowFinancialInvestingActivitiesNetIncreaseFedFundsSold) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfPropertyAndEquipment", QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfPropertyAndEquipment) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInDeposits", QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInDeposits) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesCashDividendsPaid", QuoteFieldCashFlowFinancialFinancingActivitiesCashDividendsPaid) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesRepaymentOfLongTermDebt", QuoteFieldCashFlowFinancialFinancingActivitiesRepaymentOfLongTermDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesChangeOfShortTermDebt", QuoteFieldCashFlowFinancialFinancingActivitiesChangeOfShortTermDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfLongTermDebt", QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfLongTermDebt) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfPreferredStock", QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfPreferredStock) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfCommonStock", QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfCommonStock) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesPurchaseOfTreasuryStock", QuoteFieldCashFlowFinancialFinancingActivitiesPurchaseOfTreasuryStock) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesOtherFinancingActivities", QuoteFieldCashFlowFinancialFinancingActivitiesOtherFinancingActivities) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInCashAndEquivalents", QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInCashAndEquivalents) );
    this->m_strToQuoteField.insert( std::pair<std::string, ATQuoteFieldType>("QuoteFieldCashFlowDate", QuoteFieldCashFlowDate) );

    this->m_strToCursor.insert( std::pair<std::string, ATCursorType>("CursorForward", CursorForward) );
    this->m_strToCursor.insert( std::pair<std::string, ATCursorType>("CursorBackward", CursorBackward) );

    this->m_strToConstituentList.insert( std::pair<std::string, ATConstituentListType>("ATConstituentListIndex", ATConstituentListIndex) );
    this->m_strToConstituentList.insert( std::pair<std::string, ATConstituentListType>("ATConstituentListSector", ATConstituentListSector) );
    this->m_strToConstituentList.insert( std::pair<std::string, ATConstituentListType>("ATConstituentListOptionChain", ATConstituentListOptionChain) );
}

AtEnumConverter::~AtEnumConverter() {
}

ATExchangeType AtEnumConverter::toAtExchange( std::string exchangeType ) {
    ATExchangeType retVal;
    retVal = this->m_strToExchange[ exchangeType ]; // TODO catch for unknown type
    return retVal;
}

ATCountryType AtEnumConverter::toAtCountry( std::string countryType ) {
    ATCountryType retVal;
    retVal = this->m_strToCountry[ countryType ]; // TODO catch for unknown type
    return retVal;
}

ATStreamRequestType AtEnumConverter::toAtStreamRequest( std::string requestType ) {
    ATStreamRequestType retVal;
    retVal = this->m_strToStreamRequest[ requestType ]; // TODO catch for unknown type
    return retVal;
}

ATQuoteFieldType AtEnumConverter::toAtQuoteField( std::string quoteFieldType ) {
    ATQuoteFieldType retVal;
    retVal = this->m_strToQuoteField[ quoteFieldType ]; // TODO catch for unknown type
    return retVal;
}

ATCursorType AtEnumConverter::toAtCursor( std::string cursorType ) {
    ATCursorType retVal;
    retVal = this->m_strToCursor[ cursorType ];
    return retVal;
}

ATConstituentListType AtEnumConverter::toAtConstituentList( std::string constituentListType ) {
    ATConstituentListType retVal;
    retVal = this->m_strToConstituentList[ constituentListType ];
    return retVal;
}