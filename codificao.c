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

//@ TABELA:

void insereOuIncrementa(Tabela **tabela, char palavra[]) {
    Tabela *aux = *tabela;
    while (aux != NULL && strcmp(aux->dados.palavra, palavra) != 0)
        aux = aux->prox;

    if (aux != NULL)
        aux->dados.frequencia++;
    else{
        inserirTabela(tabela, palavra);
    }
       
}

void criarTabela(Tabela **tabela, char arquivo[]) {
    char frase[TF], palavra[50];
    int i, TL;
    FILE *ptr = fopen(arquivo, "r");

    if (ptr != NULL) {
        while (fgets(frase, sizeof(frase), ptr) != NULL) {
            i = 0;
            while (frase[i] != '\0' && frase[i] != '\n') {
                TL = 0;

                while (frase[i] != '\0' && frase[i] != '\n' &&
                       frase[i] != ' ' && frase[i] != '.' && frase[i] != ',' &&
                       frase[i] != ';' && frase[i] != ':' && frase[i] != '"' &&
                       frase[i] != '!' && frase[i] != '?' && frase[i] != '-') {
                    palavra[TL++] = tolower(frase[i]);  
                    i++;
                }
 
                palavra[TL] = '\0'; 
                if (TL > 0) {
                    insereOuIncrementa(tabela, palavra);
                } 

                if (frase[i] == ' ') {
                    palavra[0] = ' ';
                    palavra[1] = '\0';
                    insereOuIncrementa(tabela, palavra);
                }

                if (frase[i] != '\0') 
                    i++;   
            }
        }
        fclose(ptr);
    }
}


 

//@ FLORESTA:

void criarFloresta(Floresta **floresta,Tabela *tabela){
    Tabela *aux = tabela;
	Arvore *novo;
	while(aux != NULL){
		novoNo(&novo, aux->dados.frequencia, aux->dados.simbolo);
		inserirFloresta(&*floresta , novo);
		aux = aux->prox;
	}
}

Arvore * arvoreHuffman(Floresta **floresta) {
    Arvore *esq = NULL, *dir = NULL, *no = NULL;

    while (!isEmptyFloresta(*floresta)) {
        removerFloresta(floresta, &esq);

        if (!isEmptyFloresta(*floresta)) {
            removerFloresta(floresta, &dir);

            novoNo(&no, esq->frequencia + dir->frequencia, 0);
            no->esq = esq;
            no->dir = dir;

            inserirFloresta(floresta, no);
        } else {
            no = esq;
        }
    }
    return no;
}

 
//@ PILHA:

void gerarCodigosHuffman(Arvore *raiz, Tabela *tabela) {

    char codigo[50], novoCodigo[50];
    Tabela *auxTabela;

    PilhaArvore *PA;
    PilhaCodigo *PC;
    initPilhaArvore(&PA);
    initPilhaCodigo(&PC);

    pushPilhaArvore(&PA, raiz);
    pushPilhaCodigo(&PC, "");

    while (!isEmptyPilhaArvore(PA)) {
        popPilhaArvore(&PA, &raiz);
        popPilhaCodigo(&PC, codigo);

        if (raiz->esq == NULL && raiz->dir == NULL) {
            auxTabela = tabela;
            while (auxTabela != NULL && auxTabela->dados.simbolo != raiz->simbolo)
                auxTabela = auxTabela->prox;


            if (auxTabela != NULL)
                strcpy(auxTabela->dados.codigo, codigo);
        }

        if (raiz->dir != NULL) {
            pushPilhaArvore(&PA, raiz->dir);
            strcpy(novoCodigo, codigo);
            strcat(novoCodigo, "1");
            pushPilhaCodigo(&PC, novoCodigo);
        }

        if (raiz->esq != NULL) {
            pushPilhaArvore(&PA, raiz->esq);
            strcpy(novoCodigo, codigo);
            strcat(novoCodigo, "0");
            pushPilhaCodigo(&PC, novoCodigo);
        }
    }
}

void gravarTabelaArqBin(Tabela *tabela){
	FILE *ptr = fopen("tabela.dat", "wb");
	Dados dado;
	while (tabela != NULL)
	{
		dado = tabela->dados;
		fwrite(&dado, sizeof(Dados), 1, ptr);
		tabela = tabela->prox;
	}
	fclose(ptr);
}


