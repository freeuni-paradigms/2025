#include "Scheme.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
recursively concats all string nodeTypes
*/
char *ConcatAll(nodeType *list)
{
    if (*list == Nil || list == NULL)
        return malloc(1);

    // არაა საჭირო ამოცანის მიხედვით ინტის სტრინგად ამოღება, მაგრამ შეგვიძლია მივამატოთ.
    if (*list == Integer)
    {
        char *buf = malloc(13);
        sprintf(buf, "%d", *(int *)(list + 1));
        return buf;
    }

    if (*list == String)
        return strdup((char *)(list + 1));

    nodeType **list_ptr_pair = (nodeType **)(list + 1);
    nodeType *first_ptr = *list_ptr_pair;
    nodeType *second_ptr = *(list_ptr_pair + 1); 
    // მოერე ფოინთერის ამოღებისას მეწერა ესეთი კოდი &first_ptr,
    // ეს შეცდომაა რადგან ლოკალურად გადაწერილი ცვლადის მისამართს ამოიღებს
    // და არა ბლოკის მისამართს

    char *first = ConcatAll(first_ptr);
    char *second = ConcatAll(second_ptr);

    char *result = malloc(strlen(first) + strlen(second) + 1);
    result[0] = '\0';
    strcat(strcat(strcat(result, first), " "), second);

    free(first);
    free(second);

    return result;
}

int main() {
    nodeType *stringNodes[32] = {};
    nodeType *intNodes   [32] = {};
    nodeType *listNodes  [32] = {};

    nodeType  nilNode = Nil;


    for (int i = 0; i < 32; i++) {
        char some_string[32] = {};

        sprintf(some_string, "test%d", i);

        
        nodeType *ptr = malloc(sizeof(nodeType) + strlen(some_string) + 1);

        *ptr = String;

        strcpy((char *)(ptr + 1), some_string);
        stringNodes[i] = ptr;
    }

    for (int i = 0; i < 32; i++) {
        
        nodeType *ptr = malloc(sizeof(nodeType) + sizeof(int));
        *ptr = Integer;

        memcpy(ptr + 1, &i, sizeof(int));

        intNodes[i] = ptr;
    }


    for (int i = 0; i < 32; i++) {
        
        nodeType *ptr = malloc(sizeof(nodeType) + 2 * sizeof(void *));
        *ptr = List;
        
        // set both pointers to nil

        ((nodeType **) (ptr + 1))[0] = &nilNode;
        ((nodeType **) (ptr + 1))[1] = &nilNode; 
        
        listNodes[i] = ptr;
    }

    for (int i = 0; i < 31; i++) {
        // connect all lists to eachother
        ((nodeType **) (listNodes[i] + 1))[1] = listNodes[i + 1]; 

        // even lists point to strings, odds point to ints
        if ( i % 2 == 0) {
            ((nodeType **) (listNodes[i] + 1))[0] = stringNodes[i]; 
        } else {
            ((nodeType **) (listNodes[i] + 1))[0] = intNodes[i]; 
        }
    }

    printf("%s\n", ConcatAll(listNodes[0]));
}