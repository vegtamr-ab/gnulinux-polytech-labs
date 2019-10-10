#!/bin/sh

INVARGS="Invalid arguments. Aborting..."

if [ -z $1 ]; then
  echo "$INVARGS"
fi

res=$1
shift 1
while [ $# -gt 1 ];
do
  case $1 in
    '+')
      res=$(echo "$res + $2" | bc)
      ;;
    '-')
      res=$(echo "$res - $2" | bc)
      ;;
    'x')
      res=$(echo "$res * $2" | bc)
      ;;
    'X')
      res=$(echo "$res * $2" | bc)
      ;;
    '/')
      eq0=$(echo "$2 == 0" | bc)
      if [ $eq0 -eq 1 ]; then
        echo "$INVARGS"
        exit
      fi
      res=$(echo "scale=6; $res / $2" | bc)
      ;;
  esac
  shift 2
done

echo $res
