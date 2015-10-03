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
                }
            ]
        },
        {
            "name": "ATServerTime",
            "fields": [
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "year",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "month",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "dayOfWeek",
                    "id": 3
                },
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "day",
                    "id": 4
                }
            ]
        },
        {
            "name": "ATSymbol",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "symbol",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "symbolType",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "exchangeType",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "countryType",
                    "id": 4
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
                    "type": "ATServerTime",
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