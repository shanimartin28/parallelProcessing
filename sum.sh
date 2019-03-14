#!/bin/bash
#
mpicc -c sum.c >& compiler.txt
if [ $? -ne 0 ]; then
  echo "Errors while compiling sum.c"
  exit
fi
rm compiler.txt
#
mpicc sum.o
if [ $? -ne 0 ]; then
  echo "Errors while linking and loading sum.o"
  exit
fi
rm sum.o
#
mv a.out sum
mpirun -v -np 8 ./sum > sum_output.txt
if [ $? -ne 0 ]; then
  echo "Errors while running sum"
  exit
fi
rm sum
#
echo "Program output written to sum_output.txt"
