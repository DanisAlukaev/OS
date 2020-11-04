# BS19-02 Alukaev Danis
# Task 2.

# Compile code.
gcc ex2.c -o ex2
# Run program on /proc/cpuinfo and save the output to ex2.txt.
cat /proc/cpuinfo | ./ex2 -a ex2.txt
