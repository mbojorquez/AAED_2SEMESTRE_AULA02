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

TDicionario *TDicionario_Inicia();
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c);
int TDicionario_Insere(TDicionario *D, TItem x);
int TDicionario_Retira(TDicionario *D, TChave c);

TDicionario *TDicionario_Inicia(){
    TDicionario *D;
    D=(TDicionario *) malloc(sizeof(TDicionario));
    D->n=0;
    D->max=10;
    D->Item=(TItem *) malloc(D->max * sizeof(TItem));
    return D;
}

//Pesquisa Lineal o sequencial
//Análise de complexidade: O(n)
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c){
    TApontador i;
    for (i=0;i<D->n;i++) {
        if (D->Item[i].Chave == c)
            return i;
    }
    return NIL;
}

int TDicionario_Insere(TDicionario *D, TItem x){
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0;
    if (D->n == D->max) {
        D->max *= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    D->Item[D->n++] = x;
    return 1;
}

void TDicionario_Imprime(TDicionario *D) {
    printf("Dictionary Contents:\n");
    for (int i = 0; i < D->n; i++) {
        printf("Item %d: Chave = %d\n", i + 1, D->Item[i].Chave);
    }
}

void ArrayToDictionary(int array[], int array_size, TDicionario *dic) {
    for (int i = 0; i < array_size; i++) {
        TItem item = { array[i] }; // Cria TItem com elemento de array como chave
        TDicionario_Insere(dic, item); //Insere item no dicionário
    }
}


int main() {
    clock_t start_t, end_t;
    double total_t;
    int i;

    int array_size = sizeof(shared_array) / sizeof(shared_array[0]);

//Random
    initialize_array(shared_array, ARRAY_SIZE);    
    srand((unsigned)time(NULL));
    shuffle_fixed(shared_array, ARRAY_SIZE);
    
    printf("Vector inicial: ");
    printim(shared_array, ARRAY_SIZE);  
    // Inicializa um dicionário
    TDicionario *dic = TDicionario_Inicia();

    // Converte array em dicionário
    ArrayToDictionary(shared_array, array_size, dic);

    int size = TDicionario_Tamanho(dic);   

    int array[]={9,99999};
    int j;
    int array_b_size=0;
    int array_b[2];
    printf("\n>>  Searching for & Delete: [");
    for (int j=0; j<2;j++){
        printf("%d ", array[j]);
    }
    printf("]\n");
    for (j = 0; j < 2; j++) {

    start_t = clock(); 
    //PESQUISA (3 ELEMENTOS)
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

    //Finish Time
    end_t = clock();   
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nTempo: %f\n", total_t  );
    
    free(dic->Item);
    free(dic);

    return 0;
}
