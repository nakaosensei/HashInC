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
	
	for (int i =0; i< 5; i++){
		TipoElemento *r = (TipoElemento*) malloc(sizeof(TipoElemento));	
		r->chave = i;
		hash_inserir(h, r);
	}
	hash_imprimir(h);
	TipoElemento *r1 = NULL;
	hash_remover(h, 5, &r1);
	hash_imprimir(h);
	hash_remover(h, 5, &r1);
	hash_imprimir(h);
	hash_remover(h, 5, &r1);
	hash_imprimir(h);
	hash_remover(h, 4, &r1);
	hash_imprimir(h);
	hash_remover(h, 4, &r1);
	hash_imprimir(h);
	hash_destruir(&h);
}

int main(int argc, char *argv[ ]){
	int tamanho = atoi(argv[1]);
	Hash *h = hash_criar(tamanho);

	while (!hash_cheio(h)){
		TipoElemento *r = (TipoElemento*) malloc(sizeof(TipoElemento));	
		r->chave = randomInteger(0,tamanho);
		r->dado = r->chave;
		if (!hash_inserir(h, r)){
			free(r);
		}
		
	}
	printf("%d\n", hash_tamanho(h));
	
	while (!hash_vazio(h)){

		TipoElemento *r = NULL;
			
		if (hash_remover(h, randomInteger(0,tamanho), &r)){
			free(r);
			r = NULL;
		}
		
	}
	printf("%d\n", hash_tamanho(h));
	hash_destruir(&h);
}

