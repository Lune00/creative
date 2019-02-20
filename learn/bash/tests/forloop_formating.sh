#!/usr/local/bin/bash


#For loop C-style
#Avec printf
for ((i=1;i<=10;i++))
do
  id=$(printf "%04d\n" "$i")
  file="walls$id.txt"
  echo $file
done


