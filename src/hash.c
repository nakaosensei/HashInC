#include "hash.h"

#define TAM_INICIAL 100000
#define EST_CONFLITO 2

/**************************************
* DADOS
**************************************/

struct hash{
  int qtde, tamanho;
  TipoElemento **itens;
};


/**************************************
* FUNÇÕES AUXILIARES
**************************************/

/*
int sondagemLinear(Hash *h, int hashPos){	
	for (int i = hashPos+1; i < h->tamanho;i++){
		if(h->itens[i] == NULL)	return i;		
	}	
	return -1;
}*/

int hash_funcao(Hash* h, int chave){
	return chave % h->tamanho;	
}

int hash_funcao_multiplicacao(Hash* h, int chave){
	float constanteFracionaria = 0.8897;
	float temp = chave * constanteFracionaria;
	temp = temp - (int)temp;
	return (int) (temp*h->tamanho);	
}
int sondagemLinear(Hash *h, int hashPos){
	while(h->itens[hashPos] != NULL){
		hashPos = hash_funcao(h, hashPos+1);
	}
	return hashPos;
}

int sondagemQuadratica(Hash *h, int hashPos){	
	int c1=0.4;int c2=0.6;
	for (int i = hashPos; i < h->tamanho;i++){
		int pos = hashPos+(c1*i)+(c2*(i*i));
		if (pos>=h->tamanho){
			pos = pos % h->tamanho;//encaixa dentro do tamanho do vetor
		}		
		if(h->itens[pos] == NULL) return pos;
	}
	return sondagemLinear(h, hashPos);
}

int duploHash(Hash *h, int hashPos, int hashPos2){
	for(int i = 0; i< h->tamanho; i++){
		int pos = hashPos + (i*hashPos2);
		if (pos>=h->tamanho){
			pos = pos % h->tamanho;
		}
		if(h->itens[pos] == NULL) return pos;
	}
	return sondagemLinear(h, hashPos);
}


bool hash_ehValida(Hash* h){
    return (h != NULL? true: false);
}

int hash_get_next_node(Hash* h, int chave, int estrategiaConflito){
	int hashPos=hash_funcao(h, chave);
	if (h->itens[hashPos]==NULL) return hashPos;	
	if (estrategiaConflito==0){
		return sondagemLinear(h,hashPos);
	}else if (estrategiaConflito==1){
		return sondagemQuadratica(h,hashPos);
	}else if(estrategiaConflito==2){
		int hashPos2 = hash_funcao_multiplicacao(h,chave);
		return duploHash(h, hashPos, hashPos2);
	}	
}

int buscaSondagemLinear(Hash *h, int chave){	
	int pos = hash_funcao(h, chave);
	while(h->itens[pos] != NULL){
		if(h->itens[pos]->chave == chave){
			return pos;
		}else{
			pos = hash_funcao(h, pos+1);
		}
	}
	return -1;
}

int buscaSondagemQuadratica(Hash *h, int chave){	
	int hashPos = hash_funcao(h, chave);
	if(h->itens[hashPos]->chave==chave) return hashPos;
	int c1=0.4;int c2=0.6;
	for (int i = hashPos; i < h->tamanho;i++){		
		int pos = hashPos+(c1*i)+(c2*(i*i));
		if (pos>=h->tamanho){
			pos = pos % h->tamanho;//encaixa dentro do tamanho do vetor
		}		
		if(h->itens[pos]->chave==chave) return pos;
	}	

	return buscaSondagemLinear(h, chave);
}

int buscaSondagemDupla(Hash *h, int chave){	
	int hashPos = hash_funcao(h, chave);
	int hashPos2 = hash_funcao_multiplicacao(h, chave);
	if(h->itens[hashPos]->chave==chave) return hashPos;
	for(int i = 0; i< h->tamanho; i++){
		int pos = hashPos + (i*hashPos2);
		if (pos>=h->tamanho){
			pos = pos % h->tamanho;
		}
		if(h->itens[pos]->chave==chave) return pos;
	}
	return buscaSondagemLinear(h, chave);
}
/**************************************
* IMPLEMENTAÇÃO
**************************************/

Hash* hash_criar(int tamanho){
	Hash *h = (Hash*) malloc(sizeof(Hash)); 
	h->itens = (TipoElemento**) malloc(sizeof(TipoElemento)*tamanho); 
	for (int i=0; i<tamanho;i++){
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
	int estrategiaConflito=EST_CONFLITO;//0 = sondagem linear, 1 = sondagem dupla, 2 = duplo hash
	int pos = hash_get_next_node(h, elemento->chave, estrategiaConflito);
	h->itens[pos] = elemento;
	h->qtde++;
	return true;
}

int hash_buscar(Hash *h, int chave){
	int estrategiaConflito=EST_CONFLITO;//0 = sondagem linear, 1 = sondagem dupla, 2 = duplo hash
	int hashPos=hash_funcao(h, chave);
	int pos;	
	if (estrategiaConflito==0){
		pos = buscaSondagemLinear(h,chave);
	}else if (estrategiaConflito==1){
		pos = buscaSondagemQuadratica(h,chave);
	}else if(estrategiaConflito==2){
		pos = buscaSondagemDupla(h,chave);
	}
	if (pos==-1) return -1;
	return h->itens[pos]->dado;
}

bool hash_remover(Hash *h, int chave, TipoElemento **elemento){
	int estrategiaConflito=EST_CONFLITO;//0 = sondagem linear, 1 = sondagem dupla, 2 = duplo hash
	int pos;	
	if (estrategiaConflito==0){
		pos = buscaSondagemLinear(h,chave);
	}else if (estrategiaConflito==1){
		pos = buscaSondagemQuadratica(h,chave);
	}else if(estrategiaConflito==2){
		pos = buscaSondagemDupla(h,chave);
	}
	if (pos==-1) return false;
	*elemento = h->itens[pos];  
	h->itens[pos] = NULL;
	h->qtde--;
	return true;
}

int hash_tamanho(Hash *ha){
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
	for (int i = 0; i < h->tamanho-1;i++){
		if(h->itens[i] != NULL){
			printf("%d, ", h->itens[i]->chave);
		}else{
			printf("NULL, ");
		}
	}
	if(h->itens[h->tamanho-1] != NULL){
		printf("%d", h->itens[h->tamanho-1]->chave);	
	}else{
		printf("NULL");
	}	
	printf("]\n");
}