#include <stdio.h>
#include <stdlib.h>
#include "cvector.h"

int cvector_size = CVECTOR_SIZE;

void cvector_init(struct cvector *v)
{
    v->index = -1;
    v->size = 0;
    v->holder = NULL;
}

void cvector_exit(struct cvector *v)
{
    free(v->holder);
}

void cvector_stat(struct cvector *v, int *index, int *size)
{
    *index = v->index;
    *size = v->size;
}

void cvector_info(struct cvector *v)
{
    printf("\nindex position %d\n", v->index);
    printf("capacity %d\n\n", v->size);
}

void cvector_insert(struct cvector *v, void *data, int index)
{
    if (v->index == -1 && v->size == 0) {
        fprintf(stderr, "vector is not yet initialized.\n");
        exit(EXIT_FAILURE);
    } else if (index >= 0 && index <= v->index) {  
        if ((v->index == v->size - 1)) {
            v->size += cvector_size;
            void *temp;
            temp = realloc(v->holder, sizeof(void *) * v->size);
            if (!temp) {
                fprintf(stderr, "cvector_insert: reallocation fail!\n");
                exit(EXIT_FAILURE);
            } else {
                v->holder = temp;
            }
        }
        int i;
        for (i = v->index; i >= index; i--) {
            v->holder[i + 1] = v->holder[i];
        }
        v->holder[index] = data;
        v->index++;
    } else {
        fprintf(stderr, "cvector_insert: index %d is not valid!\n", index);
    }
}

void cvector_push(struct cvector *v, void *data)
{
    if (v->index == -1 && v->size == 0) {
        v->size = cvector_size;
        v->holder = malloc(sizeof(void *) * v->size);
        v->holder[++v->index] = data;
    } else if (v->index == v->size - 1) {
        v->size += cvector_size;
        void *temp;
        temp = realloc(v->holder, sizeof(void *) * v->size);
        if (!temp) {
            fprintf(stderr, "cvector_push: reallocation fail!\n");
            exit(EXIT_FAILURE);
        } else {
            v->holder = temp;
            v->holder[++v->index] = data;
        }
    } else {
        v->holder[++v->index] = data;
    }
}

void *cvector_pop(struct cvector *v)
{
    if (v->index != -1) {
        int index = v->index;
        v->index--;
        cvector_shrink(v);
        return v->holder[index];
    } else {
        fprintf(stderr, "cvector_pop: cvector underflow!\n");
        return NULL;
    }
}

void *cvector_get(struct cvector *v, int index)
{
    if (index >= 0 && index <= v->index)
        return v->holder[index];
    else {
        fprintf(stderr, "cvector_get: index %d is not valid!\n", index);
        return NULL;
    }
}

int cvector_delete(struct cvector *v, int index, int blank)
{
    if (index >= 0 && index <= v->index) {
        if (!blank) {
            int i;
            for (i = index + 1; i <= v->index; i++) {
                v->holder[i - 1] = v->holder[i];
            }
            v->index--;
            return -1;
        } else {
            v->holder[index] = NULL;
            cvector_shrink(v);
            return index;
        }
    } else {
        fprintf(stderr, "cvector_delete: index %d is not valid!\n", index);
        exit(EXIT_FAILURE);
    }
}

void cvector_swap(struct cvector *v, int index1, int index2)
{
    int r_index1, r_index2;
    if ((r_index1 = (index1 >= 0 && index1 <= v->index)) 
    && (r_index2 = (index2 >= 0 && index2 <= v->index))) {
        void *temp;
        temp = v->holder[index1];
        v->holder[index1] = v->holder[index2];
        v->holder[index2] = temp;
    } else {
        if (r_index1 == 0) {
            fprintf(stderr, \
                    "cvector_swap: second parameter %d is not valid!\n", \
                    index1);
        } else if (r_index2 == 1) {
            fprintf(stderr, \
                    "cvector_swap: third parameter %d is not valid!\n", \
                    index2);
        } else {
            fprintf(stderr, "this should not be printed!\n");
        }
    }
}

static inline int cvector_shrink(struct cvector *v)
{
    int two_page = cvector_size * 2;
    int max_limit = v->size - two_page;
    if (v->index < max_limit) {
        v->size -= cvector_size;
        void *temp;
        temp = realloc(v->holder, sizeof(void *) * v->size);
        if (!temp)
            return 1;
        else {
            printf("Shrinking... \n");
            v->holder = temp;
            return 0;
        }
    } else
        return 1;
}
