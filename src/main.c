#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "inputs/aleatorio-100.h"

int randomInteger (int low, int high){
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}


int teste1(){
	Hash *h = hash_criar(size);
	for (int i = 0; i < size; i++){//insere os elementos		
		hash_inserir(h, &vetor[i]);
	}
	for (int i = 0; i < size; i++){//imprime as chaves e seus respectivos dados
		printf("chave: [%d] -> [%d]\n", vetor[i].chave, vetor[i].dado);
	}
	printf("\nPrint hash keys: ");
	hash_imprimir(h);
	for (int i = 0; i< size; i++){//imprime o buscar
		int achou = hash_buscar(h, vetor[i].chave);
		printf("\nChave[%d] -> valor[%d]\n", vetor[i].chave, achou);
	}
}

int main(int argc, char *argv[ ]){
	int tamanho = atoi(argv[1]);
	srand(time(NULL));
	teste1();
}
