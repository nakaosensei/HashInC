# Inserção na Hash
```
bool hash_inserir(Hash *h, TipoElemento *elemento){
	long int pos = hash_get_next_node(h, elemento->chave);
	h->itens[pos] = elemento;
	h->qtde++;
	return true;
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
long int sondagemLinear(Hash *h, long int hashPos){
	while(h->itens[hashPos] != NULL){
		hashPos = hash_funcao(h, hashPos+1);
	}
	return hashPos;
}
long int sondagemQuadratica(Hash *h, long int hashPos){
	float c1 = 0.4;
	float c2 = 0.6;
	long int i = 1;
	long int pos = hashPos;
	while(h->itens[pos] != NULL){
		int pos = hashPos + (c1 * i) + (c2 * (i * i));
		pos = pos % h->tamanho;
		if(h->itens[pos] == NULL) return pos;
		i++;
	}
	return -1;
}
long int duploHash(Hash *h, long int hashPos, long int hashPos2){
	long int i = 1, pos = hashPos;
	while(h->itens[pos] != NULL){
		pos = hashPos + (i * hashPos2);
		pos = pos % h->tamanho;
		if(h->itens[pos] == NULL) return pos;
		i++;
	}
	return -1;
}
```
