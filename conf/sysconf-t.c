#include <unistd.h>
#include <stdio.h>

int
main(int argc, char* args[])
{
    long res = sysconf(_SC_CLK_TCK);
    printf("max clock is [%ld]\n", res);
    return 0;
}
