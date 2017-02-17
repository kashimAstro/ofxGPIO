#!/bin/bash

radice=${PWD}
origpath=`dirname $radice`

for i in $( ls $origpath|grep example ); do
	cd $origpath'/'$i
	make
	cd $radice
done
