#!/bin/bash

i=0

for f in $(find . -name '*.c'); do
  new_f="uniq/file_$i.c"
  mv "$f" "$new_f"
  sed -i "s/loop\s*(/loop_$i(/g" "$new_f"
  i=$((i + 1))
done
