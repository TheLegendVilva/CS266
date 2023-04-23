echo "The five numbers are: $@"
average=0
max=0
min=1000
for arg in $@
do
    average=$((average+arg))
    if [ $arg -gt $max ]
    then 
        max=$arg
    fi
    if [ $min -gt $arg ]
    then 
        min=$arg
    fi
done
average=$(($average/5))
echo "average = $average"
echo "max = $max"
echo "min = $min"

