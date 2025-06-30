#!/bin/bash
set -e  # Exit immediately if any command fails

# Create or clean the build directory
if [ ! -d build ]; then
    mkdir build
fi

# Step 1: Configure with CMake
cmake -S . -B build

# Step 2: Build the all_tests target
cmake --build build --target all_tests

# Step 3: Run the tests
echo -e "\nRunning all_tests...\n"
./build/all_tests
