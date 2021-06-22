# Inserção na Hash
```
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
	while(h->itens[pos] != NULL){
		pos = hashPos + (c1 * i) + (c2 * (i * i));
		pos = pos % h->tamanho;
		if(h->itens[pos]->chave == chave) return pos;
		i++;
	}
	return -1;
}
long int buscaSondagemDupla(Hash *h, long int chave){	
	long int hashPos = hash_funcao(h, chave);
	long int hashPos2 = hash_funcao_multiplicacao(h, chave);
	long int pos = hashPos, i = 1;
	if(h->itens[hashPos]->chave==chave) return hashPos;
	if(h->itens[hashPos2]->chave==chave) return hashPos2;
	hashPos++;hashPos2++;	
	while(h->itens[pos] != NULL){
		pos = hashPos + (i * hashPos2);
		pos = pos % h->tamanho;		
		if(h->itens[pos]->chave==chave) return pos;
		i++;
	}
	return -1;
}
```
