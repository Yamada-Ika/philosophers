#!/bin/bash

function TEST_EAT_COUNT() {
	if [ $# -ne 4 ]
	then
		echo "error: Invalid argument" 1>&2
		echo "example: bash eat_count.sh number_of_philo log_file_path" 1>&2
		exit 1
	fi

	n=$1
	min_ate_cnt=$2
	file=$3
	test_case="$4"

	for i in `seq $n`
	do
		cnt=$(cat $file | grep " $i is eating" | wc -l)
		if [ $cnt -lt $min_ate_cnt ]
		then
			echo "Faile : $test_case" 1>&2
			echo "philo $i ate $cnt times, but should eat $min_ate_cnt times at least" 1>&2
			exit 1
		fi
	done
}

function TEST() {
	echo "case : ./philo $1 $2 $3 $4 $5"
	../philo $1 $2 $3 $4 $5 > $6
	TEST_EAT_COUNT $1 $5 $6 "case : ./philo $1 $2 $3 $4 $5"
	exit 1
}

TEST 5 800 200 200 7 res1.log &
TEST 3 610 200 200 10 res1.log &
TEST 200 410 200 200 10 res2.log &
wait
echo "end"
