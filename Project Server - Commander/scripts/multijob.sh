#!/bin/bash

for file in "$@"; do
  while read -r line; do
    ./build/jobCommander issueJob "$line"
  done < "$file"
done
