#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libHT.h"
#define m 11

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
        key = atoi ( number ); /* pega o valor inteiro da string e transforma em int */

        executeOp( ht1, ht2, op, key );
    }
    free( str );

    printTables( ht1, ht2 );

    return 0;
}