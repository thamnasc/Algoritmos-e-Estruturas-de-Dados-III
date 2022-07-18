#ifndef libAVL_H_
#define libAVL_H_

typedef struct tNo tNo;

/* Retorna o nó criado 
 */
tNo *criaNo(int chave);

/* Inclui um nó na árvore, retorna a raiz.
 */
tNo *inclui(tNo *no, int chave);

/* Busca pelo nó utilizando a chave,
 * a função é utilizada para "exclui".
 * Retorna a raiz.
 */
tNo *busca(tNo *no, int chave);

/* Exclui o nó, caso não seja NULL
 */
tNo *exclui(tNo *raiz, tNo *no);

/* Travessia em ordem alterada para
 * imprimir a altura também
 */
void emOrdem(tNo *no);

/* Retorna o sucessor, que é o nó mais a esquerda 
 * da sua subárvore à direita.
 */
tNo *sucessor(tNo *no);

/* Procura pela chave mínima à esquerda 
 */
tNo *minimo(tNo *no);

/* Corrige os ponteiros do pai em caso de exclusão.
 */
void transplante(tNo *no, tNo *next);

/* Rotaciona o nó para a direita, elevando
 * seu filho da esquerda.
 */
tNo *rotacaoDir(tNo *x);

/* Rotaciona o nó para a esquerda, elevando
 * seu filho da direita.
 */
tNo *rotacaoEsq(tNo *x);

/* Função para ajustar a AVL, caso a diferença
 * entre as alturas das subárvores direita e esquerda 
 * de um nó sejam -2 (desbalanceada à esquerda) ou 
 * 2 (desbalanceada à direita).
 * O ajuste trata 4 casos.
 */
tNo *ajustaBalanco(tNo *no);

/* Retona a altura da subárvore
 */
int alturaArvore(tNo *no);

/* Retorna a altura do nó atual 
 */
int alturaNo(tNo *no);

/* Remove pela raiz até desalocar todos os nós
 */
void liberaNos(tNo *raiz);

#endif 