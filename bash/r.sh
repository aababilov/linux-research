read a_line
echo "1: I have scanned: $a_line"

while read a_line; do
    echo "2: While has scanned: $a_line"
done < /tmp/for_a_while

read a_line
echo "3: finally, I have scanned: $a_line"
