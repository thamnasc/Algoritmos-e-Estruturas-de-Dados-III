#include <stdlib.h>
#define MAX 500

typedef struct ApontadorNo {
    char *valor;
    struct ApontadorNo ponteiros[26];
} ApontadorNo;

int ord(char *chr);

char *procuraChaveSucessora(ApontadorNo *trie, char *chave) {

    char *aux;
    int ord;

    if(trie->valor == NULL) /* se a letra não existir nesse nível */
        return NULL;

    if((ord = trie->ponteiros[ord(trie->valor)]) < 25) { /* se está dentro do limite do vetor */
        chave[strlen(chave)] = trie->ponteiros[ord+1]->valor; /* adiciona a próxima letra a palavra */
        if((aux = procuraChaveSucessora(trie->ponteiros[ord(trie->valor)+1], chave))) 
            return aux;
        chave[strlen(chave)-1] = '\0'; /* retira a letra caso seja nula */
    }

    if(ord == 25) /* se chegou ao final do vetor e não havia letras */
        if((aux = procuraChaveSucessora(trie->ponteiros[ord(trie->valor)-1], chave))) /* volta um nível --> exemplo cam */
            return aux;

    return NULL;
}

char *retornaChaveSucessora(ApontadorNo *trie, char *chave) {

    char string[MAX], *stringCompleta;
    int tam = strlen(chave), i;

    for(i = 0; i < tam; i++) 
        string[i] = chave[i];
    
    stringCompleta = procuraChaveSucessora(trie->ponteiros[ord(trie->valor)+ 1], &string);
    
    if(stringCompleta != NULL)
        stringCompleta[strlen(stringCompleta)] = '\0'; /* garante \0 no final */

    return stringCompleta; /* NULL para não encontrada ou a chave sucessora */
}