#!/bin/bash
set -e
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
ctest --output-on-failure
echo "---"
./firmwarecbom ../firmware_samples IoT-Sensor-v1 output
echo "---"
cat output/report.txt
