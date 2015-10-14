// Copyright 2015-present Sheldon Thomas
#include <node.h>
#include "NodeActiveTick.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    NodeActiveTick::Init(exports);
}

NODE_MODULE(NodeActiveTickAddon, InitAll);