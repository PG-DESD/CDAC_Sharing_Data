#! /bin/env bash

if [ ! -f $PWD/config ];then
    echo "Configuration file absent, aborting installation!"
    exit 1
fi

source $PWD/config

set -e

# Check if running as root
if [[ "$EUID" != 0 ]]
then 
    echo "${MAGENTA}Please run the script with administrator privileges!${NORMAL}"
    echo "Try sudo $0"
    exit
fi

# Remove files/directories 
if [ -d "$HEADER_PATH" ];then
    rm -rf $HEADER_PATH
fi

if [ -d "$SDK_PATH" ];then
    rm -rf $SDK_PATH
fi

if [ -f "$MINIRC" ];then
    rm $MINIRC
fi

if [ -f "$UDEV_CONFIG" ];then
    rm $UDEV_CONFIG
fi


# Copy header files
mkdir -p "$HEADER_PATH"
cp "$SETUP_PATH"/hal/include/* "$HEADER_PATH"

# Copy libraries
mkdir -p "$SDK_PATH"
cp hal/thejas32/* "$SDK_PATH"
cp -r "$SETUP_PATH"/hal/drivers "$SDK_PATH"
cp -r "$SETUP_PATH"/hal/libs "$SDK_PATH"
gcc "$SETUP_PATH"/tools/xmodem.c -o "$SDK_PATH"/xmodem


printf "
# THEJAS32 Minicom Configuration
pu port             /dev/ttyUSB0
pu baudrate         115200
pu bits             8
pu parity           N
pu stopbits         1
pu rtscts           No
" > $MINICOM_CONFIG

# Add user to dialout group
usermod -aG dialout $SUDO_USER

# Add udev rules

echo '
# CP2102 on ARIESv3
SUBSYSTEM=="usb", SYSFS{idVendor}=="0x10c4", SYSFS{idProduct}=="0xea60", ACTION=="add", GROUP="dialout", MODE="0664"

# FT230X on ARIESv2
SUBSYSTEM=="usb", SYSFS{idVendor}=="0404", SYSFS{idProduct} =="6015", ACTION=="add", GROUP="dialout", MODE="0664"

' > $UDEV_CONFIG

# Reload rules
udevadm control --reload-rules && udevadm trigger


echo "${GREEN}
------------------------------
Successfully Updated SDK
------------------------------
${NORMAL}"