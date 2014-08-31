#ifndef __CVECTOR_H_
#define __CVECTOR_H_

#define CVECTOR_SIZE    128

struct cvector {
    void **holder;
    int index;
    int size;
};

/* initialize structure members */
void cvector_init(struct cvector *v);

/* free allocated memory of structure member holder */
void cvector_exit(struct cvector *v);

/* insert [data] in holder member of [v] at offset [index] */
void cvector_insert(struct cvector *v, void *data, int index);

/* insert [data] after last element of holder member of [v] */
void cvector_push(struct cvector *v, void *data);

/* return and delete last element of holder member of [v] */
void *cvector_pop(struct cvector *v);

/* store current index and size of structure [v]
 * at pointer [index] and [size] */
void cvector_stat(struct cvector *v, int *index, int *size);

/* print current index and size of structure [v]
 * on stdout stream */
void cvector_info(struct cvector *v);

/* return pointer of data at offset [index] */
void *cvector_get(struct cvector *v, int index);

/* delete / null pointer at offset [index]
 *
 * if blank is one, pointer assign NULL,
 * index member of structure will remain as it is
 *
 * if blank is zero, pointer remove at offset [index],
 * index member of structure will decrement and all 
 * element of member move one index up */
int cvector_delete(struct cvector *v, int index, int blank);

/* swap element at index1 and index2 */
void cvector_swap(struct cvector *v, int index1, int index2);

/* array will shrink if possible */
static inline int cvector_shrink(struct cvector *v);

#endif
