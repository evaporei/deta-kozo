#!/usr/bin/env bash

set -e

rustc "rust/$1.rs" -o "rust/$1" && "./rust/$1"
