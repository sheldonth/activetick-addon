#include "Jsonifier.h"
#include "AtEnumConverter.h"
#include <string.h>
#include <utility>
#include "import/libjson/libjson.h"
#include "import/atfeed-cppsdk/example/Helper.h"

std::map<uint8_t, std::string> createSymbolTypeMap()
{
    std::map<uint8_t, std::string> symbolTypeToStr;
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolStock, "SymbolStock") );
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolIndex, "SymbolIndex") );
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolStockOption, "SymbolStockOption") );
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolBond, "SymbolBond") );
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolMutualFund, "SymbolMutualFund") );
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolTopMarketMovers, "SymbolTopMarketMovers") );
    symbolTypeToStr.insert( std::pair<uint8_t, std::string>(SymbolCurrency, "SymbolCurrency") );
    return symbolTypeToStr;
}

std::map<uint8_t, std::string> symbolTypeToStr = createSymbolTypeMap();

std::map<uint8_t, std::string> createExchangeTypeMap()
{
    std::map<uint8_t, std::string> exchangeTypeToStr;
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeAMEX, "ExchangeAMEX") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNasdaqOmxBx, "ExchangeNasdaqOmxBx") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNationalStockExchange, "ExchangeNationalStockExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeFinraAdf, "ExchangeFinraAdf") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeCQS, "ExchangeCQS") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeForex, "ExchangeForex") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeInternationalSecuritiesExchange, "ExchangeInternationalSecuritiesExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeEdgaExchange, "ExchangeEdgaExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeEdgxExchange, "ExchangeEdgxExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeChicagoStockExchange, "ExchangeChicagoStockExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNyseEuronext, "ExchangeNyseEuronext") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNyseArcaExchange, "ExchangeNyseArcaExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNasdaqOmx, "ExchangeNasdaqOmx") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeCTS, "ExchangeCTS") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeCTANasdaqOMX, "ExchangeCTANasdaqOMX") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOTCBB, "ExchangeOTCBB") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNNOTC, "ExchangeNNOTC") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeChicagoBoardOptionsExchange, "ExchangeChicagoBoardOptionsExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeNasdaqOmxPhlx, "ExchangeNasdaqOmxPhlx") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeBatsYExchange, "ExchangeBatsYExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeBatsExchange, "ExchangeBatsExchange") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeCanadaToronto, "ExchangeCanadaToronto") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeCanadaVenture, "ExchangeCanadaVenture") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOpra, "ExchangeOpra") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOptionBoston, "ExchangeOptionBoston") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOptionCboe, "ExchangeOptionCboe") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOptionNyseArca, "ExchangeOptionNyseArca") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOptionC2, "ExchangeOptionC2") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeOptionNasdaqOmxBx, "ExchangeOptionNasdaqOmxBx") );
    exchangeTypeToStr.insert( std::pair<uint8_t, std::string>(ExchangeComposite, "ExchangeComposite") );
    return exchangeTypeToStr;
}

std::map<uint8_t, std::string> exchangeTypeToStr = createExchangeTypeMap();

std::map<uint8_t, std::string> createCountryTypeMap()
{
    std::map<uint8_t, std::string> countryTypeToStr;
    countryTypeToStr.insert( std::pair<uint8_t, std::string>(CountryInternational, "CountryInternational") );
    countryTypeToStr.insert( std::pair<uint8_t, std::string>(CountryUnitedStates, "CountryUnitedStates") );
    countryTypeToStr.insert( std::pair<uint8_t, std::string>(CountryCanada, "CountryCanada") );
    return countryTypeToStr;
}

std::map<uint8_t, std::string> countryTypeToStr = createCountryTypeMap();

std::map<uint8_t, std::string> createFieldStatusMap()
{
    std::map<uint8_t, std::string> fieldStatusToStr;
    fieldStatusToStr.insert( std::pair<uint8_t, std::string>(FieldStatusSuccess, "FieldStatusSuccess") );
    fieldStatusToStr.insert( std::pair<uint8_t, std::string>(FieldStatusInvalid, "FieldStatusInvalid") );
    fieldStatusToStr.insert( std::pair<uint8_t, std::string>(FieldStatusUnavailable, "FieldStatusUnavailable") );
    fieldStatusToStr.insert( std::pair<uint8_t, std::string>(FieldStatusDenied, "FieldStatusDenied") );
    return fieldStatusToStr;
}

std::map<uint8_t, std::string> fieldStatusToStr = createFieldStatusMap();