//@ COFICACAO:


void concatenarCodigos(Tabela *tabela, char frase[], char palavra[], char codigo[]) {
    Tabela *auxTabela;
    int i = 0, TL, resto, qtde;

    while (frase[i] != '\0' && frase[i] != '\n') {
        TL = 0;
        while (frase[i] != '\0' && frase[i] != '\n' &&
               frase[i] != ' ' && frase[i] != '.' && frase[i] != ',' &&
               frase[i] != ';' && frase[i] != ':' && frase[i] != '"' &&
               frase[i] != '!' && frase[i] != '?' && frase[i] != '-') {
            palavra[TL++] = tolower(frase[i]);
            i++;
        }

        palavra[TL] = '\0';
        if (TL > 0) {
            auxTabela = tabela;
            while (auxTabela != NULL && strcmp(palavra, auxTabela->dados.palavra) != 0)
                auxTabela = auxTabela->prox;

            if (auxTabela != NULL)
                strcat(codigo, auxTabela->dados.codigo);
        }
        if (frase[i] == ' ') {
            auxTabela = tabela;
            while (auxTabela != NULL && strcmp(" ", auxTabela->dados.palavra) != 0)
                auxTabela = auxTabela->prox;

            if (auxTabela != NULL)
                strcat(codigo, auxTabela->dados.codigo);
        }

        if (frase[i] != '\0')
            i++;
    }

    resto = strlen(codigo) % 8;
    if (resto != 0) {
        qtde = 8 - resto;
        for (i = 0; i < qtde; i++)
            strcat(codigo, "0");
    }
}


void codificacao(Tabela *tabela, char arquivo[]) {
    
    char frase[TF], palavra[50], codigo[TF] = "";
    int i = 0;

    FILE *ptrCodificar = fopen(arquivo, "r");
    fgets(frase, sizeof(frase), ptrCodificar);
    fclose(ptrCodificar);
    printf("\n\t @ Frase: %s\n",frase);

    concatenarCodigos(tabela, frase, palavra, codigo);
    
    Byte B;
    FILE *ptrCodificada = fopen("fraseCodificada.dat", "wb");
    
     for (i = 0; i < strlen(codigo); i += 8) {
        B.bi.b0 = codigo[i]   - '0';
        B.bi.b1 = codigo[i+1] - '0';
        B.bi.b2 = codigo[i+2] - '0';
        B.bi.b3 = codigo[i+3] - '0';
        B.bi.b4 = codigo[i+4] - '0';
        B.bi.b5 = codigo[i+5] - '0';
        B.bi.b6 = codigo[i+6] - '0';
        B.bi.b7 = codigo[i+7] - '0';
        fwrite(&B, sizeof(char), 1, ptrCodificada);
    }
    

    fclose(ptrCodificada);

    printf("\n\t @ Codificada: ");
    FILE *ptrLerCodificada = fopen("fraseCodificada.dat", "rb");
    Byte b;
	fread(&b.num,sizeof(char),1,ptrLerCodificada);
	while(!feof(ptrLerCodificada)){
		printf("%d",b.bi.b0);
		printf("%d",b.bi.b1);
		printf("%d",b.bi.b2);
		printf("%d",b.bi.b3);
		printf("%d",b.bi.b4);
		printf("%d",b.bi.b5);
		printf("%d",b.bi.b6);
		printf("%d",b.bi.b7);
		fread(&b.num,sizeof(char),1,ptrLerCodificada);
	}
	fclose(ptrLerCodificada);
    printf("\n");
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
        printf("\t%*s(%d, %d)\n", 5 * nivel, "", aux->simbolo, aux->frequencia);
        aux = aux->esq;
        nivel++;
    }
}

int main(void){
    Tabela *tabela = NULL;
    criarTabela(&tabela,"frase.txt");
    ordenarTabelaFrequencia(&tabela);

    Floresta *floresta = NULL;
    criarFloresta(&floresta, tabela);
    Arvore *raiz = arvoreHuffman(&floresta);
    gerarCodigosHuffman(raiz,tabela);
    gravarTabelaArqBin(tabela); 

    printf("\n\n\n");
    codificacao(tabela,"fraseCodificar.txt");
    printf("\n\n\n");
    exibirTabela(tabela);
    printf("\n\n\n");
    exibeArvore(raiz);

    return 0;
}
