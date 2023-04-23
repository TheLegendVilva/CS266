count=1
while [ $count -lt 11 ]
do
    echo "Enter the working hours of employee no $count"
    read working_hours
    if [ $working_hours -gt 40 ]
    then
        ot=working_hours-40
        otp=$((ot*12))
        echo "employee $count overtime pay is $otp"
    else
        echo "you have to work more than 40 hours to get over pay"
    fi
count=$((count+1))
done
