#!/bin/sh
#PBS -A 5DV011-VT11
### Job name - defaults to name of submit script
#PBS -N OpenMP
### Output files - defaults to jobname.[eo]jobnumber
#PBS -o prefix_sum.output
#PBS -e prefix_sum.err
### Mail on - a=abort, b=beginning, e=end - defaults to a
#PBS -m e
### Requesting 1 nodes with 8 cores
#PBS -l nodes=1:ppn=8
### Requesting time - 5 minutes
#PBS -l walltime=00:05:00 
#PBS -M mcs10smn@cs.umu.se
#PBS -l nodes=2:ppn=8

# Change to Working Directory
cd $PBS_O_WORKDIR
module add openmpi/gcc

echo "Hypercube Prefix Sum..." >>prefix_sum.txt
mpirun -v -np 8 ./prefix_sum > prefix_sum.txt
if [ $? -ne 0 ]; then
  echo "Errors while running sum"
  exit

