#!/bin/bash
i="1"
l="0"

cd $1

if [ ! -d "src" ]
then
echo "Error: Directory \"src\" does not exist." >&2
exit 1
fi

rm -f src/levels.inc
if [ -f "src/levels.inc" ]
then
echo "Error: Could not delete file \"src/levels.inc\"." >&2
exit 1
fi

if [ ! -d "levels" ]
then
echo "Warning: Directory \"levels\" does not exist." >&2
echo > src/levels.inc
if [ -f "src/levels.inc" ]
then
exit 0
else
echo "Error: Could not create file \"src/levels.inc\"." >&2
exit 1
fi
fi

while [ -f "levels/level$i.inc" ]
do
echo "case $i:" >> src/levels.inc
echo "{" >> src/levels.inc
echo "	#include \"../levels/level$i.inc\"" >> src/levels.inc
echo "	break;" >> src/levels.inc
echo "}" >> src/levels.inc
i=$[$i+1]
l="1"
done

if [ $l -lt 1 ]
then
echo "Warning: Directory \"levels\" does not contain \"level1.inc\"." >&2
echo > src/levels.inc
fi

if [ -f "src/levels.inc" ]
then
exit 0
else
echo "Error: Could not create file \"src/levels.inc\"." >&2
exit 1
fi

