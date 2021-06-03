#!/bin/bash

mpic++ -o project7 project7.cpp

for cpus in 1 2 4 8 16 32
do
    mpiexec -mca blt self,tcp -np $cpus project7
done

rm project7
