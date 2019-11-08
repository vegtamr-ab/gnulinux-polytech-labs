#!/bin/sh

INVARGS="Invalid arguments. Aborting..."

modula=$(($1 % 2))
halved=$(($1 / 2 + 1))

if [[ -z $1 ]] || [[ $modula -eq 0 ]];
then
  echo "$INVARGS"
  exit
fi

diamond=""
spaces=1
for ((i = 1; i <= $halved; i++))
do
  str=""
  j=$(($(($1 - $spaces)) / 2))
  for ((k = 1; k <= $j; k++))
  do
    str=$str"p"
  done

  for ((k = 1; k <= $i; k++))
  do
    str=$str"*p"
  done

  diamond=$diamond$str"n"
  spaces=$(($spaces + 2))
done

spaces=$(($spaces - 4))

for ((i = $(($halved + 1)); i <= $1; i++))
do
  str=""
  j=$(($(($1 - $spaces)) / 2))
  for ((k = 1; k <= $j; k++))
  do
    str=$str"p"
  done

  for ((k = 1; k <= $(($1 - $i + 1)); k++))
  do
    str=$str"*p"
  done

  diamond=$diamond$str"n"
  spaces=$(($spaces - 2))
done

echo $diamond | sed 's/p/ /g' | sed 's/n/\n/g'
