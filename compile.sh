#!/bin/bash

# This script compiles and runs the program.

set -euo pipefail

# Compile the program with all warnings enabled, C++11 features enabled and pthread library linked
g++ -Wall -Werror -std=c++11 -pthread main.cpp fuelorder.cpp socket-server.cpp -o program

# Run the program
./program
