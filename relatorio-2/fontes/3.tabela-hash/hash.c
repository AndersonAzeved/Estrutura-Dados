#include "hash.h"
#include <time.h>

void list_insert(NODE **l, NODE *w){
    w->next = (*l);
    (*l) = w;
}

int f(int value, int m){
    return value % m;
}

void hash_insert(HASH **h, NODE *w){
    if((*h)->m > (*h)->n){
        list_insert(&(*h)->t[f(w->value, (*h)->m)], w);
        (*h)->n++;
    }else{
        rehash(&(*h));
        list_insert(&(*h)->t[f(w->value, (*h)->m)], w);
        (*h)->n++;
    }
}

void rehash(HASH **h){
   HASH *new = inicia_hash(&new, (((*h)->m) * 2));

   NODE *item, *next;
   
    for(int i = 0; i < (*h)->m; i++){
        item = (*h)->t[i];
        while(item != NULL){
            next = item->next;
            list_insert(&new->t[f(item->value, new->m)], item);
            new->n++;
            item = next;
        }
    }

    free((*h)->t);
    free((*h));
    
    (*h) = new;

}


NODE *node_new(int v){ 
    NODE *w;
 
    w = (NODE*) malloc(sizeof(NODE));
    w->value = v;
    w->next = NULL;
 
    return w;
}


HASH *inicia_hash(HASH **h, int m){
    (*h) = (HASH*) malloc(sizeof(HASH));
    if((*h) != NULL){
        (*h)->m = m;
        (*h)->t = (NODE**) malloc(m * sizeof(NODE*));
        if((*h)->t == NULL){
            free((*h));
            return NULL;
        }
        (*h)->n = 0;
        for(int i = 0; i < (*h)->m; i++)
            (*h)->t[i] = NULL;
    }
    return (*h);
}

void liberar_hash(HASH **h){
    NODE *item, *next;

    for(int i = 0; i < (*h)->m; i++){
        item = (*h)->t[i];
        while(item != NULL){
            next = item->next;
            free(item);
            item = next;
        }      
    }
}

NODE *search(HASH *h, int value){
    int resto = f(value, h->m);
    NODE *aux = h->t[resto];
    while(aux != NULL){
        if(aux->value == value){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}


int main(int argc, char const *argv[]){
    HASH *hash = inicia_hash(&hash, 1);
    
    srand(time(NULL));

    int n = 10;

    for(int i = 0; i < n; i++){
        hash_insert(&hash, node_new(rand()));
    }

    NODE *aux;
    for(int i = 0; i < hash->m; i++){
        aux = hash->t[i];
        printf("Posicao %d: ", i);
        while(aux != NULL){
            printf("%d -> ", aux->value);
            aux = aux->next;
        }
        printf("\n");
    }

    NODE* res = search(hash, rand());
    if(res)
        printf("Achou %d\n",res->value);
    else
        printf("Não achou\n");

    liberar_hash(&hash);

    return 0;
}
