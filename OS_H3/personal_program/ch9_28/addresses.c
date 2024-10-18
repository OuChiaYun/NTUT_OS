#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned long page;
    unsigned long offset;
    unsigned long address;

    if (argc != 2)
    {
        printf("Usage : ./addresses.out <value>\n");
    }
    else if (atoi(argv[1]) < 0)
    {
        printf("<value> need >= 0\n");
    }
    else
    {

        address = atoi(argv[1]);

        page = address >> 12; // 位移12
        offset = address & 0xfff;

        printf("The address %lu contains: \n", address);
        printf("page number = %lu\n", page);
        printf("offset = %lu\n", offset);
    }
}