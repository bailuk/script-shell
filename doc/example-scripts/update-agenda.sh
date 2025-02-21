#!/bin/sh

# Download calendar data from WebDav server
# First install curl on the watch: 'opkg install curl'

url="http://webdav/url"
user="username"
password="password"

target="~/script-shell/export.ics"

echo "-> Downloading"
curl --digest -u ${user}:${password} -o ${target} ${url} || exit 1
size=$(du -h ${target} | cut -f 1)
echo "-> $size"

echo "-> Importing"

# -d, --destructive local calendar data will be removed prior to import.
icalconverter import ${target} -d || exit 1
