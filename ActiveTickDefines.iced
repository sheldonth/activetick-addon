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

module.exports = {ATConstituentRequestTypes, ATStreamRequestTypes, ATBarHistoryType}