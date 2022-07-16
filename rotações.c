#include <stdlib.h>

typedef struct tNo {
    char chave;
    int valor;
    struct tNo *pai, *esq, *dir;
} tNo;
tNo *rotacaoDir(tNo *x) {
    
    tNo *y = x->pai;
    y->esq = x->dir;
    if(x->dir != NULL)
        x->dir->pai = y;
    x->dir = y;
    x->pai = y->pai;
    y->pai = x;

    return y;
}

tNo *rotacaoEsq(tNo *x) {

    tNo *y = x->dir;
    x->dir = y->esq;
    if(y->esq != NULL)
        y->esq->pai = x;
    y->esq = x;
    y->pai = x->pai;
    x->pai = y;

    return y;
}