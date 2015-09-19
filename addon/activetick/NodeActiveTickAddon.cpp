#include <node.h>
#include "NodeActiveTick.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    NodeActiveTick::Init(exports);
}

NODE_MODULE(NodeActiveTickAddon, InitAll);