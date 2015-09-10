#pragma once
#include <string>
#include <queue>
#include <node.h>
#include "Jsonifier.h"
#include "import/atfeed-cppsdk/include/ActiveTickServerAPI/ActiveTickServerAPI.h"
#include "import/libjson/_internal/Source/JSONNode.h"

using namespace v8;
class APISession
{
public:
    APISession( std::queue< JSONNode > *pInboundMsgs );
    virtual ~APISession(void);

public:
    uint64_t GetSessionHandle() const { return m_hSession; }

public:
    bool Init( const ATGUID& apiUserid, 
               const std::string& serverIpAddress, 
               uint32_t serverPort,
               const wchar16_t* userid, 
               const wchar16_t* password );
    bool Destroy();

private:
    static void ATSessionStatusChangeCallback(
                        uint64_t hSession,
                        ATSessionStatusType statusType);
    static void ATLoginResponseCallback(
                        uint64_t hSession,
                        uint64_t hRequest,
                        LPATLOGIN_RESPONSE pResponse );
    static void ATServerTimeUpdateCallback( LPATTIME pTime );
    static void ATRequestTimeoutCallback( uint64_t hOrigRequest );

private:
    static JSONNode jsonifyAtloginResponse( LPATLOGIN_RESPONSE pResponse );

private:
    uint64_t    m_hSession;
    uint64_t    m_hLastRequest;
    wchar16_t   m_userid[50];
    wchar16_t   m_password[50];
    
private:
    static Jsonifier m_jsonifier;
    static APISession*  s_pInstance;
    static std::queue< JSONNode > *s_pInboundMsgs;
};
