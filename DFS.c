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

*tNo DFS(tNo *no, int x) {
    
    tNo *noAnalisado;

    /* verifica se é folha */
    if(no == NULL)
        return NULL;
    if(no->chave == x)
        return no;

    /* filho da esquerda */
    if(noAnalisado = DFS(no->esq, x) != NULL)
        return noAnalisado;
    /* filho da direita */
    if(noAnalisado = DFS(no->dir, x) != NULL)
        return noAnalisado;

    return NULL; /* nó raiz da subárvore não é a chave buscada*/ 
}