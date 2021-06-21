#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hash.h"

int randomInteger (int low, int high){
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}
int teste1(int argc, char *argv[ ]){
	Hash *h = hash_criar(5);	
	TipoElemento *r = (TipoElemento*) malloc(5 * sizeof(TipoElemento));
	r[0].chave = 0;
	r[1].chave = 1;
	r[2].chave = 4;
	r[3].chave = 8;
	r[4].chave = 9;//colisão

	for (int i = 0; i < 5; i++){//insere os elementos
		r[i].dado = randomInteger(10, 4);
		hash_inserir(h, &r[i]);
	}

	for (int i = 0; i< 5; i++){//imprime as chaves e seus respectivos dados
		printf("chave: %d - %d\n", r[i].chave, r[i].dado);
	}
	printf("\n");
	hash_imprimir(h);
	for (int i = 0; i< 5; i++){//imprime o buscar
		int achou = hash_buscar(h, r[i].chave);
		printf("\nChave[%d] -> valor[%d]\n", r[i].chave, achou);
	}
}

int main(int argc, char *argv[ ]){
	int tamanho = atoi(argv[1]);
	srand(time(NULL));
	teste1(argc, argv);
}

