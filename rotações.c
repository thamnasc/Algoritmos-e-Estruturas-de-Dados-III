#include <stdlib.h>

typedef struct tNo {
    char chave;
    int valor;
    struct tNo *pai, *esq, *dir;
} tNo;

tNo *rotacaoDir(tNo *x) {
    
    tNo *y = x->esq;
    x->esq = y->dir;
    y->pai = x->pai;
    x->pai = y;
    if(y->dir != NULL)
        y->dir->pai = x;
    y->dir = x;

    return y;
}

tNo *rotacaoEsq(tNo *x) {

    tNo *y = x->dir;
    x->dir = y->esq;
    y->pai = x->pai;
    x->pai = y; 
    if(y->esq != NULL)
        y->esq->pai = x;
    y->esq = x;

    return y;
}