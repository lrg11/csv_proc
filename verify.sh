#!/bin/bash

# default settings
dir="./dataset"
option="1"
field=""
newkey=""
path=""

function show_help() {
	cat <<EOF
Benchmark tool used to test the various compression algorithms on the data set

Args:
   -h
      Show help message.

   -t 0 
      QUIT

   -t 1 -d [directory] 
      Check dataset of the directory for compliance (filename format, file content format)

   -t 2 -d [directory] -f [field] -k [newkey]
      Batch adjust the field key in the header information of the dataset of the directory, according the field
   
   -t 3 -d [directory] 
      Batch adjust the field key in the header information of the dataset of the directory, according the program prompt
   
   -t 4 -p [path] 
      Aadjust the field key in the header information of the dataset along the path, according the program prompt
   
   -t 5 -d [directory] -c [characteristic] -r [rename]
      Batch rename the filename of the dataset of directory with the specific characteristic to another trait, keep everything else the same
Usage:
    ./verify.sh -t 1 -d ./dataset
    ./verify.sh -t 2 -d . -f domain -k category
    ./verify.sh -t 5 -c fenghuo -r fh
    all the dataset with fenghuo within filename will be replaced with another filename, just with fenghuo to fh
    ./verify.sh -t 3 -d dataset
    > field key: scenario, do you want to modify? (y/n)
    > y
    > Input new key:
    > class
    > Finished, continue? (y/n)
    > n

EOF
}

function parse_args() {
	OPTIND=1
	while getopts ":t:p:d:f:k:c:r:h" opt; do
		case "$opt" in
		t) option="$OPTARG" ;;
		p) path="$OPTARG" ;;
		d) dir="$OPTARG" ;;
		f) field="$OPTARG" ;;
		k) newkey="$OPTARG" ;;
		c) charac="$OPTARG" ;;
		r) rename="$OPTARG" ;;
		h)
			show_help
			exit 0
			;;
		\?)
			printf "%s\n" "Invalid Option! -$OPTARG" >&2
			exit 1
			;;
		:)
			printf "%s\n" "-$OPTARG requires an argument" >&2
			exit 1
			;;
		esac
	done
	shift "$((OPTIND - 1))"
}

parse_args $@

statuslist="using deprecated deprecating"
datatypelist="float8 float4 int8 int4 int2 int1"

if [ "$option" = "1" ]; then
	for dataset in $(ls ${dir}/*.csv); do
		dataname=$(basename $dataset)
		echo ""
		echo $dataname
		dataname=$(echo $dataname | cut -d '.' -f 1)
		# $(echo $dataset | cut -d '/' -f 2)
		status=$(echo $dataname | cut -d '~' -f 1)
		if ! [[ "$statuslist" =~ "$status" ]]; then
			echo "filename's status field is not correct"
		fi

		datatype=$(echo $dataname | cut -d '~' -f 4)
		if ! [[ "$datatypelist" =~ "$datatype" ]]; then
			echo "filename's datatype field is not correct"
		fi
		./dataset_verify "${option}" "${dataset}"
	done
elif [ "$option" = "2" ]; then
	for dataset in $(ls ${dir}/*.csv); do
		./dataset_verify "${option}" "${dataset}" "${field}" "${newkey}"
	done
	rm tmp.csv
elif [ "$option" = "3" ]; then
	for dataset in $(ls ${dir}/*.csv); do
		dataname=$(basename $dataset)
		echo $dataname
		./dataset_verify "${option}" "${dataset}"
	done
	rm tmp.csv
elif [ "$option" = "5" ]; then
	for dataset in $(ls ${dir}/*${charac}*.csv); do
		dataname=$(basename $dataset)
		before=$(echo $dataname | awk -F ${charac} '{print $1}')
		after=$(echo $dataname | awk -F ${charac} '{print $2}')
		mv ${dataset} ${dir}/${before}${rename}${after}
	done
elif [ "$option" = "4" ]; then
	./dataset_verify "${option}" "${path}"
	rm tmp.csv
elif [ "$option" = "0" ]; then
	echo "The script exit"
else
	echo "The option of shell is not correct, need to between 0-4"
fi

echo ""
echo "option = ${option}"

cat <<EOF
Successfully finished the dataset check or adjust 
EOF
