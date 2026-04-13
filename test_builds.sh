#! /bin/sh

set -e
rm -rf variants
scons -f SConsMatrix check
cmake -B variants/cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build variants/cmake --config Debug
