#!/bin/sh

echo "-> Disable wifi"

result=$(connmanctl disable wifi)

if echo $result | grep "already"
then
    echo "-> Already disabled"
    exit 0
fi

result=$(ip a show dev wlan0)

if echo $result | grep DOWN;
then
    echo "-> Disabled"
    exit 0
fi

echo "-> Failed"
exit 1
