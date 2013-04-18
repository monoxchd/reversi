#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"

void resultado_jogo(int *tamanho_tab, char **tabuleiro){
	int i, j; //Vari�veis de itera��o//
	int pecas_branco = 0; //Contador de pe�as brancas//
	int pecas_preto = 0; //Contador de pe�as pretas//

	for(i = 0; i < tamanho_tab; i++){ //Loop para contar a quantidade de pe�as de cada jogador//
		for(j = 0; j < tamanho_tab; j++){
			if(tabuleiro[i][j] == PRETO){
				pecas_preto++;
			}
			else if(tabuleiro[i][j] == BRANCO){
				pecas_branco++;
			}
		}
	}

	printf("Pe�as do jogador branco: %d \n", pecas_branco); //Mostra a quantidade de pe�as do jogador branco.//
	printf("Pe�as do jogador preto: %d \n", pecas_preto);	//Mostra a quantidade de pe�as do jogador preto.//
	printf("\n");
	if(pecas_branco >  pecas_preto){ 			//Condi��es que definem quem ganhou. Se algum jogador tiver mais pe�as do que o outro, ele � declarado vencendor.//
		printf("O jogador BRANCO ganhou!\n");
	}
	else if(pecas_preto > pecas_branco){
		printf("O jogador PRETO ganhou!\n");
	}
	else if(pecas_branco == pecas_preto){	//Se o n�mero de pe�as for igual, ocorreu um empate.//
		printf("Empate!\n");
	}


}

void salvar_jogo(int *tamanho_tab, char **tab, char *caminho){
	int i, j; //Vari�veis de itera��o//
	FILE *aux; //Vari�vel auxiliar para criar o arquivo e salv�-lo//

	aux = fopen(caminho, "w+");
	if(!aux){ //Se n�o for poss�vel criar o arquivo, � mostrado uma mensagem de erro.//
		printf("ERRO: O caminho � inv�lido ou um arquivo n�o pode ser criado neste diret�rio. \n");
		fclose(aux);
		return;
	}
	else{ //Sen�o, � salvo o jogo.//
		printf("Arquivo criado com sucesso, salvando...\n");
		fprintf(aux, "%d", tamanho_tab);
		fprintf(aux, "\n");
		for(i = 0; i < *tamanho_tab; i++){
			for(j = 0; j < *tamanho_tab; j++){
				fprintf(aux, "%d", tab[i][j]);
			}
			fprintf(aux, "\n");
		}
		printf("Jogo salvo com sucesso.\n");
	}
	fclose(aux); //Depois de salvo, � fechado o arquivo.//
	return;
}

