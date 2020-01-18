#!/bin/bash

# test-integer: evalute the value of a integer

echo -n "Please enter an integer -> "
read INT

echo $(($INT))
echo $((INT))

if [ -z "$INT" ]; then
    echo "INT is empty." >&2
    exit 1
fi

if [ "$INT" -eq 0 ]; then
    echo "INT is zero."
else
    if [ "$INT" -lt 0 ]; then
        echo "$INT is negative."
    elif [ "$INT" -gt 0 ]; then
        echo "$INT is positive."
    fi

    if [ $((INT % 2)) -eq 0 ]; then
        echo "$INT is even."
    else
        echo "$INT is odd."
    fi
fi

