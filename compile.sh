#!/bin/bash

# SocialNet Simulator Compilation Script
# COL106 Long Assignment 2

echo "=========================================="
echo "  SocialNet Simulator - Compilation"
echo "=========================================="
echo ""

# Check if g++ is available
if ! command -v g++ &> /dev/null
then
    echo "Error: g++ compiler not found!"
    echo "Please install g++ to compile this project."
    exit 1
fi

echo "Compiler found: $(g++ --version | head -n 1)"
echo ""

# Set compilation flags
CXX=g++
CXXFLAGS="-std=c++11 -Wall -Wextra -I."
TARGET=socialnet
SOURCE=main.cpp

echo "Compiling SocialNet Simulator..."
echo "Command: $CXX $CXXFLAGS $SOURCE -o $TARGET"
echo ""

# Compile the project
$CXX $CXXFLAGS $SOURCE -o $TARGET

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "=========================================="
    echo "  ✓ Compilation Successful!"
    echo "=========================================="
    echo ""
    echo "Executable created: ./$TARGET"
    echo ""
    echo "To run the program, use:"
    echo "  ./$TARGET"
    echo ""
    echo "For help with commands, type 'HELP' after starting the program."
    echo ""
else
    echo "=========================================="
    echo "  ✗ Compilation Failed!"
    echo "=========================================="
    echo ""
    echo "Please check the error messages above and fix the issues."
    echo ""
    exit 1
fi
