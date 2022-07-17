#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("%d,%d\n", no->chave, no->altura);
    emOrdem(no->dir);
}

tNo *inclui(tNo *no, int chave) {

    if(no == NULL) 
        return criaNo(chave);
    
    //inclui chave igual à esquerda
    if(no->chave >= chave) {
        no->esq = inclui(no->esq, chave);
        no->esq->pai = no;
        no->esq->altura = no->altura + 1;
    }
    else { //no->chave < chave
        no->dir = inclui(no->dir, chave);
        no->dir->pai = no;
        no->dir->altura = no->altura + 1;
    }
            
    return no;
}

tNo *minimo(tNo *no) {

    if(no->esq == NULL)
        return no;
    else 
        return minimo(no->esq);
}

/* Função utilizada para encontrar o sucessor.
 * Entre com no->dir do nó que deseja excluir
 * o sucessor é o nó mais a esquerda da sua
 * subárvore à direita
 */
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

/* TODO: a cada rotação preciso lembrar de
 * verificar a altura e ajustar
 */
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

int contaNos(tNo *no) {
    
    if(no == NULL)
        return 0;

    return contaNos(no->esq) + contaNos(no->dir) + 1;
}

/* tNo *exclui(tNo *raiz, tNo *no) {
    
    tNo *novaRaiz = raiz, *next = sucessor(no);

    //exclui folha
    if((no->esq == NULL) && (no->dir == NULL)) {
        if(no->pai->dir == no)
            no->pai->dir = NULL;
        else
            no->pai->esq = NULL;
        free(no);
    }

    //nó com um filho no meio da árvore
     else if((no->esq == NULL || no->dir == NULL)) {
        if(no->esq->pai == no) {
            if(no->esq == NULL) 
                no->pai->esq = no->dir;
            else
                no->pai->esq = no->esq;
            no->pai->esq->pai = no->pai;
        }
        else { //no->dir->pai == no
            if(no->dir->pai = no)
                if(no->esq == NULL)
                    no->pai->dir = no->dir;
                else
                    no->pai->dir = no->esq;
            no->pai->dir->pai = no->pai;
        }
        free(no);
    } 

    else {
        if((next->pai != no))
            next = rotacaoDir(next->pai);
        next = rotacaoEsq(no);
        next->esq = no->esq;
        if(no->esq != NULL)
            next->esq->pai = next;
        if(no == raiz)
            novaRaiz = next;
        free(no);
    }

    return novaRaiz;
} */

/* TODO: a cada deleção dar um jeito de verificar
 * a altura e alterar
 */
tNo *exclui(tNo *raiz, tNo *no) {

    tNo *next, *nextsFather;
    tNo *novaRaiz = raiz; 
    //tNo *no;
    //if((no = busca(raiz, chave)) == NULL)
    //return novaRaiz;

    /* encontra o sucessor */
    //next = minimo(no->dir);//

    // guardar pai do sucessor para verificar
    // se árvore ficou balanceada depois da deleção
    //verificando de cima para baixo
    //nextsFather = next->pai;//

    // ==================

    if(no->esq == NULL) {
        transplante(no, no->dir);
        //nextsFather = next->pai;

        // caso de dois nós e quero excluir a raiz 
        if(no->pai == NULL) 
            novaRaiz = no->dir;
    
        free(no);
    }
    else {
        if(no->dir == NULL) {
            transplante(no, no->esq);
            //nextsFather = next->pai;

            // caso de dois nós e quero excluir a raiz 
            if(no->pai == NULL) 
                novaRaiz = no->esq;

            free(no);
        }
        else { 
    /*         next = sucessor(no);
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
            if(no == raiz)
                novaRaiz = next;
            free(no);  */
            next = sucessor(no);
            transplante(next, next->dir);
            next->esq = no->esq;
            next->dir = no->dir;
            transplante(no, next);
            if(no == raiz)
                novaRaiz = next;
            free(no);
        }
    }

    return novaRaiz;
} 

tNo *executaOp(tNo *raiz, char op, int key) {

    if(op == 'i') {
        if((raiz = inclui(raiz, key)) != NULL) {
            printf("Incluiu!");
        }
    }  
    else /* r */
        if((raiz = exclui(raiz, busca(raiz, key))) != NULL)
            printf("excluiu!");

    return raiz;  
}

int main() {

    char op;
    int key;
    char *str = NULL;
    size_t len = 0;
    char *number;
    int keyArray[1000];
    int i = -1;
    tNo *raiz = NULL;
    tNo *aux = NULL;

    while(getline(&str, &len, stdin) != -1) {
        /* exemplo de entrada: "i 10" */
        printf("%s", str);
        /* pega a operação */
        op = str[0];
        /* pega o restante da string depois do espaço */
        number = strrchr(str, ' ');
        /* pega o valor inteiro da string e transforma em int */
        key = atoi(number);

        if(op != 'r') {
            i++;
            keyArray[i] = key;
        }

        printf("op: %c key: %d\n", op, key);

        raiz = executaOp(raiz, op, key);
    }
    
    free(str);

    
/*     raiz = inclui(raiz, 15);
    raiz = inclui(raiz, 30);
    raiz = inclui(raiz, 6); */
    emOrdem(raiz);
/*     raiz = exclui(raiz, raiz);
    raiz = exclui(raiz, raiz);
    free(raiz); */
/*     for(i; i > 0; i--) {
        //if(contaNos(raiz) > 1)
            //if((aux = busca(raiz, keyArray[j])) != NULL)
        raiz = exclui(raiz, keyArray[i]);
    } */
    while( contaNos(raiz) > 1 ) {
        emOrdem(raiz);
        aux = sucessor(raiz);
        if(raiz->esq !=NULL)
            printf("%d eh esq de %d, ", raiz->esq->chave, raiz->chave);
        else
            printf("NULL eh esq de %d, ", raiz->chave);
        if(raiz->dir !=NULL)
            printf("%d eh dir de %d, ", raiz->dir->chave, raiz->chave);
        else
            printf("NULL eh dir de %d, ", raiz->chave);
        //printf("%d eh sucessor de %d\n", aux->chave, raiz->chave); 
        raiz = exclui(raiz, raiz);
    }
    free(raiz);
/*     raiz = inclui(raiz, 15);
    raiz = inclui(raiz, 6);
    raiz = inclui(raiz, 3);
    printf("%d numero de nos\n", contaNos(raiz));
    
    exclui(raiz, busca(raiz, 6), 6);
    exclui(raiz, busca(raiz, 3), 3);
    free(raiz); */
    // printf("imprime raiz %d\n", raiz->chave);
    //aux = inclui(raiz, 6);
    
    //aux = busca(raiz, 6);
    //free(aux);
    //printf("imprime busca %d", busca(raiz, 15)->altura);
    

    
    //printf(" %d, %d", raiz->esq->chave, raiz->esq->altura);
    //free(raiz->esq);
    //free(raiz);
    
    return 0;
}

