#!/bin/sh

if test $# -lt 1; then
echo "Usage: bdconvertCmp <input1.jpg> ... <inputn.jpg>" >&2
exit 1
fi

old_IFS=$IFS
IFS=$'\n'

for i in `seq 382329 441926`;
do
	fichier=$(printf '%04d' $i)
	fichier="$fichier"".jpg"
	if [ -f $fichier ]; then
	OUT=`echo "$ARG" | sed "s/\.jpg//"`

	echo "* Conversion $fichier en r_$fichier.jpg"
	convert -depth 24 "$fichier" "conv/$fichier.jpg"
	fi
done

IFS=$old_IFS

