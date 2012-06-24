#!/bin/bash

cd `dirname "$0"`

protoc --cpp_out="./" "Message.proto"
