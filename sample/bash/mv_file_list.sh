#!/bin/bash

# use this script to move file lists from src dir to des dir
# for example: ./script ./file_list.txt ./src ./des


if [[ $# -ne 3 ]]; then
    echo "usage: $0 ./file_list.txt ./src ./des"
    exit 1
fi

namelist_file=$1
src_dir=$2
des_dir=$3

# if [[ ! -e ${des_dir} ]]; then
#     mkdir ${des_dir}
# fi

while IFS= read -r line;
do
    echo "$src_dir/$line -> $des_dir/$line"
    mv $src_dir/$line $des_dir/$line
done < "$namelist_file"

