// BS19-02 Alukaev Danis
// Task 2.

#include <stdio.h>

int main()
{
    // Change the buffering mode of stdout stream.
    // As a mode select Line Buffering.
    // Set size of the buffer to 6 bytes.
    setvbuf(stdout, 0, _IOLBF, 6);
    // Code according to the instructions proposed in task.
    printf("%c", 'H');
    sleep(1);
    printf("%c", 'e');
    sleep(1);
    printf("%c", 'l');
    sleep(1);
    printf("%c", 'l');
    sleep(1);
    printf("%c", 'o');
    sleep(1);
    return 0;
}
