#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tNo {
    int chave;
    struct tNo *esq, *dir, *pai;
} tNo;

tNo *criaNo(int chave) {
    
    tNo *no = malloc(sizeof(tNo));

    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;

    return no;
}

int alturaNo(tNo *no) {
    
    if(no == NULL)
        return -1;
    return alturaNo(no->pai) + 1;
}

void emOrdem(tNo *no) {
    
    if(no == NULL)
        return;

    emOrdem(no->esq);
    printf("%d,%d\n", no->chave, alturaNo(no));
    emOrdem(no->dir);
}

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

tNo *inclui(tNo *no, int chave) {

    if(no == NULL) 
        return criaNo(chave);
    
    /* inclui chave igual à esquerda */
    if(no->chave >= chave) {
        no->esq = inclui(no->esq, chave);
        no->esq->pai = no;
    }
    else { /* no->chave < chave */
        no->dir = inclui(no->dir, chave);
        no->dir->pai = no;
    }

    return no;
}

tNo *incluiNaRaiz(tNo *no, int chave) {

    tNo *aux = no, *pai;

/*     if( no == NULL )
        return criaNo(chave);
    
    while( aux != NULL ) {
        pai = aux;
        if( chave <= pai->chave )
            aux = aux->esq;
        if( chave > pai->chave )
            aux = aux->dir;
    }
    aux = criaNo(chave); */
    /*     if( chave <= pai->chave )
        pai->esq = aux;
    else
        pai->dir = aux;
    aux->pai = pai; */
    aux = inclui(no, chave);
    
    while( aux->pai != NULL ) {
        if( aux->pai->esq == aux )
            aux = rotacaoDir(aux->pai);
        else 
            aux = rotacaoEsq(aux->pai);
    }
    return aux;
}

int main() {

    tNo *raiz = NULL;

    raiz = incluiNaRaiz(raiz, 1);
    raiz = incluiNaRaiz(raiz, 2);
    raiz = incluiNaRaiz(raiz, 4);

    emOrdem(raiz);

    //liberaNos(raiz);

    return 0;
}