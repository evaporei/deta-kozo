#!/usr/bin/env bash

set -e

clang -O0 -Wall -Wextra -Wno-logical-op-parentheses -lm -std=c11 "c/$1.c" -o "c/$1" "$2" && "./c/$1"
