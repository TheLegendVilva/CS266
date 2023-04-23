read -p "Enter the value of n : " n

for (( i=0; i<=$n; i++))
do
    for (( j=0; j<=$((n-i)); j++))
    do
        echo -n " "
    done

    for (( j=0; j<=$i; j++))
    do
        mul=1
        k=$j

        while [ $k != 0 ]
        do
            mul=$((mul*k))
            k=$((k-1))
        done

        m=1
        k=$((i-j))

        while [ $k != 0 ]
        do
            m=$((m*k))
            k=$((k-1))
        done

        u=1
        k=$i

        while [ $k != 0 ]
        do
            u=$((u*k))
            k=$((k-1))
        done
        
        l=$((mul*m))
        echo -n " "$((u/l))
    done
    echo
done