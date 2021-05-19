#!/bin/bash

#SBATCH -J Project6
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o project6.out
#SBATCH -e project6.err
bash project6.bash
