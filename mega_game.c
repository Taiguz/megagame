#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"megalib.h"

// Atribuindo à struct seu respectivo vetor.

TELA telas[20];

HUD hud[5];

MENU menus[10];

CARTA cartas[10];

INIMIGO inimigos[10];


// Declarando variáveis a serem utilizadas neste código.

int i, j, entrada;

int mesa_aliada[4];

int mesa_inimiga[4];

int mao_jogador[4];

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

	CriarCartas(cartas);

	CriarTelas(telas);

	CriarHUD(hud);

	//Executa enquanto estiver nas telas antes do jogo
	while (entrada) {

		TransicaoTela(tela_num, &tela_anterior, &tela_criar, telas);

		scanf( "%s", &cmd);

		comand = Comando(cmd);

		MudarTela(comand, &tela_num, &atgame, &entrada);

	}
	//Executa enquanto estiver em jogo
	while (atgame) {

		int game_ini;

		int menu;

		menu = 0;

		game_ini = 0;

		IniciarJogo(&game_ini, mesa_aliada, mesa_inimiga, mao_jogador);

		DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud);

		scanf("%s", &cmd);

		comand = Comando(cmd);

		MudarHud(comand, hud, cartas, &atgame, &menu, mao_jogador);

	}

	return 0;
}

