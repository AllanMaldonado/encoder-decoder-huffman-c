typedef struct arvore {
    int simbolo, frequencia;            
    struct arvore *esq, *dir;   
} ; typedef struct arvore Arvore;

typedef struct floresta {
    Arvore *no;                  
    struct floresta *prox;     
}; typedef struct floresta Floresta;


void novaArvore(Floresta **nova, Arvore *no){
	*nova= (Floresta*) malloc (sizeof(Floresta));
	(*nova)->prox = NULL;
	(*nova)->no = no;
}

void inserirFloresta(Floresta **floresta, Arvore *no){
	Floresta *nova,*aux,*ant;
	novaArvore(&nova,no);
	
	if(*floresta == NULL)
		*floresta = nova;
	else{
		if(no->frequencia <= (*floresta)->no->frequencia){
			nova->prox = *floresta;
			*floresta = nova;	
		}
		else{
			ant = *floresta;
            aux = ant->prox;

			while(aux!=NULL && no->frequencia > aux->no->frequencia){
				ant=aux;
				aux=aux->prox;
			}
			nova->prox=aux;
			ant->prox=nova;
		}
	}
}

void removerFloresta(Floresta **floresta,Arvore **no){
	Floresta *aux= *floresta;
	*floresta = aux->prox;
	*no= aux->no;
	free(aux);
}

void novoNo(Arvore **novo, int frequencia, int simbolo){
	*novo = (Arvore*) malloc(sizeof(Arvore));
	(*novo)->dir = NULL;
    (*novo )->esq = NULL;
	(*novo)->simbolo = simbolo;
	(*novo)->frequencia = frequencia;
}

char isEmptyFloresta(Floresta *floresta){
    return floresta == NULL;
} 

