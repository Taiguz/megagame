
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "megalib.h"

// Atribuindo à struct seu respectivo vetor.

TELA telas[20];

HUD hud[5];

MENU menus[10];

CARTA cartas[10];

TEMP_CARTA temp_mesa_jogador[5];

TEMP_CARTA temp_mesa_inimigo[5];


INIMIGO inimigos[10];


// Declarando variáveis a serem utilizadas neste código.

int i, j, entrada;

int mesa_aliada[5];

int mesa_inimiga[5];

int vida[2];

int mao_inimiga[5];

int mao_jogador[5];

int deck_jogador[40];

int count;

int comand;

char cmd[50];



// Criando função "main()", a estrutura principal do jogo.

int main(int argc, char const *argv[]) {

	setlocale(LC_ALL, "PORTUGUESE");

	int tela_anterior = -1;

	int tela_num, tela_criar, atgame;

	atgame = 0;

	tela_num = 0;

	tela_criar = 0;

	entrada = 1;



	int menu;

	menu = 0;



	CriarCartas(cartas);

	CriarTelas(telas);

	CriarHUD(hud);





	//Executa enquanto estiver nas telas antes do jogo
	while (entrada) {

		TransicaoTela(tela_num, &tela_anterior, &tela_criar, telas);

		scanf( "%s", cmd);

		comand = Comando(cmd, &atgame);

		MudarTela(comand, &tela_num, &atgame, &entrada);

	}

	//Inicia as variáveis do jogo
	IniciarJogo(mesa_aliada, mesa_inimiga, mao_jogador,mao_inimiga, vida, temp_mesa_jogador, temp_mesa_inimigo, cartas);

	//Executa enquanto estiver em jogo
	while (atgame) {




		DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador,temp_mesa_inimigo);

		scanf("%s", cmd);

		comand = Comando(cmd, &atgame);

		Controle(comand, hud, cartas, &atgame, &menu, mao_jogador, mesa_aliada, mesa_inimiga, temp_mesa_jogador,temp_mesa_inimigo,vida);

	}


	return 0;
}


