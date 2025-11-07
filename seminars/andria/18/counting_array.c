#include "counting_array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GET_ELEM(a, i) ((char *)(a)->elem_arr + (i) * (a)->elem_size)

// typedef struct { 
//     void *elem_arr;
//     int *count_arr;

//     int log_len;          // number of unique elements in array
//     int aloc_len;         // alocated max number of elements

//     int elem_size;        // size of a single element
//     CmpFn cmp_fn;
//     FreeFn free_fn;
// } CountingArray;

void CountingArrayInit(CountingArray* a, int elem_size, CmpFn cmp_fn, FreeFn free_fn) {
    a->aloc_len = 5;
    a->log_len = 0;

    a->elem_size = elem_size;
    a->cmp_fn = cmp_fn;
    a->free_fn = free_fn;

    a->elem_arr = malloc(a->aloc_len * elem_size);
    a->count_arr = malloc(a->aloc_len * sizeof(int));

    assert(a->elem_arr);
    assert(a->count_arr);
}

void CountingArrayDestroy(CountingArray* a) {
    if (a->free_fn)
    {
        for (int i = 0; i < a->log_len; i++)
            a->free_fn(GET_ELEM(a, i));
    }
    
    free(a->elem_arr);
    free(a->count_arr);
}

int CountingArraySize(CountingArray* a) {
    return a->log_len;
}

void* CountingArrayGet(CountingArray* a, int index) {
    if (index < 0 || index >= a->log_len)
        return NULL;

    return GET_ELEM(a, index);
}

bool CountingArrayInsert(CountingArray* a, void* elem) {
    int i = 0;
    for (; i < a->log_len; i++)
    {
        if (a->cmp_fn(elem, GET_ELEM(a, i)) == 0) {
            a->count_arr[i]++;
            if (a->free_fn) a->free_fn(elem);
            return false;
        }

        if (a->cmp_fn(elem, GET_ELEM(a, i)) < 0) 
          break;
    }

    if (a->log_len == a->aloc_len) {
        a->aloc_len *= 2;

        a->elem_arr = realloc(a->elem_arr, a->aloc_len * a->elem_size);
        a->count_arr = realloc(a->count_arr, a->aloc_len * sizeof(int));

        assert(a->elem_arr);
        assert(a->count_arr);
    }

    if (a->log_len != 0 && i != a->log_len)
    {
        memmove(GET_ELEM(a, i + 1), GET_ELEM(a, i), (a->log_len - i) * a->elem_size);
        memmove(a->count_arr + i + 1, a->count_arr + i, (a->log_len - i) * sizeof(int));
    }

    memmove(GET_ELEM(a, i), elem, a->elem_size);
    a->count_arr[i] = 1;

    a->log_len++;
    return true;
}

void CountingArrayRemove(CountingArray* a, void* elem) {
    for (int i = 0; i < a->log_len; i++)
    {
        if (a->cmp_fn(elem, GET_ELEM(a, i)) < 0)
            return;

        if (a->cmp_fn(elem, GET_ELEM(a, i)) == 0) {
            a->count_arr[i]--;

            if (a->count_arr[i] == 0) {
                if (a->free_fn) a->free_fn(GET_ELEM(a, i));

                a->log_len--;
                if (i != a->log_len) {
                    memmove(GET_ELEM(a, i), GET_ELEM(a, i + 1), (a->log_len - i) * a->elem_size);
                    memmove(a->count_arr + i, a->count_arr + i + 1, (a->log_len - i) * sizeof(int));
                }
            }
            
            return;
        }
    }
}

void CountingArrayMerge(CountingArray* a, CountingArray* o) {
    for (int i = 0; i < o->log_len; i++)
    {   
        // შეცდომა სემინარზე, 1 ობიექტს, რომელიც o-ში ინახება, ბევრჯერ როდესაც ვაინსერტებდით
        // a არაი ამას განსხვავებულ ობიექტებად აღიქვამდა და შესაბამისად, 1-ზე მეტჯერ იძახებდა მასზე free-ს
        // რეალურად, ერთ ობიექტზე მხოლოდ ერთხელ უნდა მოხდეს free
        // ჩვენ შეგვიძლია ინსერტი გამოვიძახოთ ერთხელ თუ არ არსებობს ობიექტი საწყის არაიში და დანარჩენ
        // შემთხვევაში (თუ უკვე არსებობს ან ერთხელ გამოძახების შემდეგ) გავზარდოთ ქაუნთ არაის მნიშვნელობა
        void *elem_loc = bsearch(GET_ELEM(o, i), a->elem_arr, a->log_len, a->elem_size, a->cmp_fn);
        int count = o->count_arr[i];

        if (elem_loc == NULL) {
            CountingArrayInsert(a, GET_ELEM(o, i));

            // თავიდან ვიპოვოთ ლოკაცია სადაც დაემატა, ინდექსის გასაგებად
            elem_loc = bsearch(GET_ELEM(o, i), a->elem_arr, a->log_len, a->elem_size, a->cmp_fn);
            count--;                // ერთხელ უკვე ინსერტმა დაამატა
        }

        int index = (elem_loc - a->elem_arr) / a->elem_size;
        a->count_arr[index] += o->count_arr[i];           // 1 უკვე დაემატა ინსერტის დროს 
    }

    free(o->elem_arr);
    free(o->count_arr);
}
