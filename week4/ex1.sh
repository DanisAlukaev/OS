#!/bin/bash
gcc ex1.c -o ex1
for i in $(seq 10)
do 
   ./ex1 ${i}
done
