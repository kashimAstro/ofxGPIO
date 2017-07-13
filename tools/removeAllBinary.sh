#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

radice=${PWD}
origpath=`dirname $radice`
list=($(ls -1 $origpath*|grep 'example-'|cut -d':' -f1))
for item in ${list[*]}
do
	d=`basename $item`
	if [ -f $origpath/$item/bin/$d ];
	then
        	echo -e "${RED}Remove:${NC} ${GREEN}$origpath/$item/bin/$d${NC}"
		rm $origpath/$item/bin/$d
	fi

	#if [ -f $origpath/$item/compile.log ];
	#then
        #	echo -e "${RED}Remove:${NC} ${GREEN}$origpath/$item/compile.log${NC}"
	#	rm $origpath/$item/compile.log
	#fi

	if [ -d $origpath/$item/bin/libs/ ];
	then
		echo -e "${BLUE}Remove:${NC} ${YELLOW}$origpath/$item/bin/libs/${NC}"
		rm -fr $origpath/$item/bin/libs/
	fi

	if [ -d $origpath/$item/obj/ ];
	then
		echo -e "${BLUE}Remove:${NC} ${YELLOW}$origpath/$item/obj/${NC}"
		rm -fr $origpath/$item/obj/
	fi
done
