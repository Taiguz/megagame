#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "megalib.h"
#define HUD_INICIO 26
#define HUD_FIM 34
#define TAM_DECK 20


void AI(int *mesa_aliada, int *mesa_inimiga, int *mao_inimiga, CARTA *carta, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, int *vida) {

    int cont = 0;
    int jogoucarta = 0;
    //le as cartas que estao na mao
    for (int n = 0; n < 4; n++) {

        for (int m = 0; m < 4; m++) {
            //verifica as cartas que estao na mesa aliada e compara com uma das cartas que possui na mao
            if (carta[mao_inimiga[n]].atk > temp_mesa_jogador[m].atk) {



                if (carta[mao_inimiga[n]].atk > temp_mesa_jogador[m].def) {
                    cont++;

                    break;
                }

            } else if (carta[mao_inimiga[n]].atk < temp_mesa_jogador[m].atk) {
                continue;
            }
        }
        //se uma carta atender ao condicional, sumona as carta
        if (cont > 0) {


            SumonarCarta(0, n, mesa_inimiga, mao_inimiga, temp_mesa_inimigo, carta);
            //sumonar carta que atende aos condicionais

            jogoucarta = 1;

        } else {
            SumonarCarta(0, n, mesa_inimiga, mao_inimiga, temp_mesa_inimigo, carta);
            //sumona uma carta em modo de defesa

            jogoucarta = 1;
        }

        //se atender ao condicional, quebra o looping
        if (jogoucarta == 1) {

            break;
            //se nao atender ao condicional. continua o looping para outra carta da mao
        } else {

            continue;
        }
    }
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {

            if (mesa_aliada[n] != -1) { //tem carta do adversário na mesa
                //se a carta estiver no modo ataque
                if (temp_mesa_jogador[m].modo == 0) {
                    //verifica se vale a pena atacar ou colocar em modo defesa
                    if (temp_mesa_jogador[n].atk < temp_mesa_inimigo[m].atk && temp_mesa_jogador[n].modo != 1 ) {

                        vida[1] -= AtacarCarta(m, n, temp_mesa_inimigo, temp_mesa_jogador, mesa_inimiga, mesa_aliada, vida );
                        //atacar carta que atende aos condicionais
                        // Com qual carta ?

                    } else {

                        TrocarModo(m, temp_mesa_inimigo);
                        //modo de defesa
                        //Que carta ?

                    }

                    //verifica se vale a pena atacar ou colocar em modo defesa
                    if (temp_mesa_jogador[n].atk > temp_mesa_inimigo[n].atk && temp_mesa_jogador[n].modo != 1) {

                        TrocarModo(m, temp_mesa_inimigo);
                        //modo de defesa
                        // Que carta ?
                    } else {

                        vida[1] -= AtacarCarta(m, n, temp_mesa_inimigo, temp_mesa_jogador, mesa_inimiga, mesa_aliada, vida );
                        // Com que carta ?
                        //atacar carta que atende aos condicionais
                    }

                    //verifica se vale a pena atacar a carta em modo defesa ou colocar em modo de defesa
                    if (temp_mesa_jogador[n].def < temp_mesa_inimigo[n].atk && temp_mesa_jogador[n].modo != 0 ) {

                        vida[1] -= AtacarCarta(m, n, temp_mesa_inimigo, temp_mesa_jogador, mesa_inimiga, mesa_aliada, vida);
                        //atacar carta que atende aos condicionais

                    } else {

                        TrocarModo(m, temp_mesa_inimigo);
                        //modo de defesa
                    }

                    //verifica se vale a pena atacar a carta em modo defesa ou colocar em modo de defesa
                    if (temp_mesa_jogador[n].def > temp_mesa_inimigo[n].atk && temp_mesa_jogador[n].modo != 0 ) {

                        TrocarModo(m, temp_mesa_inimigo);
                        //modo de defesa
                    } else {

                        vida[1] -= AtacarCarta(m, n, temp_mesa_inimigo, temp_mesa_jogador, mesa_inimiga, mesa_aliada, vida);
                        //atacar carta que atende aos condicionais
                    }


                }
                //se a carta estiver no modo ataque
                if (temp_mesa_inimigo[m].modo == 1) {
                    //verifica se vale a pena trocar a carta para o modo ataque

                    if (temp_mesa_jogador[n].atk < temp_mesa_inimigo[m].atk && temp_mesa_jogador[n].modo != 1 ) {

                        if (temp_mesa_jogador[n].def < temp_mesa_inimigo[m].atk) {
                            TrocarModo(m, temp_mesa_inimigo);
                            //modo de ataque
                        }
                    }
                }

            }
            /*
            else {//atacar vida do adversário

            }
            */
        }
    }
}

