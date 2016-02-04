_ = require 'underscore'

# Enums defined in here that the particular problem they aren't integer sequenced
# they use char underlying types, and as such require definition on the javascript side

ATExchangeTypes = { 
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

ATExchangeTypes_i = _.invert(ATExchangeTypes)

exchange_type_for_char = (char) ->
  exchangeKey = new Buffer([char]).toString 'utf8'
  exchange = ATExchangeTypes_i[exchangeKey]
  return exchange

ATSymbolTypes = { 
  SymbolStock : 'S',
  SymbolIndex : 'I',
  SymbolStockOption : 'O',
  SymbolBond : 'B', 
  SymbolMutualFund : 'M',
  SymbolTopMarketMovers : 'T',
  SymbolCurrency : 'C' 
}

ATSymbolTypes_i = _.invert(ATSymbolTypes)

symbol_type_for_char = (char) ->
  symbolKey = new Buffer([char]).toString 'utf8'
  symbol = ATSymbolTypes_i[symbolKey]
  return symbol

ATOptionTypes = { 
  OptionTypeCall : 'C',
  OptionTypePut : 'P'
}

ATOptionTypes_i = _.invert(ATOptionTypes)

option_type_for_char = (char) ->
  optionKey = new Buffer([char]).toString 'utf8'
  option = ATOptionTypes_i[optionKey]
  return option

ATCountryTypes = {
  CountryInternational : 'I',
  CountryUnitedStates : 'U',
  CountryCanada : 'C'
}

ATCountryTypes_i = _.invert(ATCountryTypes)

country_type_for_char = (char) ->
  countryKey = new Buffer([char]).toString 'utf8'
  country = ATCountryTypes_i[countryKey]
  return country

module.exports = {
  ATExchangeTypes,
  ATCountryTypes,
  ATSymbolTypes,
  ATOptionTypes,
  exchange_type_for_char,
  country_type_for_char,
  option_type_for_char,
  symbol_type_for_char
}
        
        