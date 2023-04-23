read -a arr
n=${#arr[@]}
min=1000
max=0
for (( i=0; i<$n; i++))
do 
    if [ ${arr[$i]} -gt $max ]
    then
        max=${arr[$i]}
    fi
    if [ ${arr[$i]} -lt $min ]
    then 
        min=${arr[$i]}
    fi
done

echo "range=" $((max-min))