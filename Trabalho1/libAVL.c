#include <stdlib.h>

typedef struct tNo {
    int chave;
    int altura;
    struct tNo *esq, *dir, *pai;
} tNo;

tNo *criaNo(tNo *pai, int chave) {
    
    tNo *no = malloc(sizeof(tNo));

    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = pai;

    return no;
}

/*TODO: modificar emOrdem para imprimir a altura junto também*/
emOrdem(tNo *no) {
    
    if(no == NULL)
        return;

    emOrdem(no->esq);
    printf("%d,%d\n", no->chave,no->altura);
    emOrdem(no->dir);
}

/*TODO: verificar se o filho é null, guardar pai para poder inserir*/
/* talvez o return criaNodo(chave) na base possa resolver */
/* tentar criar um código que seja genérico para inserção e remoção */
tNo *inclui(tNo *no, tNo *pai, int chave) {
    
    if(no == NULL) 
        return criaNo(pai, chave);
    
    /*inclusão de chaves iguais à esquerda*/
    if(no->chave >= chave) 
        return inclui(no->esq, no, chave);
    else if(no->chave < chave)
        return inclui(no->dir, no, chave);
}

/*protótipo de inclui com backtracing*/
/* tNo *inclui(tNo *no, int chave) {
    
    tNo *auxNo;

    if(no == NULL) 
        return NULL;
    
    //inclusão de chaves iguais à esquerda
    if(no->chave >= chave) 
        if(auxNo = inclui(no->esq, chave) == NULL)
            return criaNo(no, chave);
    else if(no->chave < chave)
        if(auxNo = inclui(no->dir, chave) == NULL)
            return criaNo(no, chave);
    return auxNo;
} */

/* função utilizada para encontrar o sucessor
 * entre com no->dir do nó que deseja excluir
 * o sucessor é o nó mais a esquerda da subárvore
 * à direita
 */
tNo *minimo(tNo *no) {
    
    if(no->esq == NULL)
        return no;
    else
        return minimo(no->esq);
}

/* a cada rotação preciso lembrar de
 * verificar a altura e ajustar
 */
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

/* a cada deleção dar um jeito de verificar
 * a altura e alterar
 */
tNo *exclui(tNo *no, int chave) {

    tNo *next;

    /* encontra o sucessor */
    next = minimo(no->dir);

    // guardar pai do sucessor para verificar
    // se árvore ficou balanceada depois da deleção
    //verificando de cima para baixo


}