std::map<uint8_t, std::string> createQuoteFieldTypeMap()
{
    std::map<uint8_t, std::string> quoteFieldTypeToStr;
    //Intraday fields
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldSymbol, "QuoteFieldSymbol") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldOpenPrice, "QuoteFieldOpenPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldPreviousClosePrice, "QuoteFieldPreviousClosePrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldClosePrice, "QuoteFieldClosePrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLastPrice, "QuoteFieldLastPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBidPrice, "QuoteFieldBidPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldAskPrice, "QuoteFieldAskPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldHighPrice, "QuoteFieldHighPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLowPrice, "QuoteFieldLowPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldDayHighPrice, "QuoteFieldDayHighPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldDayLowPrice, "QuoteFieldDayLowPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldPreMarketOpenPrice, "QuoteFieldPreMarketOpenPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldExtendedHoursLastPrice, "QuoteFieldExtendedHoursLastPrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldAfterMarketClosePrice, "QuoteFieldAfterMarketClosePrice") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBidExchange, "QuoteFieldBidExchange") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldAskExchange, "QuoteFieldAskExchange") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLastExchange, "QuoteFieldLastExchange") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLastCondition, "QuoteFieldLastCondition") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldQuoteCondition, "QuoteFieldQuoteCondition") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLastTradeDateTime, "QuoteFieldLastTradeDateTime") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLastQuoteDateTime, "QuoteFieldLastQuoteDateTime") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldDayHighDateTime, "QuoteFieldDayHighDateTime") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldDayLowDateTime, "QuoteFieldDayLowDateTime") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldLastSize, "QuoteFieldLastSize") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBidSize, "QuoteFieldBidSize") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldAskSize, "QuoteFieldAskSize") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldVolume, "QuoteFieldVolume") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldPreMarketVolume, "QuoteFieldPreMarketVolume") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldAfterMarketVolume, "QuoteFieldAfterMarketVolume") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldTradeCount, "QuoteFieldTradeCount") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldPreMarketTradeCount, "QuoteFieldPreMarketTradeCount") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldAfterMarketTradeCount, "QuoteFieldAfterMarketTradeCount") );

    //Profile fields
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldProfileShortName, "QuoteFieldProfileShortName") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldProfilePrimaryExchange, "QuoteFieldProfilePrimaryExchange") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldProfileLongName, "QuoteFieldProfileLongName") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldProfileSector, "QuoteFieldProfileSector") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldProfileIndustry, "QuoteFieldProfileIndustry") );

    //Option fields
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldOptionOpenInterest, "QuoteFieldOptionOpenInterest") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldOptionStrikePrice, "QuoteFieldOptionStrikePrice") );

    //Financials - Income statement fields
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSFromContinuingOperations, "QuoteFieldIncomeStatementBasicEPSFromContinuingOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSFromDiscontinuedOperations, "QuoteFieldIncomeStatementBasicEPSFromDiscontinuedOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSFromTotalOperations, "QuoteFieldIncomeStatementBasicEPSFromTotalOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSFromExtraordinaryIncome, "QuoteFieldIncomeStatementBasicEPSFromExtraordinaryIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSFromCumEffectOfAccountingChange, "QuoteFieldIncomeStatementBasicEPSFromCumEffectOfAccountingChange") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSFromOtherGains, "QuoteFieldIncomeStatementBasicEPSFromOtherGains") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicEPSTotal, "QuoteFieldIncomeStatementBasicEPSTotal") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementBasicNormalizedNetIncomePerShare, "QuoteFieldIncomeStatementBasicNormalizedNetIncomePerShare") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedEPSFromContinuingOperations, "QuoteFieldIncomeStatementDilutedEPSFromContinuingOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedEPSFromDiscontinuedOperations, "QuoteFieldIncomeStatementDilutedEPSFromDiscontinuedOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedEPSFromTotalOperations, "QuoteFieldIncomeStatementDilutedEPSFromTotalOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedEPSFromExtraordinaryIncome, "QuoteFieldIncomeStatementDilutedEPSFromExtraordinaryIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedEPSFromOtherGains, "QuoteFieldIncomeStatementDilutedEPSFromOtherGains") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedEPSTotal, "QuoteFieldIncomeStatementDilutedEPSTotal") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDilutedNormalizedNetIncomePerShare, "QuoteFieldIncomeStatementDilutedNormalizedNetIncomePerShare") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDividendsPaidPerShare, "QuoteFieldIncomeStatementDividendsPaidPerShare") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementIncomeAcquiredInProcessRD, "QuoteFieldIncomeStatementIncomeAcquiredInProcessRD") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementOtherSpecialCharges, "QuoteFieldIncomeStatementOtherSpecialCharges") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementIncomeTaxes, "QuoteFieldIncomeStatementIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementMinorityInterest, "QuoteFieldIncomeStatementMinorityInterest") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementNetIncomeFromContinuingOperations, "QuoteFieldIncomeStatementNetIncomeFromContinuingOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementNetIncomeFromDiscontinuedOperations, "QuoteFieldIncomeStatementNetIncomeFromDiscontinuedOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementNetIncomeFromTotalOperations, "QuoteFieldIncomeStatementNetIncomeFromTotalOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementIncomeFromTaxLossCarryforward, "QuoteFieldIncomeStatementIncomeFromTaxLossCarryforward") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementOtherGainsLosses, "QuoteFieldIncomeStatementOtherGainsLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementTotalNetIncome, "QuoteFieldIncomeStatementTotalNetIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementNormalizedIncome, "QuoteFieldIncomeStatementNormalizedIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementNetIncomeAvailableForCommon, "QuoteFieldIncomeStatementNetIncomeAvailableForCommon") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementPreferredDividends, "QuoteFieldIncomeStatementPreferredDividends") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardOperatingRevenue, "QuoteFieldIncomeStatementStandardOperatingRevenue") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardTotalRevenue, "QuoteFieldIncomeStatementStandardTotalRevenue") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardAdjustmentToRevenue, "QuoteFieldIncomeStatementStandardAdjustmentToRevenue") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardCostOfSales, "QuoteFieldIncomeStatementStandardCostOfSales") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardCostOfSalesWithDepreciation, "QuoteFieldIncomeStatementStandardCostOfSalesWithDepreciation") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardGrossMargin, "QuoteFieldIncomeStatementStandardGrossMargin") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardGrossOperatingProfit, "QuoteFieldIncomeStatementStandardGrossOperatingProfit") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardResearchAndDevelopment, "QuoteFieldIncomeStatementStandardResearchAndDevelopment") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardSellingGeneralAndAdminExpense, "QuoteFieldIncomeStatementStandardSellingGeneralAndAdminExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardAdvertising, "QuoteFieldIncomeStatementStandardAdvertising") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardOperatingProfit, "QuoteFieldIncomeStatementStandardOperatingProfit") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardOperatingProfitBeforeDepreciation, "QuoteFieldIncomeStatementStandardOperatingProfitBeforeDepreciation") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardDepreciation, "QuoteFieldIncomeStatementStandardDepreciation") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardDepreciationUnreconciled, "QuoteFieldIncomeStatementStandardDepreciationUnreconciled") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardAmortization, "QuoteFieldIncomeStatementStandardAmortization") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardAmortizationOfIntangibles, "QuoteFieldIncomeStatementStandardAmortizationOfIntangibles") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardOperatingIncomeAfterDepreciation, "QuoteFieldIncomeStatementStandardOperatingIncomeAfterDepreciation") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardInterestIncome, "QuoteFieldIncomeStatementStandardInterestIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardEarningsFromEquityInterest, "QuoteFieldIncomeStatementStandardEarningsFromEquityInterest") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardOtherIncomeNet, "QuoteFieldIncomeStatementStandardOtherIncomeNet") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardInterestRestructuringAndMA, "QuoteFieldIncomeStatementStandardInterestRestructuringAndMA") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardTotalIncomeAvailForInterestExpense, "QuoteFieldIncomeStatementStandardTotalIncomeAvailForInterestExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardInterestExpense, "QuoteFieldIncomeStatementStandardInterestExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardIncomeBeforeTax, "QuoteFieldIncomeStatementStandardIncomeBeforeTax") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardPreferredSecuritiesOfSubsidiaryTrust, "QuoteFieldIncomeStatementStandardPreferredSecuritiesOfSubsidiaryTrust") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardExtraordinaryIncomeOrLosses, "QuoteFieldIncomeStatementStandardExtraordinaryIncomeOrLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardIncomeFromCumEffectOfAccountChange, "QuoteFieldIncomeStatementStandardIncomeFromCumEffectOfAccountChange") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementStandardExciseTaxes, "QuoteFieldIncomeStatementStandardExciseTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialLoans, "QuoteFieldIncomeStatementFinancialLoans") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialInvestmentSecurities, "QuoteFieldIncomeStatementFinancialInvestmentSecurities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialLeaseFinancingIncome, "QuoteFieldIncomeStatementFinancialLeaseFinancingIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialOtherInterestIncome, "QuoteFieldIncomeStatementFinancialOtherInterestIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialFedFundsSoldPurchased, "QuoteFieldIncomeStatementFinancialFedFundsSoldPurchased") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialInterestBearingDeposits, "QuoteFieldIncomeStatementFinancialInterestBearingDeposits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialLoansHeldForResale, "QuoteFieldIncomeStatementFinancialLoansHeldForResale") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTradingAccountSecurities, "QuoteFieldIncomeStatementFinancialTradingAccountSecurities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTimeDepositsPlaced, "QuoteFieldIncomeStatementFinancialTimeDepositsPlaced") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialOtherMoneyMarketInvestments, "QuoteFieldIncomeStatementFinancialOtherMoneyMarketInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTotalMoneyMarketInvestments, "QuoteFieldIncomeStatementFinancialTotalMoneyMarketInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTotalInterestIncome, "QuoteFieldIncomeStatementFinancialTotalInterestIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialDeposits, "QuoteFieldIncomeStatementFinancialDeposits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialFedFundsPurchasedSecSold, "QuoteFieldIncomeStatementFinancialFedFundsPurchasedSecSold") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialCapitalizedLeaseObligations, "QuoteFieldIncomeStatementFinancialCapitalizedLeaseObligations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialOtherInterestExpense, "QuoteFieldIncomeStatementFinancialOtherInterestExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTotalInterestExpense, "QuoteFieldIncomeStatementFinancialTotalInterestExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialNetInterestIncomeExpense, "QuoteFieldIncomeStatementFinancialNetInterestIncomeExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialProvisionForLoanLoss, "QuoteFieldIncomeStatementFinancialProvisionForLoanLoss") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTrustFeesByCommissions, "QuoteFieldIncomeStatementFinancialTrustFeesByCommissions") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialServiceChargeOnDepositAccounts, "QuoteFieldIncomeStatementFinancialServiceChargeOnDepositAccounts") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialOtherServiceCharges, "QuoteFieldIncomeStatementFinancialOtherServiceCharges") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialSecurityTransactions, "QuoteFieldIncomeStatementFinancialSecurityTransactions") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialPremiumsEarned, "QuoteFieldIncomeStatementFinancialPremiumsEarned") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialNetRealizedCapitalGains, "QuoteFieldIncomeStatementFinancialNetRealizedCapitalGains") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialInvestmentBankingProfit, "QuoteFieldIncomeStatementFinancialInvestmentBankingProfit") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialOtherNonInterestIncome, "QuoteFieldIncomeStatementFinancialOtherNonInterestIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTotalNonInterestIncome, "QuoteFieldIncomeStatementFinancialTotalNonInterestIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialSalariesAndEmployeeBenefits, "QuoteFieldIncomeStatementFinancialSalariesAndEmployeeBenefits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialNetOccupancyExpense, "QuoteFieldIncomeStatementFinancialNetOccupancyExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialPromotionsAndAdvertising, "QuoteFieldIncomeStatementFinancialPromotionsAndAdvertising") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialPropLiabInsuranceClaims, "QuoteFieldIncomeStatementFinancialPropLiabInsuranceClaims") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialPolicyAcquisitionCosts, "QuoteFieldIncomeStatementFinancialPolicyAcquisitionCosts") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialAmortDefPolicyAcqCost, "QuoteFieldIncomeStatementFinancialAmortDefPolicyAcqCost") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialCurrentAndFutureBenefits, "QuoteFieldIncomeStatementFinancialCurrentAndFutureBenefits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialOtherNonInterestExpense, "QuoteFieldIncomeStatementFinancialOtherNonInterestExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialTotalNonInterestExpense, "QuoteFieldIncomeStatementFinancialTotalNonInterestExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialPremiumTaxCredit, "QuoteFieldIncomeStatementFinancialPremiumTaxCredit") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialIncomeRestructuringAndMA, "QuoteFieldIncomeStatementFinancialIncomeRestructuringAndMA") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialSpecialIncomeCharges, "QuoteFieldIncomeStatementFinancialSpecialIncomeCharges") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialExtraordinaryIncomeLosses, "QuoteFieldIncomeStatementFinancialExtraordinaryIncomeLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementFinancialIncomeFromCumEffectOfAcctChg, "QuoteFieldIncomeStatementFinancialIncomeFromCumEffectOfAcctChg") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldIncomeStatementDate, "QuoteFieldIncomeStatementDate") );
    
    //Financials - Balance sheets fields
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsAssetsRestrictedCash, "QuoteFieldBalanceSheetsAssetsRestrictedCash") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsAssetsOtherReceivable, "QuoteFieldBalanceSheetsAssetsOtherReceivable") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsAssetsTotalAssets, "QuoteFieldBalanceSheetsAssetsTotalAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsLiabilitiesShortTermDebt, "QuoteFieldBalanceSheetsLiabilitiesShortTermDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsLiabilitiesLongTermDebt, "QuoteFieldBalanceSheetsLiabilitiesLongTermDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsLiabilitiesCapitalLeaseObligations, "QuoteFieldBalanceSheetsLiabilitiesCapitalLeaseObligations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsLiabilitiesMinorityInterest, "QuoteFieldBalanceSheetsLiabilitiesMinorityInterest") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsLiabilitiesTotalLiabilities, "QuoteFieldBalanceSheetsLiabilitiesTotalLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsShareDataSharesOutstandingCommonClassOnly, "QuoteFieldBalanceSheetsShareDataSharesOutstandingCommonClassOnly") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsShareDataPreferredShares, "QuoteFieldBalanceSheetsShareDataPreferredShares") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsShareDataTotalOrdinaryShares, "QuoteFieldBalanceSheetsShareDataTotalOrdinaryShares") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsShareDataTotalCommonSharesOutstanding, "QuoteFieldBalanceSheetsShareDataTotalCommonSharesOutstanding") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsShareDataTreasuryShares, "QuoteFieldBalanceSheetsShareDataTreasuryShares") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityPreferredStockEquity, "QuoteFieldBalanceSheetsEquityPreferredStockEquity") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityCommonStockEquity, "QuoteFieldBalanceSheetsEquityCommonStockEquity") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityCommonPar, "QuoteFieldBalanceSheetsEquityCommonPar") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityAdditionalPaidInCapital, "QuoteFieldBalanceSheetsEquityAdditionalPaidInCapital") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityCumulativeTranslationAdjustment, "QuoteFieldBalanceSheetsEquityCumulativeTranslationAdjustment") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityRetainedEarnings, "QuoteFieldBalanceSheetsEquityRetainedEarnings") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityTreasuryStock, "QuoteFieldBalanceSheetsEquityTreasuryStock") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityOtherEquityAdjustments, "QuoteFieldBalanceSheetsEquityOtherEquityAdjustments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityTotalEquity, "QuoteFieldBalanceSheetsEquityTotalEquity") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityTotalCapitalization, "QuoteFieldBalanceSheetsEquityTotalCapitalization") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsEquityTotalLiabilitiesAndStockEquity, "QuoteFieldBalanceSheetsEquityTotalLiabilitiesAndStockEquity") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsNumberOfEmployees, "QuoteFieldBalanceSheetsNumberOfEmployees") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsNumberOfPartTimeEmployees, "QuoteFieldBalanceSheetsNumberOfPartTimeEmployees") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsCashAndEquivalents, "QuoteFieldBalanceSheetsStandardAssetsCashAndEquivalents") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsMarketableSecurities, "QuoteFieldBalanceSheetsStandardAssetsMarketableSecurities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsAccountsReceivable, "QuoteFieldBalanceSheetsStandardAssetsAccountsReceivable") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsLoansReceivable, "QuoteFieldBalanceSheetsStandardAssetsLoansReceivable") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsReceivables, "QuoteFieldBalanceSheetsStandardAssetsReceivables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsRawMaterials, "QuoteFieldBalanceSheetsStandardAssetsRawMaterials") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsWorkInProgress, "QuoteFieldBalanceSheetsStandardAssetsWorkInProgress") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsPurchasedComponents, "QuoteFieldBalanceSheetsStandardAssetsPurchasedComponents") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsFinishedGoods, "QuoteFieldBalanceSheetsStandardAssetsFinishedGoods") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsOtherInventories, "QuoteFieldBalanceSheetsStandardAssetsOtherInventories") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsInventoriesAdjAllowances, "QuoteFieldBalanceSheetsStandardAssetsInventoriesAdjAllowances") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsInventories, "QuoteFieldBalanceSheetsStandardAssetsInventories") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsPrepaidExpenses, "QuoteFieldBalanceSheetsStandardAssetsPrepaidExpenses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsCurrentDeferredIncomeTaxes, "QuoteFieldBalanceSheetsStandardAssetsCurrentDeferredIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsOtherCurrentAssets, "QuoteFieldBalanceSheetsStandardAssetsOtherCurrentAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsTotalCurrentAssets, "QuoteFieldBalanceSheetsStandardAssetsTotalCurrentAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsGrossFixedAssets, "QuoteFieldBalanceSheetsStandardAssetsGrossFixedAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsAccumulatedDepreciationAndDepletion, "QuoteFieldBalanceSheetsStandardAssetsAccumulatedDepreciationAndDepletion") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsNetFixedAssets, "QuoteFieldBalanceSheetsStandardAssetsNetFixedAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsIntangibles, "QuoteFieldBalanceSheetsStandardAssetsIntangibles") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsCostInExcess, "QuoteFieldBalanceSheetsStandardAssetsCostInExcess") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsNonCurrentDeferredIncomeTaxes, "QuoteFieldBalanceSheetsStandardAssetsNonCurrentDeferredIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsOtherNonCurrentAssets, "QuoteFieldBalanceSheetsStandardAssetsOtherNonCurrentAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardAssetsTotalNonCurrentAssets, "QuoteFieldBalanceSheetsStandardAssetsTotalNonCurrentAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesAccountsPayable, "QuoteFieldBalanceSheetsStandardLiabilitiesAccountsPayable") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesNotesPayable, "QuoteFieldBalanceSheetsStandardLiabilitiesNotesPayable") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesAccruedExpenses, "QuoteFieldBalanceSheetsStandardLiabilitiesAccruedExpenses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesAccruedLiabilities, "QuoteFieldBalanceSheetsStandardLiabilitiesAccruedLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesDeferredRevenues, "QuoteFieldBalanceSheetsStandardLiabilitiesDeferredRevenues") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesCurrentDeferredIncomeTaxes, "QuoteFieldBalanceSheetsStandardLiabilitiesCurrentDeferredIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesOtherCurrentLiabilities, "QuoteFieldBalanceSheetsStandardLiabilitiesOtherCurrentLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesTotalCurrentLiabilities, "QuoteFieldBalanceSheetsStandardLiabilitiesTotalCurrentLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesDeferredIncomeTaxes, "QuoteFieldBalanceSheetsStandardLiabilitiesDeferredIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesOtherNonCurrentLiabilities, "QuoteFieldBalanceSheetsStandardLiabilitiesOtherNonCurrentLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesPreferredSecuritiesOfSubsidiaryTrust, "QuoteFieldBalanceSheetsStandardLiabilitiesPreferredSecuritiesOfSubsidiaryTrust") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesPreferredEquityOutsideStockEquity, "QuoteFieldBalanceSheetsStandardLiabilitiesPreferredEquityOutsideStockEquity") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardLiabilitiesTotalNonCurrentLiabilities, "QuoteFieldBalanceSheetsStandardLiabilitiesTotalNonCurrentLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardCashFlow, "QuoteFieldBalanceSheetsStandardCashFlow") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardWorkingCapital, "QuoteFieldBalanceSheetsStandardWorkingCapital") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardFreeCashFlow, "QuoteFieldBalanceSheetsStandardFreeCashFlow") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsStandardInvestedCapital, "QuoteFieldBalanceSheetsStandardInvestedCapital") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsCashAndDueFromBanks, "QuoteFieldBalanceSheetsFinancialAssetsCashAndDueFromBanks") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsFedFundsSoldSecuritiesPurchased, "QuoteFieldBalanceSheetsFinancialAssetsFedFundsSoldSecuritiesPurchased") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsInterestBearingDepAtOtherBanks, "QuoteFieldBalanceSheetsFinancialAssetsInterestBearingDepAtOtherBanks") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsInvestmentSecuritiesNet, "QuoteFieldBalanceSheetsFinancialAssetsInvestmentSecuritiesNet") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsLoans, "QuoteFieldBalanceSheetsFinancialAssetsLoans") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsUnearnedPremiums, "QuoteFieldBalanceSheetsFinancialAssetsUnearnedPremiums") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsAllowanceForLoansAndLeaseLosses, "QuoteFieldBalanceSheetsFinancialAssetsAllowanceForLoansAndLeaseLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsNetLoans, "QuoteFieldBalanceSheetsFinancialAssetsNetLoans") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsPremisesAndEquipment, "QuoteFieldBalanceSheetsFinancialAssetsPremisesAndEquipment") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsDueFromCustomersAcceptance, "QuoteFieldBalanceSheetsFinancialAssetsDueFromCustomersAcceptance") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsTradingAccountSecurities, "QuoteFieldBalanceSheetsFinancialAssetsTradingAccountSecurities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsAccruedInterest, "QuoteFieldBalanceSheetsFinancialAssetsAccruedInterest") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsDeferredAcquisitionCost, "QuoteFieldBalanceSheetsFinancialAssetsDeferredAcquisitionCost") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsAccruedInvestmentIncome, "QuoteFieldBalanceSheetsFinancialAssetsAccruedInvestmentIncome") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsSeparateAccountBusiness, "QuoteFieldBalanceSheetsFinancialAssetsSeparateAccountBusiness") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsTimeDepositsPlaced, "QuoteFieldBalanceSheetsFinancialAssetsTimeDepositsPlaced") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsIntangibleAssets, "QuoteFieldBalanceSheetsFinancialAssetsIntangibleAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialAssetsOtherAssets, "QuoteFieldBalanceSheetsFinancialAssetsOtherAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesNonInterestBearingDeposits, "QuoteFieldBalanceSheetsFinancialLiabilitiesNonInterestBearingDeposits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesInterestBearingDeposits, "QuoteFieldBalanceSheetsFinancialLiabilitiesInterestBearingDeposits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesOtherLiabilities, "QuoteFieldBalanceSheetsFinancialLiabilitiesOtherLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesBankersAcceptanceOutstanding, "QuoteFieldBalanceSheetsFinancialLiabilitiesBankersAcceptanceOutstanding") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesFedFundsPurchasedSecuritiesSold, "QuoteFieldBalanceSheetsFinancialLiabilitiesFedFundsPurchasedSecuritiesSold") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedTaxes, "QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedInterestPayables, "QuoteFieldBalanceSheetsFinancialLiabilitiesAccruedInterestPayables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesOtherPayables, "QuoteFieldBalanceSheetsFinancialLiabilitiesOtherPayables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesClaimsAndClaimExpense, "QuoteFieldBalanceSheetsFinancialLiabilitiesClaimsAndClaimExpense") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesFuturePolicyBenefits, "QuoteFieldBalanceSheetsFinancialLiabilitiesFuturePolicyBenefits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesUnearnedPremiums, "QuoteFieldBalanceSheetsFinancialLiabilitiesUnearnedPremiums") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesPolicyHolderFunds, "QuoteFieldBalanceSheetsFinancialLiabilitiesPolicyHolderFunds") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesParticipatingPolicyholderEquity, "QuoteFieldBalanceSheetsFinancialLiabilitiesParticipatingPolicyholderEquity") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialLiabilitiesSeparateAccountsBusiness, "QuoteFieldBalanceSheetsFinancialLiabilitiesSeparateAccountsBusiness") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialEquityForeignCurrencyAdjustments, "QuoteFieldBalanceSheetsFinancialEquityForeignCurrencyAdjustments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnInvestments, "QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnForeignCurrency, "QuoteFieldBalanceSheetsFinancialEquityNetUnrealizedLossGainOnForeignCurrency") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsFinancialEquityNetOtherUnearnedLossesGains, "QuoteFieldBalanceSheetsFinancialEquityNetOtherUnearnedLossesGains") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldBalanceSheetsDate, "QuoteFieldBalanceSheetsDate") );

    //Financials - Cash flow fields
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowOperatingActivitiesNetIncomeOrLoss, "QuoteFieldCashFlowOperatingActivitiesNetIncomeOrLoss") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowOperatingActivitiesDeferredIncomeTaxes, "QuoteFieldCashFlowOperatingActivitiesDeferredIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowOperatingActivitiesOtherNonCashItems, "QuoteFieldCashFlowOperatingActivitiesOtherNonCashItems") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowInvestingActivitiesAcquisitions, "QuoteFieldCashFlowInvestingActivitiesAcquisitions") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowInvestingActivitiesOtherInvestingChangesNet, "QuoteFieldCashFlowInvestingActivitiesOtherInvestingChangesNet") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowInvestingActivitiesNetCashFromInvestingActivities, "QuoteFieldCashFlowInvestingActivitiesNetCashFromInvestingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancingActivitiesNetCashFromFinancingActivities, "QuoteFieldCashFlowFinancingActivitiesNetCashFromFinancingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancingActivitiesEffectOfExchangeRateChanges, "QuoteFieldCashFlowFinancingActivitiesEffectOfExchangeRateChanges") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancingActivitiesCashAtBeginningOfPeriod, "QuoteFieldCashFlowFinancingActivitiesCashAtBeginningOfPeriod") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancingActivitiesCashAtEndOfPeriod, "QuoteFieldCashFlowFinancingActivitiesCashAtEndOfPeriod") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesDepreciation, "QuoteFieldCashFlowStandardOperatingActivitiesDepreciation") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesAmortization, "QuoteFieldCashFlowStandardOperatingActivitiesAmortization") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesAmortizationOfIntangibles, "QuoteFieldCashFlowStandardOperatingActivitiesAmortizationOfIntangibles") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesOperatingGainsOrLosses, "QuoteFieldCashFlowStandardOperatingActivitiesOperatingGainsOrLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesExtraordinaryGainsOrLosses, "QuoteFieldCashFlowStandardOperatingActivitiesExtraordinaryGainsOrLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInReceivables, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInReceivables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInInventories, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInInventories") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPrepaidExpenses, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPrepaidExpenses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrentAssets, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrentAssets") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPayables, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInPayables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrLiabilities, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherCurrLiabilities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherWorkingCapital, "QuoteFieldCashFlowStandardOperatingActivitiesIncreaseOrDecreaseInOtherWorkingCapital") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromContinuingOperations, "QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromContinuingOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromDiscontinuedOperations, "QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromDiscontinuedOperations") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromOperatingActivities, "QuoteFieldCashFlowStandardOperatingActivitiesNetCashFromOperatingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesSaleOfPropertyPlantEquipment, "QuoteFieldCashFlowStandardInvestingActivitiesSaleOfPropertyPlantEquipment") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesSaleOfLongTermInvestments, "QuoteFieldCashFlowStandardInvestingActivitiesSaleOfLongTermInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesSaleOfShortTermInvestments, "QuoteFieldCashFlowStandardInvestingActivitiesSaleOfShortTermInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfPropertyPlantEquipment, "QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfPropertyPlantEquipment") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfLongTermInvestments, "QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfLongTermInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfShortTermInvestments, "QuoteFieldCashFlowStandardInvestingActivitiesPurchaseOfShortTermInvestments") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardInvestingActivitiesCashFromDiscInvestingActivities, "QuoteFieldCashFlowStandardInvestingActivitiesCashFromDiscInvestingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfDebt, "QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfCapitalStock, "QuoteFieldCashFlowStandardFinancingActivitiesIssuanceOfCapitalStock") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesRepaymentOfDebt, "QuoteFieldCashFlowStandardFinancingActivitiesRepaymentOfDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesRepurchaseOfCapitalStock, "QuoteFieldCashFlowStandardFinancingActivitiesRepurchaseOfCapitalStock") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesPaymentOfCashDividends, "QuoteFieldCashFlowStandardFinancingActivitiesPaymentOfCashDividends") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesOtherFinancingChargesNet, "QuoteFieldCashFlowStandardFinancingActivitiesOtherFinancingChargesNet") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesCashFromDiscFinancingActivities, "QuoteFieldCashFlowStandardFinancingActivitiesCashFromDiscFinancingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowStandardFinancingActivitiesNetChangeInCashAndCashEquivalents, "QuoteFieldCashFlowStandardFinancingActivitiesNetChangeInCashAndCashEquivalents") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesProvisionForLoanLosses, "QuoteFieldCashFlowFinancialOperatingActivitiesProvisionForLoanLosses") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesDepreciationandAmortization, "QuoteFieldCashFlowFinancialOperatingActivitiesDepreciationandAmortization") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesChangeInAssetsReceivables, "QuoteFieldCashFlowFinancialOperatingActivitiesChangeInAssetsReceivables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesChangeInLiabilitiesPayables, "QuoteFieldCashFlowFinancialOperatingActivitiesChangeInLiabilitiesPayables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesInvestmentSecuritiesGain, "QuoteFieldCashFlowFinancialOperatingActivitiesInvestmentSecuritiesGain") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesNetPolicyAcquisitionCosts, "QuoteFieldCashFlowFinancialOperatingActivitiesNetPolicyAcquisitionCosts") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesRealizedInvestmentGains, "QuoteFieldCashFlowFinancialOperatingActivitiesRealizedInvestmentGains") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesNetPremiumsReceivables, "QuoteFieldCashFlowFinancialOperatingActivitiesNetPremiumsReceivables") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesChangeInIncomeTaxes, "QuoteFieldCashFlowFinancialOperatingActivitiesChangeInIncomeTaxes") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialOperatingActivitiesNetCashFromOperatingActivities, "QuoteFieldCashFlowFinancialOperatingActivitiesNetCashFromOperatingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialInvestingActivitiesProceedsFromSaleMatInv, "QuoteFieldCashFlowFinancialInvestingActivitiesProceedsFromSaleMatInv") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfInvestmentSecurities, "QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfInvestmentSecurities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialInvestingActivitiesNetIncreaseFedFundsSold, "QuoteFieldCashFlowFinancialInvestingActivitiesNetIncreaseFedFundsSold") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfPropertyAndEquipment, "QuoteFieldCashFlowFinancialInvestingActivitiesPurchaseOfPropertyAndEquipment") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInDeposits, "QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInDeposits") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesCashDividendsPaid, "QuoteFieldCashFlowFinancialFinancingActivitiesCashDividendsPaid") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesRepaymentOfLongTermDebt, "QuoteFieldCashFlowFinancialFinancingActivitiesRepaymentOfLongTermDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesChangeOfShortTermDebt, "QuoteFieldCashFlowFinancialFinancingActivitiesChangeOfShortTermDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfLongTermDebt, "QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfLongTermDebt") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfPreferredStock, "QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfPreferredStock") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfCommonStock, "QuoteFieldCashFlowFinancialFinancingActivitiesIssuanceOfCommonStock") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesPurchaseOfTreasuryStock, "QuoteFieldCashFlowFinancialFinancingActivitiesPurchaseOfTreasuryStock") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesOtherFinancingActivities, "QuoteFieldCashFlowFinancialFinancingActivitiesOtherFinancingActivities") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInCashAndEquivalents, "QuoteFieldCashFlowFinancialFinancingActivitiesNetChangeInCashAndEquivalents") );
    quoteFieldTypeToStr.insert( std::pair<uint8_t, std::string>(QuoteFieldCashFlowDate, "QuoteFieldCashFlowDate") );
    return quoteFieldTypeToStr;
}

