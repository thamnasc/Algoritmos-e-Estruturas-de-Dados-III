#include <stdlib.h>

rotacaoDir(tNo *x) {
    
    tNo *y = x->pai;
    y->esq = x->dir;
    if(x->dir != NULL)
        x->dir->pai = y;
    x->dir = y;
    x->pai = y->pai;
    y->pai = x;

    return y;
}

rotacaoEsq(tNo *x) {

    tNo *y = x->dir;
    x->dir = y->esq;
    if(y->esq != NULL)
        y->esq->pai = x;
    y->esq = x;
    y->pai = x->pai;
    x->pai = y;

    return y;
}