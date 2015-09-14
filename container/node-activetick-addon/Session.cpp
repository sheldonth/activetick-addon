#include "StdAfx.h"
#include "Session.h"
#include <stdio.h>
#include <cstring>

#include <iostream>

#include <node.h>
#include "import/atfeed-cppsdk/example/Helper.h"
#include "import/libjson/libjson.h"

APISession* APISession::s_pInstance = NULL;
std::queue< JSONNode > *APISession::s_pInboundMsgs = NULL;

using namespace v8;

APISession::APISession( std::queue< JSONNode > *pInboundMsgs )
    : m_hSession( 0 ),
      m_hLastRequest( 0 ) {
    m_hSession = ATCreateSession();
    s_pInstance = this;
    s_pInboundMsgs = pInboundMsgs;
}

APISession::~APISession( void ) {
    ATDestroySession( m_hSession );
    s_pInstance = NULL;
    s_pInboundMsgs = NULL;
}

bool APISession::Init( const ATGUID& apiUserid,
                       const std::string& serverIpAddress,
                       uint32_t serverPort, const wchar16_t* userid,
                       const wchar16_t* password) {
    if( Helper::StringLength( userid ) >= _countof( m_userid ) ||
        Helper::StringLength( password ) >= _countof( m_password ) )
        return false;

    Destroy();

    Helper::CopyString( m_userid, userid );
    Helper::CopyString( m_password, password );

    bool rc = ATSetAPIUserId( m_hSession, (LPATGUID)&apiUserid );

    if(rc == true) {
        rc = ATInitSession( m_hSession, serverIpAddress.c_str(),
                            serverIpAddress.c_str(), serverPort,
                            ATSessionStatusChangeCallback, true );
    }

    return rc;
}

bool APISession::Destroy()
{
    ATShutdownSession(m_hSession);
    return true;
}

/*static*/ void APISession::ATSessionStatusChangeCallback(
                        uint64_t hSession, ATSessionStatusType statusType ) {
    std::string strStatusType;
    switch(statusType)
    {
      case SessionStatusConnected:
        strStatusType = "SessionStatusConnected";
        break;
      case SessionStatusDisconnected:
        strStatusType = "SessionStatusDisconnected";
        break;
      case SessionStatusDisconnectedDuplicateLogin:
        strStatusType = "SessionStatusDisconnectedDuplicateLogin"; 
        break;
      default:
        strStatusType = "None";
        break;
    }

    if(statusType == SessionStatusConnected)
    {
      JSONNode n(JSON_NODE);
      n.push_back( JSONNode( "foo", "bar" ) );
      s_pInboundMsgs->push( n );
      
      APISession::s_pInstance->m_hLastRequest = ATCreateLoginRequest(hSession, APISession::s_pInstance->m_userid, APISession::s_pInstance->m_password, APISession::ATLoginResponseCallback);
      bool rc = ATSendRequest(hSession, APISession::s_pInstance->m_hLastRequest, DEFAULT_REQUEST_TIMEOUT, APISession::ATRequestTimeoutCallback);
    }
    
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATSessionStatus" ) );
    n.push_back( JSONNode( "hSession" , hSession ) );
    n.push_back( JSONNode( "statusType", strStatusType ) );
    s_pInboundMsgs->push( n );
}

/*static*/ void APISession::ATLoginResponseCallback(
                        uint64_t hSession, uint64_t hRequest,
                        LPATLOGIN_RESPONSE pResponse ) {
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATLoginResponse" ) );
    n.push_back( JSONNode( "hSession", hSession ) );
    n.push_back( JSONNode( "hRequest", hRequest ) );
    n.push_back( jsonifyAtloginResponse( pResponse ) );
    s_pInboundMsgs->push( n );
}

/*static*/ void APISession::ATServerTimeUpdateCallback(LPATTIME pServerTime)
{
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATServerTimeUpdate" ) );
    n.push_back( m_jsonifier.jsonifyAtTime( "serverTime", pServerTime ) );
    s_pInboundMsgs->push( n );
}    

/*static*/ void APISession::ATRequestTimeoutCallback(uint64_t hOrigRequest)
{
    JSONNode n( JSON_NODE );
    n.push_back( JSONNode( "messageId", "ATRequestTimeout" ) );
    n.push_back( JSONNode( "hOrigRequest", hOrigRequest ) );
    s_pInboundMsgs->push( n );
}

/*static*/ JSONNode APISession::jsonifyAtloginResponse(
                            LPATLOGIN_RESPONSE pResponse ) {
    std::string strLoginResponseType;
    switch(pResponse->loginResponse)
    {
      case LoginResponseSuccess:
        strLoginResponseType = "LoginResponseSuccess"; break;
      case LoginResponseInvalidUserid:
        strLoginResponseType = "LoginResponseInvalidUserid"; break;
      case LoginResponseInvalidPassword:
        strLoginResponseType = "LoginResponseInvalidPassword"; break;
      case LoginResponseInvalidRequest:
        strLoginResponseType = "LoginResponseInvalidRequest"; break;
      case LoginResponseLoginDenied:
        strLoginResponseType = "LoginResponseLoginDenied"; break;
      case LoginResponseServerError:
        strLoginResponseType = "LoginResponseServerError"; break;
      default: strLoginResponseType = "unknown"; break;
    }
    
    
    JSONNode n( JSON_NODE );
    n.set_name( "ATLoginResponse" );
    n.push_back( JSONNode( "loginResponse", pResponse->loginResponse ) );
    n.push_back( JSONNode( "loginResponseString", strLoginResponseType ) );

    // JSONNode permissions( JSON_ARRAY );
    // permissions.set_name( "permissions" );
    // for ( size_t i = 0; i < 255; i++ ) {
    //     permissions.push_back( JSONNode( "permissionEntry", pResponse->permissions[i] ) );
    // }
    // n.push_back( permissions );  

    n.push_back( m_jsonifier.jsonifyAtTime( 
                    "serverTime", &pResponse->serverTime ) );
    return n;
}
