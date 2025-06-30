#!/bin/bash
set -e

# Clean build directory
rm -rf build

# Configure the project
cmake -S . -B build

# Build the all_tests target
cmake --build build --target all_tests

# Run the tests executable
./build/all_tests
