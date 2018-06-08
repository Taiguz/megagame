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


INIMIGO inimigos[5];


// Declarando variáveis a serem utilizadas neste código.

int i, j, entrada;

int mesa_aliada[5];

int mesa_inimiga[5];

int vida[2];

int mao_inimiga[5];

int mao_jogador[5];

int deck_jogador[20];

int count;

int comand;

char cmd[50];

int tela_anterior;

int tela_num;

int tela_criar;

int atgame;

int menu;



// Criando função "main()", a estrutura principal do jogo.

int main(int argc, char const *argv[]) {

	setlocale(LC_ALL, "PORTUGUESE");

	// Atribuindo alguns valores iniciais

	tela_anterior = -1;

	atgame = 0;

	tela_num = 0;

	tela_criar = 0;

	entrada = 1;

	menu = 0;

	//Função que irá criar todas as cartas do jogo.
	CriarCartas(cartas);

	// Função que cria as telas pré do jogo.
	CriarTelas(telas);

	// Função que cria as HUDs (mostra as informações básicas relativas ao jogador na tela) do jogo.
	CriarHUD(hud);


	//Executa enquanto estiver nas telas antes do jogo
	while (entrada) {

		// Desenha a nova tela se a mesma tiver mudado
		TransicaoTela(tela_num, &tela_anterior, &tela_criar, telas);

		scanf( "%s", cmd);

		// Pega a o valor em cmd e converte para um inteiro e atribui ao comand que será o comando do jogador
		comand = Comando(cmd, &atgame);

		// Muda as telas do jogo baseado nos comando dados pelo jogador
		MudarTela(comand, &tela_num, &atgame, &entrada);

	}

	//Inicia as variáveis do jogo
	IniciarJogo(mesa_aliada, mesa_inimiga, mao_jogador, mao_inimiga, vida, temp_mesa_jogador, temp_mesa_inimigo, cartas, inimigos, deck_jogador);
	
	AtualizarPlacar(hud, vida);
	//Executa enquanto estiver em jogo
	while (atgame) {

		// Desenhando a Mesa do Jogo.
		DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, &menu);

		scanf("%s", cmd);

		// Pega a o valor em cmd e converte para um inteiro e atribui ao comand que será o comando do jogador
		comand = Comando(cmd, &atgame);

		// Muda a hud e os elementos do jogo de acordo com os comandos do jogador
		Controle(comand, hud, cartas, &atgame, &menu, mao_jogador, mao_inimiga, mesa_aliada, mesa_inimiga, temp_mesa_jogador, temp_mesa_inimigo, vida, deck_jogador, inimigos);



		AtualizarPlacar(hud, vida);

	}


	return 0;
}

