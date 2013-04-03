#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"

void desenha_tab(char **tabuleiro, int tamanho_tab) //desenha o tabuleiro na tela
{
	int i, j;

	for (i = 0; i < tamanho_tab; i++) //iteração para desenhar as linhas de divisão das casas, com exceção da última parte
	{
		printf("+"); //começa a imprimir a linha divisória
		for (j = 0; j < (tamanho_tab - 1); j++)
		{
			printf("----"); //imprime o corpo da linha divisória
		}
		printf("---+\n"); //imprime a última parte da linha divisória

		for (j = 0; j < tamanho_tab; j++)	//iteração para desenhar as casas do tabuleiro, com exceção da última parte
		{
			switch(tabuleiro[i][j]){ //verifica o que deve ser preenchido no tabuleiro de acordo com o valor de determinada posição da matriz e imprime o desenho adequado
				case VAZIO:
					printf("|   ");
					break;
				case PRETO:
					printf("| X ");
					break;
				case BRANCO:
					printf("| O ");
					break;
			}
		}
		printf("|\n"); //fecha a sequência de casas e vai para a próxima linha
	}
	printf("+"); //começa a imprimir a última linha
	for (j = 0; j < (tamanho_tab - 1); j++)
	{
		printf("----"); //imprime o corpo da última linha
	}
	printf("---+\n"); //imprime a última parte da linha divisória
}

int main(){
	
	/*variáveis*/

	int i, j;

	char **tabuleiro; //apontador da matriz tabuleiro na memória
	char resposta[1]; //resposta da pergunta inicial (carregar jogo salvo)
	char caminho[200];  //Variável que recebe o caminho do jogo
	
	FILE *jogo; //Ponteiro que guarda arquivos de jogo, sejam eles novos ou velhos
	
	int *tamanho_tab; //tamanho do tabuleiro

	/*comandos*/
	tamanho_tab = malloc(sizeof(int)); //alocação do tamanho do tabuleiro

	while((strcmp(resposta, "s") != 0) && (strcmp(resposta, "n") != 0)){ //o programa pergunta ao jogador se ele deseja carregar um jogo salvo. enquanto o jogador não der uma resposta válida ("s" ou "n"), o programa continua perguntando.
		printf("Deseja carregar um jogo salvo? (s/n)\n");
		gets(resposta);
		printf("%c", resposta);
		if ((strcmp(resposta, "s") != 0) && (strcmp(resposta, "n") != 0))
		{
			printf("OPCAO INVALIDA\n\n");
		}
	}
	
	if (strcmp(resposta, "s") == 0) //se a resposta do jogador for "sim", um jogo salvo num arquivo de texto é carregado.
	{
		//pede ao jogador o arquivo do jogo salvo e verifica se esse arquivo existe. se o arquivo não existir, um novo caminho é pedido.
			printf("Digite o caminho do arquivo\n");
			gets(caminho);
			jogo = fopen(caminho, "r+"); //verificando se o arquivo existe.
			if (!jogo)
			{
				printf("CAMINHO INVALIDO\n");
			}
			fscanf(jogo, "%d", tamanho_tab);
			
		tabuleiro = carrega(jogo, tamanho_tab);
		//carrega
	}
	else{				//senão, começa um novo jogo
		while((*tamanho_tab <= 2) || (*tamanho_tab % 2 == 1)){ //pergunta ao jogador qual é o tamanho do tabuleiro que será utilizado
			printf("Digite o tamanho do tabuleiro (Deve ser par e maior que 2): ");
			scanf("%d", &*tamanho_tab);
			if ((*tamanho_tab <= 2) || (*tamanho_tab % 2 == 1))
			{
				printf("TAMANHO INVALIDO\n\n"); //caso o tabuleiro seja muito pequeno, é exibida uma mensagem de erro e o programa volta a pedir o tamanho do tabuleiro
			}
		}
		printf("\n");
		printf("Digite o caminho, junto com o nome,\n do arquivo onde o jogo ser� guardado: ");
		gets(caminho);
		
		jogo = fopen(caminho, "w+");
		
		for (i = 0; i < *tamanho_tab; i++) //percorre todas as casas do tabuleiro e atribui a todas o valor de VAZIO
		{
			for (j = 0; j < *tamanho_tab; j++)
			{
	            tabuleiro[i][j] = VAZIO; //atribui à casa do tabuleiro na posição i,j o valor VAZIO
			}
		}
	}

	desenha_tab(tabuleiro, *tamanho_tab); //desenha o tabuleiro alocado na memória de acordo com o tamanho definido pelo usuário

	system("PAUSE");

	//Liberação de memória//
	for(i = 0; i < *tamanho_tab; i++){
		free(tabuleiro[i]);
	}
	free(tabuleiro);
	printf("%d", *tamanho_tab);
	fclose(jogo);
    free(tamanho_tab);

	return 0;
}
