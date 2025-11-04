#include "compress.h"
#include <stdbool.h>

int Compress(void* data, void* out) {
    int size = 0;

    int count = 0;
    int last_elem = -1;
    unsigned char *byte = data;
    while (true) 
    {
        int first = (*byte & 0b11110000) >> 4;
        int second = *byte & 0b00001111;

        if (last_elem == -1) last_elem = first;

        if (last_elem == first) count++;
        else {
            *(char *)out++ = (count << 4) | (last_elem & 0b00001111);
            size++;

            count = 1;
            last_elem = first;
        }

        if (!first) break;
            
        if (last_elem == second) count++;
        else {
            *(char *)out++ = (count << 4) | (last_elem & 0b00001111);
            size++;

            count = 1;
            last_elem = second;
        }
        
        if (!second) break;

        byte++;
    }

    return size;
}
