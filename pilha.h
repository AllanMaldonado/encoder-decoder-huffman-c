struct pilhaArvore{
	Arvore *no;
	struct pilhaArvore *prox;
}; typedef struct pilhaArvore PilhaArvore;

struct pilhaCodigo{
	char codigo[50];
	struct pilhaCodigo *prox;
}; typedef struct pilhaCodigo PilhaCodigo;

struct pilhaArvoreNivel {
    Arvore *no;
    int nivel;
    struct pilhaArvoreNivel *prox;
}; typedef struct pilhaArvoreNivel  PilhaArvoreNivel;


// @ Arvore
void initPilhaArvore(PilhaArvore **PA){
	*PA = NULL;
}

void pushPilhaArvore(PilhaArvore **PA, Arvore *no){
	PilhaArvore *novo = (PilhaArvore*)malloc(sizeof(PilhaArvore));
	novo->no = no;
	novo->prox = *PA;
	*PA = novo;
}

void popPilhaArvore(PilhaArvore **PA, Arvore **no){
	PilhaArvore *aux = *PA;
	*no = (*PA)->no;
	*PA = (*PA)->prox;
	free(aux);
}

char isEmptyPilhaArvore(PilhaArvore *PA){
	return PA == NULL;
}


// @ Codigo
void initPilhaCodigo(PilhaCodigo **PC){
	*PC = NULL;
}

void pushPilhaCodigo(PilhaCodigo **PC, char codigo[]){
	PilhaCodigo *novo = (PilhaCodigo*)malloc(sizeof(PilhaCodigo));
	strcpy(novo->codigo, codigo);
	novo->prox = *PC;
	*PC = novo;
}

void popPilhaCodigo(PilhaCodigo **PC, char *codigo){
	PilhaCodigo *aux = *PC;
	strcpy(codigo,(*PC)->codigo);
	*PC = (*PC)->prox;
	free(aux);
}

// @ Arvore Nivel
void initPilhaArvoreNivel(PilhaArvoreNivel **PN) {
    *PN = NULL;
}

void pushPilhaArvoreNivel(PilhaArvoreNivel **PN, Arvore *no, int nivel) {
    PilhaArvoreNivel *novo = (PilhaArvoreNivel*)malloc(sizeof(PilhaArvoreNivel));
    novo->no = no;
    novo->nivel = nivel;
    novo->prox = *PN;
    *PN = novo;
}

void popPilhaArvoreNivel(PilhaArvoreNivel **PN, Arvore **no, int *nivel) {
    PilhaArvoreNivel *aux = *PN;
    *no = aux->no;
    *nivel = aux->nivel;
    *PN = aux->prox;
    free(aux);
}

char isEmptyPilhaArvoreNivel(PilhaArvoreNivel *PN) {
    return PN == NULL;
}


