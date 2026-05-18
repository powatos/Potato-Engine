#!/bin/bash

PWD=$(pwd)

rm -rf docs/html docs/latex

doxygen Doxyfile

echo "API Docs mashed"