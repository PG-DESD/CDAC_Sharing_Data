#! /bin/env bash

if [ ! -f $PWD/config ];then
    echo "Configuration file absent, aborting installation!"
    exit 1
fi

source $PWD/config

if [[ "$EUID" != 0 ]]
then 
    echo "${MAGENTA}Please run the script with administrator privileges!${NORMAL}"
    echo "Try sudo $0"
    exit
fi

if [ -d "$HEADER_PATH" ];then
    rm -rf $HEADER_PATH
fi

if [ -d "$SDK_PATH" ];then
    rm -rf $SDK_PATH
fi

printf "${YELLOW}Remove the RISC-V Toolchain (Y/n):${NORMAL} "
read -r input 

if [ -z "$input" ] || [ "${input^^}" = "Y" ]; then

    if [ -d "$RISCV_TOOLCHAIN_PATH" ];then
        rm -rf $RISCV_TOOLCHAIN_PATH
    fi
fi

if [ -f "$MINIRC" ];then
    rm $MINIRC
fi

if [ -f "$UDEV_CONFIG" ];then
    rm $UDEV_CONFIG
fi

case "$DEFAULT_SHELL" in
  "bash")
    RC_FILE=/home/$SUDO_USER/.bashrc
    ;;
  "zsh")
    RC_FILE=/home/$SUDO_USER/.zshrc
    ;;
  *)
    printf "Unsupported shell: %s
    Manually delete the environment variable VEGA_SDK_PATH from your shell profile",$DEFAULT_SHELL
    ;;
esac

# Remove the environment variable from rc file
sed -i '/VEGA_SDK_PATH/d' "$RC_FILE"

#EOF
