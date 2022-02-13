#!/bin/bash

function ASSERT() {
	if [ "$1" = "$2" ]
	then
		echo "test ok     : $1 $2"
	else
		echo "test failed : $1 $2" 1>&2
		echo "Maybe you forget to add leak check function in C programs?"
		exit 1
	fi
}

cur_path=$(pwd)
echo "test : ${cur_path}/../philo 0 100 100 100"
leak_block=$(${cur_path}/../philo 0 100 100 100 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
