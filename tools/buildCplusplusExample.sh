#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

radice=${PWD}
origpath=`dirname $radice`

for i in $( ls $origpath|grep example-without ); do
	echo -e "${RED}Compile:${NC} ${GREEN}${i}${NC}"
	cd $origpath'/'$i
        echo -e "${i}\n" >> $radice/compile.log
	make -s &>> $radice/compile.log
        echo -e "************************************\n" >> $radice/compile.log
	cd $radice
done
