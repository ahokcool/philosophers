#!/bin/bash

declare -A count_map

# Read each line and extract the number and action
while read -r line; do
    number=$(echo "$line" | awk '{print $2}')
    action=$(echo "$line" | awk '{print $NF}')  # Get the last field
	echo $line
    if [ "$action" == "eating" ]; then
        eating_count=${count_map[$number]}
        count_map[$number]=$((eating_count + 1))
    fi
done

# Print the counts for each number and sort in ascending order
for number in "${!count_map[@]}"; do
    echo "${count_map[$number]} meals (number $number))"
done | sort -n -k1
