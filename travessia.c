/* tipos de varredura em uma árvore de grau máximo 2 */
/* a forma de andar em uma árvore é chamado de travessia */

/* preOrdem(raiz, esq, dir)
 * emOrdem(esq, raiz, dir)
 * posOrdem(esq, dir, raiz)
 */

typedef struct no_t {
    struct tNo *esq;
    struct tNo *dir;
    char chave;
    int valor;
} no_t;

preOrdem(no_t *n) {
    
    if(n == NULL)
        return;

    printf("%d", n->chave);
    preOrdem(n->esq);
    preOrdem(n->dir);
}

emOrdem(no_t *n) {
    
    if(n == NULL)
        return;

    emOrdem(n->esq);
    printf("%d", n->chave);
    emOrdem(n->dir);
}

posOrdem(no_t *n) {
    
    if(n == NULL)
        return;

    posOrdem(n->esq);
    posOrdem(n->dir);
    printf("%d", n->chave);
}


 