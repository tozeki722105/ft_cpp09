#!/bin/bash

echo "case 1"
./btc test_err_input.txt

echo "case 2"
empty="empty.txt"
touch ${empty}
./btc ${empty}

echo "case 3"
echo "date | value" > ${empty}
./btc ${empty}

rm ${empty}

echo "case 4"
testfile="input.txt"
backup="input_cp.txt"
cp ${testfile} ${backup}
echo >> ${testfile}
echo "2011-7-01 | 1" >> ${testfile}
./btc ${testfile}
mv ${backup} ${testfile}
