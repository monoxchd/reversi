#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"

int valida(char **tabuleiro, int n, int i, int j, char cor) {

    int i2, j2; //posi��es em volta de onde foi feita a jogada
    int i3, j3; //casas na dire��o da pe�a advers�ria encontrada
    int direcao_i, direcao_j; //controladores da dire��o onde est�o as pe�as advers�rias
    char direcao[50]; //dire��o da pe�a advers�ria em rela��o � pe�a jogada
    strcpy(direcao, "DEFAULT");

        
    if((i >= 0) && (i < n) && (j >= 0) && (j < n)){ // Checa se a jogada foi feita dentro do tabuleiro
    	if(tabuleiro[i][j] != VAZIO){
    		return 1;
    	}
        for(i2 = i - 1; i2 <= i + 1; i2++){ //Checa as casas em volta da pe�a que ser� jogada
            for(j2 = j - 1; j2 <= j + 1; j2++){
                if(i2 >= 0 && i2 < n && j2 >= 0 && j2 < n){ //Verifica se o espa�o que est� sendo checado � uma casa dentro do tabuleiro
                    if(tabuleiro[i2][j2] == 1 - cor){ //Se for encontrada alguma pe�a advers�ria, � checada a dire��o desta pe�a em rela��o � pe�a jogada
                        direcao_i = i2 - i; //verifica se a pe�a advers�ria est� uma linha antes ou depois da pe�a jogada, ou na mesma linha
                        direcao_j = j2 - j; //verifica se a pe�a advers�ria est� uma coluna antes ou depois da pe�a jogada, ou na mesma coluna
                        printf("%d, %d\n", direcao_i, direcao_j);
                        
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
                                        printf(direcao);
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
                                        printf("\nEntrou\n\n");
                                        break;
                                    case 1:
                                        strcpy(direcao,"NORDESTE");
                                        printf("%s\n", direcao);
                                        break;
                                }
                                break;
                        }
                        
                        printf("Dire��o: %s\n");

                        if (strcmp(direcao, "SUDOESTE") == 0) //checa as casas seguintes na dire��o determinada
                        {  
                            i3 = i2 + 1;
							j3 = j2 - 1;
							while((i3 < n && j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){ //continua-se a checar por uma pe�a que valide a jogada at� que seja encontrado um espa�o vazio ou que seja atingido o fim do tabuleiro
								if(tabuleiro[i3][j3] == cor){ //se for encontrada uma pe�a que valide a jogada, a fun��o retorna 0 e � encerrada
			
									return 0;
									break;
								}
								i3++; //sen�o, continua procurando uma pe�a v�lida na mesma dire��o
								j3--;								
							}
                        }
                        else if (strcmp(direcao, "SUL") == 0)
                        {
                            i3 = i2 + 1;
							j3 = j2;
							while((i3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									
									return 0;
									break;
								}
								i3++;						
							}
                        
                        }
                        else if (strcmp(direcao, "SUDESTE") == 0)
                        {
                        	printf("entrou\n");
                            i3 = i2 + 1;
							j3 = j2 + 1;
							while((i3 < n && j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									
									return 0;
									break;
								}
								i3++;
								j3++;						
							} 
                        }
							
						else if (strcmp(direcao, "LESTE") == 0)
                        {
                            i3 = i2;
							j3 = j2 + 1;
							while((j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									printf("%d\n", cor);
									printf("\ni = %d, j = %d\n", i, j);
									return 0;
									break;
								}
								j3++;						
							} 
                        }		
				
						else if (strcmp(direcao, "OESTE") == 0)	
						{
                            i3 = i2;
							j3 = j2 - 1;
							while((j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									
									return 0;
									break;
								}
								j3--;						
							}
                        }		
						
						else if (strcmp(direcao, "NORDESTE") == 0)
						{
                            printf("entrou\n");
							i3 = i2 - 1;
							j3 = j2 + 1;
							while((i3 >= 0 && j3 < n) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									
									return 0;
									break;
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
								if(tabuleiro[i3][j3] == cor){
									
									return 0;
									break;
								}
								i3--;						
							}
						}
								
						else if (strcmp(direcao, "NOROESTE") == 0)
						{
							i3 = i2 - 1;
							j3 = j2 - 1;
							while((i3 >= 0 && j3 >= 0) && (tabuleiro[i3][j3] != VAZIO)){
								if(tabuleiro[i3][j3] == cor){
									
									return 0;
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
		printf(direcao);
		printf("\n");
		return 1; //a fun��o retorna 1 quando a jogada n�o � v�lida, ou seja, n�o cumpriu as condi��es acima.
	
}


char **carrega(char *caminho, int *n) {
	int i, j; //vari�veis de incrementa��o//
    char **tab; //Matriz auxiliar para inicializar o tabuleiro.//
    FILE *aux; //Vari�vel auxiliar, para recuperar os dados do arquivo.//
    aux = fopen(caminho, "r+");

    fscanf(aux, "%d", n);
    
    tab = malloc(*n * sizeof(int *)); //Aloca��o de mem�ria para a matriz.//
    for(i = 0; i < *n; i++){
		tab[i] = malloc(*n * sizeof(int));
    }
    

   //Leitura de arquivo//
    for(i = 0; i < *n; i++){
           for(j = 0; j < *n; j++){
           	     fscanf(aux, "%d", &tab[i][j]); //O programa recebe o valor do arquivo e atribui ao tabuleiro...//
           	     if (tab[i][j] != -1 && tab[i][j] != 0 && tab[i][j] != 1){    //...E um if checa se o valor � v�lido ou n�o.//
     	            return NULL; //Se for um valor inv�lido, � retornado NULL, e a fun��o � cancelada.//
                    break;       //Se for um valor v�lido, ocorre um loop, e � incrementado o pr�ximo valor.//         
                  }
            
           }
     } 
    
    fclose(aux); 
    return tab; //Se o tabuleiro foi preenchido completamente sem nenhum erro, � retornada a matriz, que atribui todos os valores para a matriz principal.
}


