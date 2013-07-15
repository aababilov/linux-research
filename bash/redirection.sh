#!/bin/bash

echo "1
2
3" > /tmp/for_bash
echo "4" > /tmp/for_a_while

exec < /tmp/for_bash

ls -l /proc/$$/fd/

read a_line
echo "1: I have scanned: $a_line"

while read a_line; do
    ls -l /proc/$$/fd/
    echo "2: While has scanned: $a_line"
    rm -f /tmp/for_bash
done < /tmp/for_a_while

ls -l /proc/$$/fd/

read a_line
echo "3: Finally, I have scanned: $a_line"
