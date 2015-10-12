#! /bin/bash

protoc --cpp_out=. messages.proto
# pbjs messages.proto -t json > messages.js