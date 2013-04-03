#ifndef _REVERSI_H_
#define _REVERSI_H_


#define VAZIO -1
#define PRETO 0
#define BRANCO 1


char **carrega(FILE *caminho, int *n);


int valida(char **tabuleiro, int n, int i, int j, char cor);



#endif
