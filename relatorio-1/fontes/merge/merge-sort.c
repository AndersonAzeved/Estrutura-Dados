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

void merge(int *v, int s, int m, int e){
    int w[e+1];
    int p = s;
    int q = m+1;
    unsigned int i;
    for(i = 1; i <= (e-s+1); i++){
        if((q > e) || ((p <= m) && (v[p] < v[q]))){
            w[i] = v[p];
            p++;
        }
        else{
            w[i] = v[q];
            q++;
        }
    }
    for(i = 1; i <= (e-s+1); i++){
        v[s+i-1] = w[i];
    }
}

void mergeSort(int *v, int s, int e){
    if(s < e){
        int m = (s+e)/2;
        mergeSort(v,s,m);
        mergeSort(v,m+1,e);
        merge(v,s,m,e);
    }
}


int main(int argc, char **argv){
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));

    // CASO MEDIO - Vetor aleatório - nlog2(n)
    for (i = 0; i < n; i++)
        v[i] = rand(); 

    clock_gettime(CLOCK_MONOTONIC, &b);
    mergeSort(v, 0,n-1);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}