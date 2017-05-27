#!/usr/bin/env bash
MOUNTED_CASE_SENSITIVE="/Volumes/case-sensitive"
PATH_TO_SDK="${MOUNTED_CASE_SENSITIVE}/v2.0.0_16_07_19/ESP8266_NONOS_SDK"
TTY_PORT=/dev/tty.SLAB_USBtoUART
ESPTOOL="${MOUNTED_CASE_SENSITIVE}/esp-open-sdk/esptool/esptool.py"
BUILD_FLAVOR="release"

export PATH=$PATH:${MOUNTED_CASE_SENSITIVE}/esp-open-sdk/xtensa-lx106-elf/bin

make SDK_BASE=${PATH_TO_SDK} FLAVOR=${BUILD_FLAVOR} ESPPORT=${TTY_PORT} ESPTOOL=${ESPTOOL} $1
