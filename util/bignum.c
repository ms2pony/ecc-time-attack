#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int array2Num(char *bn, uint8_t a[], int size) // size为a数组的大小
{

    sprintf(bn, "0x%02x", a[size - 1]);
    for (int i = size - 2, count = 0; i >= 0; i--, count += 2)
    {
        sprintf(bn + 4 + count, "%02x", a[i]);
    }
    return 0;
}