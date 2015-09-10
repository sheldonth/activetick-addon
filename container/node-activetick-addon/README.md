node-activetick-addon
=====================
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/dchem/node-activetick-addon?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

[![Build Status](https://gitlord.com:8080/job/node-activetick-addon/badge/icon)](https://gitlord.com:8080/job/node-activetick-addon)

ActiveTick API addon for Node.js

Author: Jae Yang - [dchem] (https://github.com/dchem/)

### Change Notes:
* 2015-09-09 - 1.0.10 - Removes github nonsense
* 2015-06-27 - 1.0.8  - Fixes build (removed sourceforge)
* 2015-05-25 - 1.0.0  - Working 1.0 version
* 2015-02-18 - 0.0.1  - Initial commit

### Installation dependency
* Download Activetick cppsdk from Activetick.com website, unpack into working
  directory where you will run ```npm install activetick```.
* Install Python 2.7
* Install node-gyp
```
npm install node-gyp -g
```
* Install unzip if Linux
```
sudo apt-get install unzip
```

### Additional installation dependency for Windows:
* Install MinGW
* Install msys-unzip instead of unzip
* Install msys-wget
```
mingw-get install msys-unzip
mingw-get install msys-wget
```
* Install Microsoft Visual Studio

### Installation from NPM:
```
npm install activetick
```

For Windows with MSVS 2013:
```
npm install activetick --msvs_version=2013
```

For Windows with MSVS 2012:
```
npm install activetick --msvs_version=2012
```
Alternatively, include GYP_MSVS_VERSION=2012 or GYP_MSVS_VERSION=2013 in 
environment variables for Windows.

### Additional installation dependency for OS X:
* Install xcode command line tools
* Install homebrew
* Install wget through homebrew

### Installation from git repo:

1. Make sure to have Activetick API package downloaded to two directories up from this project
2. Run the preinstall.sh which does the following:
  * Copies the Activetick API package and places them in the import directory
  * Download libjson 7.6.1
3. ```node-gyp rebuild```
4. If build fails because you have VS2012, use ```node-gyp --msvs_version=2012 rebuild```

### Usage
1. Require activetick
2. Create event handlers
3. Register event handlers for messageIds
4. Incoke connect
5. ...
6. Profit!

```js
var addon = require('activetick');
var messageIds = addon.messageIds;
var api = new addon.NodeActivetick();

var activetickCb = function (data) {
  console.log(JSON.stringify(data,null,2));
};

// See messageId.js for message types to be tracked
Object.keys(messageIds).forEach(function (messageId) {
  api.handlers[messageId] = activetickCb;
});

// Don't put credentials in your scripts. Make sure you export
//   them as environment variables
var connected = api.connect( process.env.ATAPIKEY,
                             "activetick1.activetick.com",
                             5000,
                             process.env.ATUID,
                             process.env.ATPWD );

if (connected) {
  api.beginProcessing();
}
```

## Activetick API Methods
For more details, see activetick.js or run jsdoc on the package directory
```js
.getSessionHandle()
.closeAllATRequests()
.closeATRequest()
.sendATBarHistoryDbRequest( request )
.sendATLoginRequest( request )
.sendATMarketHolidaysRequest( request )
.sendATMarketMoversDbRequest( request )
.sendATMarketMoversStreamRequest( request )
.sendATQuoteDbRequest( request )
.sendATQuoteStreamRequest( request )
.sendATTickHistoryDbRequest( request )
.sendATSectorListRequest( request )
.sendATConstituentListRequest( request )
.connect( apiKey, serverAddr, port, userid, passwd )

```

### Issues:
* See issues list in https://github.com/dchem/node-activetick-addon/issues?state=open

### License
Copyright (c) 2015 Jae Yang. See LICENSE file for license rights and limitations (MIT).
