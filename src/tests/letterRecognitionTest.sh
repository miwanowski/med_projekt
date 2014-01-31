#!/bin/bash

TIMEFORMAT=%R
> lrres.txt

cat ./letter-recognition.csv | head -n 100 > ./letter-recognition100.csv
cat ./letter-recognition.csv | head -n 200 > ./letter-recognition200.csv
cat ./letter-recognition.csv | head -n 500 > ./letter-recognition500.csv
cat ./letter-recognition.csv | head -n 1000 > ./letter-recognition1000.csv
cat ./letter-recognition.csv | head -n 2000 > ./letter-recognition2000.csv
cat ./letter-recognition.csv | head -n 5000 > ./letter-recognition5000.csv
cat ./letter-recognition.csv | head -n 10000 > ./letter-recognition10000.csv
cat ./letter-recognition.csv | head -n 15000 > ./letter-recognition15000.csv


lrArray=( "./letter-recognition100.csv" "./letter-recognition200.csv" 
	"./letter-recognition500.csv" "./letter-recognition1000.csv" "./letter-recognition2000.csv" )

echo 'Letter Recognition tests'
echo '_____________'

for filename in "${lrArray[@]}"
do
	echo $filename
	echo $'\nH'
	time ../fun $filename 0 "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" >> lrres.txt 
	echo $'\nH/P'
	time ../fun $filename 0 "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" --optprune >> lrres.txt
	echo $'\nSH'
	time ../fun $filename 0 "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" --sholds --sproduct >> lrres.txt
	echo $'\nSH/P'
	time ../fun $filename 0 "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" --sholds --sproduct --optprune >> lrres.txt
	echo $'\nPRSH'
	time ../fun $filename 0 "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" --prsholds --sproduct >> lrres.txt
	echo $'\nRSH'
	time ../fun $filename 0 "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16" --rsholds --sproduct >> lrres.txt
done
