read n
d=$((n*2))

for (( i=0; i<n; i++))
do 
    l=$((i+1))
    ld=$((2*l))
    for (( j=0; j<$((i+1)); j++))
    do 
        echo -n "*"
    done

    for (( j=0; j<$((d-ld)); j++))
    do 
        echo -n " "
    done

    for (( j=0; j<$((i+1)); j++))
    do 
        echo -n "*"
    done
    echo " "
done


