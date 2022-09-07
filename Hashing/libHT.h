#ifndef libHT_H_
#define libHT_H_

typedef struct hashTable {
    int key;
    int deleted;
} hashTable;

/* Registro para guardar chave-tabela.
 * Utiliza para impressão das tabelas.
  */
typedef struct keyInfo {
    int key;
    int table;
} keyInfo;

/* Hashcode da tabela 1. Procura pelo slot para a chave em questão.
 */
int h1( int k );

/* Hashcode da tabela 2. Procura pelo slot para a chave em questão.
 */
int h2( int k );

/* Deleta uma chave na correspondente tabela.
 * Retorna o índice da chave. Retorna -1 se não encontrar.
 */
int delete( int key, hashTable *ht1, hashTable *ht2 );

/* Procura por uma chave nas duas tabelas.
 * Retorna o índice ou -1 caso não encontrar.
 */
int lookup( int key, hashTable *ht1, hashTable *ht2 );

/* Insere uma chave se ainda não estiver em alguma das tabelas.
 * Tenta inserir na primeira, caso o slot esteja vazio. 
 * Caso não esteja, move a chave antiga para a segunda tabela e 
 * então insere na primeira.
 */
int insert( int key, hashTable *ht1, hashTable *ht2 );

/* Função utilizada para varrer as tabelas e procurar por slots que contenham dados.
 * Forma um vetor com os elementos das duas tabelas.
 */
int searchForData( int offset, hashTable *ht, int table, keyInfo *keys );

/* Imprime os dados contidos nas duas tabelas por ordem crescente das chaves.
 */
void printTables( hashTable *ht1, hashTable *ht2 );

/* Inicializa uma tabela com -1 no atributo "key" e 0 no atributo "deleted".
 */
void initializeHash( hashTable *ht );

/* Executa a operação lida pelo stdin. 
 */
void executeOp( hashTable *ht1, hashTable *ht2, char op, int key );

#endif 