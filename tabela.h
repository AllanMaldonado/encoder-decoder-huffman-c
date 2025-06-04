typedef struct dados {
    int simbolo, frequencia;                
    char palavra[50], codigo[50];    
}; typedef struct dados Dados;

typedef struct tabela {
    Dados dados; 
    struct tabela *prox;    
} ; typedef struct tabela Tabela;

void NovoDado(Dados *dado, char palavra[]) {
    dado->simbolo = 0;
    strcpy(dado->palavra, palavra);
    dado->frequencia = 1;
    dado->codigo[0] = '\0'; 
}

void NovaTabela(Tabela **novo, char palavra[]) {
    *novo = (Tabela *)malloc(sizeof(Tabela));
    NovoDado(&(*novo)->dados, palavra);   
    (*novo)->prox = NULL;
}

void inserirTabela(Tabela **tabela, char palavra[]){
	Tabela *aux, *nova;
    NovaTabela(&nova,palavra); 
    aux=*tabela;
    if(aux == NULL)
		*tabela = nova;
	else{
		while(aux->prox!=NULL)
			aux = aux->prox;
		aux->prox = nova;
	}  
}

void inserirTabelaDecod(Tabela **tabela, Dados dado) {
    Tabela *aux, *nova = (Tabela*) malloc(sizeof(Tabela));
    nova->dados = dado;
    nova->prox = NULL;

    if (*tabela == NULL) {
        *tabela = nova;
    } else {
        aux = *tabela;
        while (aux->prox != NULL) 
            aux = aux->prox;
        aux->prox = nova;
    }
}




void exibirTabela(Tabela *tabela) {
    Tabela *aux = tabela;

    printf("\t-------------------------------------------------------------\n");
    printf("\t%-10s | %-20s | %-10s | %-20s\n", "SIMBOLO", "PALAVRA", "FREQUENCIA", "CODIGO");
    printf("\t-------------------------------------------------------------\n");

    while (aux != NULL) {
        if (strcmp(aux->dados.palavra, " ") == 0)
            printf("\t%-10d | %-20s | %-10d | %-20s\n", aux->dados.simbolo, "[ ]", aux->dados.frequencia, aux->dados.codigo);
        else
            printf("\t%-10d | %-20s | %-10d | %-20s\n", aux->dados.simbolo, aux->dados.palavra, aux->dados.frequencia, aux->dados.codigo);

        aux = aux->prox;
    }
    printf("\t-------------------------------------------------------------\n");
}

void ordenarTabelaFrequencia(Tabela **tabela) {
    Tabela *tabelaOrdenada = NULL,  *prox, *atual, *ant;

    while (*tabela != NULL) {
        prox = (*tabela)->prox;
        atual = tabelaOrdenada;
        ant = NULL; 

        while (atual != NULL && atual->dados.frequencia >= (*tabela)->dados.frequencia) {
            ant = atual;
            atual = atual->prox;
        }
        
        if (ant == NULL) {
            (*tabela)->prox = tabelaOrdenada;
            tabelaOrdenada = *tabela;
        } 
        else {
            (*tabela)->prox = atual;
            ant->prox = *tabela;
        }
        *tabela = prox;
    }

    int simbolo = 0;
    atual = tabelaOrdenada;
    while (atual != NULL) {
        atual->dados.simbolo = simbolo++;
        atual = atual->prox;
    }

    *tabela = tabelaOrdenada;
}
