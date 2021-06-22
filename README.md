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
```
