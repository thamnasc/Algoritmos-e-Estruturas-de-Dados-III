#include <stdio.h>
#include <stdlib.h>
#define m 11

typedef struct hashTable {
    int key;
    int deleted;
} hashTable;

int h1(int k) {
    return k % m;
}

int h2(int k, int i) {
    return floor(m * (k * 0.9 - floor(k * 0.9)));
    /*return floor(m * ((k + i) * 0.9 - floor((k + i) * 0.9)));*/
}

/* TODO: ajustar para ignorar chaves repetidas */
int insert(int key, hashTable ht1, hashTable ht2) {

    int index, i = 0;

    index = h1(key);
    if(ht1[index].key == NULL || ht1[index].deleted) 
        ht1[index] = key;
    else {
        do {
            index = h2(key, i);
            if(ht2[index].key == NULL || ht2[index].deleted) {
                ht2[index].key = key;
                if(ht2[index].deleted)
                    ht2[index].deleted = 0;
                return 
            }
            i++;
        } while ( ( i < m ) && ( ht2[index].key != NULL || ) ); /* sondagem caso ocorra colisão em ht2 */
    
    return NULL; /* não há espaço para alocar outras chaves */
}
        
}

int lookup(int key, hashTable ht1, hashTable ht2) {
    
    int index, i = 0;

    index = h1(key);
    if( ht1[index].key == NULL ) /* chave não existe em nenhuma das tabelas */
        return NULL;
    else if( ht1[index].key == key )
        return index;
    /* se a posição não estiver vazia em ht1 ou se a posição estiver marcada como deletada, procura em ht2 */
    do {
        index = h2(key, i);
        if( ( ht2[index].key == key ) && ( !ht2[index].deleted ) )
            return index;
        i++;
    } while ( ( i < m ) && ( ht2[index].key != NULL ) ); /* sondagem caso ocorra colisão em ht2 */

    return NULL; /* não encontrado em nenhuma tabela */
}

void initializeHash(hashTable ht) {
    
    int i = 0;

    for(i; i < m; i++) {
        ht[i].key = NULL;
        ht[i].deleted = 0;
    }
}

int main() {

    hashTable ht1[m], ht2[m];

    initializeHash(ht1);
    initializeHash(ht2);

    return 0;
}