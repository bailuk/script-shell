#!/bin/sh

dir="/home/ceres/screenshots"

mkdir -p $dir | exit 1

for i in $(seq 1 100); do
    index=$(printf %03d $i)
    file="$dir/screenshot$index.jpg"
    
    if ! [ -e $file ]; then
        screenshottool $file 10 &        
        for i in $(seq 1 10); do
            echo "->in $((10-$i)) seconds"
            sleep 1
        done
        exit 0
    fi
done

echo "-> too many files"
exit 1
