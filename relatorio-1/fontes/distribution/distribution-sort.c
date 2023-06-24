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

int min(int *v, int n){
    int min = v[0];
    unsigned int i;
    for(i = 0; i < n; i++){
        if(v[i] < min){
            min = v[i];
        }
    }
    return min;
}

int max(int *v, int n){
    int max = v[0];
    unsigned int i;
    for(i = 0; i < n; i++){
        if(v[i] > max){
            max = v[i];
        }
    }
    return max;
}


void distributionSort(int *v, int n){
    unsigned int i;
    int s = min(v,n); //1
    int b = max(v,n); //5
    int d;
    int* c; 
    int* w;
    c = (int*) malloc((b-s+1)*sizeof(int)); // gera um vetor c, com o tamanho da diferença entre o min e max, mais um
    w = (int*) malloc(n*sizeof(int)); // gera um vetor w, com o tamanho da diferença entre o min e max, mais um

    for(i = 0; i < (b-s+1); i++){ // Atribui 0 a todas as posições do vetor
        c[i] = 0;
    }
    for(i = 0; i < n; i++){ // 
        c[v[i]-s] = c[v[i]-s]+1;
    }

    for(i = 1; i < (b-s+1); i++){
        c[i] = c[i]+c[i-1];
    }

    for(i = 0; i < n; i++){
        d = v[i]-s;
        w[c[d]] = v[i];
        c[d] = c[d]-1;
    }

    for(i = 0; i < n; i++){
        v[i] = w[i+1];
    }   
}


int main(int argc, char **argv){
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));

    // DISTRIBUTION 
    // CASO ÚNICO
    for (i = 0; i < n; i++)
        v[i] = rand()%1000;

    clock_gettime(CLOCK_MONOTONIC, &b);
    distributionSort(v,n);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}