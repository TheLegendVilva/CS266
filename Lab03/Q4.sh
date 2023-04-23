echo "Enter the integer of which you expect factorial:"
read num
ans=1
for (( i=2; i <= $num; i++ ))
do 
    ans=$((ans*i))
done
echo "factorial of $num = $ans"
