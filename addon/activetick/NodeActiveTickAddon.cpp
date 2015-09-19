#include <node.h>
#include "NodeActivetick.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    NodeActivetick::Init(exports);
}

NODE_MODULE(NodeActivetickAddon, InitAll);