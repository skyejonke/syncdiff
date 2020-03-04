#!/bin/bash
cmake .
./dirTesting.sh
make
./bin/tests
