#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-ggdb -Wfatal-errors" -DCMAKE_CXX_COMPILER="clang++" ..
cmake --build .
