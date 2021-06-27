#bin/bash

counter=0
for dir in ex1 ex2 ex3 ex4
do	
    cd $dir/pngs
    counter=$(($counter+$(ls -l | wc -l)-1))
    cd ..
    cd ..
done
echo $counter

