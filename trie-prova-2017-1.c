#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALFABETO 26

typedef struct trie_t {
    char *valor;
    struct trie_t ptrs[ALFABETO];
} trie_t;

int ord(char chr) { // retorna o índice correspondente a letra
                    // exemplo: ord('a') == 0  
    return 97 - chr;
}

// i começa em 0
void imprimePalavras(trie_t *trie, char *input, int i) {

    trie_t *trieAux = trie;

    if(trieAux->valor == NULL) 
       return;
    
    if(i == 0) // encontra o prefixo
        for(i; i < strlen(input); i++)
            trieAux = trieAux->ptrs[ord(input[i])];

    for(int j = 0; j < ALFABETO; j++) { // entra em cada posição possível do alfabeto
        imprimePalavras(trieAux->ptrs[j], input, i);

        if(trieAux->ptrs[ord(input[i])]->valor == NULL) //imprime todas as chaves com o mesmo prefixo
            printf("%s \n", trieAux->valor);
    }
}

int main() {
    
    printf("%d", ord('a'));
    return 0;
}