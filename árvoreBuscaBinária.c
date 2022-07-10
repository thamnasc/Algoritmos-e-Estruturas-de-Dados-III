#include <stdlib.h>

typedef struct tNo {
    int chave;
    struct tNo *esq, *dir;
} tNo;

tNo *binary(tNo *no, int chave) {
    
    if(no == NULL) {
        return criaNodo(chave);
    }
    
    if(no->chave > chave) 
        return binary(no->esq, chave);
    else if(no->chave < chave)
        return binary(no->dir, chave);
    else
        return no;
}