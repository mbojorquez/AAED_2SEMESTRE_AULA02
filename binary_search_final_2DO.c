#include <stdio.h>
#include <stdlib.h>
#define NIL -1
#include "shared_array.h"
#include "initialize_array.c"

typedef int TChave;
typedef struct {
    TChave Chave;
    /* data */
} TItem;

typedef int TApontador;

typedef struct {
    TItem *Item;
    int n, max;

} TDicionario;

int TDicionario_Tamanho(TDicionario *D); // Função para obter o tamanho do dicionário
int TDicionario_Tamanho(TDicionario *D) {
    return D->n;
}

TDicionario *TDicionario_Inicia(){
    TDicionario *D;
    D=(TDicionario *) malloc(sizeof(TDicionario));
    D->n=0;
    D->max=10;
    D->Item=(TItem *) malloc(D->max * sizeof(TItem));
    return D;
}

//Pesquisa iterativa
//Análise de complexidade: O(logn)
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c) {
    TApontador meio, esq, dir;
    esq = 0;
    dir = D->n - 1;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        if (c > D->Item[meio].Chave) {
            esq = meio + 1;
        } else if (c < D->Item[meio].Chave) {
            dir = meio - 1;
        } else {
            return meio;
        }
    }
    return NIL;
}

//Insercao
int TDicionario_Insere(TDicionario *D, TItem x) {
    TApontador i;
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0;

    if (D->n == D->max) {
        D->max *= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    i = D->n - 1;
    while ((i >= 0) && (x.Chave < D->Item[i].Chave)) {
        D->Item[i + 1] = D->Item[i];
        i--;
    }
    D->Item[i + 1] = x;
    D->n++;
    return 1;
}


void TDicionario_Imprime(TDicionario *D) {
    printf("Dictionary Contents:\n");
    for (int i = 0; i < D->n; i++) {
        printf("Item %d: Chave = %d\n", i + 1, D->Item[i].Chave);
    }
}

void PrintDictionaryAsArray(TDicionario *D) {
    printf("[");
    for (int i = 0; i < D->n; i++) {
        printf("%d", D->Item[i].Chave);
        if (i < D->n - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void ArrayToDictionary(int array[], int array_size, TDicionario *dic) {
    for (int i = 0; i < array_size; i++) {
        TItem item = { array[i] }; // Cria TItem com elemento de vetor como chave
        TDicionario_Insere(dic, item); // Inserir item no dicionário
    }
}

int TDicionario_Size(TDicionario *D) {
    return D->n;
}

int main() {
    clock_t start_t, end_t;
    double total_t;
    int i;
    int array_size = sizeof(shared_array) / sizeof(shared_array[0]);

//RANDOM
    initialize_array(shared_array, ARRAY_SIZE);    
    srand((unsigned)time(NULL));
    shuffle_fixed(shared_array, ARRAY_SIZE);

    printf("Vector inicial: ");
    printim(shared_array, ARRAY_SIZE);  
     
    // Inicializar um dicionário
    TDicionario *dic = TDicionario_Inicia();
    // Converter vetor em dicionário
    ArrayToDictionary(shared_array, array_size, dic);

    //INSERCAO (2 ELEMENTOS)
    TItem item1 = {ARRAY_SIZE}; 
    TItem item2 = {ARRAY_SIZE+1};
    int size = TDicionario_Tamanho(dic);
    printf("\nTotal de elementos %d\n", size);
   
    int array[]={9,99999};
    int j;
    int array_b_size=0;
    int array_b[2];
    printf("\n>>  Searching for & deleting: [");
    for (int j=0; j<2;j++){
        printf("%d ", array[j]);
    }
    printf("]\n");
    for (j = 0; j < 2; j++) {

    start_t = clock(); 
    //PESQUISA
        TChave key_to_search = array[j];
        TApontador result = TDicionario_Pesquisa(dic, key_to_search);
        if (result != NIL) {
            printf("Item com chave %d encontrado.\n", key_to_search);
            array_b[array_b_size]=key_to_search;
            array_b_size++;
        } else {
            printf("Item com chave %d não encontrado.\n", key_to_search);
        }
    }

    end_t = clock();   
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nTempo %f\n", total_t  );
    
    //Finish Time
    free(dic->Item);
    free(dic);
    return 0;
}
