#!/bin/bash

cmake -S . -B build -DCMAKE_BUILD_TYPE=debug
cmake --build build && ./build/bin/sfml
