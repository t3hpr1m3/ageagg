#!/bin/bash

usage() {
	echo -e "Usage: "
	echo -e "    ageagg <filename>\n\n"
}

a_bort() {
	echo -e "$1"
	usage
	exit 1
}

if [[ $# -lt 1 ]]; then
	a_bort "Error: filename is required.\n"
fi

#
# Name of the file to process
#
filename=$1

#
# Make sure its an actual file
#
if [[ ! -f $filename ]]; then
	a_bort "Error: file not found: $filename\n"
fi

#
# Pipeline to generate unique age counts.
#
cut -d ',' -f 2 $filename | sort | uniq -c | sort -k2 -n | awk '{printf "%s,%s\n", $2, $1}'
