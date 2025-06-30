#!/bin/bash
set -e

# Clean build directory
rm -rf build

# Configure the project
cmake -S . -B build

# Build the WeatherApp target
cmake --build build --target WeatherApp

# Run the WeatherApp executable
./build/WeatherApp
