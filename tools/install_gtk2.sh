#!/bin/bash

YELLOW='\033[1;33m'
NC='\033[0m'

if [ "$USER" != "root" ];
then 
	echo -e "${YELLOW}Run script with superuser privileges${NC}"
	exit
fi

apt-get install build-essential libgtk2.0-dev
