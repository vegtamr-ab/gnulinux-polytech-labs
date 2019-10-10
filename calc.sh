#!/bin/sh

INVARGS="Invalid arguments. Aborting..."

if [ -z $1 ];
then
  echo "$INVARGS"
fi

count=0
while [ $# -gt 1 ];
do
  flag=0
  res=$1
  shift 1
  while [[ $1 != "+" ]] && [[ $1 != "-" ]] && [[ $# -gt 1 ]];
  do
    case $1 in
      'x')
        res=$(echo "$res * $2" | bc)
        ;;
      'X')
        res=$(echo "$res * $2" | bc)
        ;;
      '/')
        eq0=$(echo "$2 == 0" | bc)
        if [ $eq0 -eq 1 ];
        then
          echo "$INVARGS"
          exit
        fi
        res=$(echo "scale=6; $res / $2" | bc)
        ;;
    esac
    shift 2
    flag=1
  done

  if [ $# -eq 1 ];
  then
    echo "$INVARGS"
  elif [ $# -lt 1 ];
  then
    simple[$count]=$res
    count=$(echo "$count + 1" | bc)
    break
  fi

  if [ $flag -ne 1 ];
  then
    while [[ $3 != "x" ]] && [[ $3 != "X" ]] && [[ $3 != "/" ]] && [[ $# -gt 1 ]];
    do
      res=$(echo "$res $1 $2" | bc)
      shift 2
    done
  fi

  simple[$count]=$res
  simple[$(echo "$count + 1" | bc)]=$1
  count=$(echo "$count + 2" | bc)
  if [ $# -gt 1 ];
  then
    shift 1
  fi
done

res=${simple[0]}

i=1;
while [ $i -lt $count ];
do
  res=$(echo "$res ${simple[$i]} ${simple[$(echo "$i + 1" | bc)]}" | bc)
  i=$(echo "$i + 2" | bc)
done

echo $res
