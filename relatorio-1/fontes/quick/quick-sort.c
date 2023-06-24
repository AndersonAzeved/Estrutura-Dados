#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void swap(int *a, int *b)
{
    int m;
    m = *a;
    *a = *b;
    *b = m;
}

int partition(int *v, int s, int e){
    int d = s-1;
    unsigned int i;
    for(i = s; i <= e-1; i++){
        if(v[i] <= v[e]){
            d = d+1;
            swap(&v[d],&v[i]);
            
        }
    }
    swap(&v[d+1],&v[e]);
    return d+1;
}


void quickSort(int *v, int s, int e){
    if (s < e){
        int p = partition(v,s,e);
        quickSort(v,s,p-1);
        quickSort(v,p+1,e);
    }
}

int main(int argc, char **argv){
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));
    for (i = 0; i < n; i++)
        v[i] = rand(); // CASO NORMAL/MEDIO O(n∗logn)

    clock_gettime(CLOCK_MONOTONIC, &b);
    quickSort(v,0,n-1);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}