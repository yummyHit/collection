#!/usr/bin/env bash
for std in c89 c99 c11 c17 gnu89 gnu99 gnu11 gnu17; do
	echo $std
	msg=`gcc -std=$std -o gcc_version.out gcc_version.c 2>&1`
	if [ "$msg" = "" ]; then
		./gcc_version.out
	else
		echo "This version has error with this message."
		echo "($msg)"
	fi
	echo
done
echo "##### default #####"
gcc -o gcc_version.out gcc_version.c
./gcc_version.out
