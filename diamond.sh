#!/bin/sh

INVARGS="Invalid arguments. Aborting..."

modula=$(($1 % 2))
halved=$(($1 / 2 + 1))

if [[ -z $1 ]] || [[ $modula eq 0 ]];
then
  echo "$INVARGS"
  exit
fi

spaces=1
for ((i = 1; i <= $halved; i++))
do
  str=""
  j=$(($(echo "$1 - $spaces" | bc) / 2))
  for ((k = 1; k <= $j; k++))
  do
    str=$str"p"
  done

  for ((k = 1; k <= $i; k++))
  do
    str=$str"*p"
  done

  echo $str | sed 's/p/ /g'
  spaces=$(($spaces + 2))
done

spaces=$(($spaces - 4))

for ((i = $(($halved + 1)); i <= $1; i++))
do
  str=""
  j=$(($(echo "$1 - $spaces" | bc) / 2))
  for ((k = 1; k <= $j; k++))
  do
    str=$str"p"
  done

  for ((k = 1; k <= $(($1 - $i + 1)); k++))
  do
    str=$str"*p"
  done

  echo $str | sed 's/p/ /g'
  spaces=$(($spaces - 2))
done
