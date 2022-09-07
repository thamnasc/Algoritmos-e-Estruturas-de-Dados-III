#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define m 11

typedef struct hashTable {
    int key;
    int deleted;
} hashTable;

typedef struct keyArray {
    int key;
    int table;
} keyInfo;

int h1( int k ) {
    return k % m;
}

int h2( int k ) {
    return floor( m * ( k * 0.9 - floor( k * 0.9 ) ) );
}

int delete( int key, hashTable *ht1, hashTable *ht2 ) {
    
    int index = h1( key );

    if( index != -1 ) { /* se encontrou o elemento, deleta */
        if( ht1[index].key == key ) 
            ht1[index].deleted = 1;
        else {
            index = h2( key );
            ht2[index].deleted = 1;
        }
    }

    return index;
}

int lookup( int key, hashTable *ht1, hashTable *ht2 ) {
    
    int index;

    index = h1( key );
    if( ht1[index].key == -1 ) /* chave não existe em nenhuma das tabelas */
        return -1;
    else if( ( ht1[index].key == key ) && ( !ht1[index].deleted ) )
        return index;
    /* se a posição não estiver vazia em ht1 ou se a posição estiver marcada como deletada, procura em ht2 */
    index = h2( key );
    if( ( ht2[index].key == key ) && ( !ht2[index].deleted ) )
        return index;

    return -1; /* não encontrado em nenhuma tabela */
}

int insert( int key, hashTable *ht1, hashTable *ht2 ) {

    int index, oldKey, oldKeyIndex;

    index = lookup( key, ht1, ht2 ); /* procura se a chave já existe */
    if( index == -1 ) { /* apenas se a chave não existir tenta inserir */
        index = h1( key );
        if( ht1[index].key == -1 || ht1[index].deleted ) { /* insere na primeira tabela se estiver vazia */
            ht1[index].key = key;
            ht1[index].deleted = 0;
        }
        else { /* em caso de colisão, insere a chave antiga na segunda tabela e a recente na primeira */
            oldKey = ht1[index].key; 
            ht1[index].key = key; 
            oldKeyIndex = h2( oldKey );
            ht2[oldKeyIndex].key = oldKey;
            ht2[oldKeyIndex].deleted = 0; 
        }
    }
    return index;
}

int searchForData( int offset, hashTable *ht, int table, keyInfo *keys ) {

    int slot = offset; /* controle do índice do vetor */
   
    for( int i = 0; i < m ; i++ ) {
        if( ( !ht[i].deleted ) && ( ht[i].key != -1 ) ) {
            keys[slot].key = ht[i].key;
            keys[slot].table = table;
            slot++;
        }
    }

    return slot; /* retorna o tamanho atual do vetor */ 
}

void printTables( hashTable *ht1, hashTable *ht2 ) {

    keyInfo keys[m*2], min;
    int size = 0, i, j, minIndex, index;

    size = searchForData( size, ht1, 1, keys );
    size = searchForData( size, ht2, 2, keys );

    if( size > 0 ) {
        while( size > 0 ) {
            min = keys[0];
            for( i = 0; i < size; i++ ) /* procura pelo menor elemento */
                if( min.key > keys[i].key ) {
                    min = keys[i];
                    minIndex = i;
                }
            if( min.table == 1 )
                index = h1( min.key );
            else
                index = h2( min.key ); 
            printf( "%d,T%d,%d\n", min.key, min.table, index );
            for( j = minIndex; j < ( size - 1 ); j++ ) /* retira o elemento que acabou de ser impresso */
                keys[j] = keys[j+1];
            size--;
        }
    }
}

void initializeHash( hashTable *ht ) {

    for( int i = 0; i < m; i++ ) {
        ht[i].key = -1;
        ht[i].deleted = 0;
    }
}

void executeOp( hashTable *ht1, hashTable *ht2, char op, int key ) {

    if( op == 'i' )
        insert( key, ht1, ht2 );
    else /* op == 'r' */
        delete( key, ht1, ht2 );
}