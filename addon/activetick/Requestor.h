#pragma once
#include <queue>
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <ActiveTickServerAPI/ActiveTickServerRequestor.h>
#include <node.h>

using namespace v8;

class Requestor : public ActiveTickServerRequestor
{
public:
  Requestor(const uint64_t session);
  virtual ~Requestor(void);
private:
  uint64_t session_handle;
  
  virtual void OnATConstituentListResponse( uint64_t origRequest,
                                            LPATSYMBOL pSymbols,
                                            uint32_t symbolsCount);

  virtual void OnATQuoteStreamResponse (  uint64_t origRequest,
                                          ATStreamResponseType responseType,
                                          LPATQUOTESTREAM_RESPONSE pResponse,
                                          uint32_t responseCount);
                                          
};