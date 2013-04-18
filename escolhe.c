void escolhe(char **tabuleiro, int n, char cor, int *i, int *j) {
	i = -1;
	j = -1;

//Checa se é possível fazer uma jogada nos cantos;
	if(valida(tabuleiro, n, cor, 0, 0) == 0){
		i = 0;
		j = 0;
	}
	else if(valida(tabuleiro, n, cor, 0, n - 1) == 0){
		i = 0;
		j = n - 1;
	}
	else if(valida(tabuleiro, n, cor, n - 1, 0) == 0){
		i = n - 1;
		j = 0;
	}
	else if(valida(tabuleiro, n, cor, n - 1, n - 1) == 0){
		i = n - 1;
		j = n - 1;
	}

	

