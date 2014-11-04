# Sample .bashrc for SuSE Linux
# Copyright (c) SuSE GmbH Nuernberg

# There are 3 different types of shells in bash: the login shell, normal shell
# and interactive shell. Login shells read ~/.profile and interactive shells
# read ~/.bashrc; in our setup, /etc/profile sources ~/.bashrc - thus all
# settings made here will also take effect in a login shell.
#
# NOTE: It is recommended to make language settings in ~/.profile rather than
# here, since multilingual X sessions would not work properly if LANG is over-
# ridden in every subshell.

# Some applications read the EDITOR variable to determine your favourite text
# editor. So uncomment the line below and enter the editor of your choice :-)
#export EDITOR=/usr/bin/vim
#export EDITOR=/usr/bin/mcedit

# For some news readers it makes sense to specify the NEWSSERVER variable here
#export NEWSSERVER=your.news.server

# If you want to use a Palm device with Linux, uncomment the two lines below.
# For some (older) Palm Pilots, you might need to set a lower baud rate
# e.g. 57600 or 38400; lowest is 9600 (very slow!)
#
#export PILOTPORT=/dev/pilot
#export PILOTRATE=115200

test -s ~/.alias && . ~/.alias || true
export DISPLAY=" 10.170.97.176:0.0"
export LD_LIBRARY_PATH=/home/zhangrui/eSDK_Client/IVS_SDK_LINUX/IVS_Demo/lib
source /home/purify/purifyplus_setup.sh
export PURIFYOPTIONS="-cache-dir=${HOME}/cache -static-checking=no -force-rebuild=no -follow-child-processes=yes -chain-length=8 -search-thread-stacks=yes -always-use-cache-dir=yes -windows=yes -log-file=/home/zhangrui/eSDK_Client/IVS_SDK_LINUX/IVS_Demo/purifylog/`whoami`-`date +%Y%m%d-%H%M%S`.log -output-limit=0 -g++=yes"
export QUANTIFYOPTIONS="-record-child-process-data=yes"


