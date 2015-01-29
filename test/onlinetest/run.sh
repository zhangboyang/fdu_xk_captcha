#!/bin/bash
./clean.sh
mkdir data
for ((i = 1; i <= 10; i++))
do
    ./test.sh $i
done

if grep 2$ testlog.txt; then
    exit 1
fi

