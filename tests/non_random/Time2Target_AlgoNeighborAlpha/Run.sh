#! /bin/bash


# Element Flip mit RandFirstBetterHC
echo "Testing n=2, l=2, a=0"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=0 > /dev/null

echo "Testing n=2, l=2, a=0.1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=0.1 > /dev/null

echo "Testing n=2, l=2, a=0.3"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=0.3 > /dev/null

echo "Testing n=2, l=2, a=0.6"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=0.6 > /dev/null

echo "Testing n=2, l=2, a=1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=1 > /dev/null

echo "Testing n=2, l=2, a=E"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=E > /dev/null

echo "Testing n=2, l=2, a=R"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=2 -a=R > /dev/null



# Element Flip mit BestImprHC
echo "Testing n=2, l=1, a=0"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=0 > /dev/null

echo "Testing n=2, l=1, a=0.1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=0.1 > /dev/null

echo "Testing n=2, l=1, a=0.3"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=0.3 > /dev/null

echo "Testing n=2, l=1, a=0.6"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=0.6 > /dev/null

echo "Testing n=2, l=1, a=1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=1 > /dev/null

echo "Testing n=2, l=1, a=E"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=E > /dev/null

echo "Testing n=2, l=1, a=R"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=2 -a=R > /dev/null



# Adj Element Flip mit RandFirsBestHC
echo "Testing n=1, l=2, a=0"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=0 > /dev/null

echo "Testing n=1, l=2, a=0.1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=0.1 > /dev/null

echo "Testing n=1, l=2, a=0.3"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=0.3 > /dev/null

echo "Testing n=1, l=2, a=0.6"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=0.6 > /dev/null

echo "Testing n=1, l=2, a=1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=1 > /dev/null

echo "Testing n=1, l=2, a=E"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=E > /dev/null

echo "Testing n=1, l=2, a=R"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=2 -n=1 -a=R > /dev/null



# Adj Element Flip mit BestImprHC
echo "Testing n=1, l=1, a=0"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=0 > /dev/null

echo "Testing n=1, l=1, a=0.1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=0.1 > /dev/null

echo "Testing n=1, l=1, a=0.3"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=0.3 > /dev/null

echo "Testing n=1, l=1, a=0.6"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=0.6 > /dev/null

echo "Testing n=1, l=1, a=1"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=1 > /dev/null

echo "Testing n=1, l=1, a=E"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=E > /dev/null

echo "Testing n=1, l=1, a=R"
./SMP2_TimeToTarget -S=19510210 -I=250 -p="Test16-13-7.dat" -o="Test16-13-7.csv" -t=44.527197 -l=1 -n=1 -a=R > /dev/null

