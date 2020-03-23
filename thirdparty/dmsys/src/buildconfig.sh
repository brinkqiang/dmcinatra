#!/bin/bash

./dmconfig --PROTONAME=dmconfig.proto

./protoc --cpp_out=. dmconfig.proto
