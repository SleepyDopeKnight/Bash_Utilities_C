#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="patterns.txt"
echo "" > log.txt

for var in -n -c -l -i -v -e -o -s -h #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in cl
  do
    TEST1="$var $var2 $TEST_FILE"
    echo "$TEST1"
    ./s21_grep $TEST1 > s21_grep.txt
    grep $TEST1 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST1" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"