#!/bin/bash

# Generates a random set of records, each containing a tuple:
#    id,age

OPTIND=1

RECORD_COUNT=10000
MAX_AGE=80
MAX_ID=10000

usage() {
	cat <<EOF
Usage: ${0##*/} [-h] [-c RECORD_COUNT] [-a MAX_AGE] [-i MAX_ID]

Generate a random set of records consisting of id,age tuples.

	-h         display this help and exit
	-c         Number of records to generate (default: $RECORD_COUNT)
	-a         Maximum range for ages (default: $MAX_AGE)
	-i         Maximum range for ids (default: $MAX_ID)

EOF
}


# Number of records to generate
record_count=$RECORD_COUNT

# Ceiling for the ages.
max_age=$MAX_AGE

# Ceiling for the ids
max_id=$MAX_ID

# Process command line arguments
while getopts "ha:i:c:" opt; do
	case "$opt" in
		h)
			usage
			exit 0
			;;
		c)
			record_count=$OPTARG
			;;
		a)
			max_age=$OPTARG
			;;
		i)
			max_id=$OPTARG
			;;
		*)
			usage
			exit 1
			;;
		
	esac
done

counter=0

while [[ $counter -lt $record_count ]]; do
	let counter=counter+1
	rec="$(((RANDOM % $max_id ) + 1)),$(((RANDOM % max_age ) + 1))"
	echo $rec
done
