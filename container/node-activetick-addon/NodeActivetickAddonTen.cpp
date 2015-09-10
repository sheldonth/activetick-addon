#include <node.h>
#include "NodeActivetickTen.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    NodeActivetick::Init(exports);
}

NODE_MODULE(NodeActivetickAddon, InitAll);
