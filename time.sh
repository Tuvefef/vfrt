#!/bin/bash
# script just to calculate the average execution time
#

execn=10
makeb=make

$makeb all

for ((i=1; i<=$execn; i++)); 
do
    $makeb run
    echo "exec $i"
done