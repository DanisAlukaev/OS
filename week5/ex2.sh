# BS19-02 Alukaev Danis
# Task 2.

# It is impossible to predict the occurence of the race condition;
# in particular, in the first run it appeared on the 10-th iteration, in the second-on the 2-nd iteration.

# create file ex2.txt
touch ex2.txt
# write 0 as the starting number in ex2.txt
echo 0 > ex2.txt; 
# perform read-write process N times 
N=500
while true; do
    if ln ex2.txt ex2.lock; then 	
        # read last element from ex2.txt
        last=`tail -n 1 ex2.txt`
        echo $last
        # write incremented last element to ex2.txt
        echo $((last+1)) >> ex2.txt     
        #remove ex2.lock
        rm ex2.lock
        # exit from loop  
        if [ $last = $((N-1)) ]; then 
        	break
        fi
    fi
done
