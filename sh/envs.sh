IFS=$'\n'

__OS=linux
LIB_EXT=so # linux
if [[ $OS =~ ^[wW]indows* ]]; then
    __OS=win
    LIB_EXT=dll
fi
export __OS
export LIB_EXT

libgcc_file_name=`gcc -print-libgcc-file-name`
multi_os_directory="`gcc -print-multi-os-directory`*"
LIBGCC_DIRECTORY="${libgcc_file_name%$multi_os_directory}`gcc -print-multi-os-directory`"
export LIBGCC_DIRECTORY