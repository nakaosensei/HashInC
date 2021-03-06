#ifndef _HASH_H_
#define _HASH_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

struct registro {
  long int chave;
  int dado;
};


typedef struct registro TipoElemento;
typedef struct hash Hash;

Hash* hash_criar(long int tamanho);
long int hash_tamanho(Hash *ha);
void  hash_destruir(Hash** enderecoHash);
bool  hash_inserir(Hash *ha, TipoElemento *elemento);
bool  hash_remover(Hash *h, long int chave, TipoElemento **elemento);
bool  hash_cheio(Hash *ha);
bool  hash_getElemento(Hash *ha, long int chave);
bool  hash_vazio(Hash *ha);
void  hash_imprimir(Hash *ha);
int   hash_buscar(Hash *h, long int chave);

#endif