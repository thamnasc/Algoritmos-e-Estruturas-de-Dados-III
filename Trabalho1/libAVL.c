#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libAVL.h"

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

int alturaArvore(tNo *no) {
    
    int he, hd;

    if(no == NULL)
        return -1;

    he = alturaArvore(no->esq);
    hd = alturaArvore(no->dir);
    if(he > hd)
        return he+1;
    else
        return hd+1;
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

tNo *minimo(tNo *no) {

    if(no->esq == NULL)
        return no;
    else 
        return minimo(no->esq);
}

tNo *sucessor(tNo *no) {
    
    tNo *next = NULL;

    if(no->dir != NULL)
        return minimo(no->dir);
    else {
        next = no->pai;
        while(next != NULL && no == next->dir) {
            no = next;
            next = next->pai;
        }
    }

    return next;
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

tNo *busca(tNo *no, int chave) {
    
    if(no == NULL)
        return NULL;
    
    if(no->chave > chave) 
        return busca(no->esq, chave);
    else if(no->chave < chave)
        return busca(no->dir, chave);
    else
        return no;
}

void transplante(tNo *no, tNo *next) {

    if(no->pai != NULL) {
        if(no->pai->esq == no) 
            no->pai->esq = next;
        else
            no->pai->dir = next;
    }
    if(next != NULL)
        next->pai = no->pai;
}

tNo *ajustaBalanco(tNo *no) {

    /* atribui valores para inicializar que não impactem no cálculo,
     * caso não sejam necessários */
    int altDir, altDirDir = 10, altEsq, altEsqEsq = 10, dif;
    tNo *ajustado = no;

    altDir = alturaArvore(no->dir);
    altEsq = alturaArvore(no->esq);
    dif = altDir - altEsq;   
    
    if((dif == 2) || (dif == -2)) { /* está desbalanceada */
        if(no->dir != NULL)
            altDirDir = alturaArvore(no->dir->dir);
        if(no->esq != NULL)
            altEsqEsq = alturaArvore(no->esq->esq);

        /* caso 1: filho profundamente balanceado */
        if((dif == 2) && (altDirDir == (altEsq + 1))) /* dir desbalanceada */
            ajustado = rotacaoEsq(no);
        else if((dif == -2) & (altEsqEsq == (altDir + 1))) /* esq desbalanceada */
            ajustado = rotacaoDir(no);

        /* caso 2: filho em zig-zag */
        else if((dif == 2) && (altDirDir == altEsq)) { /* dir desbalanceada */
            no->dir = rotacaoDir(no->dir);
            ajustado = rotacaoEsq(no);
        }
        else if((dif == -2) && (altEsqEsq == altDir)) { /* esq desbalanceada */
            no->esq = rotacaoEsq(no->esq);
            ajustado = rotacaoDir(no);
        }
    }

    return ajustado;
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

    return ajustaBalanco(no);
}

tNo *exclui(tNo *raiz, tNo *no) {

    tNo *next, *ajuste, *novaRaiz = raiz; 

    /* medida preventiva */
    if(no == NULL)
        return NULL;

    if(no->esq == NULL) {
        transplante(no, no->dir);

        /* caso de dois nós e quero excluir a raiz */
        if(no->pai == NULL) 
            novaRaiz = no->dir;

        ajuste = no->dir;
        free(no);
    }
    else {
        if(no->dir == NULL) {
            transplante(no, no->esq);

            /* caso de dois nós e quero excluir a raiz */
            if(no->pai == NULL) 
                novaRaiz = no->esq;

            ajuste = no->esq;
            free(no);
        }
        else { 
            next = sucessor(no);
            if(next->pai != no) {
                transplante(next, next->dir);
                next->dir = no->dir;
                next->dir->pai = next;
            }
            transplante(no, next);
            next->esq = no->esq;
            next->esq->pai = next;
            if(no == raiz)
                novaRaiz = next;

            ajuste = next;
            free(no);
        }
    }

    /* corrige o desbalanceamento, caso existir */
    while(ajuste != NULL) {
        no = ajustaBalanco(ajuste);
        if(no->pai == NULL) {
            novaRaiz = no;
            ajuste = NULL;
        }       
        else
            ajuste = ajuste->pai;
    }

    return novaRaiz;
} 

void liberaNos(tNo *raiz) {

    while(raiz != NULL)
        raiz = exclui(raiz, raiz);
}

