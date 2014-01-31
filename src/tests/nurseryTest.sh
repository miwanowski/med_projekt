#!/bin/bash

TIMEFORMAT=%R
> results/nres.txt

cat ./nursery.csv | head -n 4500 > ./nursery4500.csv
cat ./nursery.csv | head -n 6500 > ./nursery6500.csv
cat ./nursery.csv | head -n 7000 > ./nursery7000.csv
cat ./nursery.csv | head -n 9000 > ./nursery9000.csv

nurseryArray=( "./nursery4500.csv" "./nursery6500.csv" 
	"./nursery7000.csv" "./nursery9000.csv"	"./nursery.csv")

echo 'Nursery tests'
echo '_____________'

for filename in "${nurseryArray[@]}"
do
	echo $filename
	echo $'\nH'
	time ../fun $filename 8 "0,1,2,3,4,5,6,7" >> results/nres.txt 
	echo $'\nH/P'
	time ../fun $filename 8 "0,1,2,3,4,5,6,7" --optprune >> results/nres.txt
	echo $'\nSH'
	time ../fun $filename 8 "0,1,2,3,4,5,6,7" --sholds --sproduct >> results/nres.txt
	echo $'\nSH/P'
	time ../fun $filename 8 "0,1,2,3,4,5,6,7" --sholds --sproduct --optprune >> results/nres.txt
	echo $'\nPRSH'
	time ../fun $filename 8 "0,1,2,3,4,5,6,7" --prsholds --sproduct >> results/nres.txt
	echo $'\nRSH'
	time ../fun $filename 8 "0,1,2,3,4,5,6,7" --rsholds --sproduct >> results/nres.txt
done

rm *0.csv