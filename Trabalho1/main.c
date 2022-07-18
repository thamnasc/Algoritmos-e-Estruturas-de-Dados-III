#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libAVL.h"


tNo *executaOp(tNo *raiz, char op, int key) {

    if(op == 'i')
        raiz = inclui(raiz, key);
    else /* 'r' */
        raiz = exclui(raiz, busca(raiz, key));

    return raiz;  
}

int main() {

    char op;
    int key;
    char *str = NULL;
    size_t len = 0;
    char *number;
    tNo *raiz = NULL;

    /* lê uma linha do stdin até o \n */
    while(getline(&str, &len, stdin) != -1) {
        /* exemplo de entrada: "i 10" */
        op = str[0]; /* pega a operação */
        number = strrchr(str, ' '); /* pega o restante da string depois do espaço */
        key = atoi(number); /* pega o valor inteiro da string e transforma em int */

        raiz = executaOp(raiz, op, key);
    }
    free(str);

    emOrdem(raiz);

    liberaNos(raiz);
    
    return 0;
}