// Criando função responsável por receber comandos "in-game" (digitados no console).
int Comando(char *copy, int *atgame, int *jogo_on) {

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

    switch (comando) {


    case 55:
        *atgame = 0;
        *jogo_on = 0;
        break;

    }

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
    strcpy(hud->linhas[0].linha, "                                                    +---------+                                               ");
    strcpy(hud->linhas[1].linha, "+---------------------------------------------------+ SUA MÃO +---------------------------------------------+ ");
    strcpy(hud->linhas[2].linha, "                                                    +---------+                                               ");

    hud ++;

    strcpy(hud->linhas[0].linha, "   +----------------+");
    strcpy(hud->linhas[1].linha, "   | PONTOS DE VIDA |");
    strcpy(hud->linhas[2].linha, "+--+----------------+--+");
    strcpy(hud->linhas[3].linha, "|          VOCÊ        |");
    strcpy(hud->linhas[4].linha, "|                      |");
    strcpy(hud->linhas[5].linha, "+----------------------+");
    strcpy(hud->linhas[6].linha, "|                      |");
    strcpy(hud->linhas[7].linha, "+----------------------+");
    strcpy(hud->linhas[8].linha, "|        INIMIGO       |");
    strcpy(hud->linhas[9].linha, "|                      |");
    strcpy(hud->linhas[10].linha, "+----------------------+");

}
//Função que irá criar todas as cartas do jogo.
void CriarCartas(CARTA *cartas) {



    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|                   |");
    strcpy(cartas->linhas[2].linha, "|                   |");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|                   |");
    strcpy(cartas->linhas[5].linha, "|                   |");
    strcpy(cartas->linhas[6].linha, "|                   |");
    strcpy(cartas->linhas[7].linha, "|                   |");
    strcpy(cartas->linhas[8].linha, "|                   |");
    strcpy(cartas->linhas[9].linha, "|                   |");
    strcpy(cartas->linhas[10].linha, "|                   |");
    strcpy(cartas->linhas[11].linha, "|                   |");
    strcpy(cartas->linhas[12].linha, "|                   |");
    strcpy(cartas->linhas[13].linha, "|                   |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "|                   |");
    strcpy(cartas->linhas[16].linha, "|                   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");
    cartas++;

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
    strcpy(cartas->linhas[16].linha, "| ATK:3000| DEF:1500|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");
    strcpy(cartas->nome_menu[0].linha, "|# - Satella           |");



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
    strcpy(cartas->linhas[16].linha, "| ATK:3200| DEF:1300|");
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
    strcpy(cartas->linhas[6].linha, "|@@@@@   \\     ||   |");
    strcpy(cartas->linhas[7].linha, "|@@@@@  _|     ||   |");
    strcpy(cartas->linhas[8].linha, "|@@@@/__/      ||   |");
    strcpy(cartas->linhas[9].linha, "|@@@XXXXXX     ||   |");
    strcpy(cartas->linhas[10].linha, "|@XXXXXXXXX  ====== |");
    strcpy(cartas->linhas[11].linha, "|XXXXXXXXXXX  XXXX  |");
    strcpy(cartas->linhas[12].linha, "|XXXXXXXXXXXXXXXX   |");
    strcpy(cartas->linhas[13].linha, "|XXXXXXXX XXXXX^^   |");
    strcpy(cartas->linhas[14].linha, "|XXXXXXXX XXXXX^^   |");
    strcpy(cartas->linhas[15].linha, "+---------+---------+");
    strcpy(cartas->linhas[16].linha, "| ATK:4100| DEF:1900|");
    strcpy(cartas->linhas[17].linha, "+---------+---------+");

    strcpy(cartas->nome_menu[0].linha, "|# - Rhaegon           |");
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
    strcpy(cartas->linhas[16].linha, "| ATK:3200| DEF:1300|");
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
    strcpy(cartas->linhas[16].linha, "| ATK:3900| DEF:1000|");
    strcpy(cartas->linhas[17].linha, "+---------+---------+");

    strcpy(cartas->nome_menu[0].linha, "|# - Golyan            |");
}
// Função que cria as telas de início do jogo.
void CriarTelas(TELA *telas) {
// 109 largura 34 altura

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


    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                                                                                           |");
    strcpy(telas->linhas[3].linha, "|                                                                                                           |");
    strcpy(telas->linhas[4].linha, "|                                                                                                           |");
    strcpy(telas->linhas[5].linha, "|                                                                                                           |");
    strcpy(telas->linhas[6].linha, "|                                                                                                           |");
    strcpy(telas->linhas[7].linha, "|                                                                                                           |");
    strcpy(telas->linhas[8].linha, "|                                                                                                           |");
    strcpy(telas->linhas[9].linha, "|                                                                                                           |");
    strcpy(telas->linhas[10].linha, "|                                                                                                           |");
    strcpy(telas->linhas[11].linha, "|                                                                                                           |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|                                                                                                           |");
    strcpy(telas->linhas[14].linha, "|                                                                                                           |");
    strcpy(telas->linhas[15].linha, "|        __      __                           _____                   _                         _           |");
    strcpy(telas->linhas[16].linha, "|        \\ \\    / /                          / ____+                 + +                       + +          |");
    strcpy(telas->linhas[17].linha, "|         \\ \\  / /    ___     ___    ___    + +  __    __ _   _ __   | +__     ___    _   _    | |          |");
    strcpy(telas->linhas[18].linha, "|          \\ \\/ /    / _ \\   / __+  / _ \\   | | +_ +  / _` + + '_ \\  | '_ \\   / _ \\  + + + +   | |          |");
    strcpy(telas->linhas[19].linha, "|           \\  /    + (_) + + (__  +  __/   + +__+ | + (_+ | | + + + | + + + + (_) + + +_+ |   +_+          |");
    strcpy(telas->linhas[20].linha, "|            \\/      \\___/   \\___+  \\___+    \\_____+  \\__,_+ +_+ +_+ +_+ +_+  \\___/   \\__,_+   (_)          |");
    strcpy(telas->linhas[21].linha, "|                                                                                                           |");
    strcpy(telas->linhas[22].linha, "|                                                                                                           |");
    strcpy(telas->linhas[23].linha, "|                                                                                                           |");
    strcpy(telas->linhas[24].linha, "|                                                                                                           |");
    strcpy(telas->linhas[25].linha, "|                                                                                                           |");
    strcpy(telas->linhas[26].linha, "|                                                                                                           |");
    strcpy(telas->linhas[27].linha, "|                                                                                                           |");
    strcpy(telas->linhas[28].linha, "|                                                                                                           |");
    strcpy(telas->linhas[29].linha, "|                                                                                                           |");
    strcpy(telas->linhas[30].linha, "|                                                                                                           |");
    strcpy(telas->linhas[31].linha, "|                                                                                                           |");
    strcpy(telas->linhas[32].linha, "|                                                                                                           |");
    strcpy(telas->linhas[33].linha, "|                                                                                                           |");
    strcpy(telas->linhas[34].linha, "|                                                                                                           |");
    strcpy(telas->linhas[35].linha, "|                                                                                                           |");
    strcpy(telas->linhas[36].linha, "|                                                                                                           |");
    strcpy(telas->linhas[37].linha, "+-----------------------------------------------------------------------------------------------------------+");


    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                                                                                           |");
    strcpy(telas->linhas[3].linha, "|                                                                                                           |");
    strcpy(telas->linhas[4].linha, "|                                                                                                           |");
    strcpy(telas->linhas[5].linha, "|                                                                                                           |");
    strcpy(telas->linhas[6].linha, "|                                                                                                           |");
    strcpy(telas->linhas[7].linha, "|                                                                                                           |");
    strcpy(telas->linhas[8].linha, "|                                                                                                           |");
    strcpy(telas->linhas[9].linha, "|                                                                                                           |");
    strcpy(telas->linhas[10].linha, "|                                                                                                           |");
    strcpy(telas->linhas[11].linha, "|                                                                                                           |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|                                                                                                           |");
    strcpy(telas->linhas[14].linha, "|                _____                                 ____                            _                    |");
    strcpy(telas->linhas[15].linha, "|               / ____+                               / __ \\                          + +                   |");
    strcpy(telas->linhas[16].linha, "|              + +  __    __ _   _ __ ___     ___    + +  + + __   __   ___   _ __    | |                   |");
    strcpy(telas->linhas[17].linha, "|              | | +_ +  / _` + + '_ ` _ \\   / _ \\   | |  | | \\ \\ / /  / _ \\ + '__+   | |                   |");
    strcpy(telas->linhas[18].linha, "|              + +__+ | + (_+ | | + + + + + +  __/   + +__+ +  \\ V /  +  __/ | +      +_+                   |");
    strcpy(telas->linhas[19].linha, "|               \\_____+  \\__,_+ +_+ +_+ +_+  \\___+    \\____/    \\_/    \\___+ +_+      (_)                   |");
    strcpy(telas->linhas[20].linha, "|                                                                                                           |");
    strcpy(telas->linhas[21].linha, "|                                                                                                           |");
    strcpy(telas->linhas[22].linha, "|                                                                                                           |");
    strcpy(telas->linhas[23].linha, "|                                                                                                           |");
    strcpy(telas->linhas[24].linha, "|                                                                                                           |");
    strcpy(telas->linhas[25].linha, "|                                                                                                           |");
    strcpy(telas->linhas[26].linha, "|                                                                                                           |");
    strcpy(telas->linhas[27].linha, "|                                                                                                           |");
    strcpy(telas->linhas[28].linha, "|                                                                                                           |");
    strcpy(telas->linhas[29].linha, "|                                                                                                           |");
    strcpy(telas->linhas[30].linha, "|                                                                                                           |");
    strcpy(telas->linhas[31].linha, "|                                                                                                           |");
    strcpy(telas->linhas[32].linha, "|                                                                                                           |");
    strcpy(telas->linhas[33].linha, "|                                                                                                           |");
    strcpy(telas->linhas[34].linha, "|                                                                                                           |");
    strcpy(telas->linhas[35].linha, "|                                                                                                           |");
    strcpy(telas->linhas[36].linha, "|                                                                                                           |");
    strcpy(telas->linhas[37].linha, "|                                                                                                           |");
    strcpy(telas->linhas[38].linha, "+-----------------------------------------------------------------------------------------------------------+");

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
void DesenharMesa(int *mesa_aliada, int *mesa_inimiga, int *mao_jogador, CARTA *cartas, HUD *hud, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, int *menu) {



    int count_hud, i, j;
    count_hud = 0;
    int count_hud3 = 3;
    i = 0;
    j = 0;
    // Inicio e fim das structs
    /*
    int *mesa_aliada_fim = mesa_aliada + 3;
    int *mesa_inimiga_inicio = mesa_inimiga;
    int *mesa_inimiga_fim = mesa_inimiga + 3;
    int *mesa_aliada_inicio = mesa_aliada;
    int *mao_jogador_fim = mao_jogador + 3;
    int *mao_jogador_inicio = mao_jogador;
    */
    CARTA *cartas_inicio = cartas;
    // Segunda HUD
    hud++;
    // Limpa o console

    LimparTela(SIS);

    // Desenha as primeira 17 linhas da mesa, parte do inimigo
    for (j = 0; j <= TAM_CARTA; j++) {

        for (i = 0; i < TAM_PADRAO; i++) {


            if (mesa_inimiga[i] != -1) {


                if ( j == 16) {

                    printf("%s", (temp_mesa_inimigo + i)->inf.linha);
                    printf(" ");

                } else {

                    cartas += mesa_inimiga[i];

                    printf("%s", cartas->linhas[j].linha);
                    printf(" ");

                }
            }
            else {


                cartas = cartas_inicio;
                //cartas++;
                printf("%s", cartas->linhas[j].linha);
                printf(" ");

            }
            cartas = cartas_inicio;

        }


        //mesa_inimiga = mesa_inimiga_inicio;

        printf("%s", hud->linhas[count_hud].linha);

        count_hud++;
        printf("\n");
    }
    // Desenha mais 17 linhas, parte do campo do jogador
    for (j = 0; j <= TAM_CARTA; j++) {

        for (i = 0; i < TAM_PADRAO; i++) {
            if (mesa_aliada[i] != -1) {

                if ( j == 16) {

                    printf("%s", (temp_mesa_jogador + i)->inf.linha);
                    printf(" ");

                } else {

                    cartas += mesa_aliada[i];
                    printf("%s", cartas->linhas[j].linha);
                    printf(" ");
                }

            }
            else {
                cartas = cartas_inicio;
                //cartas++;
                printf("%s", cartas->linhas[j].linha);
                printf(" ");
            }
            cartas = cartas_inicio;
        }
        //mesa_aliada = mesa_aliada_inicio;
        printf("%s", hud->linhas[count_hud].linha);
        count_hud++;
        printf("\n");
    }
    hud ++;
    //Desenha 3 linhas para separar o campo do jogo das cartas na mão do jogador
    for (i = 0; i < 3; i++) {

        printf("%s", hud->linhas[i].linha);
        printf("%s\n", (hud + 1)->linhas[i].linha);
    }
    hud++;
    // Desenha mais 17 linhas para as cartas na mão do jogador
    for (j = 0; j <= TAM_CARTA; j++) {
        for (i = 0; i < TAM_PADRAO; i++) {
            if (mao_jogador[i] != -1) {
                cartas += mao_jogador[i];
                printf("%s", cartas->linhas[j].linha);
                printf(" ");
            }
            else {
                cartas = cartas_inicio;
                //cartas++;
                printf("%s", cartas->linhas[j].linha);
                printf(" ");
            }
            cartas = cartas_inicio;
        }
        //mao_jogador = mao_jogador_inicio;
        /*
        if (count_hud2 <= 10) {
            printf("%s", (hud + 1)->linhas[i + 5].linha );
            count_hud2++;

        }
        */
        // Desenha a HUD que mostra a vida

        if (count_hud3 <= 11) {

            printf("%s", hud->linhas[j + 3].linha);

            count_hud3++;

        }


        printf("\n");
    }

    for (i = 0; i < TAM_PADRAO; i++) {

        printf("|%i| ", mesa_inimiga[i]);


    }
    printf("\n");
    printf("MENU -> %i\n", *menu );
    for (i = 0; i < TAM_PADRAO; i++) {

        printf("|%i| ", mesa_aliada[i]);


    }
    printf("\n");


    count_hud = 0 ;
}
// Função responsável por exibir as escolhas na HUD.
void DesenharMenu(int escolha, HUD * hud, CARTA * cartas, int *mao_jogador, int *mesa_aliada, int *mesa_inimiga, int *menu, TEMP_CARTA *temp_carta) {

    hud++;
    int i;
    char temp_nome[25];
    LimparMenu(hud);

    switch (escolha) {


    case 0:

        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Sumonar Carta     |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|2 - Trocar Modo       |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|3 - Passar Vez        |");
        strcpy(hud->linhas[32].linha, "|                      |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");
        break;

    case 1 :
        //CARTA *cartas_inicio = cartas;



        for (i = 0; i <= 4; i++) {

            if (*(mao_jogador + i) != -1) {

                //cartas += *mao_jogador;

                strcpy(temp_nome, (cartas + * (mao_jogador + i))->nome_menu[0].linha);

                temp_nome[1] = 49 + i ;


                strcpy(hud->linhas[26 + i].linha, temp_nome);

            }

            //cartas = cartas_inicio;
            //mao_jogador++;

        }
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6 - Voltar            |");




        break;

    case 2:


        for (i = 0; i < TAM_PADRAO; i++) {

            if (*(mesa_aliada + i) != -1) {

                //cartas += *mesa_aliada;

                strcpy(temp_nome, (cartas + * (mesa_aliada + i))->nome_menu[0].linha);

                temp_nome[1] = 49 + i ;


                strcpy(hud->linhas[26 + i].linha, temp_nome);
            }
            //cartas = cartas_inicio;


        }
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6 - Voltar            |");



        break;

    case 3:

        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Atacar            |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|2 - Trocar Modo       |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|3 - Passar Vez        |");
        strcpy(hud->linhas[32].linha, "|                      |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");

        break;

    case 4:

        for (i = 0; i < TAM_PADRAO; i++) {

            if (*(mesa_aliada + i) != -1) {

                //cartas += *mesa_aliada;
                if (temp_carta[i].modo == 0) {

                    strcpy(temp_nome, (cartas + * (mesa_aliada + i))->nome_menu[0].linha);

                    temp_nome[1] = 49 + i ;


                    strcpy(hud->linhas[26 + i].linha, temp_nome);
                }
            }
            //cartas = cartas_inicio;


        }
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6 - Voltar            |");



        break;

    case 5:

        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Modo de Ataque    |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|2 - Modo de Defesa    |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|3 - Voltar            |");
        strcpy(hud->linhas[32].linha, "|                      |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");

        break;

    case 6:

        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Passar Vez        |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|                      |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|                      |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");

        break;

    case 7:


        for (i = 0; i < TAM_PADRAO; i++) {

            if (*(mesa_aliada + i) != -1) {

                //cartas += *mesa_aliada;


                strcpy(temp_nome, (cartas + * (mesa_aliada + i))->nome_menu[0].linha);

                temp_nome[1] = 49 + i ;


                strcpy(hud->linhas[26 + i].linha, temp_nome);


            }
            //cartas = cartas_inicio;


        }
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6 - Voltar            |");



        break;
    case 8:


        for (i = 0; i < TAM_PADRAO; i++) {



            if (mesa_inimiga[i] != -1) {


                strcpy(temp_nome, (cartas + * (mesa_inimiga + i))->nome_menu[0].linha);

                temp_nome[1] = 49 + i ;


                strcpy(hud->linhas[26 + i].linha, temp_nome);
            }



        }
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6 - Voltar            |");
        break;

    case 9:
        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Atacar Vida       |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|                      |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6- Voltar             |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");
        break;

    }

}
int ContaAlgarismos(int num) {

    int count = 0;

    int temp = num;

    while (temp > 0) {

        temp = temp / 10;



        count++;

    }


    return count;
}

void AtualizarPlacar(HUD *hud, int *vida, int *atgame, int *entrada, int *tela_num) {

    int i;

    int vida_jogador = vida[0];
    int vida_inimigo = vida[1];

    printf("vida jogador -> %i\n", vida_jogador);

    printf("vida inimigo -> %i\n", vida_inimigo);

    int tam_vidaJogador = ContaAlgarismos(vida_jogador);
    int tam_vidaInimigo = ContaAlgarismos(vida_inimigo);

    hud += 3;

    char str_jogador[10];

    char str_inimigo[10];

    sprintf(str_jogador, "%d", vida_jogador);
    sprintf(str_inimigo, "%d", vida_inimigo);

    for (i = 0; i < tam_vidaJogador; i++) {

        hud->linhas[4].linha[11 + i] = str_jogador[i];
    }

    for (i = 0; i < tam_vidaInimigo; i++) {

        hud->linhas[9].linha[11 + i] = str_inimigo[i];
    }

    if (vida_jogador <= 0) {

        *atgame = 0;
        *entrada = 1;
        *tela_num = 4;

    }
    if (vida_inimigo <= 0) {

        *atgame = 0;
        *entrada = 1;
        *tela_num = 3;
    }

}
// Função responsável por desenhar as telas do jogo.
void DesenharTela(int tel, TELA * telas) {

    int i;
    LimparTela(SIS);

    telas += tel;
    for (i = 0; i <= 17; i++) {

        printf("%s\n", telas->linhas[i].linha);
    }
}
// Função que limpa a tela do console do sistema.
void LimparTela(int sistema) {

    if (sistema) {
        system("cls");

    } else {

        system("clear");

    }
}
// Função responsável por limpar o menu da HUD.
void LimparMenu(HUD * hud) {
    int i;
    hud++;
    for (i = HUD_INICIO; i <= HUD_FIM; i++) {

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
void TransicaoTela(int tela_num, int *tela_anterior, int *tela_criar, TELA * telas) {

    if (!*tela_criar || *tela_anterior != tela_num) {

        LimparTela(SIS);

        DesenharTela(tela_num, telas);

        *tela_anterior = tela_num;

        *tela_criar = 1;

    }
}

void IniciarInimigos(INIMIGO *inimigos) {

    inimigos->deck[0] = 3;
    inimigos->deck[1] = 2;
    inimigos->deck[2] = 3;
    inimigos->deck[3] = 2;
    inimigos->deck[4] = 3;
    inimigos->deck[5] = 2;
    inimigos->deck[6] = 3;
    inimigos->deck[7] = 2;
    inimigos->deck[8] = 3;
    inimigos->deck[9] = 2;
    inimigos->deck[10] = 3;
    inimigos->deck[11] = 2;
    inimigos->deck[12] = 3;
    inimigos->deck[13] = 2;
    inimigos->deck[14] = 3;
    inimigos->deck[15] = 2;
    inimigos->deck[16] = 3;
    inimigos->deck[17] = 2;
    inimigos->deck[18] = 3;
    inimigos->deck[19] = 2;

    strcpy(inimigos->nome, "Seto Procópio");

    inimigos++;

    inimigos->deck[0] = 3;
    inimigos->deck[1] = 2;
    inimigos->deck[2] = 3;
    inimigos->deck[3] = 2;
    inimigos->deck[4] = 3;
    inimigos->deck[5] = 2;
    inimigos->deck[6] = 3;
    inimigos->deck[7] = 2;
    inimigos->deck[8] = 3;
    inimigos->deck[9] = 2;
    inimigos->deck[10] = 3;
    inimigos->deck[11] = 2;
    inimigos->deck[12] = 3;
    inimigos->deck[13] = 2;
    inimigos->deck[14] = 3;
    inimigos->deck[15] = 2;
    inimigos->deck[16] = 3;
    inimigos->deck[17] = 2;
    inimigos->deck[18] = 3;
    inimigos->deck[19] = 2;

    strcpy(inimigos->nome, "Jono");

    inimigos++;

    inimigos->deck[0] = 3;
    inimigos->deck[1] = 2;
    inimigos->deck[2] = 3;
    inimigos->deck[3] = 2;
    inimigos->deck[4] = 3;
    inimigos->deck[5] = 2;
    inimigos->deck[6] = 3;
    inimigos->deck[7] = 2;
    inimigos->deck[8] = 3;
    inimigos->deck[9] = 2;
    inimigos->deck[10] = 3;
    inimigos->deck[11] = 2;
    inimigos->deck[12] = 3;
    inimigos->deck[13] = 2;
    inimigos->deck[14] = 3;
    inimigos->deck[15] = 2;
    inimigos->deck[16] = 3;
    inimigos->deck[17] = 2;
    inimigos->deck[18] = 3;
    inimigos->deck[19] = 2;

    strcpy(inimigos->nome, "Yami Redaj");
}
void EmbaralharDecks(int *deck_jogador, INIMIGO *inimigos) {

    int temp_deck[TAM_DECK];

    int ind = 0;

    srand(time(0));

    //Embaralha as cartas do jogador
    for (int i = 0; i < TAM_DECK; i++) {

        temp_deck[i] = -1;
    }

    for (int i = 0; i < TAM_DECK; i++) {

        do  {

            ind = rand() % 21;

            printf("ind -> %i\n", ind );

            if (temp_deck[ind] == -1) {

                temp_deck[ind] = deck_jogador[i];

                break;

            }


        } while (temp_deck[ind] != -1);


    }

    for (int i = 0; i < TAM_DECK; i++) {

        *(deck_jogador + i) = temp_deck[i];

    }

    //Embaralha as cartas do inimigo escolhido

    for (int i = 0; i < TAM_DECK; i++) {

        temp_deck[i] = -1;
    }

    for (int i = 0; i < TAM_DECK; i++) {

        do  {

            ind = rand() % 21;

            if (temp_deck[ind] == -1) {

                temp_deck[ind] = inimigos->deck[i];

                break;
            }


        } while (temp_deck[ind] != -1);


    }

    for (int i = 0; i < TAM_DECK; i++) {

        inimigos->deck[i] = temp_deck[i];

    }

}
// Inicia todas as variaveis referentes ao inicio do jogo
void IniciarJogo(int *mesa_aliada, int *mesa_inimiga, int *mao_jogador, int *mao_inimiga, int *vida, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, CARTA * cartas, INIMIGO *inimigos, int *deck_jogador) {

    int i;

    mesa_aliada[0] = -1;
    mesa_aliada[1] = -1;
    mesa_aliada[2] = -1;
    mesa_aliada[3] = -1;
    mesa_aliada[4] = -1;

    mesa_inimiga[0] = -1;
    mesa_inimiga[1] = -1;
    mesa_inimiga[2] = -1;
    mesa_inimiga[3] = -1;
    mesa_inimiga[4] = -1;

    for (i = 0; i < TAM_PADRAO; i++) {

        if (mesa_aliada[i] != -1) {

            (temp_mesa_jogador + i)->modo = 0;
            (temp_mesa_jogador + i)->atk = (cartas + mesa_aliada[i])->atk;
            (temp_mesa_jogador + i)->def = (cartas + mesa_aliada[i])->def;
            strcpy( (temp_mesa_jogador + i)->inf.linha, (cartas + mesa_aliada[i])->linhas[16].linha  );
        }
        if (mesa_inimiga[i] != -1) {

            (temp_mesa_inimigo + i)->modo = 0;
            (temp_mesa_inimigo + i)->atk = (cartas + mesa_inimiga[i])->atk;
            (temp_mesa_inimigo + i)->def = (cartas + mesa_inimiga[i])->def;
            strcpy( (temp_mesa_inimigo + i)->inf.linha, (cartas + mesa_inimiga[i])->linhas[16].linha  );
        }

    }


    vida[0] = 8000;

    vida[1] = 8000;

    IniciarInimigos(inimigos);

    deck_jogador[0] = 1;
    deck_jogador[1] = 1;
    deck_jogador[2] = 1;
    deck_jogador[3] = 1;
    deck_jogador[4] = 1;
    deck_jogador[5] = 2;
    deck_jogador[6] = 3;
    deck_jogador[7] = 4;
    deck_jogador[8] = 3;
    deck_jogador[9] = 5;
    deck_jogador[10] = 2;
    deck_jogador[11] = 3;
    deck_jogador[12] = 3;
    deck_jogador[13] = 4;
    deck_jogador[14] = 2;
    deck_jogador[15] = 4;
    deck_jogador[16] = 3;
    deck_jogador[17] = 2;
    deck_jogador[18] = 3;
    deck_jogador[19] = 2;

    EmbaralharDecks(deck_jogador, inimigos);

    mao_jogador[0] = -1;
    mao_jogador[1] = -1;
    mao_jogador[2] = -1;
    mao_jogador[3] = -1;
    mao_jogador[4] = -1;

    mao_inimiga[0] = -1;
    mao_inimiga[1] = -1;
    mao_inimiga[2] = -1;
    mao_inimiga[3] = -1;
    mao_inimiga[4] = -1;

    DarCartas(1, deck_jogador, inimigos, mao_jogador, mao_inimiga);

}
void DarCartas(int inicio, int *deck_jogador, INIMIGO *inimigos, int *mao_jogador, int *mao_inimiga) {

    if (inicio) {

        mao_jogador[0] = deck_jogador[0];
        mao_jogador[1] = deck_jogador[1];
        mao_jogador[2] = deck_jogador[2];
        mao_jogador[3] = deck_jogador[3];
        mao_jogador[4] = deck_jogador[4];

        mao_inimiga[0] = inimigos->deck[0];
        mao_inimiga[1] = inimigos->deck[1];
        mao_inimiga[2] = inimigos->deck[2];
        mao_inimiga[3] = inimigos->deck[3];
        mao_inimiga[4] = inimigos->deck[4];

        deck_jogador[0] = -1;
        deck_jogador[1] = -1;
        deck_jogador[2] = -1;
        deck_jogador[3] = -1;
        deck_jogador[4] = -1;

        inimigos->deck[0] = -1;
        inimigos->deck[1] = -1;
        inimigos->deck[2] = -1;
        inimigos->deck[3] = -1;
        inimigos->deck[4] = -1;


    } else {

        // Pega uma carta do baralho e coloca na mao do jogador
        int ind = -1;

        for (int i = 0; i < 5; i++) {

            if (mao_jogador[i] == -1) {
                ind = i;
            }
        }

        if (ind != -1) {


            int ind2 = -1;

            for (int i = 0; i < TAM_DECK; i++) {

                if (deck_jogador[i] != -1) {
                    ind2 = i;
                    break;
                }

            }

            if (ind2 != -1) {

                mao_jogador[ind] = deck_jogador[ind2];
                deck_jogador[ind2] = -1;
                OrganizarMao(mao_jogador);

            } else {

                // Não há mais cartas no baralho;
            }

        }


        ind = -1;

        for (int i = 0; i < 5; i++) {

            if (mao_inimiga[i] == -1) {
                ind = i;
            }
        }

        if (ind != -1) {


            int ind2 = -1;

            for (int i = 0; i < TAM_DECK; i++) {

                if (inimigos->deck[i] != -1) {
                    ind2 = i;
                    break;
                }

            }

            if (ind2 != -1) {

                mao_inimiga[ind] = inimigos->deck[ind2];
                inimigos->deck[ind2] = -1;

            } else {

                // Não há mais cartas no baralho;
            }

        }

    }
}

void OrganizarMao(int *mao_jogador) {

    int temp[5];

    for (int i = 0; i < 5; i++) {

        temp[i] = -1;

    }

    for (int i = 0; i < 5; i++) {

        if (mao_jogador[i] != -1) {

            temp[i] = mao_jogador[i];

        }

    }
}
// Muda a hud e os elementos do jogo de acordo com os comandos do jogador

void Controle(int comand, HUD * hud, CARTA * cartas, int *atgame, int *entrada, int *tela_num, int *jogo_on, int *menu, int *mao_jogador, int *mao_inimiga, int *mesa_aliada, int *mesa_inimiga, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, int *vida, int *deck_jogador, INIMIGO *inimigos) {

    int i;
    static int mesa_aliada_escolha;
    static int mesa_inimiga_escolha;
    static int summon_escolha;
    int sum = 0;

    int sum_attack = 0;

    int mao_vazia;

    int mesa_vazia;

    LINHA temp_nome[5];

    CARTA *cartas_inicio = cartas;

    for (i = 0; i < TAM_PADRAO; i++) {

        if (mesa_aliada[i] == -1) {

            mesa_vazia++;
        }
        if (mao_jogador[i] == -1) {

            mao_vazia++;
        }

    }

    if (mao_vazia == 5 && mesa_vazia == 5) {
        LimparMenu(hud);
        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
        *menu = 6;

    }
    else if (mao_vazia == 5 && mesa_vazia != 5) {
        LimparMenu(hud);
        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
        *menu = 3;
    }

    switch (*menu) {


    case 0:

        switch (comand) {


        case 1:
            LimparMenu(hud);
            DesenharMenu(1, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 1;

            break;
        case 2:

            LimparMenu(hud);
            DesenharMenu(2, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 2;

            break;
        case 3 :
            //Passar Vez



            PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame);

            break;


        }

        break;

    case 1:


        switch (comand) {

        case 1:

            summon_escolha = comand;
            DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 5;

            break;

        case 2:
            summon_escolha = comand;
            DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 5;
            break;

        case 3:
            summon_escolha = comand;
            DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 5;
            break;

        case 4:
            summon_escolha = comand;
            DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 5;
            break;

        case 5:
            summon_escolha = comand;
            DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 5;
            break;

        case 6:

            LimparMenu(hud);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        }


        break;

    case 2:
        switch (comand) {

        case 1:

            TrocarModo(comand, temp_mesa_jogador);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;

            break;

        case 2:
            TrocarModo(comand, temp_mesa_jogador);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 3:
            TrocarModo(comand, temp_mesa_jogador);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 4:
            TrocarModo(comand, temp_mesa_jogador);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 5:
            TrocarModo(comand, temp_mesa_jogador);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 6:
            LimparMenu(hud);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        }

        break;
    case 3:

        switch (comand) {


        case 1:
            LimparMenu(hud);
            DesenharMenu(4, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 4;

            break;
        case 2:
            LimparMenu(hud);
            DesenharMenu(7, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 7;

            break;
        case 3 :
            //Passar Vez
            // passar vez
            PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame);
            break;





        }

        break;

    case 4:
        switch (comand) {

        case 1:

            mesa_aliada_escolha = comand;
            LimparMenu(hud);


            if (EstaVazio(mesa_inimiga)) {
                DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 9;

            } else {
                DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 8;

            }



            break;
        case 2:

            mesa_aliada_escolha = comand;
            LimparMenu(hud);
            if (EstaVazio(mesa_inimiga)) {
                DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 9;

            } else {
                DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 8;

            }
            break;
        case 3:

            mesa_aliada_escolha = comand;
            LimparMenu(hud);
            if (EstaVazio(mesa_inimiga)) {
                DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 9;

            } else {
                DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 8;

            }
            break;
        case 4:

            mesa_aliada_escolha = comand;
            LimparMenu(hud);
            if (EstaVazio(mesa_inimiga)) {
                DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 9;

            } else {
                DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 8;

            }
            break;
        case 5:

            mesa_aliada_escolha = comand;
            LimparMenu(hud);
            if (EstaVazio(mesa_inimiga)) {
                DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 9;

            } else {
                DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 8;

            }
            break;
        case 6:

            mesa_aliada_escolha = comand;
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;


        }

        break;

    case 5:

        switch (comand) {

        case 1:
            SumonarCarta(0, summon_escolha, mesa_aliada, mao_jogador, temp_mesa_jogador, cartas);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        case 2:
            SumonarCarta(1, summon_escolha, mesa_aliada, mao_jogador, temp_mesa_jogador, cartas);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        case 3:
            LimparMenu(hud);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        }
        break;

    case 6:

        switch (comand) {

        case 1:
            // passar vez
            PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame);

            break;

        }
        break;

    case 7:


        switch (comand) {

        case 1:

            TrocarModo(comand, temp_mesa_jogador);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;

            break;

        case 2:
            TrocarModo(comand, temp_mesa_jogador);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        case 3:
            TrocarModo(comand, temp_mesa_jogador);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        case 4:
            TrocarModo(comand, temp_mesa_jogador);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        case 5:
            TrocarModo(comand, temp_mesa_jogador);
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        case 6:
            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;
            break;

        }

        break;



    case 8:


        switch (comand) {

        case 1:

            mesa_inimiga_escolha = comand;
            vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1));
            AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
            // checar se ainda há cartas para atacar
            for (i = 0; i < TAM_PADRAO; i++) {

                if (mesa_aliada[i] != -1) {

                    sum++;
                }

            }

            for (i = 0; i < TAM_PADRAO; i++) {

                if (temp_mesa_jogador[i].atacou == 1) {

                    sum_attack++;
                }

            }
            if (sum == sum_attack) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }


            break;
        case 2:

            mesa_inimiga_escolha = comand;
            vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1));
            AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
            // checar se ainda há cartas para atacar
            for (i = 0; i < TAM_PADRAO; i++) {

                if (mesa_aliada[i] != -1) {

                    sum++;
                }

            }

            for (i = 0; i < TAM_PADRAO; i++) {

                if (temp_mesa_jogador[i].atacou == 1) {

                    sum_attack++;
                }

            }
            if (sum == sum_attack) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }

            break;
        case 3:

            mesa_inimiga_escolha = comand;
            vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1));
            AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
            // checar se ainda há cartas para atacar
            for (i = 0; i < TAM_PADRAO; i++) {

                if (mesa_aliada[i] != -1) {

                    sum++;
                }

            }

            for (i = 0; i < TAM_PADRAO; i++) {

                if (temp_mesa_jogador[i].atacou == 1) {

                    sum_attack++;
                }

            }
            if (sum == sum_attack) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }
            break;
        case 4:

            mesa_inimiga_escolha = comand;
            vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1));
            AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
            // checar se ainda há cartas para atacar
            for (i = 0; i < TAM_PADRAO; i++) {

                if (mesa_aliada[i] != -1) {

                    sum++;
                }

            }

            for (i = 0; i < TAM_PADRAO; i++) {

                if (temp_mesa_jogador[i].atacou == 1) {

                    sum_attack++;
                }

            }
            if (sum == sum_attack) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }
            break;
        case 5:

            mesa_inimiga_escolha = comand;
            vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1));
            AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
            // checar se ainda há cartas para atacar
            for (i = 0; i < TAM_PADRAO; i++) {

                if (mesa_aliada[i] != -1) {

                    sum++;
                }

            }

            for (i = 0; i < TAM_PADRAO; i++) {

                if (temp_mesa_jogador[i].atacou == 1) {

                    sum_attack++;
                }

            }
            if (sum == sum_attack) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }
            break;
        case 6:

            mesa_inimiga_escolha = comand;
            vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1));
            AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
            // checar se ainda há cartas para atacar
            for (i = 0; i < TAM_PADRAO; i++) {

                if (mesa_aliada[i] != -1) {

                    sum++;
                }

            }

            for (i = 0; i < TAM_PADRAO; i++) {

                if (temp_mesa_jogador[i].atacou == 1) {

                    sum_attack++;
                }

            }
            if (sum == sum_attack) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }
            break;


        }
        break;

    case 9:
        switch (comand) {

        case 1:
            // Atacar pontos de vida
            AtaqueDireto((vida + 1), mesa_aliada_escolha, temp_mesa_jogador);
            PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame);


            break;

        case 6:

            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;

            break;

        }

        break;
    }

}

