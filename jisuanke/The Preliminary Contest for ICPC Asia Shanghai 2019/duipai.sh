#/usr/bin/bash

while true; do
  python gen.py
  ./a < a.in > a.out
 ./std < a.in > a.ans
  if diff a.out a.ans; then
    printf AC
  else
    echo WA
    exit 0
  fi
done

