#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define CLOCKTYPE CLOCK_MONOTONIC

int randomInteger (int low, int high){
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}


int teste1(){
    struct timespec tsi, tsf;
    double elaps_s = 0.0;
    long elaps_ns = 0;
    clock_gettime(CLOCKTYPE, &tsi);	
	Hash *h = hash_criar(size);
	for (long int i = 0; i < size; i++){//insere os elementos		
		hash_inserir(h, &vetor[i]);
	}
	clock_gettime(CLOCKTYPE, &tsf);
	elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
	elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
    printf("Tempo : %lf s", (elaps_s + ((double)elaps_ns) / 1.0e9));

	// for (int i = 0; i < size; i++){//imprime as chaves e seus respectivos dados
	// 	printf("chave: [%d] -> [%d]\n", vetor[i].chave, vetor[i].dado);
	// }
	// printf("\nPrint hash keys: ");
	// hash_imprimir(h);
	// for (int i = 0; i< size; i++){//imprime o buscar
	// 	int achou = hash_buscar(h, vetor[i].chave);
	// 	printf("\nChave[%d] -> valor[%d]\n", vetor[i].chave, achou);
	// }
}

int main(int argc, char *argv[ ]){
	int tamanho = atoi(argv[1]);
	srand(time(NULL));
	teste1();
}
