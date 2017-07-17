#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "levenshtein.h"


int check_arguments (int arguments)
{
    if (arguments < 3) {
        fprintf(stderr, "Error: two arguments required\n");
        return 1;
    }
    return 0;
}

char** make_array (size_t m, size_t n)
{
    char** array = malloc(sizeof array * m);
    for (size_t i = 0; i < m; ++i) {
        array[i] = malloc(sizeof i * n);
    }
    return array;
}

size_t load_array (char** array, const char* filename, int rows)
{
    // Load each line into array[i] and return total number of lines
    FILE* stream = fopen(filename, "r");
    size_t i = 0;
    while (fgets(array[i], rows, stream)) {
        array[i][strlen(array[i]) -1] = '\0';
        ++i;
    }
    fclose(stream);
    return i;
}

void find_distances (char** array1, char** array2, size_t string1, size_t string2)
{
    int distance[string1][string2];
    for (size_t i = 0; i < string1; ++i) {
        #pragma omp parallel for
        for (size_t j = 0; j < string2; ++j) {
            distance[i][j] = levenshtein(array1[i], array2[j]);
        }
    }
    // printf is called in separate loop to prevent locking threads
    for (size_t i = 0; i < string1; ++i) {
        for (size_t j = 0; j < string2; ++j) {
            printf("%s, %s, %d\n", array1[i], array2[j], distance[i][j]);
        }
    }
}

void free_array (char** array, size_t m)
{
    for (size_t i = 0; i < m; ++i) {
        free(array[i]);
    }
    free(array);
}

int main (int argc, char** argv)
{
    check_arguments(argc);

    const char* source_file = argv[1];
    const char* target_file = argv[2];
    static size_t rows = 2000;
    static size_t cols = 60;

    char** source = make_array(rows, cols);
    char** target = make_array(rows, cols);
    size_t source_size = load_array(source, source_file, rows);
    size_t target_size = load_array(target, target_file, rows);

    find_distances(source, target, source_size, target_size);

    free_array(source, rows);
    free_array(target, rows);

    return 0;
}
