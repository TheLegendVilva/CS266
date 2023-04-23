a=$1
b=$2
c=$3
ans=0
if [ "$b" == "+" ]
then 
    ans=$((a+c))
fi
if [ "$b" == "-" ]
then 
    ans=$((a-c))
fi
if [ "$b" == "x" ]
then 
    ans=$((a*c))
fi
if [ "$b" == "/" ]
then 
    ans=$((a/c))
fi
echo $ans