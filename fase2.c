#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"

void resultado_jogo(int *tamanho_tab, char **tabuleiro){
	int i, j; //Variáveis de iteração//
	int pecas_branco = 0; //Contador de peças brancas//
	int pecas_preto = 0; //Contador de peças pretas//

	for(i = 0; i < tamanho_tab; i++){ //Loop para contar a quantidade de peças de cada jogador//
		for(j = 0; j < tamanho_tab; j++){
			if(tabuleiro[i][j] == PRETO){
				pecas_preto++;
			}
			else if(tabuleiro[i][j] == BRANCO){
				pecas_branco++;
			}
		}
	}

	printf("Peças do jogador branco: %d \n", pecas_branco); //Mostra a quantidade de peças do jogador branco.//
	printf("Peças do jogador preto: %d \n", pecas_preto);	//Mostra a quantidade de peças do jogador preto.//
	printf("\n");
	if(pecas_branco >  pecas_preto){ 			//Condições que definem quem ganhou. Se algum jogador tiver mais peças do que o outro, ele é declarado vencendor.//
		printf("O jogador BRANCO ganhou!\n");
	}
	else if(pecas_preto > pecas_branco){
		printf("O jogador PRETO ganhou!\n");
	}
	else if(pecas_branco == pecas_preto){	//Se o número de peças for igual, ocorreu um empate.//
		printf("Empate!\n");
	}


}