void PassarVez(HUD *hud, int *vida, int *deck_jogador, int *mao_jogador, int *mesa_aliada, int *mesa_inimiga, int *mao_inimiga, CARTA *cartas, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, INIMIGO *inimigos, int *menu, int *entrada, int *tela_num, int *atgame) {


    //AI(mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, vida);
    DarCartas(0, deck_jogador, inimigos, mao_jogador, mao_inimiga);
    AtualizarPlacar(hud, vida, atgame, entrada, tela_num);
    LimparMenu(hud);
    DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
    *menu = 0 ;


}
void AtaqueDireto(int *vida, int indice, TEMP_CARTA *temp) {

    printf("vida antes -> %i\n", *(vida));

    printf("atk direto -> %i\n", temp[indice - 1].atk );

    *(vida) -= temp[indice - 1].atk;

    printf("vida depois -> %i\n", *(vida));
}

int EstaVazio(int *mesa) {

    int ind = 0;

    for (int i = 0; i < 5; i++) {

        if (*(mesa + i) == -1) {

            ind++;
        }

    }

    if ( ind == 5) {

        return 1;
    }
    else {

        return 0;
    }

}
// Coloca uma carta em campo e tira a mesma da mão do jogador
void SumonarCarta(int modo, int indice, int *mesa, int *mao, TEMP_CARTA *temp_carta, CARTA *cartas) {
    int i;
    int space = -1;

    for (i = (TAM_PADRAO - 1); i >= 0; i--) {

        if (mesa[i] == -1) {

            space = i;
        }

    }
    if (space != -1) {

        mesa[space] = mao[indice - 1];

        mao[indice - 1] = -1;
        if (modo == 0) {

            (temp_carta + space)->modo = 1;

        } else {

            (temp_carta + space)->modo = 0;
        }

        (temp_carta + space)->atk = (cartas + mesa[space])->atk;
        (temp_carta + space)->def = (cartas + mesa[space])->def;
        strcpy( (temp_carta + space)->inf.linha, (cartas + mesa[space])->linhas[16].linha );

        TrocarModo((space + 1), temp_carta);

    } else {

        // Sem espaço ( ALERTAR QUE NÃO HÁ ESPAÇO)

    }
}
// Ataca uma carta inimiga com a carta aliada seleciona e retorna a vida perdida
int AtacarCarta(int indice_1, int indice_2, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, int *mesa_aliada, int *mesa_inimiga, int *vida) {


    // Se for ataque do AI inverter ordem de temp_mesa_aliada com inimigo e mesa_aliada

    int num1 = indice_1 - 1;
    int num2 = indice_2 - 1;

    temp_mesa_jogador[num1].atacou = 1;
    if (temp_mesa_inimigo[num2].modo == 1) {

        int dano_carta_jogador = temp_mesa_jogador[num1].atk;
        int def_carta_inimigo  = temp_mesa_inimigo[num2].def;

        if (dano_carta_jogador > def_carta_inimigo) {

            mesa_inimiga[num2] = -1;

            return 0;
        } else {

            return 0;
        }


    }
    else if (temp_mesa_inimigo[num2].modo == 0) {

        int dano_carta_jogador = temp_mesa_jogador[num1].atk;
        int dano_carta_inimigo  = temp_mesa_inimigo[num2].atk;

        if (dano_carta_jogador > dano_carta_inimigo) {

            int diff = dano_carta_jogador - dano_carta_inimigo;

            *vida -= diff;
            mesa_inimiga[num2] = -1;
            return 0;
        }
        else if (dano_carta_jogador == dano_carta_inimigo) {

            mesa_inimiga[num2] = -1;
            mesa_aliada[num1] = -1;
            return 0;
        }
        else if (dano_carta_jogador < dano_carta_inimigo) {
            int diff = dano_carta_inimigo - dano_carta_jogador;
            mesa_aliada[num1] = -1;

            return diff;

        }
        else {

            return 0;
        }


    } else {


        return 0;
    }



    //int dano_1 = (cartas + * (mesa_aliada + (indice_1 - 1)))->atk;
    //int dano_2 = (cartas + * (mesa_inimiga + (indice_2 - 1)))->atk;
// Troca o modo da carta enviada.
}
void TrocarModo(int comand, TEMP_CARTA *temp_mesa) {

    int indice = comand - 1;

    if (temp_mesa[indice].modo == 0) {

        temp_mesa[indice].modo = 1;


        temp_mesa[indice].inf.linha[1] = 32;

        temp_mesa[indice].inf.linha[11] = 42;


    } else {


        temp_mesa[indice].modo = 0;



        temp_mesa[indice].inf.linha[1] = 42;

        temp_mesa[indice].inf.linha[11] = 32;


    }
}

