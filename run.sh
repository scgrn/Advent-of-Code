#!/bin/bash

set -e

year=$1
day=$2
if [ 1 -eq "${#day}" ]; then
    day="0`echo $day`"
fi

g++ $year/day$day/day$day-$3.cpp -o test
time ./test
rm ./test

