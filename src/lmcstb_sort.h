#if !defined(LMCSTB_SORT_H_)
#define LMCSTB_SORT_H_

#include <stdlib.h>


#if !defined(LMCSTB_SORT_DEF)
# define LMCSTB_SORT_DEF static inline
#endif /* if !def(LMCSTB_SORT_DEF) */


LMCSTB_SORT_DEF size_t lmcstb_sort_qsort(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_selection(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_doubleSelection(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_heap(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_insertion(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_binaryInsertion(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_shell(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_bubble(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_shaker(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_comb(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_quick(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_mergeIn(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_mergeOut(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_stalin(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));
LMCSTB_SORT_DEF size_t lmcstb_sort_bogo(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));

LMCSTB_SORT_DEF size_t lmcstb_sort_cycle(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*));


#endif /* if !defined(LMCSTB_SORT_H_) */



#if defined(LMCSTB_SORT_IMPLEMENTATION)

#if !defined(LMCSTB_SORT_ASSERT)
# include <assert.h>
# define LMCSTB_SORT_ASSERT(_exp_) assert(_exp_)
#endif /* if !defined(LMCSTB_SORT_ASSERT) */ 


LMCSTB_SORT_DEF int lmcstb_sort_bytes_same(const void *x_ptr, const void *y_ptr, const size_t size)
{
    size_t byte; char *x, *y;
    byte = 0; x = (char*)(x_ptr); y = (char*)(y_ptr);

    for (; byte < size; byte++, x++, y++) {
        if (*x != *y) { return 0; }
    } return 1;
}
LMCSTB_SORT_DEF void lmcstb_sort_bytes_swap(void *x_ptr, void *y_ptr, const size_t size)
{
    size_t byte; char *x, *y, tmp;
    byte = 0; x = (char*)(x_ptr); y = (char*)(y_ptr);

    for (; byte < size; byte++, x++, y++) {
        tmp = *x; *x = *y; *y = tmp;
    } return;
}

#if !defined(LMCSTB_SORT_SHUFFLE)
# define LMCSTB_SORT_SHUFFLE lmcstb_sort_shuffle

LMCSTB_SORT_DEF void lmcstb_sort_shuffle(void *ptr, const size_t length, const size_t size)
{
    char * array;
    size_t x, y;

    array = (char *)(ptr);
    x = rand() % length; y = rand() % length;

    lmcstb_sort_bytes_swap(array + x * size, array + y * size, size);

    return;
}

#endif /* if !defined(LMCSTB_SORT_SHUFFLE) */


LMCSTB_SORT_DEF size_t lmcstb_sort_qsort(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    qsort(ptr, length, size, compare);
    
    return length;
}

LMCSTB_SORT_DEF size_t lmcstb_sort_selection(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t i, j; char *i_elem, *j_elem;
    void *min_ptr;

    array = (char *)(ptr);
    i = 0; i_elem = array;

    for (; i < length; i++, i_elem += size) {
        j = i + 1; j_elem = i_elem + size;
        min_ptr = i_elem;

        for (; j < length; j++, j_elem += size) {
            if (compare(j_elem, min_ptr) < 0) { min_ptr = j_elem; }
        }

        if (!lmcstb_sort_bytes_same(i_elem, min_ptr, size)) {
            lmcstb_sort_bytes_swap(i_elem, min_ptr, size);
        }
    }

    return length;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_doubleSelection(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t left, right; char *left_elem, *right_elem;
    size_t i; char *i_elem;
    void *min_ptr, *max_ptr;

    array = (char *)(ptr);
    left = 0, left_elem = array;
    right = length - 1, right_elem = array + right * size;

    while (right > left) {
        i = left + 1; i_elem = left_elem + size;
        min_ptr = max_ptr = left_elem;

        for (; i <= right; i++, i_elem += size) {
            if (compare(i_elem, min_ptr) < 0) { min_ptr = i_elem; }
            else
            if (compare(i_elem, max_ptr) > 0) { max_ptr = i_elem; }
        }

        if (!lmcstb_sort_bytes_same(max_ptr, right_elem, size)) {
            lmcstb_sort_bytes_swap(max_ptr, right_elem, size);

            min_ptr = lmcstb_sort_bytes_same(min_ptr, right_elem, size) ? max_ptr : min_ptr;
        }

        if (!lmcstb_sort_bytes_same(min_ptr, left_elem, size)) {
            lmcstb_sort_bytes_swap(left_elem, min_ptr, size);
        }

        left++; left_elem += size;
        right--; right_elem -= size;
    }

    return length;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_heap(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }
    
    char * array;
    size_t begin, end; char *begin_elem, *end_elem;
    size_t root, child; char *root_elem, *child_elem;

    array = (char *)(ptr);
    begin = length >> 1; begin_elem = array + begin * size;
    end = length; end_elem = begin_elem + (end - begin) * size;

    while (end > 1) {
        if (begin > 0) { begin--; begin_elem -= size; }
        else {
            end--; end_elem -= size;

            lmcstb_sort_bytes_swap(array, end_elem, size);
        }

        root = begin; root_elem = begin_elem;

        while ((child = 2 * root + 1) < end) {
            child_elem = root_elem + root * size + size;

            if (child + 1 < end && compare(child_elem, child_elem + size) < 0) { child++; child_elem += size; }

            if (compare(root_elem, child_elem) >= 0) { break; }
            lmcstb_sort_bytes_swap(root_elem, child_elem, size);

            root = child; root_elem = child_elem;
        }
    }

    return length;
}

LMCSTB_SORT_DEF size_t lmcstb_sort_insertion(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t i, j; char *i_elem, *j_elem;
    size_t k; char *kprev_elem, *k_elem;

    array = (char *)(ptr);
    i = 1; i_elem = array + size;

    for (; i < length; i++, i_elem += size) {
        j = 0; j_elem = array;

        for (; j < i; j++, j_elem += size) {
            if (compare(i_elem, j_elem) < 0) { break; }
        }

        if (lmcstb_sort_bytes_same(j_elem, i_elem, size)) { continue; }

        k = i; kprev_elem = i_elem - size; k_elem = i_elem;

        for (; k > j; k--, k_elem = kprev_elem, kprev_elem -= size) {
            lmcstb_sort_bytes_swap(kprev_elem, k_elem, size);
        }
    }

    return length;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_binaryInsertion(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t i; char *i_elem;
    size_t left, middle, right, tmp; char *middle_elem;
    size_t j; char *jprev_elem, *j_elem;

    array = (char *)(ptr);
    i = 1; i_elem = array + size;

    for (; i < length; i++, i_elem += size) {
        left = 0; right = i;
        middle = 0; middle_elem = array;

        while (left != right) {
            tmp = (left + right) / 2; middle_elem += (tmp - middle) * size;
            middle = tmp;

            if (compare(i_elem, middle_elem) < 0) { right = middle; } else { left = middle + 1; }
        }

        j = i; jprev_elem = i_elem - size; j_elem = i_elem;

        for (; j > right; j--, j_elem = jprev_elem, jprev_elem -= size) {
            lmcstb_sort_bytes_swap(jprev_elem, j_elem, size);
        }
    }

    return length;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_shell(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t gap, gap_size; float gap_divisor;
    size_t i, j; char *i_elem, *jgap_elem, *j_elem;

    array = (char *)(ptr);
    gap = length; gap_divisor = 2.2f;

    do {
        gap = gap / gap_divisor;
        gap = gap < 1 ? 1 : gap;
        gap_size = gap * size;

        i = gap; i_elem = array + i * size;

        for (; i < length; i++, i_elem += size) {
            j = i; jgap_elem = i_elem - gap_size; j_elem = i_elem;

            while (j >= gap && compare(jgap_elem, j_elem) > 0) {
                lmcstb_sort_bytes_swap(jgap_elem, j_elem, size);

                j -= gap; j_elem = jgap_elem; jgap_elem -= gap_size;
            }
        }
    } while (gap != 1);

    return length;
}

LMCSTB_SORT_DEF size_t lmcstb_sort_bubble(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array; size_t end;
    size_t i; char *iprev_elem, *i_elem;
    int hasSwap;

    array = (char *)(ptr); end = length;

    do {
        hasSwap = 0;
        i = 1; iprev_elem = array; i_elem = array + size;

        for (; i < end; i++, iprev_elem = i_elem, i_elem += size) {
            if (compare(iprev_elem, i_elem) <= 0) { continue; }

            lmcstb_sort_bytes_swap(iprev_elem, i_elem, size);
            hasSwap = 1;
        }

        end--;
    } while (hasSwap);

    return length;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_shaker(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array; size_t counter;
    size_t i; char *iprev_elem, *i_elem;
    size_t end; int hasSwap;

    array = (char *)(ptr); counter = 0;
    i = 1; iprev_elem = array; i_elem = array + size;

    do {
        end = length - counter; hasSwap = 0;

        for (; i < end; i++, iprev_elem = i_elem, i_elem += size) {
            if (compare(iprev_elem, i_elem) <= 0) { continue; }

            lmcstb_sort_bytes_swap(iprev_elem, i_elem, size);
            hasSwap = 1;
        }

        if (!hasSwap) { break; }
        
        i -= 2; i_elem = iprev_elem - size; iprev_elem = i_elem - size;
        end = counter; hasSwap = 0;
        
        for (; i > end; i--, i_elem = iprev_elem, iprev_elem -= size) {
            if (compare(iprev_elem, i_elem) <= 0) { continue; }
            
            lmcstb_sort_bytes_swap(iprev_elem, i_elem, size);
            hasSwap = 1;
        }
        
        i += 1; iprev_elem = i_elem; i_elem += size;
        
        counter++;
    } while (hasSwap);

    return length;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_comb(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t gap; float gap_divisor;
    size_t i; char *i_elem, *igap_elem;
    int hasSwap;

    array = (char *)(ptr);
    gap = length; gap_divisor = 1.3;

    do {
        gap /= gap_divisor;
        gap = (gap <= 1) ? 1 : (gap == 9 || gap == 10) ? 11 : gap;
        hasSwap = (gap > 1);

        i = 0; i_elem = array; igap_elem = array + gap * size;

        for (; i < length; i++, i_elem += size, igap_elem += size) {
            if (compare(i_elem, igap_elem) <= 0) { continue; }

            lmcstb_sort_bytes_swap(i_elem, igap_elem, size);
            hasSwap = 1;
        }
    } while (hasSwap);

    return length;
}

LMCSTB_SORT_DEF size_t lmcstb_sort_quick_partition(const size_t left, char *left_elem, const size_t right, char **pivot_elem_ptr, const size_t size, int (*compare)(const void*, const void*))
{
    size_t i, j; char *i_elem, *j_elem;
    i = j = left; i_elem = j_elem = left_elem;

    for (; j < right; j++, j_elem += size) {
        if (compare(j_elem, *pivot_elem_ptr) >= 0) { continue; }

        lmcstb_sort_bytes_swap(i_elem, j_elem, size);
        i++; i_elem += size;
    }

    lmcstb_sort_bytes_swap(i_elem, j_elem, size);
    *pivot_elem_ptr = i_elem;

    return i;
}
LMCSTB_SORT_DEF void lmcstb_sort_quick_rec(const size_t left, char *left_elem, const size_t right, char *right_elem, const size_t size, int (*compare)(const void*, const void*))
{
    if (left >= right) { return; }

    size_t pivot; char *pivot_elem;
    pivot = right; pivot_elem = right_elem;

    pivot = lmcstb_sort_quick_partition(left, left_elem, right, &pivot_elem, size, compare);

    if (pivot > 0) {
        lmcstb_sort_quick_rec(left, left_elem, pivot - 1, pivot_elem - size, size, compare);
    } lmcstb_sort_quick_rec(pivot + 1, pivot_elem + size, right, right_elem, size, compare);

    return;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_quick(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t left, right; char *left_elem, *right_elem;

    array = (char *)(ptr);
    left = 0; left_elem = array;
    right = length - 1; right_elem = array + right * size;

    lmcstb_sort_quick_rec(left, left_elem, right, right_elem, size, compare);

    return length;
}

LMCSTB_SORT_DEF void lmcstb_sort_mergeIn_fusion(const size_t left, char *left_elem, const size_t middle, char *middle_elem, const size_t right, const size_t size, int (*compare)(const void*, const void*))
{
    size_t x, y; char *x_elem, *y_elem;
    size_t i; char *iprev_elem, *i_elem;

    x = left; x_elem = left_elem;
    y = middle; y_elem = middle_elem;

    while (x < y && y < right) {
        if (compare(x_elem, y_elem) < 0) { x++; x_elem += size; continue; }

        i = y; iprev_elem = y_elem - size; i_elem = y_elem;

        for (; i > x; i--, i_elem = iprev_elem, iprev_elem -= size) {
            lmcstb_sort_bytes_swap(iprev_elem, i_elem, size);
        }

        y++; y_elem += size;
    }

    return;
}
LMCSTB_SORT_DEF void lmcstb_sort_mergeIn_rec(const size_t left, char *left_elem, const size_t right, char *right_elem, const size_t size, int (*compare)(const void*, const void*))
{
    if (right - left <= 1) { return; }

    size_t middle; char *middle_elem;
    middle = (left + right) / 2; middle_elem = left_elem + (middle - left) * size;

    lmcstb_sort_mergeIn_rec(left, left_elem, middle, middle_elem, size, compare);
    lmcstb_sort_mergeIn_rec(middle, middle_elem, right, right_elem, size, compare);

    lmcstb_sort_mergeIn_fusion(left, left_elem, middle, middle_elem, right, size, compare);

    return;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_mergeIn(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t left, right; char *left_elem, *right_elem;

    array = (char *)(ptr);
    left = 0; left_elem = array;
    right = length; right_elem = array + right * size;

    lmcstb_sort_mergeIn_rec(left, left_elem, right, right_elem, size, compare);

    return length;
}
LMCSTB_SORT_DEF void lmcstb_sort_mergeOut_fusion(const size_t left, char *left_elem, const size_t middle, char *middle_elem, const size_t right, char *tmp, const size_t size, int (*compare)(const void*, const void*))
{
    size_t i, x, y; char *i_elem, *x_elem, *y_elem;
    i = left; i_elem = left_elem; x_elem = tmp;

    for (; i < middle; i++, i_elem += size, x_elem += size) {
        lmcstb_sort_bytes_swap(x_elem, i_elem, size);
    }

    i = x = left; y = middle; i_elem = left_elem; x_elem = tmp; y_elem = middle_elem;

    while (x < middle && y < right) {
        if (compare(x_elem, y_elem) <= 0) {
            lmcstb_sort_bytes_swap(x_elem, i_elem, size);

            x++; x_elem += size;
        }
        else {
            lmcstb_sort_bytes_swap(y_elem, i_elem, size);

            y++; y_elem += size;
        }

        i++; i_elem += size;
    }

    if (x == middle) { return; }

    for (; i < right; i++, i_elem += size, x_elem += size) {
        lmcstb_sort_bytes_swap(x_elem, i_elem, size);
    }

    return;
}
LMCSTB_SORT_DEF void lmcstb_sort_mergeOut_rec(const size_t left, char *left_elem, const size_t right, char *right_elem, char *tmp, const size_t size, int (*compare)(const void*, const void*))
{
    if (right - left <= 1) { return; }

    size_t middle; char *middle_elem;
    middle = (left + right) / 2; middle_elem = left_elem + (middle - left) * size;

    lmcstb_sort_mergeOut_rec(left, left_elem, middle, middle_elem, tmp, size, compare);
    lmcstb_sort_mergeOut_rec(middle, middle_elem, right, right_elem, tmp, size, compare);

    lmcstb_sort_mergeOut_fusion(left, left_elem, middle, middle_elem, right, tmp, size, compare);

    return;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_mergeOut(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array, tmp[(length + 1) / 2 * size];
    size_t left, right; char *left_elem, *right_elem;

    array = (char *)(ptr);
    left = 0; left_elem = array;
    right = length; right_elem = array + right * size;

    lmcstb_sort_mergeOut_rec(left, left_elem, right, right_elem, tmp, size, compare);

    return length;
}

LMCSTB_SORT_DEF size_t lmcstb_sort_stalin(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t write, read; char *write_elem, *read_elem;
    size_t i; char *i_elem;

    array = (char *)(ptr);
    write = read = 1; write_elem = read_elem = array + size;

    for (; read < length; read++, read_elem += size) {
        if (compare(write_elem - size, read_elem) <= 0) {
            if (write != read) {
                lmcstb_sort_bytes_swap(write_elem, read_elem, size);
            }

            write++; write_elem += size;
        }
    }

    i = write; i_elem = write_elem;

    for (; i < length; i++, i_elem += size) { *i_elem = 0; }

    return write;
}
LMCSTB_SORT_DEF size_t lmcstb_sort_bogo(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t i; char *iprev_elem, *i_elem;

    array = (char *)(ptr);

    for (;;) {
        i = 1; iprev_elem = array; i_elem = array + size;

        for (; i < length; i++, iprev_elem = i_elem, i_elem += size) {
            if (compare(iprev_elem, i_elem) > 0) { break; }
        }

        if (i == length) { break; }

        LMCSTB_SORT_SHUFFLE(ptr, length, size);
    }

    return length;
}

LMCSTB_SORT_DEF size_t lmcstb_sort_cycle(void *ptr, const size_t length, const size_t size, int (*compare)(const void*, const void*))
{
    LMCSTB_SORT_ASSERT(ptr && compare);
    if (length < 2) { return length; }

    char * array;
    size_t i, j; char *i_elem, *j_elem;
    size_t pos; char *pos_elem;

    array = (char *)(ptr);
    i = 0; i_elem = array;

    for (; i < length;) {
        j = i + 1; j_elem = i_elem + size;
        pos = i; pos_elem = i_elem;

        for (; j < length; j++, j_elem += size) {
            if (compare(j_elem, i_elem) < 0) { pos++; pos_elem += size; }
        }
        
        if (i == pos) { i++; i_elem += size; continue; }

        while (lmcstb_sort_bytes_same(i_elem, pos_elem, size)) { pos++; pos_elem += size; }
        lmcstb_sort_bytes_swap(i_elem, pos_elem, size);
    }

    return length;
}


#endif /* if defined(LMCSTB_SORT_IMPLEMENTATION) */



/* 
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2025 LemilCa
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/