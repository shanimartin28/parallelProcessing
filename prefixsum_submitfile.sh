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

echo "Hypercube Prefixsum Algorithm" >>prefixsum.txt
mpirun -v -np 8 ./prefixsum> prefixsum_output.txt
echo -en "\n" >>out.txt
