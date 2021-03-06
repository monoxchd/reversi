#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"

void resultado_jogo(int tamanho_tab, char **tabuleiro){
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

void realiza_jogada(char **tabuleiro, int n, int i, int j, char cor)
{
	tabuleiro[i][j] = cor;
	

	int i2, j2; //posi��es em volta de onde foi feita a jogada
    int i3, j3; //casas na dire��o da pe�a advers�ria encontrada
    int i4 = 0, j4 = 0; //vari�veis para auxiliar na transforma��o de pe�as
    int direcao_i, direcao_j; //controladores da dire��o onde est�o as pe�as advers�rias
    char direcao[50];
    printf("\ni = %d, j = %d\n", i, j);
    printf("%d %d \n", i4, j4);

	if((i >= 0) && (i < n) && (j >= 0) && (j < n)){ // Checa se a jogada foi feita dentro do tabuleiro
        for(i2 = i - 1; i2 <= i + 1; i2++){ //Checa as casas em volta da pe�a que ser� jogada
            for(j2 = j - 1; j2 <= j + 1; j2++){
                if(i2 >= 0 && i2 < n && j2 >= 0 && j2 < n){ //Verifica se o espa�o que est� sendo checado � uma casa dentro do tabuleiro
                    if(tabuleiro[i2][j2] == 1 - cor){ //Se for encontrada alguma pe�a advers�ria, � checada a dire��o desta pe�a em rela��o � pe�a jogada
                        direcao_i = i2 - i; //verifica se a pe�a advers�ria est� uma linha antes ou depois da pe�a jogada, ou na mesma linha
                        direcao_j = j2 - j; //verifica se a pe�a advers�ria est� uma coluna antes ou depois da pe�a jogada, ou na mesma coluna

                        
                        switch(direcao_i){ //determina a dire��o da pe�a advers�ria de acordo com suas coordenadas no tabuleiro
                            case 1:
                                switch(direcao_j){
                                    case -1:
                                        strcpy(direcao,"SUDOESTE");
                                        break;
                                    case 0:
                                        strcpy(direcao,"SUL");
                                        break;
                                    case 1:
                                        strcpy(direcao,"SUDESTE");
                                        break;
                                }
                                break;
                            case 0:
                                switch(direcao_j){
                                    case 1:
                                        strcpy(direcao,"LESTE");
                                        break;
                                    case -1:
                                        strcpy(direcao,"OESTE");
                                        break;
                                }
                                break;
                            case -1:
                                switch(direcao_j){
                                    case -1:
                                        strcpy(direcao,"NOROESTE");
                                        break;
                                    case 0:
                                        strcpy(direcao,"NORTE");
                                        break;
                                    case 1:
                                        strcpy(direcao,"NORDESTE");
                                        break;
                                }
                                break;
                        }
                        if (strcmp(direcao, "SUDOESTE") == 0) //checa as casas seguintes na dire��o determinada
                        {  
                        	printf("%d 1 \n", i4);
                            i3 = i2 + 1;
							j3 = j2 - 1;
							while((i3 < n && j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){ //continua-se a checar por uma pe�a que valide a jogada at� que seja encontrado um espa�o vazio ou que seja atingido o fim do tabuleiro
								if(tabuleiro[i3][j3] == cor){	//Se for encontrada, todas as pe�as que estavam nesta dire��o s�o transformadas nas pe�as do jogador que propos a jogada//
									i4 = i;
									j4 = j;
									while(i4 <= i3 && j4 >= j3){
										tabuleiro[i4][j4] = cor;
										i4++;
										j4--;
									}
									break;
								}
								i3++; //sen�o, continua procurando uma pe�a v�lida na mesma dire��o
								j3--;								
							}
                        }
                        else if (strcmp(direcao, "SUL") == 0)
                        {
                        	printf("%d 2 \n", i4);
                            i3 = i2 + 1;
							j3 = j2;
							j4 = j;
							while((i3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									for(i4 = i; i4 < i3; i4++){
										tabuleiro[i4][j4] = cor;
									}
								}
								i3++;						
							}
                        
                        }
                        else if (strcmp(direcao, "SUDESTE") == 0)
                        {

                        	printf("%d 3 \n", i4);
                            i3 = i2 + 1;
							j3 = j2 + 1;
							while((i3 < n && j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									i4 = i;
									j4 = j;
									while(i4 <= i3 && j4 <= j3){
										tabuleiro[i4][j4] = cor;
										i4++;
										j4++;
									}
									break;
								}
								i3++;
								j3++;						
							} 
                        }
							
						else if (strcmp(direcao, "LESTE") == 0)
                        {
                        	printf("%d 4 \n", i4);
                            i3 = i2;
							j3 = j2 + 1;
							i4 = i;
							while((j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									for(j4 = j; j4 <= j3; j4++){
										tabuleiro[i4][j4] = cor;
									}
									break;
								}
								j3++;						
							} 
                        }		
				
						else if (strcmp(direcao, "OESTE") == 0)	
						{
							printf("%d 5 \n", i4);
                            i3 = i2;
							j3 = j2 - 1;
							i4 = i;
							while((j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									for(j4 = j; j4 >= j3; j4--){
										tabuleiro[i4][j4] = cor;
									}
									break;
								}
								j3--;						
							}
                        }		
						
						else if (strcmp(direcao, "NORDESTE") == 0)
						{
							printf("%d 6 \n", i4);
							i3 = i2 - 1;
							j3 = j2 + 1;
							while((i3 >= 0 && j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									i4 = i;
									j4 = j;
									while(i4 >= i3 && j4 <= j3){
										tabuleiro[i4][j4] = cor;
										i4--;
										j4++;
									}
									break;
								}
								i3--;
								j3++;						
							}
						}	
								
							
						else if (strcmp(direcao, "NORTE") == 0)
						{
							printf("%d 7 \n", i4);
							i3 = i2 - 1;
							j3 = j2;
							j4 = j;
							while((i3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									for(i4 = i; i4 > i3; i4--){
										tabuleiro[i4][j4] = cor;
									}
									break;
								}
								i3--;						
							}
						}
								
						else if (strcmp(direcao, "NOROESTE") == 0)
						{
							printf("%d 8 \n", i4);
							i3 = i2 - 1;
							j3 = j2 - 1;
							while((i3 >= 0 && j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									i4 = i;
									j4 = j;
									while (i4 >= i3 && j4 >= j3){
										tabuleiro[i4][j4] = cor;
										i4--;
										j4--;
									}
									break;
								}
								i3--;
								j3--;						
							}
						}
                    }
                }
            }
        }
    }
    return;
}

void desenha_tab(char **tabuleiro, int tamanho_tab) //desenha o tabuleiro na tela
{
	int i, j;

	for(i = 0; i < tamanho_tab; i++){
		printf(" %d  ", i);
	}
	printf("\n");
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
		printf("| %d\n", i); //fecha a sequ�ncia de casas e vai para a pr�xima linha
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
    *tamanho_tab = 8;

	
	tabuleiro = malloc(*tamanho_tab * sizeof(int *)); //aloca a matriz tabuleiro na mem�ria, de acordo com o tamanho especificado pelo usu�rio.
	for(i = 0; i < *tamanho_tab; i++)
	{
		tabuleiro[i] = malloc(*tamanho_tab * sizeof(int));
	}

	for (i = 0; i < *tamanho_tab; i++) //percorre todas as casas do tabuleiro e as define como vazias
	{
		for (j = 0; j < *tamanho_tab; j++)
		{
	    	tabuleiro[i][j] = VAZIO; //atribui��casa do tabuleiro na posi��o i,j o valor VAZIO
		}
	}
		
	//Abaixo � realizada a configura��o inicial das casas do tabuleiro
	tabuleiro[(*tamanho_tab / 2) - 1][(*tamanho_tab / 2) - 1] = BRANCO;
	tabuleiro[(*tamanho_tab / 2) - 1][*tamanho_tab / 2] = PRETO;
	tabuleiro[*tamanho_tab / 2][(*tamanho_tab / 2) - 1] = PRETO;
	tabuleiro[*tamanho_tab / 2][*tamanho_tab / 2] = BRANCO;
	

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
					realiza_jogada(tabuleiro, *tamanho_tab, jogada1, jogada2, jogador_atual);
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
			comando = 0;
		}

		//Condi��o - Salvar o jogo. S� entra neste if se o jogador for PRETO//
		if((comando == 3) && (jogador_atual == 0)){
			printf("Digite o caminho onde o jogo ser� salvo: ");
			scanf("%s", &caminho);
			salvar_jogo(tamanho_tab, tabuleiro, caminho);
		}	
	}
	resultado_jogo(*tamanho_tab, tabuleiro); //O jogo termina quando o loop while � finalizado. Esta fun��o determina quem venceu, ou, se houve empate.//

    system("PAUSE");
	//Libera��o de mem�ria//
	for(i = 0; i < *tamanho_tab; i++){
		free(tabuleiro[i]);
	}
	free(tabuleiro);
	free(tamanho_tab);
    

	return 0;
}
