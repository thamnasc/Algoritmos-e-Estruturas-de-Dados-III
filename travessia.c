/* tipos de varredura em uma árvore de grau máximo 2 */
/* a forma de andar em uma árvore é chamado de travessia */

/* preOrdem(raiz, esq, dir)
 * emOrdem(esq, raiz, dir)
 * posOrdem(esq, dir, raiz)
 */

emOrdem(tNo *n) {
    
    if(n == NULL)
        return;

    emOrdem(n->esq);
    printf("%d", n->chave);
    emOrdem(n->dir);
}




 