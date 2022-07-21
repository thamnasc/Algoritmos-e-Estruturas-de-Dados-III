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

int somaPares(tNo *no) {

    if(no == NULL)
        return 0;
    
    if(no->chave % 2 == 0)
        return somaPares(no->esq) + somaPares(no->dir) + no->chave;
    
    return somaPares(no->esq) + somaPares(no->dir);
}

int main() {

    tNo *raiz = NULL;

    raiz = inclui(raiz, 1);
    raiz = inclui(raiz, 2);
    raiz = inclui(raiz, 4);
    raiz = inclui(raiz, 3);
    raiz = inclui(raiz, 2);

    printf("%d\n",somaPares(raiz));

    return 0;
}