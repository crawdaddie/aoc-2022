#! /bin/bash
source ./.aocrc
dir=$(printf "day_%02d\n" $1)
if [ ! -f $dir/input.txt ]
then
  mkdir -p $dir
  curl "https://adventofcode.com/2022/day/$1/input" \
    -H 'authority: adventofcode.com' \
    -H 'accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8' \
    -H 'accept-language: en-US,en;q=0.8' \
    -H 'cache-control: max-age=0' \
    -H "cookie: $COOKIE" \
    -H "referer: https://adventofcode.com/2022/day/$1" \
    -H 'sec-fetch-dest: document' \
    -H 'sec-fetch-mode: navigate' \
    -H 'sec-fetch-site: same-origin' \
    -H 'sec-fetch-user: ?1' \
    -H 'sec-gpc: 1' \
    -H 'upgrade-insecure-requests: 1' \
    -H 'user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36' \
    --compressed >> $dir/input.txt
  echo "https://adventofcode.com/2022/day/$1" >> $dir/README.md 
fi

