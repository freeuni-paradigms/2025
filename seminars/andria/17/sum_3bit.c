#include "sum_3bit.h"

int sum_3bit(void* d) {
    int sum = 0;

    for (unsigned char *byte = d; *byte; byte++)
    {
        int op = *byte & 0b00000011;
        int x = (*byte & 0b00011100) >> 2;
        int y = (*byte & 0b11100000) >> 5;

        if (op == 0) sum += x + y;

        if (op == 1) sum += x - y;
    
        if (op == 2) sum += x * y;
        
        if (op == 3) 
            if (y != 0) sum += x / y;
    }

    return sum;
}

