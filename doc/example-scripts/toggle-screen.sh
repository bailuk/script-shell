#!/bin/sh


result=$(/sbin/mcetool | grep 'Blank inhibit')

if echo $result | grep stay-on
then
    echo "-> Screen OFF"
    /sbin/mcetool -D off | exit 1
    exit 0
fi

echo "-> Screen ON"
/sbin/mcetool -D on
