#!/bin/sh

# First install https://github.com/beroset/asteroid-weatherfetch

geo="50.812375,4.380734"
city="Université libre de Bruxelles"

echo "-> $geo"
echo "-> $city"

weatherfetch_cli -rdl --add  "$geo,$city"
