#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./12.sh <file>"
    exit 1
fi

output=""

while read first_name last_name grades; do
    sum=0
    num_grades=0
    for grade in $grades; do
        sum=`echo $sum + $grade | bc`
        let num_grades++
    done
    average=`echo "scale=2;$sum/$num_grades" | bc`
    output+="$first_name $last_name $average\n"
done < $1

echo -e $output | sort -k 3 -r
