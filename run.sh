#!/bin/bash
set -e

SRC_DIR="source"
OUT="$SRC_DIR/main"

g++ -g "$SRC_DIR"/*.cpp \
    -o "$OUT" \
    -I/usr/include \
    -L/usr/lib \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

echo
echo -e "\e[32mCompilation successful. Running program...\e[0m"
echo

"$OUT"

