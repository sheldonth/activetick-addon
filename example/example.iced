ActiveTick = require('../ActiveTick').ActiveTick
fs = require 'fs'

config = require './config.js'

# SYMBOL.EXCHANGE@COUNTRY -> CSCO.Q@U, CSCO.Q, CSCO, CSCO@U; .ABCDE.Q@U, .ABCDE.Q, .ABCDE;

main = () ->
  await a = new ActiveTick(defer())
  await a.connect config.url, config.port, config.api_key, config.username, config.password, defer(result)
  a.barHistoryDBRequest 'T'
  # await a.listRequest 'ATConstituentListOptionChain', 'fb',  defer(yang)
  # await a.listRequest 'ATConstituentListOptionChain', 'aapl',  defer(aapl)
  # getQuote = (quote) ->
  #   console.log 'getQuote'
  #   console.log quote
  # sym1 = '.' + yang.symbols[22].symbol
  # sym2 = '.' + yang.symbols[4].symbol
  # sym3 = '.' + yang.symbols[188].symbol
  # sym4 = '.' + yang.symbols[588].symbol
  # sym5 = '.' + aapl.symbols[118].symbol
  # sym6 = '.' + aapl.symbols[277].symbol
  # 
  # 
  # a.beginQuoteStream [sym1, sym2, sym3, sym4, sym5, sym6], 'StreamRequestSubscribe', getQuote, (result) ->
  #   console.log result

main() if not module.parent

