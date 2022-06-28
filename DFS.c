#include <stdlib.h>

/* depth-first search 
 * busca em profundidade
 * utilizando backtracking
 */

typedef struct tNo {
    struct tNo *esq;
    struct tNo *dir;
    char chave;
    int valor;
} tNo;

*tNo DFS(tNo *n, int x) {
    
    tNo *noAnalisado;

    /* verifica se é folha */
    if(n == NULL)
        return NULL;
    if(n->chave == x)
        return n;

    /* filho da esquerda */
    if(noAnalisado = DFS(n->esq, x) != NULL)
        return noAnalisado;
    /* filho da direita */
    if(noAnalisado = DFS(n->dir, x) != NULL)
        return noAnalisado;

    return NULL; /* nó pai */ 
}