std::map<uint8_t, std::string> quoteFieldTypeToStr = createQuoteFieldTypeMap();

Jsonifier::Jsonifier( void ) {
}

Jsonifier::~Jsonifier( void ) {
}

/*static*/ JSONNode Jsonifier::jsonifyAtTime( std::string name,
                                                LPATTIME pTime ) {
    JSONNode n( JSON_NODE );
    n.set_name( name );
    n.push_back( JSONNode( "year", pTime->year ) );
    n.push_back( JSONNode( "month", pTime->month ) );
    n.push_back( JSONNode( "dayOfWeek", pTime->dayOfWeek ) );
    n.push_back( JSONNode( "day", pTime->day ) );
    n.push_back( JSONNode( "hour", pTime->hour ) );
    n.push_back( JSONNode( "minute", pTime->minute ) );
    n.push_back( JSONNode( "second", pTime->second ) );
    n.push_back( JSONNode( "milliseconds", pTime->milliseconds ) );
    return n;
}

/*static*/ JSONNode Jsonifier::jsonifyAtSymbol( LPATSYMBOL pSymbol ) {
    JSONNode s( JSON_NODE );
    s.set_name( "ATSymbol" );

    char symbolStr[512] = {0};
    std::string str = Helper::ConvertString(pSymbol->symbol, Helper::StringLength(pSymbol->symbol));
    strncpy(symbolStr, str.c_str(), sizeof(symbolStr));
    s.push_back( JSONNode( "symbolStr", symbolStr ) );
    s.push_back( JSONNode( "symbolType", symbolTypeToStr[pSymbol->symbolType] ) );
    s.push_back( JSONNode( "exchangeType", exchangeTypeToStr[pSymbol->exchangeType] ) );
    s.push_back( JSONNode( "countryType", countryTypeToStr[pSymbol->countryType] ) );

    return s;
}

/*static*/ std::string Jsonifier::getSymbolType( uint8_t symbolType ) {
    return symbolTypeToStr[symbolType];
}
/*static*/ std::string Jsonifier::getExchangeType( uint8_t exchangeType ) {
    return exchangeTypeToStr[exchangeType];
}
/*static*/ std::string Jsonifier::getCountryType( uint8_t countryType ) {
    return countryTypeToStr[countryType];
}
/*static*/ std::string Jsonifier::getFieldStatus( uint8_t fieldStatus ) {
    return fieldStatusToStr[fieldStatus];
}
/*static*/ std::string Jsonifier::getQuoteFieldType( uint8_t quoteFieldType ) {
    return quoteFieldTypeToStr[quoteFieldType];
}
