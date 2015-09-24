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
        }
    ]
}