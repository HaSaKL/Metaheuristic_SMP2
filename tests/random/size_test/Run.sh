#! /bin/bash

for file in `ls *.dat | sort -V`

do
	echo "$(tput setaf 1) Running Test on $file $(tput sgr0)"
	./SMP2_TimeToTarget -S=19510210 -I=20 -T=1800 -p=$file -o="RandomSize.csv" -l=2 -n=2 -a=R

done
