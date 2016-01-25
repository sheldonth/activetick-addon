ATExchangeType = { 
  ExchangeAMEX :'A',
  ExchangeNasdaqOmxBx : 'B',
  ExchangeNationalStockExchange : 'C',
  ExchangeFinraAdf : 'D', 
  ExchangeCQS : 'E',
  ExchangeForex : 'F',
  ExchangeInternationalSecuritiesExchange : 'I',
  ExchangeEdgaExchange : 'J', 
  ExchangeEdgxExchange : 'K',
  ExchangeChicagoStockExchange : 'M',
  ExchangeNyseEuronext : 'N',
  ExchangeNyseArcaExchange : 'P', 
  ExchangeNasdaqOmx : 'Q', 
  ExchangeCTS : 'S',
  ExchangeCTANasdaqOMX : 'T',
  ExchangeOTCBB : 'U', 
  ExchangeNNOTC : 'u',
  ExchangeChicagoBoardOptionsExchange : 'W',
  ExchangeNasdaqOmxPhlx : 'X',
  ExchangeBatsYExchange : 'Y', 
  ExchangeBatsExchange : 'Z', 
  ExchangeCanadaToronto : 'T',
  ExchangeCanadaVenture : 'V',
  ExchangeOpra : 'O', 
  ExchangeOptionBoston : 'B',
  ExchangeOptionCboe : 'C',
  ExchangeOptionNyseArca : 'N',
  ExchangeOptionC2 : 'W', 
  ExchangeOptionNasdaqOmxBx : 'T',
  ExchangeComposite : ' ' 
}

ATCountryTypes = {
  CountryInternational : 'I',
  CountryUnitedStates : 'U',
  CountryCanada : 'C'
}

ATConstituentRequestTypes = [
  'ATConstituentListIndex',
  'ATConstituentListSector',
  'ATConstituentListOptionChain'
]

ATStreamRequestTypes = [
  'StreamRequestSubscribe',
  'StreamRequestUnsubscribe',
  'StreamRequestSubscribeQuotesOnly',
  'StreamRequestUnsubscribeQuotesOnly',
  'StreamRequestSubscribeTradesOnly',
  'StreamRequestUnsubscribeTradesOnly'
]

ATBarHistoryType = [
  'BarHistoryIntraday',
  'BarHistoryDaily',
  'BarHistoryWeekly'
]

module.exports = {ATConstituentRequestTypes, ATStreamRequestTypes, ATBarHistoryType, ATExchangeType, ATCountryTypes}