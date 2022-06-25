/* API é a interface, que disponibiliza um comportamento */
/* o .h é onde se escreve as interfaces */

#ifndef _LIBAlgIII_t_H
#define _LIBAlgIII_t_H

typedef struct tNo *tNo;

/* para incluir  e excluir, é preciso fazer a busca antes */
/* retorna nó de uma árvore */
tNo *busca(tNo *no, int chave);

/* retorna nó de uma árvore */
/* a chave e o valor podem ser trocados por ptr void, por exemplo */
tNo *inclui(tNo *no, int chave, int valor);

/* retorna nó de uma árvore quando se tem a exclusão física */
/* para excluir logicamente, usa variável "booleana"; 
 * o que está excluído não entra na busca, mas ainda existe */
tNo *exclusao(tNo *no, int chave);

#endif