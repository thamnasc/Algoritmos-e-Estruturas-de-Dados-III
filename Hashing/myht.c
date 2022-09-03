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
} keyArray;

int h1( int k ) {
    return k % m;
}

int h2( int k ) {
    return floor( m * ( k * 0.9 - floor( k * 0.9 ) ) );
}

void delete( int key, hashTable *ht1, hashTable *ht2 ) {
    
    int index;

    index = h1( key );

    if( ht1[index].key == key )
        ht1[index].deleted = 1;
    else {
        index = h2( key );
        ht2[index].deleted = 1;
    }
}


int lookup( int key, hashTable *ht1, hashTable *ht2 ) {
    
    int index;

    index = h1( key );
    if( ht1[index].key == -1 ) /* chave não existe em nenhuma das tabelas */
        return -1;
    else if( ( ht1[index].key == key ) && ( !ht1[index].deleted ))
        return index;
    /* se a posição não estiver vazia em ht1 ou se a posição estiver marcada como deletada, procura em ht2 */
    index = h2( key );
    if( ( ht2[index].key == key ) && ( !ht2[index].deleted ) )
        return index;

    return -1; /* não encontrado em nenhuma tabela */
}

int insert( int key, hashTable *ht1, hashTable *ht2 ) {

    int index, auxKey;

    index = lookup( key, ht1, ht2 ); /* procura se a chave já existe */
    if( index == -1 ) { /* apenas se a chave não existir tenta inserir */
        index = h1( key );
        if( ht1[index].key == -1 || ht1[index].deleted ) 
            ht1[index].key = key;
        else { /* em caso de colisão */
            auxKey = ht1[index].key; /* salva chave de ht1 para sobrescrever pela chave mais recente */
            ht1[index].key = key; 
            index = h2( auxKey );
            ht2[index].key = auxKey; /* salva chave antiga em ht2 */
    }
    //return index; /* retorna o índice da chave já existente */
    return 1;
}

int sweepTable( int offset, hashTable *ht, int table, keyArray *keys ) {

    int tam = offset;

    for( int i = offset; i < ( m+offset ); i++ ) {
        if( ( !ht[i].deleted ) && ( ht[i].key != -1 ) ) {
            keys[i].key = ht[i].key;
            keys[i].table = table;
            tam++;
        }
    }

    return tam;
}

void printTables( hashTable *ht1, hashTable *ht2 ) {

    keyArray keys[m*2], smaller;
    int tam = 0, j = 0, index;

    tam = sweepTable( tam, ht1, 1, keys );
    tam = sweepTable( tam, ht2, 2, keys );

    if( tam > 0 ) {
        while( tam > 0 ) {
            smaller = keys[0];
            for( j; j < tam; j++ ) {
                if( smaller.key > keys[j].key )
                    smaller.key = keys[j].key;
            }
            if( smaller.table == 1 )
                index = h1( smaller.key );
            else
                index = h2( smaller.key ); 
            printf( "%d,T%d,%d", smaller.key, smaller.table, index );
            for( j; j < ( tam - 1 ); j++ ) 
                keys[j] = keys[j+1];
            j = 0;
            tam--;
        }
    }
}

void initializeHash(hashTable *ht) {

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

int main() {

    hashTable ht1[m], ht2[m];
    int key;
    char op, *str = NULL, *number;
    size_t len = 0;

    initializeHash( ht1 );
    initializeHash( ht2 );

    /* lê uma linha do stdin até o \n */
    while( getline( &str, &len, stdin ) != -1 ) {
        /* exemplo de entrada: "i 10" */
        op = str[0]; /* pega a operação */
        number = strrchr( str, ' ' ); /* pega o restante da string depois do espaço */
        key = atoi (number ); /* pega o valor inteiro da string e transforma em int */

        executeOp(ht1, ht2, op, key);
    }
    free(str);

    printTables( ht1, ht2 );

    return 0;
}