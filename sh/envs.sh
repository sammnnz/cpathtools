IFS=$'\n'

libgcc_file_name=`gcc -print-libgcc-file-name`
multi_os_directory="`gcc -print-multi-os-directory`*"
LIBGCC_DIRECTORY="${libgcc_file_name%$multi_os_directory}`gcc -print-multi-os-directory`"
export LIBGCC_DIRECTORY

__OS=linux
LIB_EXT=so # linux
CPATHTOOLS_ROOT_DIRECTORY=`pwd`
if [[ $OS =~ ^[wW]indows* ]]; then
    __OS=win
    LIB_EXT=dll
    #CPATHTOOLS_ROOT_DIRECTORY=${CPATHTOOLS_ROOT_DIRECTORY:`expr index "$CPATHTOOLS_ROOT_DIRECTORY" '/'`}
    #CPATHTOOLS_ROOT_DIRECTORY=${CPATHTOOLS_ROOT_DIRECTORY//'/'/'\'}
    #CPATHTOOLS_ROOT_DIRECTORY=${CPATHTOOLS_ROOT_DIRECTORY/'\'/':\'}
fi
export __OS
export LIB_EXT
export CPATHTOOLS_ROOT_DIRECTORY