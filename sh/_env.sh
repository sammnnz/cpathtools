#!/bin/bash
# Note: This file make on Windows, so for direct use in GitHub Actions don't forget: 
# 1. Run git command: `git update-index --chmod=+x <path>_env.sh`
#    where <path> is path to _evn.sh file;
# 2. Make commit and push in GitHub.
# This is done to avoid error: Permission denied. For more information see 
# https://github.com/orgs/community/discussions/26239#discussioncomment-3250911

if [[ $OS =~ [wW]indows ]]; then
    echo "_OS=win" >> $1/_env
    echo "LIB_SUFFIX=dll" >> $1/_env
elif [[ linux == linux ]]; then
    echo "_OS=linux" >> $1/_env
    echo "LIB_SUFFIX=so" >> $1/_env
fi
