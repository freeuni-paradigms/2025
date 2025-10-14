#include "sparsestringarray.h"
#include "vector.h"
#include <string.h>

void StringFree(void* elemAddr) {
    free(*(char**)elemAddr);
}

/**
* Function: SSANew
* ----------------
* Constructs the sparsestringarray addressed by the first argument to
* be of the specified length, using the specified group size to decide
* how many groups should be used to back the implementation. You can
* assume that arrayLength is greater than groupSize, and for simplicity you
* can also assume that groupSize divides evenly into arrayLength.
*/
void SSANew(sparsestringarray* ssa, int arrayLength, int groupSize) {
    ssa->groupSize = groupSize;
    ssa->arrayLength = 0;
    ssa->numGroups = arrayLength / groupSize;
    ssa->groups = malloc(sizeof(group) * ssa->numGroups);
 
    for (int i = 0; i < ssa->numGroups; i++)
    {   
        VectorNew(&ssa->groups[i].strings, sizeof(char *), StringFree, ssa->groupSize);
        // სემინარზე შეცდომა აქ გვქონდა, მეგონა როდესაც VectorNew-ს თაცდაპირველ ზომას გადავცემდით
        // ის შეავსებდა ცარიელი დატით სივრცეებს, თუმცა ასე არ ხდება და ეს ჩვენ უნდა გავაკეთოთ
        for (int j = 0; j < ssa->groupSize; j++) 
        {
            char *empty_str = strdup("");
            VectorAppend(&ssa->groups[i].strings, &empty_str);
        }

        ssa->groups[i].bitmap = malloc(ssa->groupSize);
        memset(ssa->groups[i].bitmap, 0, ssa->groupSize);
    }
}

/**
* Function: SSADispose
* --------------------
* Disposes of all the resources embedded within the addressed
* sparsestringarray that have built up over the course of its
* lifetime.
*/
void SSADispose(sparsestringarray* ssa) {
    for (int i = 0; i < ssa->numGroups; i++)
    {
        free(ssa->groups[i].bitmap);
        VectorDispose(&ssa->groups[i].strings);
    }

    free(ssa->groups);
}

/**
* Function: SSAInsert
* -------------------
* Inserts the C string addressed by str into the sparsestringarray addressed
* by ssa at the specified index. If some nonempty string already resides
* at the specified index, then it is replaced with the new one. Note that
* SSAInsert makes a deep copy of the string address by str.
*/
bool SSAInsert(sparsestringarray* ssa, int index, const char* str) {
    int group_idx = index / ssa->groupSize;
    int string_idx = index % ssa->groupSize;

    group *curr_group = &ssa->groups[group_idx];

    char *value = strdup(str);

    if (curr_group->bitmap[string_idx])
    {
        // აქ ასევე შეცდომა გვქონდა, როგორც ჩანს, ვექტორი პირდაპირ ფოინთერს ინახავს
        // ჩვენ გვინდა გადავაკოპიროთ, ამიტომ სტრინგი პირდაპირ არ უნდა გადავაწოდოთ ვექტორს
        // და მას დუპლიკაცია უნდა გავუკეთოთ, ასევე ვექტორს გადაეცემა ცვლადის მისამართი 
        // (იგივე შეცდომაა StringInsert-ის ხაზზე)
        VectorReplace(&curr_group->strings, &value, string_idx);

        return false;
    }
    
    VectorInsert(&curr_group->strings, &value, string_idx);
    curr_group->bitmap[string_idx] = true;
    ssa->arrayLength++;
    
    return true;
}

/**
* Function: SSAMap
* ----------------
* Applies the specified mapping routine to every single index/string pair
* (along with the specified auxiliary data). Note that the mapping routine
* is called on behalf of all strings, both empty and nonempty.
*/
void SSAMap(sparsestringarray* ssa, SSAMapFunction mapfn, void* auxData) {
    for (int i = 0; i < ssa->numGroups; i++)
    {
        group *curr_group = &ssa->groups[i];

        for (int j = 0; j < ssa->groupSize; j++)
        {
            if (curr_group->bitmap[j]) {
                const char *str = *(char **)VectorNth(&curr_group->strings, j);
                mapfn(i * ssa->groupSize + j, str, auxData);
            }
        }
    }
}

