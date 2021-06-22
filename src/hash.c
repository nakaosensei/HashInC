#include "hash.h"

/**************************************
* DADOS
**************************************/

struct hash{
  long int qtde, tamanho;
  TipoElemento **itens;
};

//0 - sondagemLinear
//1 - sondagemQuadratica
//2 - duploHash
int estrategiaConflito = 2;


/**************************************
* FUNÇÕES AUXILIARES
**************************************/
long int hash_funcao(Hash* h, long int chave){
	return chave % h->tamanho;	
}


long int hash_funcao_multiplicacao(Hash* h, long int chave){
	float constanteFracionaria = 0.8897;
	float temp = chave * constanteFracionaria;
	temp = temp - (long int)temp;
	return (long int) (temp*h->tamanho);	
}


long int sondagemLinear(Hash *h, long int hashPos){
	while(h->itens[hashPos] != NULL){
		hashPos = hash_funcao(h, hashPos+1);
	}
	return hashPos;
}


long int sondagemQuadratica(Hash *h, long int hashPos){
	float c1 = 0.4;float c2 = 0.6;long int i = 1;long int pos = hashPos;int tentativa = 0;
	while(h->itens[pos] != NULL){
		pos = hashPos + (c1 * i) + (c2 * (i * i));
		pos = hash_funcao(h, pos);
		if(h->itens[pos] == NULL) return pos;
		i++;
		if(i > 500){
			tentativa++;
			c1+=1;
			c2+=2;
			i = 0;
		}
		if(tentativa == 3){
			return sondagemLinear(h, hashPos);
		}
	}
	return sondagemLinear(h, hashPos);
}


long int duploHash(Hash *h, long int hashPos, long int hashPos2){
	long int i = 1, pos = hashPos;
	while(h->itens[pos] != NULL){
		pos = hashPos + (i * hashPos2);
		pos = hash_funcao(h, pos);
		if(h->itens[pos] == NULL) return pos;
		i++;
		if(i == 500){
			return sondagemLinear(h, hashPos);
		}
	}
	return sondagemLinear(h, hashPos);
}


bool hash_ehValida(Hash* h){
    return (h != NULL? true: false);
}


long int hash_get_next_node(Hash* h, long int chave){
	long int hashPos = hash_funcao(h, chave);
	if(h->itens[hashPos] == NULL) return hashPos;
	if(estrategiaConflito == 0){
		return sondagemLinear(h, hashPos);
	}
	else if(estrategiaConflito == 1){
		return sondagemQuadratica(h, hashPos);
	}
	else if(estrategiaConflito == 2){
		long int hashPos2 = hash_funcao_multiplicacao(h, chave);
		return duploHash(h, hashPos+1, hashPos2+1);
	}	
}


long int buscaSondagemLinear(Hash *h, long int chave){	
	long int pos = hash_funcao(h, chave);
	while(h->itens[pos] != NULL){
		if(h->itens[pos]->chave == chave){
			return pos;
		}else{
			pos = hash_funcao(h, pos+1);
		}
	}
	return -1;
}


long int buscaSondagemQuadratica(Hash *h, long int chave){
	long int hashPos = hash_funcao(h, chave);
	if(h->itens[hashPos]->chave == chave) return hashPos;
	float c1 = 0.4, c2 = 0.6;
	long int pos = hashPos, i = 1;
	int tentativa = 0;
	while(h->itens[pos] != NULL){
		pos = hashPos + (c1 * i) + (c2 * (i * i));
		pos = hash_funcao(h, pos);
		if(h->itens[pos]->chave == chave) return pos;
		i++;
		if(i > 500){
			tentativa++;
			c1+=1;
			c2+=2;
			i = 0;
		}
		if(tentativa == 3){
			return buscaSondagemLinear(h, chave);
		}
	}
	return buscaSondagemLinear(h, chave);
}


long int buscaSondagemDupla(Hash *h, long int chave){	
	long int hashPos = hash_funcao(h, chave);
	long int hashPos2 = hash_funcao_multiplicacao(h, chave);
	long int pos = hashPos, i = 1;
	if(h->itens[hashPos]->chave==chave) return hashPos;
	if(h->itens[hashPos2]->chave==chave) return hashPos2;
	hashPos++;
	hashPos2++;
	while(h->itens[pos] != NULL){
		pos = hashPos + (i * hashPos2);
		pos = hash_funcao(h, pos);		
		if(h->itens[pos]->chave==chave) return pos;
		i++;
		if(i == 500){
			return buscaSondagemLinear(h, chave);
		}
	}
	return buscaSondagemLinear(h, chave);
}
/**************************************
* IMPLEMENTAÇÃO
**************************************/

Hash* hash_criar(long int tamanho){
	Hash *h = (Hash*) malloc(sizeof(Hash)); 
	h->itens = (TipoElemento**) malloc(sizeof(TipoElemento)*tamanho); 
	for (long int i=0; i<tamanho;i++){
		h->itens[i] = NULL;
	}
	h->qtde = 0;
	h->tamanho = tamanho;
	return h;
}

void  hash_destruir(Hash** enderecoHash){
	if (enderecoHash == NULL) return;
	if (!hash_ehValida(*enderecoHash)) return;

	Hash *h = *enderecoHash;
	free(h->itens);
	free(h);
	*enderecoHash = NULL;
}



bool hash_inserir(Hash *h, TipoElemento *elemento){
	long int pos = hash_get_next_node(h, elemento->chave);
	h->itens[pos] = elemento;
	h->qtde++;
	return true;
}

int hash_buscar(Hash *h, long int chave){
	long int hashPos = hash_funcao(h, chave);
	long int pos;	
	if (estrategiaConflito == 0){
		pos = buscaSondagemLinear(h, chave);
	}
	else if(estrategiaConflito == 1){
		pos = buscaSondagemQuadratica(h, chave);
	}
	else if(estrategiaConflito == 2){
		pos = buscaSondagemDupla(h, chave);
	}
	if (pos==-1) return -1;
	return h->itens[pos]->dado;
}

bool hash_remover(Hash *h, long int chave, TipoElemento **elemento){
	long int pos;
	if(estrategiaConflito == 0){
		pos = buscaSondagemLinear(h, chave);
	}
	else if(estrategiaConflito == 1){
		pos = buscaSondagemQuadratica(h, chave);
	}
	else if(estrategiaConflito == 2){
		pos = buscaSondagemDupla(h, chave);
	}
	if(pos==-1) return false;
	*elemento = h->itens[pos];  
	h->itens[pos] = NULL;
	h->qtde--;
	return true;
}

long int hash_tamanho(Hash *ha){
	return ha->qtde;
}

bool hash_cheio(Hash *ha){
	return (ha->qtde == ha->tamanho);
}

bool hash_vazio(Hash *ha){
	if (ha->qtde == 0)
		return true;
	return false;
}

void hash_imprimir(Hash *h){
	printf("[");
	for (long int i = 0; i < h->tamanho-1;i++){
		if(h->itens[i] != NULL){
			printf("%ld, ", h->itens[i]->chave);
		}else{
			printf("NULL, ");
		}
	}
	if(h->itens[h->tamanho-1] != NULL){
		printf("%ld", h->itens[h->tamanho-1]->chave);	
	}else{
		printf("NULL");
	}	
	printf("]\n");
}