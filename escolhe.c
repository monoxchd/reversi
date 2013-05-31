#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _arvoredecisao{ //* Código da árvore de decisão. A árvore possue uma raiz que é um vértice.
	struct _vertice *raiz;	   //Cada vértice possue um estado diferente do tabuleiro, as posições que serão jogadas para cada estado,
} arvoredecisao;			   //e um vetor próximo que compõe os níveis da árvore *\\

typedef struct _vertice{
	char cor;
	char **tabaux;
	int ipos,jpos;
	struct _vertice *proximo;
}vertice; 

// ---------------FUNÇÕES AUXILIARES--------------- //

void preencher_arvore(int n, vertice *aux, int num, char **tabuleiro, char cor){
	int i, j, k;
	int numaux = 0, numjogadas = 0, numiteracao = num;

	for(i = 0; i <= n; i++){
		for(j = 0; j <= n; j++){
			aux->tabaux[i][j] = tabuleiro[i][j];
			if(valida(aux->tabaux, n, i, j, cor) == 0){
				numjogadas++;
			}
		}
	}

	aux->proximo = malloc(numjogadas * sizeof(int));
	for(i = 0; i < n; i++){
		for(j = 0; j <n; j++){
			for(k = 0; j < n; k++){
				aux->proximo[k].tabaux[i][j] = aux->tabaux[i][j];
			}
		}
	}

	
	while(numaux != numjogadas){
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				if(valida(aux->tabaux, n, i, j, cor) == 0){
					if((aux->proximo[numaux].ipos != i) && (aux->proximo[numaux].jpos != j)){
						aux->proximo[numaux].ipos = i;
						aux->proximo[numaux].jpos = j;
						break;
					}
				}
			}
	    }
	    numaux++;
	}
	for(numaux = 0; numaux <=numjogadas; numaux++){
			realiza_jogada(aux->proximo[numaux].tabaux, n, aux->proximo[numaux].ipos, aux->proximo[numaux].jpos, aux->proximo[numaux].cor);
	}

	while(numiteracao == 3){ 
		numiteracao++;
		preencher_arvore(n, &aux->proximo[numaux], numiteracao, aux->tabaux, aux->cor - 1);
	}
}


arvoredecisao *inicializar_arvore(int n, char **tabuleiro, char cor){ //Função para inicializar a árvore e descobre o número de jogadas possíveis para a primeira jogada.//
	int numjogadas = 0, numaux = 0;
	int i, j;
	arvoredecisao *aux;

	//Inicializando a árvore de decisão, e atribuindo os valores do tabuleiro atual para o tabuleiro auxiliar dentro da árvore//
	aux = malloc(sizeof(arvoredecisao));
	aux->raiz->cor = cor;
	aux->raiz->tabaux = malloc(n * sizeof(int *));
	for(i = 0; i <= n; i++){
		aux->raiz->tabaux = malloc(n * sizeof(int));
	}

	//É executado um algoritmo recursivo que preenche a árvore inteira com todas as combinações de jogadas possíveis a partir do estado atual to tabuleiro.
	//Se houver uma maneira melhor de fazer isto, sem ter problemas como memória insuficiente ou estados espelhados, é bom implementar no código.
	preencher_arvore(n, aux->raiz, 0, aux->raiz->tabaux, aux->raiz->cor);

	return aux;
}


void minimaxAlphaBeta(arvoredecisao *arvore, alpha, beta, int *i, int *j){

	alpha = -999999;
	beta = 999999;
	if(arvore->raiz )

}

// ---------------FUNÇÃO PRINCIPAL--------------- //
void escolhe(char **tabuleiro, int n, char cor, int *i, int *j) {
	//Declaração de variáveis//
	int k, m;
	arvoredecisao *arvore;
	//Fim declaração//

	arvore = inicializar_arvore(n, tabuleiro, cor);


}
	

