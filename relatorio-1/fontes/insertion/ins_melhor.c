#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void swap(int *a, int *b){
    int m;
    m = *a;
    *a = *b;
    *b = m;
}

void insertionSort(int *v, int n){
    unsigned int i;
    int e;
    for(e = 0; e < n; e++){
        i = e;
        while ((i > 0) && (v[i] < v[i-1])){
            swap(&v[i-1], &v[i]);
            i--;
        }
    }
}


int main(int argc, char **argv)
{
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));
            
    // MELHOR CASO - Vetor já ordenado em ordem crescente 
    // No melhor caso o Insertion Sort é O(n)
    for (i = 0; i < n; i++)
       v[i] = i;
    

    clock_gettime(CLOCK_MONOTONIC, &b);
    insertionSort(v,n);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}
