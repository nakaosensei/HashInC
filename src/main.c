#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "inputs/conflito-100000.h"
#define CLOCKTYPE CLOCK_MONOTONIC

int randomInteger (int low, int high){
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}


int teste1(){
    struct timespec tsi, tsf;
    struct timespec tsi2, tsf2;
    double elaps_s = 0.0, elaps_s2 = 0.0;
    long elaps_ns = 0, elaps_ns2 = 0;

    clock_gettime(CLOCKTYPE, &tsi);
	Hash *h = hash_criar(size);
	for (long int i = 0; i < size; i++){//insere os elementos
		hash_inserir(h, &vetor[i]);
	}
	clock_gettime(CLOCKTYPE, &tsf);
	elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
	elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
    printf("Tempo : %lf s\n", (elaps_s + ((double)elaps_ns) / 1.0e9));


    clock_gettime(CLOCKTYPE, &tsi2);
    for (long int i = 0; i < size; i++){//insere os elementos
		int achou = hash_buscar(h, vetor[i].chave);
	}
	clock_gettime(CLOCKTYPE, &tsf2);
	elaps_s2 = difftime(tsf2.tv_sec, tsi2.tv_sec);
	elaps_ns2 = tsf2.tv_nsec - tsi2.tv_nsec;
    printf("Tempo2 : %lf s\n", (elaps_s2 + ((double)elaps_ns2) / 1.0e9));
}

int main(int argc, char *argv[ ]){	
	srand(time(NULL));
	teste1();
}
