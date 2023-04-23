echo "Enter co-ordinates of three points: "
read x1
read y1
read x2
read y2
read x3
read y3

area=$(((($x1*$(($y2-$y3))))+(($x2*$(($y3-$y1))))+(($x3*$(($y1-$y2))))))

echo $area

if [ $area == 0 ]
then 
    echo "Three points are on the same line."
else
    echo "Three points are not on the same line."
fi



