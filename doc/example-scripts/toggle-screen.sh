#!/bin/sh


result=$(/sbin/mcetool | grep 'Display state')

if echo $result | grep on
then
    echo "-> Screen OFF"
    /sbin/mcetool -D off | exit 1
    exit 0
fi

echo "-> Screen ON"
/sbin/mcetool -D on | exit 1
exit 0
