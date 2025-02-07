#!/bin/sh
set -e # Exit early if any commands fail

gcc main.c -o main
./main
