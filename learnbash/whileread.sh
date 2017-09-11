#!/bin/bash
echo 'Please type "m" or "f" to continue'
word=""
#while [ "$word" != "f" ] || [ "$word" != "m" ]; do
while [ "$word" != f ] && [ "$word" != m ] ; do
  read -n 1 word
  echo""
done

echo "End"

