#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <ctype.h>

#include "tabela.h"
#include "arvore_floresta.h"
#include "pilha.h"
#include "byte.h"

#define TF 500 

void reconstruirTabela(Tabela **tabela, char arquivo[]){
    FILE * ptr= fopen(arquivo,"rb");

	Dados dado;
	fread(&dado,sizeof(Dados),1,ptr);
	while(!feof(ptr)){
		inserirTabelaDecod(&*tabela, dado);
		fread(&dado,sizeof(Dados),1,ptr);
	}
    ordenarTabelaFrequencia(&*tabela);
	fclose(ptr);
}

void novoNoBin(Arvore **no) {
    *no = (Arvore*) malloc (sizeof(Arvore));
    (*no)->esq = NULL;
    (*no)->dir = NULL;
    (*no)->simbolo = -1;      
    (*no)->frequencia = 0;
}

void reconstruirArvore(Arvore **raiz, Tabela *tabela) {
    int i;
    Arvore *aux;

    if (*raiz == NULL) 
        novoNoBin(&*raiz);

    while (tabela != NULL) {
        aux = *raiz;
        for (i = 0; i < strlen(tabela->dados.codigo); i++) {
            if (tabela->dados.codigo[i] == '0') {
                if (aux->esq == NULL)
                    novoNoBin(&aux->esq);
                aux = aux->esq;
            } else {
                if (aux->dir == NULL) 
                    novoNoBin(&aux->dir);
                aux = aux->dir;
            }
        }
        aux->simbolo = tabela->dados.simbolo;
        aux->frequencia = tabela->dados.frequencia;
        tabela = tabela->prox;
    }
}

void exibeArvore(Arvore *raiz) {
    PilhaArvoreNivel *PN;
    initPilhaArvoreNivel(&PN);
    Arvore *aux = raiz;
    int nivel = 0;

    while (aux != NULL || !isEmptyPilhaArvoreNivel(PN)) {
        while (aux != NULL) {
            pushPilhaArvoreNivel(&PN, aux, nivel);
            aux = aux->dir;
            nivel++;
        }

        popPilhaArvoreNivel(&PN, &aux, &nivel);
        printf("\t%*s(%d)\n", 5 * nivel, "", aux->simbolo);
        aux = aux->esq;
        nivel++;
    }
}

int decodificarBit(Arvore **aux, Arvore *raiz, Tabela *tabela, char bit, char *frase, int posFrase) {
    Tabela *auxTab;
    int len, i;

    if (bit == '0') 
        *aux = (*aux)->esq;
    else  
        *aux = (*aux)->dir;

    if ((*aux)->esq == NULL && (*aux)->dir == NULL) {  
        auxTab = tabela;
        while (auxTab && auxTab->dados.simbolo != (*aux)->simbolo)
            auxTab = auxTab->prox;

        len = strlen(auxTab->dados.palavra);
        for (i = 0; i < len; i++) 
            frase[posFrase++] = auxTab->dados.palavra[i];

        *aux = raiz;  
    }
    return posFrase;
}

void decodificacao(Arvore *raiz, Tabela *tabela) {
    Arvore *aux = raiz;
    Byte byte;
    char frase[TF];
    char codigo[9];
    int i, posFrase = 0;

    frase[0] = '\0';

    FILE *ptr = fopen("fraseCodificada.dat", "rb");

    while (fread(&byte.num, sizeof(char), 1, ptr) == 1) {
        codigo[0] = byte.bi.b0 ? '1' : '0';
        codigo[1] = byte.bi.b1 ? '1' : '0';
        codigo[2] = byte.bi.b2 ? '1' : '0';
        codigo[3] = byte.bi.b3 ? '1' : '0';
        codigo[4] = byte.bi.b4 ? '1' : '0';
        codigo[5] = byte.bi.b5 ? '1' : '0';
        codigo[6] = byte.bi.b6 ? '1' : '0';
        codigo[7] = byte.bi.b7 ? '1' : '0';

        codigo[8] = '\0';

        for (i = 0; i < 8; i++) {
            posFrase = decodificarBit(&aux, raiz, tabela, codigo[i], frase, posFrase);
        }
    }

    if (posFrase > 0 && frase[posFrase - 1] == ' ') 
        posFrase--;

    frase[posFrase] = '\0';

    printf("\n\n\t%s\n\n", frase);
    fclose(ptr);
}

int main(){
	Tabela *tabela = NULL;
	reconstruirTabela(&tabela,"tabela.dat");

	Arvore *raiz = NULL; 
    reconstruirArvore(&raiz,tabela);

	decodificacao(raiz, tabela);
    exibirTabela(tabela);
    exibeArvore(raiz);

    return 0;
}
