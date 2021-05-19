#!/bin/bash

#SBATCH -J Project5
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o project5.out
#SBATCH -e project5.err
./project5_script
