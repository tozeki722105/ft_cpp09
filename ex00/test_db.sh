#!/bin/bash

testfile="data.csv"
backup="data_cp.csv"

cp ${testfile} ${backup}

old="2009-01-14,0"

echo "case 1"
new="2009-01-14, 20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 2"
new="2009-01-14 ,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 3"
new="2009-01-14,20 "
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 4"
new=" 2009-01-14,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 5"
new="2009- 01-14,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 6"
new="2009-01 -14,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 7"
new="2009a-01-14,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 8"
new="2009-01-14,20a"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 9"
new=",20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 10"
new="2009-01-14,"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 11"
new="2009-01-14"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 12"
new="2009-01-32,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 13"
new="2009-13-10,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 14"
new="2009-12-10|20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 15"
new="2009-12-10,-0.1"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 16"
new="2009-12-10,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 17"
rm ${testfile}
touch ${testfile}
./btc input.txt

echo "case 18"
echo "date,exchange_rate" > ${testfile}
./btc input.txt

echo "case 19"
new="2009-0-10,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 20"
new="2009-12-0,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 21"
new="2003-2-29,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 22"
new="2100-2-29,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 23"
new="2009-4-31,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

echo "case 24"
new="2009-11-31,20"
sed "s/${old}/${new}/g" ${backup} > ${testfile}
./btc input.txt

mv ${backup} ${testfile}
