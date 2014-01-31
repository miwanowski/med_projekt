#!/bin/bash

TIMEFORMAT=%R
> krkoptres.txt

cat ./krkopt.csv | head -n 2000 > ./krkopt2000.csv
cat ./krkopt.csv | head -n 5000 > ./krkopt5000.csv
cat ./krkopt.csv | head -n 10000 > ./krkopt10000.csv
cat ./krkopt.csv | head -n 15000 > ./krkopt15000.csv
cat ./krkopt.csv | head -n 20000 > ./krkopt20000.csv
cat ./krkopt.csv | head -n 25000 > ./krkopt25000.csv

krkoptArray=( "./krkopt2000.csv" "./krkopt5000.csv" 
	"./krkopt10000.csv" "./krkopt15000.csv" "./krkopt20000.csv"
	"./krkopt25000.csv"	"./krkopt.csv")

echo 'krkopt tests'
echo '_____________'

for filename in "${krkoptArray[@]}"
do
	echo $filename
	echo $'\nH'
	time ../fun $filename 6 "0,1,2,3,4,5" >> krkoptres.txt 
	echo $'\nH/P'
	time ../fun $filename 6 "0,1,2,3,4,5" --optprune >> krkoptres.txt
	echo $'\nSH'
	time ../fun $filename 6 "0,1,2,3,4,5" --sholds --sproduct >> krkoptres.txt
	echo $'\nSH/P'
	time ../fun $filename 6 "0,1,2,3,4,5" --sholds --sproduct --optprune >> krkoptres.txt
	echo $'\nPRSH'
	time ../fun $filename 6 "0,1,2,3,4,5" --prsholds --sproduct >> krkoptres.txt
	echo $'\nRSH'
	time ../fun $filename 6 "0,1,2,3,4,5" --rsholds --sproduct >> krkoptres.txt
done