void salvar_jogo(int *tamanho_tab, char **tab, char *caminho){
	int i, j; //Variáveis de iteração//
	FILE *aux; //Variável auxiliar para criar o arquivo e salvá-lo//

	aux = fopen(caminho, "w+");
	if(!aux){ //Se não for possível criar o arquivo, é mostrado uma mensagem de erro.//
		printf("ERRO: O caminho é inválido ou um arquivo não pode ser criado neste diretório. \n");
		fclose(aux);
		return;
	}
	else{ //Senão, é salvo o jogo.//
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
	fclose(aux); //Depois de salvo, é fechado o arquivo.//
	return;
}

void realiza_jogada(char **tabuleiro, int n, int i, int j, int cor)
{
	int i2, j2; //posições em volta de onde foi feita a jogada
    int i3, j3; //casas na direção da peça adversária encontrada
    int direcao_i, direcao_j; //controladores da direção onde estão as peças adversárias
    char direcao[50]; //direção da peça adversária em relação à peça jogada

	if((i >= 0) && (i < n) && (j >= 0) && (j < n)){ // Checa se a jogada foi feita dentro do tabuleiro
        for(i2 = i - 1; i2 <= i + 1; i2++){ //Checa as casas em volta da peça que será jogada
            for(j2 = j - 1; j2 <= j + 1; j2++){
                if(i2 >= 0 && i2 < n && j2 >= 0 && j2 < n){ //Verifica se o espaço que está sendo checado é uma casa dentro do tabuleiro
                    if(tabuleiro[i2][j2] == 1 - cor){ //Se for encontrada alguma peça adversária, é checada a direção desta peça em relação à peça jogada
                        direcao_i = i - i2; //verifica se a peça adversária está uma linha antes ou depois da peça jogada, ou na mesma linha
                        direcao_j = j - j2; //verifica se a peça adversária está uma coluna antes ou depois da peça jogada, ou na mesma coluna
                        
                        switch(direcao_i){ //determina a direção da peça adversária de acordo com suas coordenadas no tabuleiro
                            case -1:
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
                                    case -1:
                                        strcpy(direcao,"LESTE");
                                        break;
                                    case 1:
                                        strcpy(direcao,"OESTE");
                                        break;
                                }
                            case 1:
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
                        }

                        if (strcmp(direcao, "SUDOESTE") == 0) //checa as casas seguintes na direção determinada
                        {  
                            i3 = i2 + 1;
							j3 = j2 - 1;
							while((i3 < n && j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){ //continua-se a checar por uma peça que valide a jogada até que seja encontrado um espaço vazio ou que seja atingido o fim do tabuleiro
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								i3++; //senão, continua procurando uma peça válida na mesma direção
								j3--;								
							}
                        }
                        else if (strcmp(direcao, "SUL") == 0)
                        {
                            i3 = i2 + 1;
							j3 = j2;
							while((i3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								i3++;						
							}
                        
                        }
                        else if (strcmp(direcao, "SUDESTE") == 0)
                        {
                            i3 = i2 + 1;
							j3 = j2 + 1;
							while((i3 < n && j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								i3++;
								j3++;						
							} 
                        }
							
						else if (strcmp(direcao, "LESTE") == 0)
                        {
                            i3 = i3;
							j3 = j2 + 1;
							while((j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								j3++;						
							} 
                        }		
				
						else if (strcmp(direcao, "OESTE") == 0)	
						{
                            i3 = i2;
							j3 = j2 - 1;
							while((j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								j3--;						
							}
                        }		
						
						else if (strcmp(direcao, "NORDESTE") == 0)
						{
							i3 = i2 - 1;
							j3 = j2 + 1;
							while((i3 >= 0 && j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								i3--;
								j3++;						
							}
						}	
								
							
						else if (strcmp(direcao, "NORTE") == 0)
						{
							i3 = i2 - 1;
							j3 = j2;
							while((i3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
								}
								i3++;
								j3++;						
							}
						}
								
						else if (strcmp(direcao, "NORTE") == 0)
						{
							i3 = i2 - 1;
							j3 = j2 - 1;
							while((i3 >= 0 && j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == 1 - cor){
									tabuleiro[i3][j3] = cor;
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

    return tabuleiro;
}

void desenha_tab(char **tabuleiro, int tamanho_tab) //desenha o tabuleiro na tela
{
	int i, j;

	for (i = 0; i < tamanho_tab; i++) //iteraçào para desenhar as linhas de divisào das casas, com exceçào da última parte
	{
		printf("+"); //começa a imprimir a linha divisória
		for (j = 0; j < (tamanho_tab - 1); j++)
		{
			printf("----"); //imprime o corpo da linha divisória
		}
		printf("---+\n"); //imprime a última parte da linha divisória

		for (j = 0; j < tamanho_tab; j++)	//iteraçào para desenhar as casas do tabuleiro, com exceçào da última parte
		{
			switch(tabuleiro[i][j]){ //verifica o que deve ser preenchido no tabuleiro de acordo com o valor de determinada posiçào da matriz e imprime o desenho adequado
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
	
	FILE *jogo = NULL; //Ponteiro que guarda arquivos de jogo, sejam eles novos ou velhos
	
	int *tamanho_tab; //tamanho do tabuleiro

	const char *vez_do_jogador[2]; //variável de controle da vez de cada jogador
	int jogador_atual = 0; // variável de controle da vez de cada jogador
	int flag_jogada = 0;
	int comando, jogada1, jogada2;
    
	/*comandos*/
	vez_do_jogador[0] = "PRETO";
	vez_do_jogador[1] = "BRANCO";


	tamanho_tab = malloc(sizeof(int)); //alocaçào do tamanho do tabuleiro
    *tamanho_tab = 0;

    tabuleiro = malloc(*tamanho_tab * sizeof(int *)); //aloca a matriz tabuleiro na memória, de acordo com o tamanho especificado pelo usuário.
	for(i = 0; i < *tamanho_tab; i++)
	{
		tabuleiro[i] = malloc(*tamanho_tab * sizeof(int));
	}

	while((strcmp(resposta, "s") != 0) && (strcmp(resposta, "n") != 0)){ //o programa pergunta ao jogador se ele deseja carregar um jogo salvo. enquanto o jogador nào der uma resposta válida ("s" ou "n"), o programa continua perguntando.
		printf("Deseja carregar um jogo salvo? (s/n) ");
		gets(resposta);
		if ((strcmp(resposta, "s") != 0) && (strcmp(resposta, "n") != 0))
		{
			printf("OPCAO INVALIDA\n\n");
		}
	}
	
	if (strcmp(resposta, "s") == 0) //se a resposta do jogador for "sim", um jogo salvo num arquivo de texto é carregado.
	{
		while(!jogo){//pede ao jogador o arquivo do jogo salvo e verifica se esse arquivo existe. se o arquivo nào existir, um novo caminho é pedido.
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
	else{				//senào, começa um novo jogo
		while((*tamanho_tab <= 2) || (*tamanho_tab % 2 == 1)){ //pergunta ao jogador qual é o tamanho do tabuleiro que será utilizado
			printf("Digite o tamanho do tabuleiro (Deve ser par e maior que 2): ");
			scanf("%d", tamanho_tab);
			if ((*tamanho_tab <= 2) || (*tamanho_tab % 2 == 1))
			{
				printf("TAMANHO INVALIDO\n\n"); //caso o tabuleiro seja muito pequeno, é exibida uma mensagem de erro e o programa volta a pedir o tamanho do tabuleiro
			}
		}

		tabuleiro = malloc(*tamanho_tab * sizeof(int *)); //aloca a matriz tabuleiro na memória, de acordo com o tamanho especificado pelo usuário.
		for(i = 0; i < *tamanho_tab; i++)
		{
			tabuleiro[i] = malloc(*tamanho_tab * sizeof(int));
		}

		for (i = 0; i < *tamanho_tab; i++) //percorre todas as casas do tabuleiro e as define como vazias
		{
			for (j = 0; j < *tamanho_tab; j++)
			{
	            tabuleiro[i][j] = VAZIO; //atribui à casa do tabuleiro na posiçào i,j o valor VAZIO
			}
		}
		
		//Abaixo é realizada a configuração inicial das casas do tabuleiro
		tabuleiro[(*tamanho_tab / 2) - 1][(*tamanho_tab / 2) - 1] = BRANCO;
		tabuleiro[(*tamanho_tab / 2) - 1][*tamanho_tab / 2] = PRETO;
		tabuleiro[*tamanho_tab / 2][(*tamanho_tab / 2) - 1] = PRETO;
		tabuleiro[*tamanho_tab / 2][*tamanho_tab / 2] = BRANCO;
	}
	printf("\n");
	while(comando != 2)
	{
		desenha_tab(tabuleiro, *tamanho_tab); //desenha o tabuleiro alocado na memória de acordo com o tamanho definido pelo usuário
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
			comando = NULL;
		}

		//Condição - Salvar o jogo. Só entra neste if se o jogador for PRETO//
		if((comando == 3) && (jogador_atual == 0)){
			printf("Digite o caminho onde o jogo será salvo: ");
			scanf("%s", &caminho);
			salvar_jogo(tamanho_tab, tabuleiro, caminho);
		}	
	}
	resultado_jogo(tamanho_tab, tabuleiro); //O jogo termina quando o loop while é finalizado. Esta função determina quem venceu, ou, se houve empate.//

	system("PAUSE");

	//Liberaçào de memória//
	for(i = 0; i < *tamanho_tab; i++){
		free(tabuleiro[i]);
	}
	free(tabuleiro);
	printf("%d", *tamanho_tab);
	free(tamanho_tab);
	fclose(jogo);
    

	return 0;
}
