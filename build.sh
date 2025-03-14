#!/bin/bash

BOARD="arduino:avr:uno"
PORT="/dev/ttyACM0"
SKETCH_DIR=$PWD 

compile() {
    arduino-cli compile --fqbn "$BOARD" "$SKETCH_DIR"
}

upload() {
    arduino-cli upload -p "$PORT" --fqbn "$BOARD" "$SKETCH_DIR"
}

clean() {
    rm -rf build
}

compile
upload
clean
