ActiveTick = require('../ActiveTick').ActiveTick
fs = require 'fs'

config = require './config.js'

# SYMBOL.EXCHANGE@COUNTRY -> CSCO.Q@U, CSCO.Q, CSCO, CSCO@U; .ABCDE.Q@U, .ABCDE.Q, .ABCDE;
# YYYYMMDDHHMMSS

main = () ->
  await a = new ActiveTick(defer())
  await a.connect config.url, config.port, config.api_key, config.username, config.password, defer(result)
  await a.listRequest 'ATConstituentListOptionChain', 'fb',  defer(yang)
  # await a.listRequest 'ATConstituentListOptionChain', 'aapl',  defer(aapl)
  getQuote1 = (quote) ->
    console.log 'getQuote'
    console.log quote
  getQuote2 = (quote) ->
    console.log 'getQuote2'
    console.log quote
    
  sym1 = '.' + yang.symbols[22].symbol
  sym2 = '.' + yang.symbols[4].symbol
  sym3 = '.' + yang.symbols[188].symbol
  sym4 = '.' + yang.symbols[588].symbol
  # sym5 = '.' + aapl.symbols[118].symbol
  # sym6 = '.' + aapl.symbols[277].symbol
  att = 't'
  facebook = 'fb'
  apple = 'aapl'
  
  a.beginQuoteStream [att], 'StreamRequestSubscribe', getQuote1, (result) ->
    console.log 'getQuote1', result
  a.beginQuoteStream [facebook, apple], 'StreamRequestSubscribe', getQuote2, (result) ->
    console.log 'getQuote2', result
    
  a.barHistoryDBRequest facebook, 'BarHistoryIntraday', 20, '20150908100000', '20150910100000', (result) ->
    console.log 'barhistory', result
  

main() if not module.parent

