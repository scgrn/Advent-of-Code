#!/bin/bash

set -e

year=$1
day=$2

urlPath="https://adventofcode.com/$year/day/$day/input"
cookie="$(<$year/.session)"

if [ 1 -eq "${#day}" ]; then
    day="0`echo $day`"
fi
mkdir -p ./$year/day$day

curl $urlPath --compressed \
    -o $year/day$day/input.txt \
    -H "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:120.0) Gecko/20100101 Firefox/120.0" \
    -H "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8" \
    -H "Accept-Language: en-US,en;q=0.5" \
    -H "Accept-Encoding: gzip, deflate, br" \
    -H "Referer: ${urlPath}" \
    -H "Connection: keep-alive" \
    -H "Cookie: ${cookie};" \
    -H "Upgrade-Insecure-Requests: 1" \
    -H "Sec-Fetch-Dest: document" \
    -H "Sec-Fetch-Mode: navigate" \
    -H "Sec-Fetch-Site: same-origin" \
    -H "Sec-Fetch-User: ?1"

