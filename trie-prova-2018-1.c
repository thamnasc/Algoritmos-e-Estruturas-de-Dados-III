#include <stdlib.h>
typedef struct tNo *ApontadorNo;
typedef struct tNo {
    char *valor;
    ApontadorNo ponteiros[26];
} tNo;

// contador = 0
void tamPrimeiraChave(tNo *trie, int *contador) {

    tNo *trieAux = trie, *trieBtr;
    int abc = 0;
    
    if(*contador == 0) {
        if(trie == NULL) //árvore vazia
            return NULL;
        
        while(abc < 26 && *contador == 0) {
            if(trieAux->ponteiros[abc]->valor != NULL) {
                *contador++; // encontrou prefixo
                trieAux = trieAux->ponteiros[abc];
            }
            abc++;
        }
    }
    
    if(trieAux->valor == NULL)
        return;

    tamPrimeiraChave(trieAux, contador);
    
    

}

// menor inicia em 1
int menorValor(tNo *trie, int menor, int contador) {

    if(trie == NULL)
        return 0;
    
    
    
}