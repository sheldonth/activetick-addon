{
    "package": "NodeActiveTickProto",
    "messages": [
        {
            "name": "ATLoginResponse",
            "fields": [
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "loginResponseType",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "string",
                    "name": "loginResponseString",
                    "id": 2
                }
            ]
        },
        {
            "name": "ATConstituentResponse",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "ATSymbol",
                    "name": "symbols",
                    "id": 1
                }
            ]
        },
        {
            "name": "ATQuoteStreamResponse",
            "fields": [
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "quoteStreamResponseType",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "quoteResponseCount",
                    "id": 2
                },
                {
                    "rule": "repeated",
                    "type": "ATQuoteStreamResponseItem",
                    "name": "quoteStreamItems",
                    "id": 3
                }
            ]
        },
        {
            "name": "ATQuoteStreamResponseItem",
            "fields": [
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "responseType",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "ATSymbol",
                    "name": "symbol",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "symbolStatus",
                    "id": 3
                }
            ]
        },
        {
            "name": "ATTime",
            "fields": [
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "year",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "month",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "dayOfWeek",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "day",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "hour",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "minute",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "second",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "millisecond",
                    "id": 8
                }
            ]
        },
        {
            "name": "ATQuoteStreamTradeUpdate",
            "fields": [
                {
                    "rule": "optional",
                    "type": "ATSymbol",
                    "name": "tradeSymbol",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "tradeMessageFlags",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "tradeConditionType",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "tradeExchange",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "tradePrice",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "tradeSize",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "ATTime",
                    "name": "tradeTime",
                    "id": 7
                }
            ]
        },
        {
            "name": "ATQuoteStreamQuoteUpdate",
            "fields": [
                {
                    "rule": "optional",
                    "type": "ATSymbol",
                    "name": "quoteSymbol",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "quoteCondition",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "quoteBidExchange",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "quoteAskExchange",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "quoteBidPrice",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "quoteAskPrice",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "quoteBidSize",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "quoteAskSize",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "ATTime",
                    "name": "quoteTime",
                    "id": 9
                }
            ]
        },
        {
            "name": "ATQuoteStreamRefreshUpdate",
            "fields": [
                {
                    "rule": "optional",
                    "type": "ATSymbol",
                    "name": "refreshSymbol",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "refreshLastPrice",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "refreshOpenPrice",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "refreshHighPrice",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "ATPrice",
                    "name": "refreshLowPrice",
                    "id": 5
                }
            ]
        },
        {
            "name": "ATSymbol",
            "fields": [
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "symbol",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "symbol_long",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "symbolType",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "exchangeType",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "countryType",
                    "id": 5
                }
            ]
        },
        {
            "name": "ATPrice",
            "fields": [
                {
                    "rule": "required",
                    "type": "double",
                    "name": "price",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "precision",
                    "id": 2
                }
            ]
        },
        {
            "name": "ATQuote",
            "fields": [
                {
                    "rule": "required",
                    "type": "ATSymbol",
                    "name": "symbol",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "ATPrice",
                    "name": "bidPrice",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "ATPrice",
                    "name": "askPrice",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "bidSize",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "askSize",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "quoteConditionId",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "ATTime",
                    "name": "serverTime",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "bidExchangeId",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "askExchangeId",
                    "id": 9
                }
            ]
        }
    ]
}