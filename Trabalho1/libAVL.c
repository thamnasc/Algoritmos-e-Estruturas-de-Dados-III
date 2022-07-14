#include <stdlib.h>

typedef struct tNo {
    int chave;
    int altura;
    struct tNo *esq, *dir, *pai;
} tNo;

tNo *criaNo(int chave) {
    
    tNo *no = malloc(sizeof(tNo));

    no->chave = chave;
    no->altura = 0;

    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;

    return no;
}

emOrdem(tNo *no) {
    
    if(no == NULL)
        return;

    emOrdem(no->esq);
    printf("%d,%d\n", no->chave,no->altura);
    emOrdem(no->dir);
}

tNo *inclui(tNo *no, int chave) {

    if(no == NULL) 
        return criaNo(chave);
    
    //inclui chave igual à esquerda
    if(no->chave >= chave) {
        no->esq = inclui(no->esq, chave);
        no->esq->pai = no;
        no->esq->altura = no->pai->altura + 1;
    }
    else { //no->chave < chave
        no->dir = inclui(no->dir, chave);
        no->dir->pai = no;
        no->dir->altura = no->pai->altura + 1;
    }
            
    return no;
}

/* Função utilizada para encontrar o sucessor.
 * Entre com no->dir do nó que deseja excluir
 * o sucessor é o nó mais a esquerda da sua
 * subárvore à direita
 */
tNo *minimo(tNo *no) {
    
    if(no->esq == NULL)
        return no;
    else
        return minimo(no->esq);
}

/* TODO: a cada rotação preciso lembrar de
 * verificar a altura e ajustar
 */
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

/* TODO: verificar chaves repetidas */
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

/* se o nó da vez for filho esq, 
 * entrar com filho dir para verificar,
 * caso o nó da vez seja o filho dir, 
 * entrar com o filho esq
 */
/* int balanco(tNo *no, int altura) {

    return abs(no->altura - altura);
} */

/* entra com o pai do nó e verifica
 * a diferença entre a altura de seus filhos
 */
/* int balanco(tNo *pai) {

    if(pai->dir != NULL && pai->esq != NULL)
        return abs(pai->esq->altura - pai->dir->altura);
    else if(pai->dir == NULL)
        return 
} */

/* entra com no->pai->pai se a altura do nó
 * for ao menos 2
 * verifica a altura das duas subárvores
 * retorna a diferença
 */
int contaBalanco(tNo *no) {

    tNo *aux = no;
    int altDir, altEsq;
    altDir = 0;
    altEsq = 0;

    while(aux != NULL) {
        aux = aux->dir;
        altDir++;
    }
    while(no != NULL) {
        no = no->esq;
        altEsq++;
    }

    return abs(altDir - altEsq);
}

/* TODO: a cada deleção dar um jeito de verificar
 * a altura e alterar
 */
tNo *exclui(tNo *no, int chave) {

    tNo *next, *nextsFather;

    /* encontra o sucessor */
    //next = minimo(no->dir);//

    // guardar pai do sucessor para verificar
    // se árvore ficou balanceada depois da deleção
    //verificando de cima para baixo
    //nextsFather = next->pai;//

    // ==================

    if(no->esq == NULL)
        transplante(no, no->dir);
        //nextsFather = next->pai;
        free(no);
    else if(no->dir == NULL)
        transplante(no, no->esq);
        //nextsFather = next->pai;
        free(no);
    else {
        next = minimo(no->dir);
        if(next->pai != no) {
            transplante(no, no->dir);
            //nextsFather = next->pai;
            next->dir = next->dir;
            next->dir->pai = next;
        }
        transplante(no, next);
        //nextsFather = next->pai;
        next->esq = no->esq;
        next->esq->pai = next;
        free(no);
    }
}

void transplante(tNo *no, tNo *next) {

    if(no->pai != NULL) {
        if(no->pai->esq == no)
            no->pai->esq = next;
        else
            no->pai->dir = next;
        if(next != NULL)
            next->pai = no->pai;
    }
}


