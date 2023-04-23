ls *.txt > file.txt
cat $(<file.txt) > newfile.txt
grep -wn "India" newfile.txt | cut -d: -f1
grep -wn "country" newfile.txt | cut -d: -f1
grep -wn "Taj" newfile.txt | cut -d: -f1