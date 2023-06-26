#include <time.h>
#include "hash.h"

/**/
struct hash *inicia_hash(struct hash *t, int m){
    t = (struct hash*) malloc(sizeof(struct hash));
    if(t != NULL){
        t->m = m;
        t->t = (struct list_node**) malloc(m * sizeof(struct list_node*));
        if(t->t == NULL){
            free(t);
            return NULL;
        }
        t->n = 0;
        for(int i = 0; i < t->m; i++)
            t->t[i] = NULL;
    }
    return t;
}

void liberar_hash(struct hash* t){
    if(t != NULL){
        for(int i = 0; i < t->m; i++){
            if(t->t[i] != NULL)
                free(t->t[i]);
        }
        free(t->t);
        free(t);
    }
}

int calc_resto(int value, int m){
    return value % m;
}

int inserir_SemColisão(struct hash *t, struct list_node *l){
    if(t == NULL || t->n == t->m)
        return 0;
    int posicao = calc_resto(l->value, t->m);
    struct list_node *new;
    new = (struct list_node*) malloc(sizeof(struct list_node));
    if(new == NULL)
        return 0;
    *new = *l;
    t->t[posicao] = new;
    t->n++;
    return 1;
}

int busca_SemColisao(struct hash* t, int value, struct list_node *l){
    if(t != NULL)
        return 0;
    
    int posicao = calc_resto(value, t->m);
    if(t->t[posicao] == NULL)
        return 0;
    *l = *(t->t[posicao]);
    return 1;
}



int main(int argc, char **argv){
    struct hash* table;
    inicia_hash(table, 1);

    unsigned int i;
    int n = 15;

    srand(time(NULL));


    //  Jeito certo

    for(i = 0; i < n; i++){
        //tree_insert(&root, tree_new(rand()%100));
        printf("Ok");
    }

    //tree_print_dot(root);




    // Testando manualmente
    /*
    int v[n];
    int sort;
    for(i = 0; i < n; i++){
        sort = rand()%100;
        v[i] = sort;
        tree_insert(&root, tree_new(sort));
    }
    printf("Valor da Raiz: %d\n", root->value);
    tree_print(root);
    struct tree_node *r = NULL;
    r = (struct tree_node *) malloc(sizeof(struct tree_node));
    r = search(root,15);
    if(r == NULL)
        printf("\n\nNULL\n\n");
    else
        printf("\n\nBusca Encontrada: %d\n\n", r->value);
    printf("Ordem do sorteio\n");
    for(i = 0; i < n; i++){
        printf("%d,", v[i]);
    }
    printf("\n");
    */

    return 0;
}