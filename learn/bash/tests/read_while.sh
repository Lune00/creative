#!/usr/local/bin/bash

echo "Hello world!"
echo "Continuer (Y/n):"
while read -n 1 word && [ "$word" != y ] && [ "$word" != n ] && [ "$word" != "" ];do
  echo "oui ou non"
done
echo "end"
