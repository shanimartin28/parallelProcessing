#!/bin/sh
#PBS -A 5DV011-VT11
### Job name - defaults to name of submit script
#PBS -N OpenMP
### Output files - defaults to jobname.[eo]jobnumber
#PBS -o openmp.output
#PBS -e openmp.err
### Mail on - a=abort, b=beginning, e=end - defaults to a
PBS -m e
### Requesting 1 nodes with 8 cores
#PBS -l nodes=1:ppn=8
### Requesting time - 5 minutes
#PBS -l walltime=00:05:00 

PBS -l nodes=1:ppn=8

cd $PBS_O_WORKDIR
module add openmpi/gcc

export OMP_NUM_THREADS=8
echo "Using MagicBox" >>out.txt
./Mandelbrot_MagicBox >>out.txt
echo -en "\n" >>out.txt

