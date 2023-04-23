read -p "Enter a number: " n
temp=$n
if [ ${#temp} -eq 5 ] 
then
while [ $temp -ne 0 ]
do
    reverse=$reverse$((temp%10))
    temp=$((temp/10))
done
echo "Reverse of  the number is $reverse"
if [ $reverse == $n ]
then 
    echo "The number and its reverse are equal."
fi
else
	echo "The number entered is not of length 5."
fi