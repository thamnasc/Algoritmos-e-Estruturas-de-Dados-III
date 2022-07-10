#include <stdlib.h>

rotacaoDir(tNo *x) {
    
    tNo *y;

    y = x->pai;
    y->esq = x->dir;
    x->dir->pai = y;
    x->dir = y;
    x->pai = y->pai;
    y->pai = x;
}

rotacaoEsq(tNo *x) {

    tNo *y;

    y = x->dir;
    x->dir = y->esq;
    y->esq->pai = x;
    y->esq = x;
    y->pai = x->pai;
    x->pai = y;
}