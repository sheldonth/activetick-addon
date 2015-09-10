#pragma once
#include <string>
#include <cstring>
#include <node.h>

using namespace v8;

class JSONNode;

class AtJsonParser {
public:
    AtJsonParser();
    ~AtJsonParser();

    Handle<Object> parse(const JSONNode& n);
private:
    bool filterAsString( const std::string& node_name );
    bool filterAsNumber( const std::string& node_name );
    bool filterAsInteger( const std::string& node_name );
    bool filterAsBoolean( const std::string& node_name );
};
