#!/bin/sh

function display() {
    sleep 2
    ssid=$(connmanctl services | grep "^\*"  | cut -f 2 -d ' ')
    ip=$(ip a show dev wlan0 | grep 'inet\s' | cut -f 6 -d ' ')
    echo "-> $ssid"
    echo "-> $ip"
}

echo "-> Enabling wifi"

result=$(connmanctl enable wifi 2>&1)
if echo $result | grep already;
then
    echo "-> Already enabled"
    display
    exit 0
fi

result=$(ip a show dev wlan0)
if echo $result | grep UP;
then
    echo "-> Enabled"
    display
    exit 0
fi

echo "-> Failed"
exit 1
