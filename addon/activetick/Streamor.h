#pragma once
#include "Requestor.h"
#include <ActiveTickServerAPI/ActiveTickServerAPI.h>
#include <ActiveTickServerAPI/ActiveTickServerRequestor.h>
#include <node.h>

using namespace v8;

class Streamer : public ActiveTickStreamListener, public Requestor
{
  
}