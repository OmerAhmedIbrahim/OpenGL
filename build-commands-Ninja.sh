#!/bin/bash
cmake -G Ninja -S . -B .\cmake-build-debug
cmake --build .\cmake-build-debug
cp .\src\shaders\Vertex.txt .\cmake-build-debug\Vertex.txt
cp .\src\shaders\Fragment.txt .\cmake-build-debug\Fragment.txt