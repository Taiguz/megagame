#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "megalib.h"

// Atribuindo à struct seu respectivo vetor.

TELA telas[20];

HUD hud[5];

MENU menus[10];

CARTA cartas[80];

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

int menu_state, menu_state2;

int deck_pag, deck_pag2;

int bau[40];

int count;

int comand;

int deck_edit;

int deck_side;

int blocked1, blocked2;

int inimigo_escolha;

char cmd[50];

int tela_anterior;

int tela_num;

int tela_criar;

int atgame;

int menu;

int jogo_on;

int primeiro_turno;



// Criando função "main()", a estrutura principal do jogo.

int main(int argc, char const *argv[]) {

	setlocale(LC_ALL, "PORTUGUESE");

	// Atribuindo alguns valores iniciais

	tela_anterior = -1;

	atgame = 0;

	blocked1 = 1;

	deck_edit = 0;

	blocked2 = 1;

	tela_num = 0;

	tela_criar = 0;

	entrada = 1;

	deck_pag = 0;

	deck_pag2 = 0;

	menu = 0;

	jogo_on = 1;

	inimigo_escolha = 0;

	menu_state = 0;

	menu_state2 = 0;

	deck_side = 0;

	primeiro_turno = 1;

	//Função que irá criar todas as cartas do jogo.
	CriarCartas(cartas);

	// Função que cria as telas pré do jogo.
	CriarTelas(telas);

	// Função que cria as HUDs (mostra as informações básicas relativas ao jogador na tela) do jogo.
	CriarHUD(hud);

	// Função que carrega o save do jogo se existir e cria se não existir.
	Load(deck_jogador, bau);

	//Executa enquanto o jogo estiver em andamento.
	while (jogo_on) {



		//Executa enquanto estiver nas telas antes do jogo.
		while (entrada) {

			// Desenha a nova tela se a mesma tiver mudado.
			TransicaoTela( &tela_num, &tela_anterior, &tela_criar, telas);

			scanf( "%s", cmd);

			// Pega a o valor em cmd e converte para um inteiro e atribui ao comand que será o comando do jogador.
			comand = Comando(cmd, &atgame, &jogo_on, mao_jogador);

			// Muda as telas do jogo baseado nos comando dados pelo jogador.
			MudarTela(comand, &tela_num, &atgame, &entrada, blocked1, blocked2, &inimigo_escolha, &deck_edit , &tela_anterior, &tela_criar, deck_jogador, bau);

		}
		// Executa enquanto estiver na tela de editar o deck.
		while (deck_edit) {

			// Desenha o novo valor para a tela de editar deck de acordo com as variaves mudadas.
			DesenharDeck(cartas, deck_jogador, bau, telas, &menu_state, &menu_state2, &deck_pag, &deck_pag2, &deck_side);

			scanf( "%s", cmd);

			// Pega a o valor em cmd e converte para um inteiro e atribui ao comand que será o comando do jogador.
			comand = Comando(cmd, &atgame, &jogo_on, mao_jogador);

			// Muda as variaveis referentes a tela de editar deck de acordo com os comandos do jogador.
			MudarDeck(comand, &deck_edit, &entrada, &menu_state, &menu_state2, &tela_num, &deck_side, &deck_pag, &deck_pag2, deck_jogador, bau, telas);

			// Salva as alterações feitas no deck e bau.
			Save(deck_jogador, bau);

		}

		// Se o jogo tiver sido iniciado, inicia as variaveis referentes ao jogo.
		if (atgame) {


			//Inicia as variáveis do jogo
			IniciarJogo(mesa_aliada, mesa_inimiga, mao_jogador, mao_inimiga, vida, temp_mesa_jogador, temp_mesa_inimigo, cartas, inimigos, deck_jogador, &inimigo_escolha, &primeiro_turno, hud, &menu);

			// Atualiza a HUD que mostra os valores de ponto de vida do jogador e AI.
			AtualizarPlacar(hud, vida, &atgame, &entrada, &tela_num, &inimigo_escolha, &blocked1, &blocked2, bau, inimigos);

		}

		//Executa enquanto estiver em jogo
		while (atgame) {

			// Desenhando a Mesa do Jogo.
			DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, &menu);

			scanf("%s", cmd);

			// Pega a o valor em cmd e converte para um inteiro e atribui ao comand que será o comando do jogador.
			comand = Comando(cmd, &atgame, &jogo_on, mao_jogador);

			// Muda a hud e os elementos do jogo de acordo com os comandos do jogador.
			Controle(comand, hud, cartas, &atgame, &entrada, &tela_num, &jogo_on, &menu, mao_jogador, mao_inimiga, mesa_aliada, mesa_inimiga, temp_mesa_jogador, temp_mesa_inimigo, vida, deck_jogador, inimigos, &inimigo_escolha, &blocked1, &blocked2, bau, &primeiro_turno);

			//Dá um pequeno pause de comando em comando para melhor compreensão do que está acontecendo no jogo.
			sleep(0.5);

		}

		// Como o deck havia sido embaralhado e os valores foram sendo retirados, carrega o deck do jogador apartir do save.
		LoadDeck(deck_jogador);

	}




	return 0;
}

