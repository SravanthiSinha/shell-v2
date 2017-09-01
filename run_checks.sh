#!/bin/bash
FILES="tests/hsh1.$1/*"
i=0
for f in $FILES
do
  ./checker.bash ./hsh $f | grep 'OK' &> /dev/null
  if [ $? == 0 ]; then
   ((i += 1))
  else
   echo $f
  fi
done
echo $i
