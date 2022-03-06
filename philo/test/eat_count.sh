#!/bin/bash

function TEST_EAT_COUNT() {
	echo $@ $#

	if [ $# -ne 2 ]
	then
		echo "error: Invalid argument" 1>&2
		echo "example: bash eat_count.sh number_of_philo log_file_path" 1>&2
		exit 1
	fi

	n=$1
	file=$2

	for i in `seq $n`
	do
		cnt=$(cat $file | grep " $i is eating" | wc -l)
		echo "philo $i ate $cnt times"
	done
}

../philo 100 410 200 200 5 > res.log
TEST_EAT_COUNT 100 res.log
