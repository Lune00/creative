#!/bin/bash
echo 'Please type "m" or "f" to continue'
#while [ "$word" != "f" ] || [ "$word" != "m" ]; do
while read -p 'Please' -n 1 word && [ "$word" != f ] && [ "$word" != m ] ; do
  echo ""
done

echo "End"

