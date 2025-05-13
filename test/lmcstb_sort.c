#define LMCSTB_SORT_DEF
#include "../src/lmcstb_sort.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>


#define SEPARATION(_n_) do { for (size_t i = 0; i < _n_; i++) { printf("="); } printf("\n"); } while(0)
void array_sort(const size_t capacity, const size_t iterations, size_t (*sort)(void*, const size_t, const size_t, int (*cmp)(const void*, const void*)));


void test_default(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Qsort from <stdlib.h>:\n");
    array_sort(capacity, iterations, lmcstb_sort_qsort);

    return;
}
void test_selection(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Selection sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_selection);

    printf("Double Selection sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_doubleSelection);

    printf("Heap sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_heap);

    return;
}
void test_insertion(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Insertion sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_insertion);

    printf("Binary Insertion sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_binaryInsertion);

    printf("Shell sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_shell);

    return;
}
void test_bubble(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Bubble sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_bubble);

    printf("Shaker sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_shaker);

    printf("Comb sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_comb);
    
    return;
}
void test_quick(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Quick sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_quick);

    return;
}
void test_merge(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Merge in sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_mergeIn);

    printf("Merge out sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_mergeOut);

    return;
}
void test_fun(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Stalin sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_stalin);

    printf("Bogo sort(Can not finish):\n");
    array_sort(capacity, iterations, lmcstb_sort_bogo);

    return;
}
void test_cycle(const size_t capacity, const size_t iterations)
{
    SEPARATION(50);

    printf("Cycle sort:\n");
    array_sort(capacity, iterations, lmcstb_sort_cycle);

    return;
}


#define CAPACITY 1000
#define ITERATIONS 100


int main(void)
{
    srand(time(NULL));
    
    test_default(CAPACITY, ITERATIONS);

    test_selection(CAPACITY, ITERATIONS);
    test_insertion(CAPACITY, ITERATIONS);
    test_bubble(CAPACITY, ITERATIONS);

    test_quick(CAPACITY, ITERATIONS);
    test_merge(CAPACITY, ITERATIONS);

    test_fun(10, ITERATIONS);

    test_cycle(CAPACITY, ITERATIONS);

    SEPARATION(50);
    return EXIT_SUCCESS;
}


#define LMCSTB_SORT_IMPLEMENTATION
#include "../src/lmcstb_sort.h"


int int_compare(const void *x_elem, const void *y_elem)
{
    const int x = *(const int*)(x_elem), y = *(const int*)(y_elem);
    return (x > y) - (x < y);
}

void array_print(const int array[], const size_t length)
{
    for (size_t i = 0; i < length; i++) { printf("[%d]", array[i]); } printf("\n");
    return;
}
void array_randomize(int array[], const size_t length)
{
    size_t nb = 0;
    for (size_t iteration = 0; iteration < length; iteration++) {
        nb += rand() % length;
        array[iteration] = nb % length;
    } return;
}
bool array_check(const int array[], const size_t length)
{
    for (size_t i = 1; i < length; i++) { if (array[i - 1] > array[i]) { return false; } }
    return true;
}
void array_sort(const size_t capacity, const size_t iterations, size_t (*sort)(void*, const size_t, const size_t, int (*cmp)(const void*, const void*)))
{
    int array[capacity], sorted[capacity]; clock_t time; double totalTime = 0; size_t wrong_length = 0;

    for (size_t iteration = 0; iteration < iterations; iteration++) {
        array_randomize(array, capacity); for (size_t i = 0; i < capacity; i++) { sorted[i] = array[i]; }

        time = clock(); size_t sorted_length = sort(sorted, capacity, sizeof(int), int_compare); time = clock() - time;
        bool isSorted = array_check(sorted, capacity); totalTime += (double)(time) / CLOCKS_PER_SEC;

        if (isSorted) { continue; }

        if (array_check(sorted, sorted_length)) { wrong_length += 1; continue; }
        printf("\t> iteration: %ld\n", iteration);
        printf("\t> array : "); array_print(array, capacity);
        printf("\t> sorted: "); array_print(sorted, capacity);

        return;
    }

    printf("\t> Correctly Sorted: %lu/%lu\n", iterations - wrong_length, iterations);
    printf("\t> Total time: %.3lf\n", totalTime);
    printf("\t> Average time: %.3lf\n", totalTime / iterations);

    return;
}