void desenha_tab(char **tabuleiro, int tamanho_tab) //desenha o tabuleiro na tela
{
	int i, j;

	for (i = 0; i < tamanho_tab; i++) //itera��o para desenhar as linhas de divis�o das casas, com exce��o da �ltima parte
	{
		printf("+"); //come�a a imprimir a linha divis�ria
		for (j = 0; j < (tamanho_tab - 1); j++)
		{
			printf("----"); //imprime o corpo da linha divis�ria
		}
		printf("---+\n"); //imprime a �ltima parte da linha divis�ria

		for (j = 0; j < tamanho_tab; j++)	//itera��o para desenhar as casas do tabuleiro, com exce��o da �ltima parte
		{
			switch(tabuleiro[i][j]){ //verifica o que deve ser preenchido no tabuleiro de acordo com o valor de determinada posi��o da matriz e imprime o desenho adequado
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
		printf("|\n"); //fecha a sequ�ncia de casas e vai para a pr�xima linha
	}
	printf("+"); //come�a a imprimir a �ltima linha
	for (j = 0; j < (tamanho_tab - 1); j++)
	{
		printf("----"); //imprime o corpo da �ltima linha
	}
	printf("---+\n"); //imprime a �ltima parte da linha divis�ria
}

int main(){
	
	/*vari�veis*/

	int i, j;

	char **tabuleiro; //apontador da matriz tabuleiro na mem�ria
	char resposta[1]; //resposta da pergunta inicial (carregar jogo salvo)
	char caminho[200];  //Vari�vel que recebe o caminho do jogo
	
	FILE *jogo = NULL; //Ponteiro que guarda arquivos de jogo, sejam eles novos ou velhos
	
	int *tamanho_tab; //tamanho do tabuleiro

	const char *vez_do_jogador[2]; //vari�vel de controle da vez de cada jogador
	int jogador_atual = 0; // vari�vel de controle da vez de cada jogador
	int flag_jogada = 0;
	int comando, jogada1, jogada2;
    
	/*comandos*/
	vez_do_jogador[0] = "PRETO";
	vez_do_jogador[1] = "BRANCO";


	tamanho_tab = malloc(sizeof(int)); //aloca��o do tamanho do tabuleiro
    *tamanho_tab = 0;

    tabuleiro = malloc(*tamanho_tab * sizeof(int *)); //aloca a matriz tabuleiro na mem�ria, de acordo com o tamanho especificado pelo usu�rio.
	for(i = 0; i < *tamanho_tab; i++)
	{
		tabuleiro[i] = malloc(*tamanho_tab * sizeof(int));
	}

	while((strcmp(resposta, "s") != 0) && (strcmp(resposta, "n") != 0)){ //o programa pergunta ao jogador se ele deseja carregar um jogo salvo. enquanto o jogador n�o der uma resposta v�lida ("s" ou "n"), o programa continua perguntando.
		printf("Deseja carregar um jogo salvo? (s/n) ");
		gets(resposta);
		if ((strcmp(resposta, "s") != 0) && (strcmp(resposta, "n") != 0))
		{
			printf("OPCAO INVALIDA\n\n");
		}
	}
	
	if (strcmp(resposta, "s") == 0) //se a resposta do jogador for "sim", um jogo salvo num arquivo de texto � carregado.
	{
		while(!jogo){//pede ao jogador o arquivo do jogo salvo e verifica se esse arquivo existe. se o arquivo n�o existir, um novo caminho � pedido.
			printf("Digite o caminho do arquivo\n");
			scanf("%s", caminho);
			jogo = fopen(caminho, "r+"); //verificando se o arquivo existe.
			if (!jogo)
			{
				printf("CAMINHO INVALIDO\n");
			}
			
		}
		tabuleiro = carrega(jogo, tamanho_tab);
		//carrega
	}
	else{				//sen�o, come�a um novo jogo
		while((*tamanho_tab <= 2) || (*tamanho_tab % 2 == 1)){ //pergunta ao jogador qual � o tamanho do tabuleiro que ser� utilizado
			printf("Digite o tamanho do tabuleiro (Deve ser par e maior que 2): ");
			scanf("%d", tamanho_tab);
			if ((*tamanho_tab <= 2) || (*tamanho_tab % 2 == 1))
			{
				printf("TAMANHO INVALIDO\n\n"); //caso o tabuleiro seja muito pequeno, � exibida uma mensagem de erro e o programa volta a pedir o tamanho do tabuleiro
			}
		}

		tabuleiro = malloc(*tamanho_tab * sizeof(int *)); //aloca a matriz tabuleiro na mem�ria, de acordo com o tamanho especificado pelo usu�rio.
		for(i = 0; i < *tamanho_tab; i++)
		{
			tabuleiro[i] = malloc(*tamanho_tab * sizeof(int));
		}

		for (i = 0; i < *tamanho_tab; i++) //percorre todas as casas do tabuleiro e as define como vazias
		{
			for (j = 0; j < *tamanho_tab; j++)
			{
	            tabuleiro[i][j] = VAZIO; //atribui �casa do tabuleiro na posi��o i,j o valor VAZIO
			}
		}
		
		//Abaixo � realizada a configura��o inicial das casas do tabuleiro
		tabuleiro[(*tamanho_tab / 2) - 1][(*tamanho_tab / 2) - 1] = BRANCO;
		tabuleiro[(*tamanho_tab / 2) - 1][*tamanho_tab / 2] = PRETO;
		tabuleiro[*tamanho_tab / 2][(*tamanho_tab / 2) - 1] = PRETO;
		tabuleiro[*tamanho_tab / 2][*tamanho_tab / 2] = BRANCO;
	}
	printf("\n");
	while(comando != 2)
	{
		desenha_tab(tabuleiro, *tamanho_tab); //desenha o tabuleiro alocado na mem�ria de acordo com o tamanho definido pelo usu�rio
		printf("JOGADOR: %s\n", vez_do_jogador[jogador_atual]);
		printf("1 - Realizar jogada\n2 - Sair\n");
		if(jogador_atual == 0){
			printf("3 - Salvar jogo\n");
		}
		printf("Comando: ");
		scanf("%d", &comando);
		if(comando == 1)
		{
			while(flag_jogada == 0)
			{
				printf("Digite as posicoes da jogada:\n");
				scanf("%d %d", &jogada1, &jogada2);
				if(valida(tabuleiro, *tamanho_tab, jogada1, jogada2, jogador_atual) == 1)
				{
					printf("Jogada Invalida! Tente novamente!\n");
				}
				else
				{
					flag_jogada = 1;
				}	
			}
			if(jogador_atual == 0)
			{
				jogador_atual = 1;
			}
			else
			{
				jogador_atual = 0;
			}
			flag_jogada = 0;
			comando = NULL;
		}

		//Condi��o - Salvar o jogo. S� entra neste if se o jogador for PRETO//
		if((comando == 3) && (jogador_atual == 0)){
			printf("Digite o caminho onde o jogo ser� salvo: ");
			scanf("%s", &caminho);
			salvar_jogo(tamanho_tab, tabuleiro, caminho);
		}	
	}
	resultado_jogo(tamanho_tab, tabuleiro); //O jogo termina quando o loop while � finalizado. Esta fun��o determina quem venceu, ou, se houve empate.//

	system("PAUSE");

	//Libera��o de mem�ria//
	for(i = 0; i < *tamanho_tab; i++){
		free(tabuleiro[i]);
	}
	free(tabuleiro);
	printf("%d", *tamanho_tab);
	free(tamanho_tab);
	fclose(jogo);
    

	return 0;
}
