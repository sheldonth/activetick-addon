console.log 'herro'
AT = require('..')
fs = require 'fs'
ActiveTick = AT.ActiveTick

config = require './config.js'
  
# SYMBOL.EXCHANGE@COUNTRY -> CSCO.Q@U, CSCO.Q, CSCO, CSCO@U; .ABCDE.Q@U, .ABCDE.Q, .ABCDE;
# YYYYMMDDHHMMSS

main = () ->
  await a = new ActiveTick(defer())
  await a.connect config.api_key, config.username, config.password, defer(result)
  await a.listRequest 'ATConstituentListOptionChain', 'fb',  defer(yang)
  # await a.listRequest 'ATConstituentListOptionChain', 'aapl',  defer(aapl)
  a.on 'trade', (trade) ->
    console.log trade
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

  virgin_america = 'VA'
  # att = 'T'
  # facebook = 'FB'
  # apple = 'AAPL'
  
  a.beginQuoteStream [virgin_america], 'StreamRequestSubscribe', (result) ->
    console.log 'getQuote result1', result.quoteStreamItems[0].symbol
  # a.beginQuoteStream [facebook, apple], 'StreamRequestSubscribe', (result) ->
    # console.log 'getQuote2 result2', result.symbol
    
  # a.barHistoryDBRequest facebook, 'BarHistoryIntraday', 20, '20150908100000', '20150910100000', (result) ->
    # console.log 'barhistory', result
  

main() if not module.parent

