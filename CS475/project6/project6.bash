#!/bin/bash

# ArrayMult
# 1. Check .cl   : Mult uncomment, Mult-Add comment
# 2. Check .cpp  : CSV define arrayMult
# 3. Check below : pName="arrayMult" and csv_file="$pName.csv"

# ArrayMultAdd
# 1. Check .cl   : Mult-Add uncomment, Mult comment
# 2. Check .cpp  : CSV define arrayMultAdd
# 3. Check below : pName="arrayMult" and csv_file="arrayMultAdd.csv"

# ArrayMultReduce
# 1. Check below : pName="arrayMultReduce" and csv_file="pName.csv"


#pName="arrayMult"
pName="arrayMultReduce"

csv_file="$pName.csv"
#csv_file="arrayMultAdd.csv"   

echo """,8,16,32,64,128,256,512" >> $csv_file

for g_size in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
do
    for l_size in 8 16 32 64 128 256 512
    do
        echo -n "$g_size" >> $csv_file
        g++ -DNMB=$g_size -DLOCAL_SIZE=$l_size -o $pName $pName.cpp /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
        ./$pName
    done
    echo ""
    echo >> $csv_file
done

rm $pName
