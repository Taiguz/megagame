#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#include "megalib.h"
// Criando função responsável por receber comandos "in-game" (digitados no console).
int Comando(char *copy) {

	int limit = 0;

	int found = 0;

	int i = 0;

	char cmd[50];

	strcpy(cmd, copy);

	for (i = 0; i <= 50; i++) {



		if (cmd[i] == 0 && found == 0) {

			limit = i;
			found = 1;

		}


	}

	char new_cmd[limit];



	for (i = 0; i <= limit; i++) {

		new_cmd[i] = cmd[i];




	}


	int comando = atoi(new_cmd);

	return comando;
}
// Desenhando a HUD do jogo.
void CriarHUD(HUD *hud) {
	strcpy(hud->linhas[0].linha, "     +-------+");
	strcpy(hud->linhas[1].linha, "     | CAMPO |");
	strcpy(hud->linhas[2].linha, "+----+-------+-----+");
	strcpy(hud->linhas[3].linha, "|      NORMAL      |");
	strcpy(hud->linhas[4].linha, "+------------------+");
	strcpy(hud->linhas[5].linha, "     +-------+");
	strcpy(hud->linhas[6].linha, "     |  LOG  |");
	strcpy(hud->linhas[7].linha, "+----+-------+-----+");
	strcpy(hud->linhas[8].linha, "|                  |");
	strcpy(hud->linhas[9].linha, "|                  |");
	strcpy(hud->linhas[10].linha, "|                  |");
	strcpy(hud->linhas[11].linha, "|                  |");
	strcpy(hud->linhas[12].linha, "|                  |");
	strcpy(hud->linhas[13].linha, "|                  |");
	strcpy(hud->linhas[14].linha, "|                  |");
	strcpy(hud->linhas[15].linha, "|                  |");
	strcpy(hud->linhas[16].linha, "|                  |");
	strcpy(hud->linhas[17].linha, "|                  |");
	strcpy(hud->linhas[18].linha, "|                  |");
	strcpy(hud->linhas[19].linha, "|                  |");
	strcpy(hud->linhas[20].linha, "|                  |");
	strcpy(hud->linhas[21].linha, "|                  |");
	strcpy(hud->linhas[22].linha, "+------------------+");
	strcpy(hud->linhas[23].linha, "    +----------+");
	strcpy(hud->linhas[24].linha, "    |   MENU   |");
	strcpy(hud->linhas[25].linha, "+---+----------+---+");
	strcpy(hud->linhas[26].linha, "|                  |");
	strcpy(hud->linhas[27].linha, "|1 - Sumonar Carta |");
	strcpy(hud->linhas[28].linha, "|                  |");
	strcpy(hud->linhas[29].linha, "|2 - Trocar Modo   |");
	strcpy(hud->linhas[30].linha, "|                  |");
	strcpy(hud->linhas[31].linha, "|3 - Surrender     |");
	strcpy(hud->linhas[32].linha, "|                  |");
	strcpy(hud->linhas[33].linha, "|                  |");
	strcpy(hud->linhas[34].linha, "+------------------+");
	hud++;
	strcpy(hud->linhas[0].linha, "       +-------+");
	strcpy(hud->linhas[1].linha, "       | CAMPO |");
	strcpy(hud->linhas[2].linha, "+------+-------+-------+");
	strcpy(hud->linhas[3].linha, "|       NORMAL         |");
	strcpy(hud->linhas[4].linha, "+----------------------+");
	strcpy(hud->linhas[5].linha, "       +-------+");
	strcpy(hud->linhas[6].linha, "       |  LOG  |");
	strcpy(hud->linhas[7].linha, "+------+-------+-------+");
	strcpy(hud->linhas[8].linha, "|                      |");
	strcpy(hud->linhas[9].linha, "|                      |");
	strcpy(hud->linhas[10].linha, "|                      |");
	strcpy(hud->linhas[11].linha, "|                      |");
	strcpy(hud->linhas[12].linha, "|                      |");
	strcpy(hud->linhas[13].linha, "|                      |");
	strcpy(hud->linhas[14].linha, "|                      |");
	strcpy(hud->linhas[15].linha, "|                      |");
	strcpy(hud->linhas[16].linha, "|                      |");
	strcpy(hud->linhas[17].linha, "|                      |");
	strcpy(hud->linhas[18].linha, "|                      |");
	strcpy(hud->linhas[19].linha, "|                      |");
	strcpy(hud->linhas[20].linha, "|                      |");
	strcpy(hud->linhas[21].linha, "|                      |");
	strcpy(hud->linhas[22].linha, "+----------------------+");
	strcpy(hud->linhas[23].linha, "      +----------+");
	strcpy(hud->linhas[24].linha, "      |   MENU   |");
	strcpy(hud->linhas[25].linha, "+-----+----------+-----+");
	strcpy(hud->linhas[26].linha, "|                      |");
	strcpy(hud->linhas[27].linha, "|1 - Sumonar Carta     |");
	strcpy(hud->linhas[28].linha, "|                      |");
	strcpy(hud->linhas[29].linha, "|2 - Trocar Modo       |");
	strcpy(hud->linhas[30].linha, "|                      |");
	strcpy(hud->linhas[31].linha, "|3 - Surrender         |");
	strcpy(hud->linhas[32].linha, "|                      |");
	strcpy(hud->linhas[33].linha, "|                      |");
	strcpy(hud->linhas[34].linha, "|                      |");
	strcpy(hud->linhas[35].linha, "+----------------------+");
	hud++;
	strcpy(hud->linhas[0].linha, "                                                    +---------+                                                   ");
	strcpy(hud->linhas[1].linha, "+---------------------------------------------------+ SUA MÃO +--------------------------------------------------+");
	strcpy(hud->linhas[2].linha, "                                                    +---------+                                                   ");
}
//Função que irá criar todas as cartas do jogo.
void CriarCartas(CARTA *cartas) {

	cartas->tipo = 1;
	cartas->atk = 3000;
	cartas->def = 1500;
	strcpy(cartas->nome, "Satella");
	strcpy(cartas->desc, "A grande bruxa");
	strcpy(cartas->linhas[0].linha, "+-------------------+");
	strcpy(cartas->linhas[1].linha, "|      SATELLA      |");
	strcpy(cartas->linhas[2].linha, "+-------------------+");
	strcpy(cartas->linhas[3].linha, "|                   |");
	strcpy(cartas->linhas[4].linha, "|       *    XXXXX  |");
	strcpy(cartas->linhas[5].linha, "|     *****  X   X  |");
	strcpy(cartas->linhas[6].linha, "|    ******* X   X  |");
	strcpy(cartas->linhas[7].linha, "|    *     *   XXX  |");
	strcpy(cartas->linhas[8].linha, "|    **   **   X    |");
	strcpy(cartas->linhas[9].linha, "|  ***** ****  X    |");
	strcpy(cartas->linhas[10].linha, "| ************ X    |");
	strcpy(cartas->linhas[11].linha, "|**************X    |");
	strcpy(cartas->linhas[12].linha, "|**************X    |");
	strcpy(cartas->linhas[13].linha, "|**************X    |");
	strcpy(cartas->linhas[14].linha, "|**************X    |");
	strcpy(cartas->linhas[15].linha, "+-------------------+");
	strcpy(cartas->linhas[16].linha, "|ATK:3000 |DEF:1500 |");
	strcpy(cartas->linhas[17].linha, "+-------------------+");

	strcpy(cartas->nome_menu[0].linha, "|# - Satella           |");
	cartas++;
	strcpy(cartas->linhas[0].linha, "+-------------------+");
	strcpy(cartas->linhas[1].linha, "|                   |");
	strcpy(cartas->linhas[2].linha, "|                   |");
	strcpy(cartas->linhas[3].linha, "|  XX          XX   |");
	strcpy(cartas->linhas[4].linha, "|   XX        XX    |");
	strcpy(cartas->linhas[5].linha, "|     X      XX     |");
	strcpy(cartas->linhas[6].linha, "|      XX   XX      |");
	strcpy(cartas->linhas[7].linha, "|       XX XX       |");
	strcpy(cartas->linhas[8].linha, "|        XXX        |");
	strcpy(cartas->linhas[9].linha, "|        X XX       |");
	strcpy(cartas->linhas[10].linha, "|       X    XX     |");
	strcpy(cartas->linhas[11].linha, "|     XX      XX    |");
	strcpy(cartas->linhas[12].linha, "|    XX        XX   |");
	strcpy(cartas->linhas[13].linha, "|  XX           XX  |");
	strcpy(cartas->linhas[14].linha, "|                   |");
	strcpy(cartas->linhas[15].linha, "|                   |");
	strcpy(cartas->linhas[16].linha, "|                   |");
	strcpy(cartas->linhas[17].linha, "+-------------------+");
	cartas++;

	cartas->tipo = 1;
	cartas->atk = 3200;
	cartas->def = 1300;
	strcpy(cartas->nome, "MINDSTEALER");
	strcpy(cartas->desc, "O polvo malígno controlador de mentes");
	strcpy(cartas->linhas[0].linha, "+-------------------+");
	strcpy(cartas->linhas[1].linha, "|    MINDSTEALER    |");
	strcpy(cartas->linhas[2].linha, "+-------------------+");
	strcpy(cartas->linhas[3].linha, "|    (XXXXXXXXX)    |");
	strcpy(cartas->linhas[4].linha, "|   (XXXXXXXXXXX)   |");
	strcpy(cartas->linhas[5].linha, "|  (XX(0)XXX(0)XX)  |");
	strcpy(cartas->linhas[6].linha, "|  (^^XXXXXXXXX^^)  |");
	strcpy(cartas->linhas[7].linha, "|   ((XXX^X^XXX))   |");
	strcpy(cartas->linhas[8].linha, "|    (^XX^ ^XX^)    |");
	strcpy(cartas->linhas[9].linha, "|      (X___X)      |");
	strcpy(cartas->linhas[10].linha, "|      (X(|)X)      |");
	strcpy(cartas->linhas[11].linha, "|    (( ((|)) ))    |");
	strcpy(cartas->linhas[12].linha, "| ((((((((|)))))))) |");
	strcpy(cartas->linhas[13].linha, "|((((( (((|))) )))))|");
	strcpy(cartas->linhas[14].linha, "|((((  (((|)))  ))))|");
	strcpy(cartas->linhas[15].linha, "+---------+---------+");
	strcpy(cartas->linhas[16].linha, "|ATK:3200 |DEF:1300 |");
	strcpy(cartas->linhas[17].linha, "+---------+---------+");

	strcpy(cartas->nome_menu[0].linha, "|# - MindStealer       |");
	cartas++;

	cartas->tipo = 1;
	cartas->atk = 4100;
	cartas->def = 1900;
	strcpy(cartas->nome, "RHAEGON");
	strcpy(cartas->desc, "O cavaleiro real");
	strcpy(cartas->linhas[0].linha, "+-------------------+");
	strcpy(cartas->linhas[1].linha, "|      RHAEGON      |");
	strcpy(cartas->linhas[2].linha, "+-------------------+");
	strcpy(cartas->linhas[3].linha, "|  @@@@@       /\\   |");
	strcpy(cartas->linhas[4].linha, "| @@@@@@@      ||   |");
	strcpy(cartas->linhas[5].linha, "|@@@@@ V|      ||   |");
	strcpy(cartas->linhas[6].linha, "|@@@@@   \\    ||    |");
	strcpy(cartas->linhas[7].linha, "|@@@@@  _|     ||   |");
	strcpy(cartas->linhas[8].linha, "|@@@@/__/      ||   |");
	strcpy(cartas->linhas[9].linha, "|@@@XXXXXX     ||   |");
	strcpy(cartas->linhas[10].linha, "|@XXXXXXXXX  ====== |");
	strcpy(cartas->linhas[11].linha, "|XXXXXXXXXXX  XXXX  |");
	strcpy(cartas->linhas[12].linha, "|XXXXXXXXXXXXXXXX   |");
	strcpy(cartas->linhas[13].linha, "|XXXXXXXX XXXXX^^   |");
	strcpy(cartas->linhas[14].linha, "|XXXXXXXX XXXXX^^   |");
	strcpy(cartas->linhas[15].linha, "+---------+---------+");
	strcpy(cartas->linhas[16].linha, "|ATK:4100 | DEF:1900|");
	strcpy(cartas->linhas[17].linha, "+---------+---------+");

	strcpy(cartas->nome_menu[0].linha, "|# - Rhaegon            |");
	cartas++;

	cartas->tipo = 1;
	cartas->atk = 3200;
	cartas->def = 1300;
	strcpy(cartas->nome, "KYRA");
	strcpy(cartas->desc, "A poderosa líder arqueira");
	strcpy(cartas->linhas[0].linha, "+-------------------+");
	strcpy(cartas->linhas[1].linha, "|        KYRA       |");
	strcpy(cartas->linhas[2].linha, "+-------------------+");
	strcpy(cartas->linhas[3].linha, "|                   |");
	strcpy(cartas->linhas[4].linha, "|   (     @@@@@   ^ |");
	strcpy(cartas->linhas[5].linha, "|  ((    @@--@@@  | |");
	strcpy(cartas->linhas[6].linha, "| ((    @@@ 0@@@@ | |");
	strcpy(cartas->linhas[7].linha, "|((XX   @@XXX@@@@XX |");
	strcpy(cartas->linhas[8].linha, "|(((XXXXXXXXXXXXXX| |");
	strcpy(cartas->linhas[9].linha, "| ((    XXXXXX@@  | |");
	strcpy(cartas->linhas[10].linha, "|  ((    XXXX@@     |");
	strcpy(cartas->linhas[11].linha, "|   (   XXXXXXX     |");
	strcpy(cartas->linhas[12].linha, "|      XXX  XXX     |");
	strcpy(cartas->linhas[13].linha, "|    XXXX    XXXX   |");
	strcpy(cartas->linhas[14].linha, "|    XXXX    XXXX   |");
	strcpy(cartas->linhas[15].linha, "+---------+---------+");
	strcpy(cartas->linhas[16].linha, "|ATK:3200 | DEF:1300|");
	strcpy(cartas->linhas[17].linha, "+---------+---------+");

	strcpy(cartas->nome_menu[0].linha, "|# - Kyra              |");

	cartas++;

	cartas->tipo = 1;
	cartas->atk = 3900;
	cartas->def = 1000;
	strcpy(cartas->nome, "GOLYAN");
	strcpy(cartas->desc, "O temido viking");
	strcpy(cartas->linhas[0].linha, "+-------------------+");
	strcpy(cartas->linhas[1].linha, "|      GOLYAN       |");
	strcpy(cartas->linhas[2].linha, "+-------------------+");
	strcpy(cartas->linhas[3].linha, "|           @@@@    |");
	strcpy(cartas->linhas[4].linha, "|         @@@@@@@@  |");
	strcpy(cartas->linhas[5].linha, "|        @@(- -)@@  |");
	strcpy(cartas->linhas[6].linha, "|       @@@@@_@@@@  |");
	strcpy(cartas->linhas[7].linha, "|  HH   @@@@@@@@@@  |");
	strcpy(cartas->linhas[8].linha, "| HHHH  XX@@@@@XX   |");
	strcpy(cartas->linhas[9].linha, "| HHHH XXXX@@@@@XX  |");
	strcpy(cartas->linhas[10].linha, "| HHHHXXHHHHHHHHHHXH|");
	strcpy(cartas->linhas[11].linha, "| HHHH   XX@@@@@XX  |");
	strcpy(cartas->linhas[12].linha, "| HHHH   XXX@@@@XX  |");
	strcpy(cartas->linhas[13].linha, "|  HH  XXXXX @@XXXX |");
	strcpy(cartas->linhas[14].linha, "|  HH  XXXXX @@XXXX |");
	strcpy(cartas->linhas[15].linha, "+---------+---------+");
	strcpy(cartas->linhas[16].linha, "|ATK:3900 | DEF:1000|");
	strcpy(cartas->linhas[17].linha, "+---------+---------+");

	strcpy(cartas->nome_menu[0].linha, "|# - Golyan            |");
}
// Função que cria as telas de início do jogo.
void CriarTelas(TELA *telas) {


	strcpy(telas->linhas[0].linha, "+--------------------------------------------------------------------------------------------------------+");
	strcpy(telas->linhas[1].linha, "|                                                                                                        |");
	strcpy(telas->linhas[2].linha, "|                                                                                                        |");
	strcpy(telas->linhas[3].linha, "|                                                                                                        |");
	strcpy(telas->linhas[4].linha, "|                 _______  _______  _______  _______    _______  _______  _______  _______               |");
	strcpy(telas->linhas[5].linha, "|                (       )(  ____ \\(  ____ \\(  ___  )  (  ____ \\(  ___  )(       )(  ____ \\              |");
	strcpy(telas->linhas[6].linha, "|                + () () ++ (    \\/+ (    \\/+ (   ) +  + (    \\/+ (   ) ++ () () ++ (    \\/              |");
	strcpy(telas->linhas[7].linha, "|                | ++ ++ || (__    | +      | (___) |  | +      | (___) || ++ ++ || (__                  |");
	strcpy(telas->linhas[8].linha, "|                | |(_)| ||  __)   | | ____ |  ___  |  | | ____ |  ___  || |(_)| ||  __)                 |");
	strcpy(telas->linhas[9].linha, "|                | +   + || (      | + \\_  )| (   ) |  | + \\_  )| (   ) || +   + || (                    |");
	strcpy(telas->linhas[10].linha, "|                | )   ( ++ (____/\\+ (___) ++ )   ( |  + (___) ++ )   ( || )   ( ++ (____/\\              |");
	strcpy(telas->linhas[11].linha, "|                +/     \\+(_______/(_______)+/     \\+  (_______)+/     \\++/     \\+(_______/              |");
	strcpy(telas->linhas[12].linha, "|                                                                                                        |");
	strcpy(telas->linhas[13].linha, "|                                      +--------------------+                                            |");
	strcpy(telas->linhas[14].linha, "|                                      |   DIGITE INICIAR   |                                            |");
	strcpy(telas->linhas[15].linha, "|                                      +--------------------+                                            |");
	strcpy(telas->linhas[16].linha, "|                                                                                                        |");
	strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");
	telas++;
	strcpy(telas->linhas[0].linha, "+--------------------------------------------------------------------------------------------------------+");
	strcpy(telas->linhas[1].linha, "|                                                                                                        |");
	strcpy(telas->linhas[2].linha, "|                                          +-----------+                                                 |");
	strcpy(telas->linhas[3].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[4].linha, "|                                          |   DUELO   |                                                 |");
	strcpy(telas->linhas[5].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[6].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[7].linha, "|                                          |   DECK    |                                                 |");
	strcpy(telas->linhas[8].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[9].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[10].linha, "|                                          |   OPÇÕES  |                                                 |");
	strcpy(telas->linhas[11].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[12].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[13].linha, "|                                          |   AJUDA   |                                                 |");
	strcpy(telas->linhas[14].linha, "|                                          |           |                                                 |");
	strcpy(telas->linhas[15].linha, "|                                          +-----------+                                                 |");
	strcpy(telas->linhas[16].linha, "|                                                                                                        |");
	strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");
	telas++;
	strcpy(telas->linhas[0].linha, "+--------------------------------------------------------------------------------------------------------+");
	strcpy(telas->linhas[1].linha, "|                                                                                                        |");
	strcpy(telas->linhas[2].linha, "|     +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+    |");
	strcpy(telas->linhas[3].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[4].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[5].linha, "|     |  JOHN   | |  DRAKE  | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[6].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[7].linha, "|     +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+    |");
	strcpy(telas->linhas[8].linha, "|                                                                                                        |");
	strcpy(telas->linhas[9].linha, "|     +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+    |");
	strcpy(telas->linhas[10].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[11].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[12].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[13].linha, "|     |         | |         | |         | |         | |         | |         | |         | |         |    |");
	strcpy(telas->linhas[14].linha, "|     +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+ +---------+    |");
	strcpy(telas->linhas[15].linha, "|                                                                                                        |");
	strcpy(telas->linhas[16].linha, "|                                                                                                        |");
	strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");
}
//Função que cria os gráficos dos inimigos que serão enfrentados no jogo.
void CriarInimigos(INIMIGO *inimigos) {

	strcpy(inimigos->nome, "John");
	strcpy(inimigos->linhas[0].linha, "+------------------------+");
	strcpy(inimigos->linhas[1].linha, "|                        |");
	strcpy(inimigos->linhas[2].linha, "|      XXXXXXXXXXXXXX    |");
	strcpy(inimigos->linhas[3].linha, "|   XXX XXXXXXXXXX  XX   |");
	strcpy(inimigos->linhas[4].linha, "|  X  XXXXX   XX XX  X   |");
	strcpy(inimigos->linhas[5].linha, "|  X  X    X X    X   X  |");
	strcpy(inimigos->linhas[6].linha, "|  XXXX  XX   XX  XXXXX  |");
	strcpy(inimigos->linhas[7].linha, "|     X  XX   XX  XX     |");
	strcpy(inimigos->linhas[8].linha, "|     X           X      |");
	strcpy(inimigos->linhas[9].linha, "|     XX  XXXXX   X      |");
	strcpy(inimigos->linhas[10].linha, "|   XXXXXXXXXXXXXXXXXX   |");
	strcpy(inimigos->linhas[11].linha, "|  XX                XX  |");
	strcpy(inimigos->linhas[12].linha, "|  X                  X  |");
	strcpy(inimigos->linhas[13].linha, "|  XX                 X  |");
	strcpy(inimigos->linhas[14].linha, "+------------------------+");
	strcpy(inimigos->linhas[15].linha, "| JOHN    |RANK:*****    |");
	strcpy(inimigos->linhas[16].linha, "+------------------------+");
}
// Desenhando a Mesa do Jogo.
void DesenharMesa(int *mesa_aliada, int *mesa_inimiga, int *mao_jogador, CARTA *cartas, HUD *hud) {

	int count_hud, i, j;
	count_hud = 0;
	i = 0;
	j = 0;
	// Inicio e fim das structs
	int *mesa_aliada_fim = mesa_aliada + 4;
	int *mesa_inimiga_inicio = mesa_inimiga;
	int *mesa_inimiga_fim = mesa_inimiga + 4;
	int *mesa_aliada_inicio = mesa_aliada;
	int *mao_jogador_fim = mao_jogador + 4;
	int *mao_jogador_inicio = mao_jogador;
	CARTA *cartas_inicio = cartas;
	// Limpa o console
	system("cls");
	// Desenha as primeira 17 linhas da mesa, parte do inimigo
	for (j = 0; j <= TAM_CARTA; j++) {
		for (mesa_inimiga; mesa_inimiga <= mesa_inimiga_fim; mesa_inimiga++) {

			if (*mesa_inimiga != -1) {
				cartas += *mesa_inimiga;

				printf("%s", cartas->linhas[j].linha);
				printf(" ");
			}
			else {
				cartas = cartas_inicio;
				cartas++;
				printf("%s", cartas->linhas[j].linha);
				printf(" ");
			}
			cartas = cartas_inicio;
		}
		mesa_inimiga = mesa_inimiga_inicio;
		printf("%s", (*hud).linhas[count_hud].linha);
		count_hud++;
		printf("\n");
	}
	// Desenha mais 17 linhas, parte do campo do jogador
	for (j = 0; j <= TAM_CARTA; j++) {
		for (mesa_aliada; mesa_aliada <= mesa_aliada_fim; mesa_aliada++) {
			if (*mesa_aliada != -1) {
				cartas += *mesa_aliada;
				printf("%s", cartas->linhas[j].linha);
				printf(" ");
			}
			else {
				cartas = cartas_inicio;
				cartas++;
				printf("%s", cartas->linhas[j].linha);
				printf(" ");
			}
			cartas = cartas_inicio;
		}
		mesa_aliada = mesa_aliada_inicio;
		printf("%s", hud->linhas[count_hud].linha);
		count_hud++;
		printf("\n");
	}
	hud += 2;
	//Desenha 3 linhas para separar o campo do jogo das cartas na mão do jogador
	for (i = 0; i <= 3; i++) {

		printf("%s\n", hud->linhas[i].linha);
	}
	// Desenha mais 17 linhas para as cartas na mão do jogador
	for (j = 0; j <= TAM_CARTA; j++) {
		for (mao_jogador; mao_jogador <= mao_jogador_fim; mao_jogador++) {
			if (*mao_jogador != -1) {
				cartas += *mao_jogador;
				printf("%s", cartas->linhas[j].linha);
				printf(" ");
			}
			else {
				cartas = cartas_inicio;
				cartas++;
				printf("%s", cartas->linhas[j].linha);
				printf(" ");
			}
			cartas = cartas_inicio;
		}
		mao_jogador = mao_jogador_inicio;

		printf("\n");
	}
	count_hud = 0 ;
}
// Função responsável por exibir as escolhas na HUD.
void DesenharMenu(int escolha, HUD *hud) {

	switch (escolha) {


	case 0:
		hud++;
		strcpy(hud->linhas[26].linha, "|                      |");
		strcpy(hud->linhas[27].linha, "|1 - Sumonar Carta     |");
		strcpy(hud->linhas[28].linha, "|                      |");
		strcpy(hud->linhas[29].linha, "|2 - Trocar Modo       |");
		strcpy(hud->linhas[30].linha, "|                      |");
		strcpy(hud->linhas[31].linha, "|3 - Surrender         |");
		strcpy(hud->linhas[32].linha, "|                      |");
		strcpy(hud->linhas[33].linha, "|                      |");
		strcpy(hud->linhas[34].linha, "|                      |");
		break;


	}
}
// Função responsável por desenhar as telas do jogo.
void DesenharTela(int tel, TELA *telas) {

	int i;
	system("cls");

	telas += tel;
	for (i = 0; i <= 17; i++) {

		printf("%s\n", telas->linhas[i].linha);
	}
}
// Função responsável por limpar o menu da HUD.
void LimparMenu(HUD *hud) {
	int i;
	hud++;
	for (i = 26; i <= 34; i++) {

		strcpy(hud->linhas[i].linha, "|                      |");


	}
}
// Muda as telas do jogo baseado nos comando dados pelo jogador
void MudarTela(int comand, int *tela_num, int *atgame, int*entrada) {

	switch (*tela_num) {

	case 0:

		switch (comand) {


		case 1:
			*tela_num = 1;
			break;

		case 2:
			*entrada = 0;
			break;


		default:
			printf("Comando inválido.\n");
			break;



		}

		break;

	case 1:

		switch (comand) {

		case 1:
			*tela_num = 2;
			break;

		case 2:
			*entrada = 0;
			break;


		default:
			printf("Comando inválido\n");
			break;



		}

		break;

	case 2:


		switch (comand) {

		case 1:

			*atgame = 1;
			*entrada = 0;

			break;

		case 2:
			*entrada = 0;
			break;


		default:
			printf("Comando inválido\n");
			break;



		}



		break;

	}
}
// Desenha a nova tela se a mesma tiver mudado
void TransicaoTela(int tela_num, int *tela_anterior, int *tela_criar, TELA *telas) {

	if (!*tela_criar || *tela_anterior != tela_num) {

		system("cls");

		DesenharTela(tela_num, telas);

		*tela_anterior = tela_num;

		*tela_criar = 1;

	}
}
// Inicia todas as variaveis referentes ao inicio do jogo
void IniciarJogo(int *game_ini, int *mesa_aliada, int *mesa_inimiga, int *mao_jogador) {

	if (!*game_ini) {

		*mesa_aliada = -1;
		mesa_aliada++;
		*mesa_aliada = -1;
		mesa_aliada++;
		*mesa_aliada = -1;
		mesa_aliada++;
		*mesa_aliada = -1;
		mesa_aliada++;
		*mesa_aliada = -1;


		*mesa_inimiga = 2;
		mesa_inimiga++;
		*mesa_inimiga = 3;
		mesa_inimiga++;
		*mesa_inimiga = -1;
		mesa_inimiga++;
		*mesa_inimiga = -1;
		mesa_inimiga++;
		*mesa_inimiga = -1;

		*mao_jogador = 0;
		mao_jogador++;
		*mao_jogador = 5;
		mao_jogador++;
		*mao_jogador = 2;
		mao_jogador++;
		*mao_jogador = 3;
		mao_jogador++;
		*mao_jogador = 4;

		*game_ini = 1;

	}
}
// Muda a hud de opçoes de acordo com os comandos do jogador
void MudarHud(int comand, HUD *hud, CARTA *cartas, int *atgame, int *menu, int *mao_jogador) {

	int i;

	LINHA temp_nome[5];

	CARTA *cartas_inicio = cartas;

	switch (*menu) {

	case 0:
		switch (comand) {


		case 1:
			// Sumonar
			LimparMenu(hud);

			hud++;
			for (i = 0; i <= 4; i++) {

				cartas += *mao_jogador;

				strcpy(temp_nome[i].linha, cartas->nome_menu[0].linha);

				temp_nome[i].linha[1] = 49 + i ;


				strcpy(hud->linhas[26 + i].linha, temp_nome[i].linha);

				cartas = cartas_inicio;
				mao_jogador++;

			}
			strcpy(hud->linhas[31].linha, "|                      |");
			strcpy(hud->linhas[32].linha, "|6 - Voltar            |");

			*menu = 1;

			// trocar menu
			break;
		case 2:
			*atgame = 0;

			break;


		default:
			printf("Comando inválido\n");
			break;



		}

		break;

	case 1:
		switch (comand) {

		case 6:
			DesenharMenu(0, hud);
			*menu = 0;
			break;


		}


		break;


	}
}