ActiveTick = require('..').ActiveTick
log = require('single-line-log').stdout
fs = require 'fs'

config = require './config.js'
  
# SYMBOL.EXCHANGE@COUNTRY -> CSCO.Q@U, CSCO.Q, CSCO, CSCO@U; .ABCDE.Q@U, .ABCDE.Q, .ABCDE;
# YYYYMMDDHHMMSS
# Get options
# await a.listRequest 'ATConstituentListOptionChain', 'fb',  defer(yang)
# Stream Option
# a.beginQuoteStream '.' + yang[12]


updateLogStatement = (tickers, lastTrades, lastQuotes) =>
  statement = ''
  for t in tickers
    lineStatement = t + '\t'
    if (lt = lastTrades[t])?
      lineStatement += lt.tradeSize + ' @ ' + lt.tradePrice.price
    if (lq = lastQuotes[t])?
      lineStatement += '\t| ' + lq.quoteBidPrice.price + ' ' + lq.quoteAskPrice.price
    lineStatement += '\n'
    statement += lineStatement
  log statement
      
  if @last_trade? and @last_quote?
    logstring = last_trade.tradeSize + ' @ ' + last_trade.tradePrice.price + '\n' + \
    ' Bid: ' + last_quote.quoteBidPrice.price + ' Ask: ' + last_quote.quoteAskPrice.price
    log logstring


main = () ->
  await a = new ActiveTick(defer())
  await a.connect config.api_key, config.username, config.password, defer(result)
  # a.quoteDBRequest 'AAPL,NFLX,MSFT', 'QuoteFieldIncomeStatementBasicEPSFromContinuingOperations', (quote) ->
  #   console.log quote
  #   process.exit()
    # 'QuoteFieldSymbol,QuoteFieldBalanceSheetsShareDataTotalCommonSharesOutstanding,QuoteFieldIncomeStatementBasicEPSFromContinuingOperations,QuoteFieldBidExchange,QuoteFieldLastPrice,QuoteFieldBidPrice'
  # @last_trades = {}
  # @last_quotes = {}
  a.on 'trade', (trade) =>
    console.log trade
    # @last_trades[trade.tradeSymbol.symbol] = trade
  a.on 'quote', (quote) =>
    console.log quote
    # @last_quotes[quote.quoteSymbol.symbol] = quote

  virgin_america = 'VA'
  a.subscribe virgin_america, (result) ->
    st = 'Logging Quote Stream: '
    console.log "Result " + result

  # a.beginQuoteStream [facebook, apple], 'StreamRequestSubscribe', (result) ->
  #   console.log 'getQuote2 result2', result.symbol
    
  # a.barHistoryDBRequest facebook, 'BarHistoryIntraday', 20, '20150908100000', '20150910100000', (result) ->
  #   console.log 'barhistory', result
  

main() if not module.parent

