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
#define DELAY 0.8

// Função responsável por fazer a jogada da AI
void AI(int *mesa_aliada, int *mesa_inimiga, int *mao_inimiga, CARTA *carta, TEMP_CARTA *temp_mesa_jogador, TEMP_CARTA *temp_mesa_inimigo, int *vida, HUD *hud, int *mao_jogador, CARTA* cartas, int *menu) {

    // FASE DE SUMMON

    int ind = -1;

    int mag = -1;

    if (!EstaCheio(mesa_inimiga)) {// Se tem espaço na mesa do inimigo

        if (!EstaVazio(mao_inimiga)) { // Se o inimigo tem cartas para jogar


            for (int i = 0; i < 5; i++) { // Escolhe a melhor carta do tipo monstro para jogar

                if (carta[mao_inimiga[i]].tipo == 1 ) {


                    if (carta[mao_inimiga[i]].atk > carta[mao_inimiga[ind]].atk || ind == -1 ) {

                        if (carta[mao_inimiga[i]].atk > carta[mao_inimiga[ind]].def || ind == -1 ) {
                            // Índice da carta com maior ataque e defesa na mão
                            ind = i;
                        }

                    } else if (carta[mao_inimiga[i]].atk < carta[mao_inimiga[ind]].atk || ind == -1 ) {
                        if (carta[mao_inimiga[i]].atk > carta[mao_inimiga[ind]].def || ind == -1 ) {
                            // Índice da carta com maior ataque em relacao a defesa na mão
                            ind = i;
                        }

                    } else if (carta[mao_inimiga[i]].atk < carta[mao_inimiga[ind]].atk || ind == -1 ) {

                        if (carta[mao_inimiga[i]].def > carta[mao_inimiga[ind]].atk || ind == -1 ) {
                            // Índice da carta com maior defesa em relacao ao ataque na mão
                            ind = i;
                        }

                    }

                }



            }

            for (int i = 0; i < 5; i++) {// Escolhe a melhor carta do tipo mAgica para jogar


                if (carta[mao_inimiga[i]].tipo == 2 || carta[mao_inimiga[i]].tipo == 3 ) {


                    if (abs(carta[mao_inimiga[i]].atk) > abs(carta[mao_inimiga[ind]].atk) || mag == -1 ) {

                        if (abs(carta[mao_inimiga[i]].atk) > abs(carta[mao_inimiga[ind]].def) || mag == -1 ) {
                            // Índice da carta com maior ataque e defesa na mão
                            mag = i;
                        }

                    } else if (abs(carta[mao_inimiga[i]].atk) < abs(carta[mao_inimiga[ind]].atk) || mag == -1 ) {
                        if (abs(carta[mao_inimiga[i]].atk) > abs(carta[mao_inimiga[ind]].def) || mag == -1 ) {
                            // Índice da carta com maior ataque em relacao a defesa na mão
                            mag = i;
                        }

                    } else if (abs(carta[mao_inimiga[i]].atk) < abs(carta[mao_inimiga[ind]].atk) || mag == -1 ) {

                        if (abs(carta[mao_inimiga[i]].def) > abs(carta[mao_inimiga[ind]].atk) || mag == -1 ) {
                            // Índice da carta com maior defesa em relacao ao ataque na mão
                            mag = i;
                        }

                    }


                }




            }




            // Decide se usa um buff ou sumona uma carta
            if ( mag == -1 ) {

                SumonarCarta(0, (ind + 1), mesa_inimiga, mao_inimiga, temp_mesa_inimigo, carta, hud);

                DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, menu);

                sleep(DELAY);

            } else {

                if (CartasNaMesa(mesa_inimiga, 1)) {// Se tem pelo menos uma carta na mesa


                    if (carta[mao_inimiga[mag]].tipo == 2 ) {




                        if (carta[mao_inimiga[mag]].atk >= 0) {

                            int campo = -1;

                            for (int i = 0; i < 5; i++) { // Escolhe a melhor carta no campo para buffar




                                if (carta[mesa_inimiga[i]].atk > carta[mesa_inimiga[ind]].atk || campo == -1 ) {

                                    if (carta[mesa_inimiga[i]].atk > carta[mesa_inimiga[ind]].def || campo == -1 ) {
                                        // Índice da carta com maior ataque e defesa na mão
                                        campo = i;
                                    }

                                } else if (carta[mesa_inimiga[i]].atk < carta[mesa_inimiga[ind]].atk || campo == -1 ) {
                                    if (carta[mesa_inimiga[i]].atk > carta[mesa_inimiga[ind]].def || campo == -1 ) {
                                        // Índice da carta com maior ataque em relacao a defesa na mão
                                        campo = i;
                                    }

                                } else if (carta[mesa_inimiga[i]].atk < carta[mesa_inimiga[ind]].atk || campo == -1 ) {

                                    if (carta[mesa_inimiga[i]].def > carta[mesa_inimiga[ind]].atk || campo == -1 ) {
                                        // Índice da carta com maior defesa em relacao ao ataque na mão
                                        campo = i;
                                    }

                                }


                            }



                            if (campo != -1) {




                                LogSummon(carta, hud, mesa_inimiga[campo], 7);

                                Buff(mag, campo, temp_mesa_inimigo, carta, mao_inimiga);

                                DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, menu);

                                sleep(DELAY);


                            }






                            // Dar buff
                        }
                        else if (carta[mao_inimiga[mag]].atk < 0) {

                            int campo = -1;

                            for (int i = 0; i < 5; i++) { // Escolhe a melhor carta no campo do jogador para dar debuff


                                if (carta[mesa_aliada[i]].atk > carta[mesa_aliada[ind]].atk || campo == -1 ) {

                                    if (carta[mesa_aliada[i]].atk > carta[mesa_aliada[ind]].def || campo == -1 ) {
                                        // Índice da carta com maior ataque e defesa na mão
                                        campo = i;
                                    }

                                } else if (carta[mesa_aliada[i]].atk < carta[mesa_aliada[ind]].atk || campo == -1 ) {
                                    if (carta[mesa_aliada[i]].atk > carta[mesa_aliada[ind]].def || campo == -1 ) {
                                        // Índice da carta com maior ataque em relacao a defesa na mão
                                        campo = i;
                                    }

                                } else if (carta[mesa_aliada[i]].atk < carta[mesa_aliada[ind]].atk || campo == -1 ) {

                                    if (carta[mesa_aliada[i]].def > carta[mesa_aliada[ind]].atk || campo == -1 ) {
                                        // Índice da carta com maior defesa em relacao ao ataque na mão
                                        campo = i;
                                    }

                                }


                            }



                            if (campo != -1) {

                                LogSummon(carta, hud, mesa_aliada[campo], 8);

                                Buff(mag, campo, temp_mesa_jogador, carta, mao_inimiga);

                                DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, menu);

                                sleep(DELAY);


                            }




                            // Dar debuff

                        }

                    }

                    else if (carta[mao_inimiga[mag]].tipo == 3 ) {



                        if (carta[mao_inimiga[mag]].atk > 0) {

                            BuffVida((vida + 1), carta, mag , mao_inimiga);

                            LogBuff(hud, 3);

                            DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, menu);

                            sleep(DELAY);


                            // Dar buff
                        }
                        else if (carta[mao_inimiga[mag]].atk < 0) {


                            BuffVida(vida, carta, mag , mao_inimiga);

                            LogBuff(hud, 2);

                            DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, menu);

                            sleep(DELAY);

                            // Dar debuff

                        }



                    }

                } else {

                    if (ind != -1) {

                        SumonarCarta(0, (ind + 1), mesa_inimiga, mao_inimiga, temp_mesa_inimigo, carta, hud);


                        DesenharMesa(mesa_aliada, mesa_inimiga, mao_jogador, cartas, hud, temp_mesa_jogador, temp_mesa_inimigo, menu);

                        sleep(DELAY);

                    } else {

                        //Descartar uma carta
                        mao_inimiga[0] = -1;

                    }


                }


            }

        }


    }


    // 0 - modo de ataque, 1- modo de defesa, ind - indice da carta a sumonar

    // FASE DE ATAQUE OU MUDANÇA DE MODO

    for (int i = 0; i < 5; i++) {

        if (mesa_inimiga[i] != -1) { // Se tiver carta na minha mesa

            //printf("Checando carta %i\n", i );

            //Checar se o campo inimigo estA vazio;

            if (EstaVazio(mesa_aliada)) {

                LogSummon(carta, hud, mesa_inimiga[i], 9);
                // Se a mesa estiver vazia, atacar pontos de vid'a, vida[0] - vida do jogador, i - indice + 1 da carta que vai atacar, temp_mesa_inimigo - struct que contem os atributos temporArios

                AtaqueDireto(vida, (i + 1), temp_mesa_inimigo);

                //printf("Atacando direto com %i", i);

            } else {

                //Qual carta tem o ataque maior que a defesa dela

                int temp_def[5] = { 0, 0, 0, 0, 0};

                // Quais destas cartas eu tenho ataque maior

                int temp_atk[5] = { 0, 0, 0, 0, 0};


                //Checar quais eu tenho o ataque maior que a defesa
                for (int ii = 0; ii < 5; ii++) {

                    if (mesa_aliada[ii] != -1) { // Se tiver carta na mesa do jogador

                        if (temp_mesa_jogador[ii].modo == 1) { // EstA em modo de defesa

                            if (temp_mesa_inimigo[ii].atk > temp_mesa_jogador[ii].def) { // Tenho o ataque maior
                                temp_def[ii] = 1;
                            }
                        }
                    }

                }

                //Checar quais eu tenho o ataque maior que o ataque dela
                for (int ii = 0; ii < 5; ii++) {

                    if (mesa_aliada[ii] != -1) { // Se tiver carta na mesa do jogador

                        //printf("A carta %i existe !\n", ii );

                        if (temp_mesa_jogador[ii].modo == 0) {//EstA em modo de ataque

                            if (temp_mesa_inimigo[ii].atk > temp_mesa_jogador[ii].atk) {// Tenho o ataque maior
                                // printf("Tenho o ataque maior que a -> %i\n", ii );
                                //printf("Ataque -> %i\n", temp_mesa_jogador[ii].atk );
                                temp_atk[ii] = 1;
                            }

                        }

                    }

                }

                int count = 0;

                for (int ii = 0; ii < 5; ii++) { // Checar se existe carta que eu tenho o ataque maior

                    if (temp_atk[ii] == 1) { //verificando qual carta tem valor 1, que é a com maior ataque

                        count++;
                    }
                }

                if (count > 0) { // Se existir carta com valor 1, que é a com maior ataque

                    // Checar se minha carta estA em modo de ataque
                    if (temp_mesa_inimigo[i].modo != 0) {
                        //Trocar modo
                        TrocarModo((i + 1), temp_mesa_inimigo); // (i+1) - indice da carta +1
                        LogModo(temp_mesa_inimigo, carta, hud, i , mesa_inimiga);
                    }

                    // Ver dentre as que eu tenho ataque maior qual tem o maior ataque

                    int ind2 = 0;
                    for (int ii = 0; ii < 5; ii++) {

                        if (temp_atk[ii] == 1) {

                            if (ind2 == 0) {

                                ind2 = ii;

                            } else {

                                if (temp_mesa_jogador[ii].atk > temp_mesa_jogador[ind2].atk ) {
                                    ind2 = ii;
                                }

                            }

                        }

                    }

                    // Atacar a carta que tem o maior ataque
                    //printf("Atacando carta %i com %i \n", ind2, i );

                    *(vida + 1) -= AtacarCarta((i + 1), (ind2 + 1), temp_mesa_inimigo, temp_mesa_jogador, mesa_inimiga, mesa_aliada, vida, carta, hud );


                } else {// Se não existir carta com valor 1, que é a carta com maior ataque

                    int count2 = 0;
                    for (int ii = 0; ii < 5; ii++) { // Checar se existe carta que eu tenho o ataque maior que a defesa

                        if (temp_def[ii] == 1) {

                            count2++;
                        }
                    }

                    if (count2 > 0) { // Se existir carta com ataque maior que a defesa
                        //printf("Existe cartas que tenho o ataque maior que a defesa! \n");
                        if (temp_mesa_inimigo[i].modo != 0) {// Checar se minha carta estA em modo de ataque
                            //Trocar modo
                            TrocarModo((i + 1), temp_mesa_inimigo); // (i+1) - indice da carta +1
                            LogModo(temp_mesa_inimigo, carta, hud, i , mesa_inimiga);
                        }


                        // Ver dentre as que eu tenho ataque maior qual tem a maior defesa
                        int ind2 = 0;

                        for (int ii = 0; ii < 5; ii++) {

                            if (temp_def[ii] == 1) {

                                if (ind2 == 0) {

                                    ind2 = ii;
                                } else {

                                    if (temp_mesa_jogador[ii].def > temp_mesa_jogador[ind2].def ) {

                                        ind2 = ii;

                                    }

                                }

                            }

                        }

                        // Atacar a carta que tem a maior defesa

                        *(vida + 1) -= AtacarCarta((i + 1), (ind2 + 1), temp_mesa_inimigo, temp_mesa_jogador, mesa_inimiga, mesa_aliada, vida, carta, hud );

                    } else { // Se não existir carta com ataque maior que a defesa

                        //Colocar em modo de defesa
                        if (temp_mesa_inimigo[i].modo != 1) {// Checar se minha carta estA em modo de defesa
                            //Trocar modo da carta


                            TrocarModo((i + 1), temp_mesa_inimigo); // (i+1) - indice da carta +1

                            LogModo(temp_mesa_inimigo, carta, hud, i , mesa_inimiga);
                        }


                    }


                }


            }


        }


    }

}

// Função que retorna true se há no mínimo a quantidade passada na variavel quant
int CartasNaMesa(int *mesa, int quant) {

    int ind = 0;

    for (int i = 0; i < 5; i++) {

        if (*(mesa + i) != -1) {

            ind++;
        }

    }

    if ( ind >= quant) {

        return 1;
    }
    else {

        return 0;
    }


}

// Criando função responsAvel por receber comandos "in-game" (digitados no console).
int Comando(char *copy, int *atgame, int *jogo_on, int *mao_jogador) {

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

    case 1997513:

        mao_jogador[0] = 61;

        break;
    case 1996762:

        mao_jogador[0] = 9;

        break;
    case 1997343:

        mao_jogador[0] = 63;

        break;
    case 1997394:

        mao_jogador[0] = 54;

        break;
    case 1997530:

        mao_jogador[0] = 51;

        break;

    }

    return comando;

}

// Desenhando a HUD do jogo.
void CriarHUD(HUD * hud) {
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
    strcpy(hud->linhas[0].linha, "               +-------+");
    strcpy(hud->linhas[1].linha, "               | CAMPO |");
    strcpy(hud->linhas[2].linha, "+--------------+-------+------------+");
    strcpy(hud->linhas[3].linha, "|               NORMAL              |");
    strcpy(hud->linhas[4].linha, "+-----------------------------------+");
    strcpy(hud->linhas[5].linha, "              +-------+");
    strcpy(hud->linhas[6].linha, "              |  LOG  |");
    strcpy(hud->linhas[7].linha, "+-------------+-------+------------+");
    strcpy(hud->linhas[8].linha, "|                                  |");
    strcpy(hud->linhas[9].linha, "|                                  |");
    strcpy(hud->linhas[10].linha, "|                                  |");
    strcpy(hud->linhas[11].linha, "|                                  |");
    strcpy(hud->linhas[12].linha, "|                                  |");
    strcpy(hud->linhas[13].linha, "|                                  |");
    strcpy(hud->linhas[14].linha, "|                                  |");
    strcpy(hud->linhas[15].linha, "|                                  |");
    strcpy(hud->linhas[16].linha, "|                                  |");
    strcpy(hud->linhas[17].linha, "|                                  |");
    strcpy(hud->linhas[18].linha, "|                                  |");
    strcpy(hud->linhas[19].linha, "|                                  |");
    strcpy(hud->linhas[20].linha, "|                                  |");
    strcpy(hud->linhas[21].linha, "|                                  |");
    strcpy(hud->linhas[22].linha, "+----------------------------------+");
    strcpy(hud->linhas[23].linha, "      +----------+      ");
    strcpy(hud->linhas[24].linha, "      |   MENU   |      ");
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

// Função que reanrranja os valores de log tirando o último e jogando os outros para cima.
void ReaLog(HUD * hud) {

    hud++;

    for (int i = 0; i < 14; i++) {

        strcpy(hud->linhas[8 + i].linha, hud->linhas[9 + i].linha);
    }

}
// Função que escreve no log sobre as ações das cartas conforme a escolha passada pelo parâmetro choice.
void LogSummon(CARTA * cartas, HUD * hud, int indice, int choice) {

    // Rearranjar Log
    ReaLog(hud);

    hud++;


    strcpy(hud->linhas[21].linha, (cartas + indice)->nome_menu[choice].linha);

}
// Função que escreve no log sobre aumento nos atributos de vida de acordo com a escolha da variavel choice.
void LogBuff(HUD * hud, int choice ) {



    ReaLog(hud);

    hud++;


    switch (choice) {

    case 1:
        strcpy(hud->linhas[21].linha     , "| O jogador aumentou a própria vida|");
        break;
    case 2:
        strcpy(hud->linhas[21].linha     , "| O jogador teve a vida reduzida   |");
        break;
    case 3:
        strcpy(hud->linhas[21].linha     , "| O inimigo aumentou a própria vida|");
        break;

    case 4:
        strcpy(hud->linhas[21].linha     , "| O inimigo teve a vida reduzida   |");
        break;

    }

}

//Função que irA criar todas as cartas do jogo.
void CriarCartas(CARTA * cartas) {



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
    strcpy(cartas->nome_menu[10].linha, "|               |           |                    |");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1800;
    cartas->def = 3000;
    strcpy(cartas->nome, "Golyan");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Golyan foi sumonado              |");
    strcpy(cartas->nome_menu[2].linha, "| Golyan em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| Golyan em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| Golyan foi destruido             |");
    strcpy(cartas->nome_menu[5].linha, "| Golyan atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| Golyan foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| Golyan recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| Golyan foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| Golyan atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| Golyan        |  MONSTRO  |          1800/3000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Golyan            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      GOLYAN       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|           @@@@    |");
    strcpy(cartas->linhas[4].linha, "|         @@@@@@@@  |");
    strcpy(cartas->linhas[5].linha, "|        @@(º º)@@@ |");
    strcpy(cartas->linhas[6].linha, "|       @@@@@_@@@@  |");
    strcpy(cartas->linhas[7].linha, "|  HH   @@@@@@@@@@  |");
    strcpy(cartas->linhas[8].linha, "| HHHH  XX@@@@@XX   |");
    strcpy(cartas->linhas[9].linha, "| HHHH XXXX@@@@@XX  |");
    strcpy(cartas->linhas[10].linha, "| HHHHXXHHHHHHHHHHXH|");
    strcpy(cartas->linhas[11].linha, "| HHHH   XX@@@@@XX  |");
    strcpy(cartas->linhas[12].linha, "| HHHH   XXX@@@@XX  |");
    strcpy(cartas->linhas[13].linha, "|  HH  XXXXX @@XXXX |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+---------+---------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1800| DEF:3000|");
    strcpy(cartas->linhas[17].linha, "+---------+---------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2800;
    cartas->def = 1900;
    strcpy(cartas->nome, "Haegon");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Haegon foi sumonado              |");
    strcpy(cartas->nome_menu[2].linha, "| Haegon em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| Haegon em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| Haegon foi destruido             |");
    strcpy(cartas->nome_menu[5].linha, "| Haegon atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| Haegon foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| Haegon recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| Haegon foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| Haegon atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| Haegon        |  MONSTRO  |          2800/1900 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Haegon            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      HAEGON       |");
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
    strcpy(cartas->linhas[14].linha, "|XXXXXXX   XXX      |");
    strcpy(cartas->linhas[15].linha, "+---------+---------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2800| DEF:1900|");
    strcpy(cartas->linhas[17].linha, "+---------+---------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1800;
    cartas->def = 1300;
    strcpy(cartas->nome, "Kyra");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Kyra foi sumonada                |");
    strcpy(cartas->nome_menu[2].linha, "| Kyra em modo de defesa           |");
    strcpy(cartas->nome_menu[3].linha, "| Kyra em modo de ataque           |");
    strcpy(cartas->nome_menu[4].linha, "| Kyra foi destruida               |");
    strcpy(cartas->nome_menu[5].linha, "| Kyra atacou                      |");
    strcpy(cartas->nome_menu[6].linha, "| Kyra foi atacado                 |");
    strcpy(cartas->nome_menu[7].linha, "| Kyra recebeu um buff             |");
    strcpy(cartas->nome_menu[8].linha, "| Kyra foi alvo de debuff          |");
    strcpy(cartas->nome_menu[9].linha, "| Kyra atacou diretamente          |");
    strcpy(cartas->nome_menu[10].linha, "| Kyra          |  MONSTRO  |          1800/1300 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Kyra              |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|        KYRA       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|   (     @@@@@   ^ |");
    strcpy(cartas->linhas[5].linha, "|  ((    @@--@@@  | |");
    strcpy(cartas->linhas[6].linha, "| ((    @@@ °@@@@ | |");
    strcpy(cartas->linhas[7].linha, "|((XX   @@XXX@@@@XX |");
    strcpy(cartas->linhas[8].linha, "|(((XXXXXXXXXXXXXX| |");
    strcpy(cartas->linhas[9].linha, "| ((    XXXXXX@@  | |");
    strcpy(cartas->linhas[10].linha, "|  ((    XXXX@@     |");
    strcpy(cartas->linhas[11].linha, "|   (   XXXXXXX     |");
    strcpy(cartas->linhas[12].linha, "|      XXX  XXX     |");
    strcpy(cartas->linhas[13].linha, "|    XXXX    XXXX   |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+---------+---------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1800| DEF:1300|");
    strcpy(cartas->linhas[17].linha, "+---------+---------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2100;
    cartas->def = 1800;
    strcpy(cartas->nome, "Ymidas");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Ymidas foi sumonado              |");
    strcpy(cartas->nome_menu[2].linha, "| Ymidas em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| Ymidas em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| Ymidas foi destruido             |");
    strcpy(cartas->nome_menu[5].linha, "| Ymidas atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| Ymidas foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| Ymidas recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| Ymidas foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| Ymidas atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| Ymidas        |  MONSTRO  |          2100/1800 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Ymidas            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       YMIDAS      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|   /\\              |");
    strcpy(cartas->linhas[4].linha, "|  /\\/              |");
    strcpy(cartas->linhas[5].linha, "|\\ \\/    @@@@       |");
    strcpy(cartas->linhas[6].linha, "|\\\\/\\   @@@@@@      |");
    strcpy(cartas->linhas[7].linha, "|\\/\\s\\ @@@@@@@      |");
    strcpy(cartas->linhas[8].linha, "|/\\s\\s\\@@@@@@@@     |");
    strcpy(cartas->linhas[9].linha, "|  \\s\\s\\@@@@@@@@    |");
    strcpy(cartas->linhas[10].linha, "|  *\\s\\s\\@@@@@@@**  |");
    strcpy(cartas->linhas[11].linha, "|****\\s\\s\\*@@@******|");
    strcpy(cartas->linhas[12].linha, "|*****\\s\\s\\*@*******|");
    strcpy(cartas->linhas[13].linha, "|******\\s\\s\\********|");
    strcpy(cartas->linhas[14].linha, "|*******\\s\\s\\*******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2100| DEF:1800|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1500;
    cartas->def = 2200;
    strcpy(cartas->nome, "Spear Soldier");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Spear Soldier foi sumonado       |");
    strcpy(cartas->nome_menu[2].linha, "| Spear Soldier em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Spear Soldier em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Spear Soldier foi destruido      |");
    strcpy(cartas->nome_menu[5].linha, "| Spear Soldier atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Spear Soldier foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Spear Soldier recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Spear Soldier foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Spear Soldier atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Spear Soldier |  MONSTRO  |          1500/2200 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Spear Soldier     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   SPEAR SOLDIER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|\\                  |");
    strcpy(cartas->linhas[5].linha, "|\\\\    $$$$$        |");
    strcpy(cartas->linhas[6].linha, "| \\@  $$º º$$       |");
    strcpy(cartas->linhas[7].linha, "|  @@ $$ - /SSSSS\\  |");
    strcpy(cartas->linhas[8].linha, "|  @@\\ @@/SSSSSSSSS\\|");
    strcpy(cartas->linhas[9].linha, "|  @@\\\\@|SSSSSSSSSSS|");
    strcpy(cartas->linhas[10].linha, "|   @@\\\\|SSSSSSSSSSS|");
    strcpy(cartas->linhas[11].linha, "|    |@\\\\\\SSSSSSSSS/|");
    strcpy(cartas->linhas[12].linha, "|    | @\\\\@\\SSSSS/  |");
    strcpy(cartas->linhas[13].linha, "|    | @@\\\\@@ \\     |");
    strcpy(cartas->linhas[14].linha, "|   / @@@ \\\\@@@\\    |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1500| DEF:2200|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1500;
    cartas->def = 1000;
    strcpy(cartas->nome, "Sylpher");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Sylpher foi sumonado             |");
    strcpy(cartas->nome_menu[2].linha, "| Sylpher em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Sylpher em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Sylpher foi destruido            |");
    strcpy(cartas->nome_menu[5].linha, "| Sylpher atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Sylpher foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Sylpher recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Sylpher foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Sylpher atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Sylpher       |  MONSTRO  |          1500/1000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Sylpher           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      SYLPHER      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|   _/**********\\   |");
    strcpy(cartas->linhas[4].linha, "|  /**@@@@@@@@***\\  |");
    strcpy(cartas->linhas[5].linha, "| /**@@ º   º @***| |");
    strcpy(cartas->linhas[6].linha, "||** C| - c - @***| |");
    strcpy(cartas->linhas[7].linha, "| \\*  @@  -  @@***| |");
    strcpy(cartas->linhas[8].linha, "|  \\*@@@@@@@@@@***| |");
    strcpy(cartas->linhas[9].linha, "|  _**@@@@@@@@****\\_|");
    strcpy(cartas->linhas[10].linha, "| /***@@@@@@@*******|");
    strcpy(cartas->linhas[11].linha, "|/*****@@@@@********|");
    strcpy(cartas->linhas[12].linha, "|******@@@@@********|");
    strcpy(cartas->linhas[13].linha, "|*******@@@*********|");
    strcpy(cartas->linhas[14].linha, "|*******@*|*********|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1500| DEF:1000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2100;
    cartas->def = 2000;
    strcpy(cartas->nome, "Samurai Jin");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Samurai Jin foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Samurai Jin em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Samurai Jin em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Samurai Jin foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Samurai Jin atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Samurai Jin foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Samurai Jin recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Samurai Jin foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Samurai Jin atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Samurai Jin   |  MONSTRO  |          2100/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Samurai Jin       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SAMURAI JIN    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|  @@    @@@        |");
    strcpy(cartas->linhas[5].linha, "| @@@/@ @@@@@      /|");
    strcpy(cartas->linhas[6].linha, "| @ \\@@@@@@ u|    //|");
    strcpy(cartas->linhas[7].linha, "|     @@@    \\   // |");
    strcpy(cartas->linhas[8].linha, "|      @@ __-/  //  |");
    strcpy(cartas->linhas[9].linha, "|     __|  |   //   |");
    strcpy(cartas->linhas[10].linha, "|   /****\\/*\\ //    |");
    strcpy(cartas->linhas[11].linha, "|  /******\\**//     |");
    strcpy(cartas->linhas[12].linha, "| /*********/\\|     |");
    strcpy(cartas->linhas[13].linha, "|  \\*\\*______/*\\    |");
    strcpy(cartas->linhas[14].linha, "|   \\*/***//**/     |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2100| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2000;
    cartas->def = 1700;
    strcpy(cartas->nome, "Little King");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Little King foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Little King em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Little King em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Little King foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Little King atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Little King foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Little King recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Little King foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Little King atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Little King   |  MONSTRO  |          2000/1700 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Little King       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  THE LITTLE KING  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "| |\\|\\|\\|\\|         |");
    strcpy(cartas->linhas[5].linha, "| |=======|     (WW)|");
    strcpy(cartas->linhas[6].linha, "| @@@@@@@@@    (()) |");
    strcpy(cartas->linhas[7].linha, "|@@ o   o @@   //   |");
    strcpy(cartas->linhas[8].linha, "|@@@  _  @@@  //    |");
    strcpy(cartas->linhas[9].linha, "|@@@@@@@@@@@ //     |");
    strcpy(cartas->linhas[10].linha, "|@**@@@@@@@\\//      |");
    strcpy(cartas->linhas[11].linha, "|**@@@@@**\\//**     |");
    strcpy(cartas->linhas[12].linha, "|***@@@@*********   |");
    strcpy(cartas->linhas[13].linha, "|****@@************ |");
    strcpy(cartas->linhas[14].linha, "|****@**************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2000| DEF:1700|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2500;
    cartas->def = 2000;
    strcpy(cartas->nome, "Queen Yara");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Queen Yara foi sumonada          |");
    strcpy(cartas->nome_menu[2].linha, "| Queen Yara em modo de defesa     |");
    strcpy(cartas->nome_menu[3].linha, "| Queen Yara em modo de ataque     |");
    strcpy(cartas->nome_menu[4].linha, "| Queen Yara foi destruida         |");
    strcpy(cartas->nome_menu[5].linha, "| Queen Yara atacou                |");
    strcpy(cartas->nome_menu[6].linha, "| Queen Yara foi atacado           |");
    strcpy(cartas->nome_menu[7].linha, "| Queen Yara recebeu um buff       |");
    strcpy(cartas->nome_menu[8].linha, "| Queen Yara foi alvo de debuff    |");
    strcpy(cartas->nome_menu[9].linha, "| Queen Yara atacou diretamente    |");
    strcpy(cartas->nome_menu[10].linha, "| Queen Yara    |  MONSTRO  |          2500/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Queen Yara        |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     QUEEN YARA    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|  @@@@@    /| /| /||");
    strcpy(cartas->linhas[4].linha, "| @@@@@@@@ // // // |");
    strcpy(cartas->linhas[5].linha, "|@@|u u|@@@//////   |");
    strcpy(cartas->linhas[6].linha, "|@@\\_-_/ @@@//      |");
    strcpy(cartas->linhas[7].linha, "| @( )( )_@//@      |");
    strcpy(cartas->linhas[8].linha, "| //\\ \\ | //@@/\\ /\\ |");
    strcpy(cartas->linhas[9].linha, "|// |@@@@|/ @ \\@V@/ |");
    strcpy(cartas->linhas[10].linha, "|/  \\@@@@@\\   /@@/  |");
    strcpy(cartas->linhas[11].linha, "|    \\@@@@@@\\/@@@\\  |");
    strcpy(cartas->linhas[12].linha, "|     /\\@@@@@@@@/***|");
    strcpy(cartas->linhas[13].linha, "|****//**\\@@@@/*****|");
    strcpy(cartas->linhas[14].linha, "|***//**************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2500| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1100;
    cartas->def = 2000;
    strcpy(cartas->nome, "Evelynn");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Evelynn foi sumonada             |");
    strcpy(cartas->nome_menu[2].linha, "| Evelynn em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Evelynn em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Evelynn foi destruida            |");
    strcpy(cartas->nome_menu[5].linha, "| Evelynn atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Evelynn foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Evelynn recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Evelynn foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Evelynn atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Evelynn       |  MONSTRO  |          1100/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Evelynn           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      EVELYNN      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|   @@@@@@@         |");
    strcpy(cartas->linhas[4].linha, "| @@@@@@@@@@   /\\   |");
    strcpy(cartas->linhas[5].linha, "|@@ w  w @@@@ /\\/\\  |");
    strcpy(cartas->linhas[6].linha, "|@|      @@@@ \\\\//  |");
    strcpy(cartas->linhas[7].linha, "| @\\_-__@@@   / /   |");
    strcpy(cartas->linhas[8].linha, "|  _|__@@@   / /    |");
    strcpy(cartas->linhas[9].linha, "| / \\/    \\ / /   **|");
    strcpy(cartas->linhas[10].linha, "|/   \\     / /  ****|");
    strcpy(cartas->linhas[11].linha, "||  ****  / /*******|");
    strcpy(cartas->linhas[12].linha, "|********/ / *******|");
    strcpy(cartas->linhas[13].linha, "|*******************|");
    strcpy(cartas->linhas[14].linha, "|*******************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1100| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 3;
    cartas->atk = 2000;
    cartas->def = 0;
    strcpy(cartas->nome, "Flame of Life");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Flame of Life foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Flame of Life em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Flame of Life em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Flame of Life foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Flame of Life atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Flame of Life foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Flame of Life recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Flame of Life foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Flame of Life atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Flame of Life |  MAGICA   |             2000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Flame of Life     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "| THE FLAME OF LIFE |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|             ***   |");
    strcpy(cartas->linhas[4].linha, "|             ***   |");
    strcpy(cartas->linhas[5].linha, "|    @     *********|");
    strcpy(cartas->linhas[6].linha, "|   @@@    *********|");
    strcpy(cartas->linhas[7].linha, "|  @@@@@@     ***   |");
    strcpy(cartas->linhas[8].linha, "| @@OO@@@@@   ***   |");
    strcpy(cartas->linhas[9].linha, "| @@@OOO@@@@        |");
    strcpy(cartas->linhas[10].linha, "|  @@@@OO@@@@       |");
    strcpy(cartas->linhas[11].linha, "|   @@@@OO@@@    @  |");
    strcpy(cartas->linhas[12].linha, "|@   @@@@@@@   @@   |");
    strcpy(cartas->linhas[13].linha, "|@@   /@@@    @@@@@ |");
    strcpy(cartas->linhas[14].linha, "|@@@  //@\\  @@@@@@@ |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 2000 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 0;
    cartas->def = -2000;
    strcpy(cartas->nome, "Shieldbreak");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Shieldbreak foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Shieldbreak em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Shieldbreak em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Shieldbreak foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Shieldbreak atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Shieldbreak foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Shieldbreak recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Shieldbreak foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Shieldbreak atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Shieldbreak   |  MAGICA   |            0/-2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Shieldbreak       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SHIELDBREAK    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| __________***_____|");
    strcpy(cartas->linhas[4].linha, "|||       _/*_|     |");
    strcpy(cartas->linhas[5].linha, "|||  @@@@\\***\\ @@@@@|");
    strcpy(cartas->linhas[6].linha, "||| @@@@@|**/ @@@@@@|");
    strcpy(cartas->linhas[7].linha, "|||  @@@/* /@@@@@@@ |");
    strcpy(cartas->linhas[8].linha, "|||   @/* |@@@@@@@  |");
    strcpy(cartas->linhas[9].linha, "|\\\\   |* /@@@@@@@   |");
    strcpy(cartas->linhas[10].linha, "| \\\\ /* /  @@@@     |");
    strcpy(cartas->linhas[11].linha, "|  \\/* \\    @@     /|");
    strcpy(cartas->linhas[12].linha, "|  ** *\\\\         / |");
    strcpy(cartas->linhas[13].linha, "|  * ** \\\\_______/  |");
    strcpy(cartas->linhas[14].linha, "|    *              |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    DEF: 2000 v    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Instalmuscle");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Instalmuscle foi sumonada        |");
    strcpy(cartas->nome_menu[2].linha, "| Instalmuscle em modo de defesa   |");
    strcpy(cartas->nome_menu[3].linha, "| Instalmuscle em modo de ataque   |");
    strcpy(cartas->nome_menu[4].linha, "| Instalmuscle foi destruida       |");
    strcpy(cartas->nome_menu[5].linha, "| Instalmuscle atacou              |");
    strcpy(cartas->nome_menu[6].linha, "| Instalmuscle foi atacado         |");
    strcpy(cartas->nome_menu[7].linha, "| Instalmuscle recebeu um buff     |");
    strcpy(cartas->nome_menu[8].linha, "| Instalmuscle foi alvo de debuff  |");
    strcpy(cartas->nome_menu[9].linha, "| Instalmuscle atacou diretamente  |");
    strcpy(cartas->nome_menu[10].linha, "| Instalmuscle  |  MAGICA   |             1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Instalmuscle      |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    INSTAMUSCLE    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|        /Z\\        |");
    strcpy(cartas->linhas[4].linha, "|        | |        |");
    strcpy(cartas->linhas[5].linha, "|        | |        |");
    strcpy(cartas->linhas[6].linha, "|        | |        |");
    strcpy(cartas->linhas[7].linha, "|      __| |__      |");
    strcpy(cartas->linhas[8].linha, "|     / _____ \\     |");
    strcpy(cartas->linhas[9].linha, "|    / |INSTA| \\    |");
    strcpy(cartas->linhas[10].linha, "|   /@@| MUS |@@\\   |");
    strcpy(cartas->linhas[11].linha, "|  |@@@| CLE |@@@|  |");
    strcpy(cartas->linhas[12].linha, "|  |@@@|40vol|@@@|  |");
    strcpy(cartas->linhas[13].linha, "|  |@@@@@@@@@@@@@|  |");
    strcpy(cartas->linhas[14].linha, "|   \\@@@@@@@@@@@/   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|     ATK: 1500^    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1500;
    cartas->def = -2000;
    strcpy(cartas->nome, "Anciet Coin");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Anciet Coin foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Anciet Coin em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Anciet Coin em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Anciet Coin foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Anciet Coin atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Anciet Coin foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Anciet Coin recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Anciet Coin foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Anciet Coin atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Anciet Coin   |  MAGICA   |         1500/-2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Anciet Coin       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  THE ANCIET COIN  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|    ____________   |");
    strcpy(cartas->linhas[5].linha, "|   /@/ YOU  PAY \\  |");
    strcpy(cartas->linhas[6].linha, "|  /@/  _  \\  __  \\ |");
    strcpy(cartas->linhas[7].linha, "| |@| __ \\ | / _   ||");
    strcpy(cartas->linhas[8].linha, "| |@|   \\_\\|/_/__  ||");
    strcpy(cartas->linhas[9].linha, "| |@|     |||_/    ||");
    strcpy(cartas->linhas[10].linha, "| |@|     |||      ||");
    strcpy(cartas->linhas[11].linha, "|  \\@\\    //\\     / |");
    strcpy(cartas->linhas[12].linha, "|   \\@\\THE__PRICE/  |");
    strcpy(cartas->linhas[13].linha, "|                   |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|^ATK:1500|DEF:2000v|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Peacekeeper");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Peacekeeper foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Peacekeeper em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Peacekeeper em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Peacekeeper foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Peacekeeper atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Peacekeeper foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Peacekeeper recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Peacekeeper foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Peacekeeper atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Peacekeeper   |  MAGICA   |             1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Peacekeeper       |");
    strcpy(cartas->linhas[0].linha,  "+-------------------+");
    strcpy(cartas->linhas[1].linha,  "|  THE PEACEKEEPER  |");
    strcpy(cartas->linhas[2].linha,  "+-------------------+");
    strcpy(cartas->linhas[3].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[4].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[5].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[6].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[7].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[8].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[9].linha,  "|****   |S|S|   ****|");
    strcpy(cartas->linhas[10].linha, "|*    |//|I|\\\\|    *|");
    strcpy(cartas->linhas[11].linha, "|***     |||     ***|");
    strcpy(cartas->linhas[12].linha, "|***     |||     ***|");
    strcpy(cartas->linhas[13].linha, "|*****   |||   *****|");
    strcpy(cartas->linhas[14].linha, "|*******  V  *******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1500^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1000;
    cartas->def = 0;
    strcpy(cartas->nome, "Crossbow");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Crossbow foi sumonada            |");
    strcpy(cartas->nome_menu[2].linha, "| Crossbow em modo de defesa       |");
    strcpy(cartas->nome_menu[3].linha, "| Crossbow em modo de ataque       |");
    strcpy(cartas->nome_menu[4].linha, "| Crossbow foi destruida           |");
    strcpy(cartas->nome_menu[5].linha, "| Crossbow atacou                  |");
    strcpy(cartas->nome_menu[6].linha, "| Crossbow foi atacado             |");
    strcpy(cartas->nome_menu[7].linha, "| Crossbow recebeu um buff         |");
    strcpy(cartas->nome_menu[8].linha, "| Crossbow foi alvo de debuff      |");
    strcpy(cartas->nome_menu[9].linha, "| Crossbow atacou diretamente      |");
    strcpy(cartas->nome_menu[10].linha, "| Crossbow      |  MAGICA   |             1000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Crossbow          |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   THE  CROSSBOW   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|*****         *****|");
    strcpy(cartas->linhas[4].linha, "|**       ^       **|");
    strcpy(cartas->linhas[5].linha, "|       $/|\\$       |");
    strcpy(cartas->linhas[6].linha, "|    $$$$$|$$$$$    |");
    strcpy(cartas->linhas[7].linha, "|   $$$  |||  $$$   |");
    strcpy(cartas->linhas[8].linha, "|  $$$   |||   $$$  |");
    strcpy(cartas->linhas[9].linha, "|        |||        |");
    strcpy(cartas->linhas[10].linha, "|        |||        |");
    strcpy(cartas->linhas[11].linha, "|        |||        |");
    strcpy(cartas->linhas[12].linha, "|       //I\\\\       |");
    strcpy(cartas->linhas[13].linha, "|**               **|");
    strcpy(cartas->linhas[14].linha, "|*****           ***|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1000^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1000;
    cartas->def = 1000;
    strcpy(cartas->nome, "SpearShield");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| SpearShield foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| SpearShield em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| SpearShield em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| SpearShield foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| SpearShield atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| SpearShield foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| SpearShield recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| SpearShield foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| SpearShield atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| SpearShield   |  MAGICA   |          1000/1000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - SpearShield       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  SPEAR'N'SHIELD   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|**/|\\        ******|");
    strcpy(cartas->linhas[4].linha, "|*</|\\>         ****|");
    strcpy(cartas->linhas[5].linha, "|  \\|/     _________|");
    strcpy(cartas->linhas[6].linha, "|  |@|    /@/~~~~~~~|");
    strcpy(cartas->linhas[7].linha, "|  |@|   /@/~~~~~~~~|");
    strcpy(cartas->linhas[8].linha, "|  |@|  /@/~~~~~~~~~|");
    strcpy(cartas->linhas[9].linha, "|  |@|  |@|~~~/@@@\\~|");
    strcpy(cartas->linhas[10].linha, "|  |@|  |@|~~~|@@@|~|");
    strcpy(cartas->linhas[11].linha, "|  |@|  |@|~~~\\@@@/~|");
    strcpy(cartas->linhas[12].linha, "| *|@|  \\@\\~~~~~~~~~|");
    strcpy(cartas->linhas[13].linha, "|**|@|** \\@\\~~~~~~~~|");
    strcpy(cartas->linhas[14].linha, "|**|@|*** \\@\\~~~~~~~|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|^ATK:1000|DEF:1000^|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = -1500;
    cartas->def = 0;
    strcpy(cartas->nome, "SwordBreak");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| SwordBreak foi sumonada          |");
    strcpy(cartas->nome_menu[2].linha, "| SwordBreak em modo de defesa     |");
    strcpy(cartas->nome_menu[3].linha, "| SwordBreak em modo de ataque     |");
    strcpy(cartas->nome_menu[4].linha, "| SwordBreak foi destruida         |");
    strcpy(cartas->nome_menu[5].linha, "| SwordBreak atacou                |");
    strcpy(cartas->nome_menu[6].linha, "| SwordBreak foi atacado           |");
    strcpy(cartas->nome_menu[7].linha, "| SwordBreak recebeu um buff       |");
    strcpy(cartas->nome_menu[8].linha, "| SwordBreak foi alvo de debuff    |");
    strcpy(cartas->nome_menu[9].linha, "| SwordBreak atacou diretamente    |");
    strcpy(cartas->nome_menu[10].linha, "| SwordBreak    |  MAGICA   |            -1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - SwordBreak        |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SWORD'BREAK    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|** |\\''       *****|");
    strcpy(cartas->linhas[4].linha, "|** |@\\''       ****|");
    strcpy(cartas->linhas[5].linha, "|*  |@|\\''       **/|");
    strcpy(cartas->linhas[6].linha, "|   |@|@|         /@|");
    strcpy(cartas->linhas[7].linha, "|   |@|@|        /@/|");
    strcpy(cartas->linhas[8].linha, "| __|@|@|__     /@/@|");
    strcpy(cartas->linhas[9].linha, "| \\\\_\\I/_//    /@/@/|");
    strcpy(cartas->linhas[10].linha, "|    \\|/      /@/@/ |");
    strcpy(cartas->linhas[11].linha, "|    |||     /@/@/  |");
    strcpy(cartas->linhas[12].linha, "|*   |||    /@/@''**|");
    strcpy(cartas->linhas[13].linha, "|**  \\|/   /@'' ****|");
    strcpy(cartas->linhas[14].linha, "|***  V    '' ******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|     ATK: 1500v    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 800;
    cartas->def = 0;
    strcpy(cartas->nome, "Little Axe");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Little Axe foi sumonada          |");
    strcpy(cartas->nome_menu[2].linha, "| Little Axe em modo de defesa     |");
    strcpy(cartas->nome_menu[3].linha, "| Little Axe em modo de ataque     |");
    strcpy(cartas->nome_menu[4].linha, "| Little Axe foi destruida         |");
    strcpy(cartas->nome_menu[5].linha, "| Little Axe atacou                |");
    strcpy(cartas->nome_menu[6].linha, "| Little Axe foi atacado           |");
    strcpy(cartas->nome_menu[7].linha, "| Little Axe recebeu um buff       |");
    strcpy(cartas->nome_menu[8].linha, "| Little Axe foi alvo de debuff    |");
    strcpy(cartas->nome_menu[9].linha, "| Little Axe atacou diretamente    |");
    strcpy(cartas->nome_menu[10].linha, "| Little Axe    |  MAGICA   |              800/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Little Axe        |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      LIL'AXE      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|****       ___  ***|");
    strcpy(cartas->linhas[4].linha, "|**        // \\\\  **|");
    strcpy(cartas->linhas[5].linha, "|*  ___.__// ^ \\\\  *|");
    strcpy(cartas->linhas[6].linha, "|  /__/@\\_/_/I\\ \\\\  |");
    strcpy(cartas->linhas[7].linha, "|  \\__\\@/_\\ \\I/ //  |");
    strcpy(cartas->linhas[8].linha, "|     |@| \\\\ V //   |");
    strcpy(cartas->linhas[9].linha, "|     |@|  \\\\_//   *|");
    strcpy(cartas->linhas[10].linha, "|     |@|         **|");
    strcpy(cartas->linhas[11].linha, "|     |@|        ***|");
    strcpy(cartas->linhas[12].linha, "|*    |@|       ****|");
    strcpy(cartas->linhas[13].linha, "|**   \\|/     ******|");
    strcpy(cartas->linhas[14].linha, "|****       ********|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 800^    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 0;
    cartas->def = 1500;
    strcpy(cartas->nome, "The Necklace");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| The Necklace foi sumonada        |");
    strcpy(cartas->nome_menu[2].linha, "| The Necklace em modo de defesa   |");
    strcpy(cartas->nome_menu[3].linha, "| The Necklace em modo de ataque   |");
    strcpy(cartas->nome_menu[4].linha, "| The Necklace foi destruida       |");
    strcpy(cartas->nome_menu[5].linha, "| The Necklace atacou              |");
    strcpy(cartas->nome_menu[6].linha, "| The Necklace foi atacado         |");
    strcpy(cartas->nome_menu[7].linha, "| The Necklace recebeu um buff     |");
    strcpy(cartas->nome_menu[8].linha, "| The Necklace foi alvo de debuff  |");
    strcpy(cartas->nome_menu[9].linha, "| The Necklace atacou diretamente  |");
    strcpy(cartas->nome_menu[10].linha, "| The Necklace  |  MAGICA   |           800/1500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - The Necklace      |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|NECKLACE OF WISDOMS|");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|\\@@\\~~~\\___/~~~/@@/|");
    strcpy(cartas->linhas[4].linha, "|@\\@@\\~~~~~~~~~/@@/@|");
    strcpy(cartas->linhas[5].linha, "|@@\\@@\\~~~~~~~/@@/@@|");
    strcpy(cartas->linhas[6].linha, "|@@@\\@@VWWWWWV@@/@@@|");
    strcpy(cartas->linhas[7].linha, "|@@@@\\@@@@@@@@@/@@@@|");
    strcpy(cartas->linhas[8].linha, "|@@@@@\\*******/@@@@@|");
    strcpy(cartas->linhas[9].linha, "|@@@@@*\\*/|\\*/*@@@@@|");
    strcpy(cartas->linhas[10].linha, "|@@@@***//I\\\\***@@@@|");
    strcpy(cartas->linhas[11].linha, "|@@@@***\\(O)/***@@@@|");
    strcpy(cartas->linhas[12].linha, "|@@@@@***\\I/***@@@@@|");
    strcpy(cartas->linhas[13].linha, "|@@@@@@***V***@@@@@@|");
    strcpy(cartas->linhas[14].linha, "|@@@@@@@@***@@@@@@@@|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|     DEF:1500 ^    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2200;
    cartas->def = 1300;
    strcpy(cartas->nome, "Mindstealer");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Mindstealer foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Mindstealer em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Mindstealer em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Mindstealer foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Mindstealer atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Mindstealer foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Mindstealer recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Mindstealer foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Mindstealer atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Mindstealer   |  MONSTRO  |          2200/1300 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Mindstealer       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    MINDSTEALER    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|    (XXXXXXXXX)    |");
    strcpy(cartas->linhas[4].linha, "|   (XXXXXXXXXXX)   |");
    strcpy(cartas->linhas[5].linha, "|  (XX(º)XXX(º)XX)  |");
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
    strcpy(cartas->linhas[16].linha, "| ATK:2200| DEF:1300|");
    strcpy(cartas->linhas[17].linha, "+---------+---------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1900;
    cartas->def = 1200;
    strcpy(cartas->nome, "Kyatter");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Kyatter foi sumonado             |");
    strcpy(cartas->nome_menu[2].linha, "| Kyatter em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Kyatter em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Kyatter foi destruido            |");
    strcpy(cartas->nome_menu[5].linha, "| Kyatter atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Kyatter foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Kyatter recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Kyatter foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Kyatter atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Kyatter       |  MONSTRO  |          1900/1200 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Kyatter           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      KYATTER      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|               /\\  |");
    strcpy(cartas->linhas[4].linha, "|     /\\___/\\   \\ \\ |");
    strcpy(cartas->linhas[5].linha, "|    | _   _ |   \\ \\|");
    strcpy(cartas->linhas[6].linha, "|    \\   .   /_  _\\ |");
    strcpy(cartas->linhas[7].linha, "|    /\\_ - _/  \\_/  |");
    strcpy(cartas->linhas[8].linha, "|   /               |");
    strcpy(cartas->linhas[9].linha, "|___|  \\     /  ____|");
    strcpy(cartas->linhas[10].linha, "|****\\_ \\____\\ \\****|");
    strcpy(cartas->linhas[11].linha, "|******\\ \\****\\ \\***|");
    strcpy(cartas->linhas[12].linha, "|******//|\\***/|\\\\**|");
    strcpy(cartas->linhas[13].linha, "|*******************|");
    strcpy(cartas->linhas[14].linha, "|*******************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1900| DEF:1200|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1100;
    cartas->def = 800;
    strcpy(cartas->nome, "Vampyer");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Vampyer foi sumonado             |");
    strcpy(cartas->nome_menu[2].linha, "| Vampyer em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Vampyer em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Vampyer foi destruido            |");
    strcpy(cartas->nome_menu[5].linha, "| Vampyer atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Vampyer foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Vampyer recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Vampyer foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Vampyer atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Vampyer       |  MONSTRO  |           1100/800 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Vampyer           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      VAMPYER      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|  *\\             /*|");
    strcpy(cartas->linhas[4].linha, "| /***\\__/___\\__/***|");
    strcpy(cartas->linhas[5].linha, "|/*| |*** - - ***| ||");
    strcpy(cartas->linhas[6].linha, "|*/   \\**\\v v/**/   |");
    strcpy(cartas->linhas[7].linha, "|      \\*/   \\*/    |");
    strcpy(cartas->linhas[8].linha, "|                   |");
    strcpy(cartas->linhas[9].linha, "|                   |");
    strcpy(cartas->linhas[10].linha, "| *\\           /*   |");
    strcpy(cartas->linhas[11].linha, "|***\\__/___\\__/***\\ |");
    strcpy(cartas->linhas[12].linha, "|| |*** - - ***| |*\\|");
    strcpy(cartas->linhas[13].linha, "|   \\**\\v v/**/   */|");
    strcpy(cartas->linhas[14].linha, "|    \\*/   \\*/      |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1100| DEF: 800|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1800;
    cartas->def = 2500;
    strcpy(cartas->nome, "Hydra");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Hydra foi sumonada               |");
    strcpy(cartas->nome_menu[2].linha, "| Hydra em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Hydra em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Hydra foi destruida              |");
    strcpy(cartas->nome_menu[5].linha, "| Hydra atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Hydra foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Hydra recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Hydra foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Hydra atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Hydra         |  MONSTRO  |          1800/2500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Hydra             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       HYDRA       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|  _____          **|");
    strcpy(cartas->linhas[4].linha, "| /=   =\\    ___    |");
    strcpy(cartas->linhas[5].linha, "| \\\\ ¨ //   ////\\\\  |");
    strcpy(cartas->linhas[6].linha, "|  \\_y_/   ////\\\\\\\\ |");
    strcpy(cartas->linhas[7].linha, "|   ||||_/////  \\\\\\\\|");
    strcpy(cartas->linhas[8].linha, "|    \\\\\\\\\\\\//   ////|");
    strcpy(cartas->linhas[9].linha, "|     \\\\\\\\/    //// |");
    strcpy(cartas->linhas[10].linha, "|____         ////  |");
    strcpy(cartas->linhas[11].linha, "|\\\\\\\\_      _////  *|");
    strcpy(cartas->linhas[12].linha, "| \\\\\\\\//////////  **|");
    strcpy(cartas->linhas[13].linha, "|  \\\\\\\\\\\\\\\\\\\\//  ***|");
    strcpy(cartas->linhas[14].linha, "|*              ****|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1800| DEF:2500|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1500;
    cartas->def = 1000;
    strcpy(cartas->nome, "Spitz");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Spitz foi sumonado               |");
    strcpy(cartas->nome_menu[2].linha, "| Spitz em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Spitz em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Spitz foi destruido              |");
    strcpy(cartas->nome_menu[5].linha, "| Spitz atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Spitz foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Spitz recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Spitz foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Spitz atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Spitz         |  MONSTRO  |          1500/1000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Spitz             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       SPITZ       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|     |\\     /|     |");
    strcpy(cartas->linhas[5].linha, "|     | \\___/ |     |");
    strcpy(cartas->linhas[6].linha, "|     |       |     |");
    strcpy(cartas->linhas[7].linha, "|    /         \\    |");
    strcpy(cartas->linhas[8].linha, "|   / <0>   <0> \\   |");
    strcpy(cartas->linhas[9].linha, "|   \\           /   |");
    strcpy(cartas->linhas[10].linha, "|    \\\\\\  v  ///    |");
    strcpy(cartas->linhas[11].linha, "|      \\     /  (*) |");
    strcpy(cartas->linhas[12].linha, "|      |\\NNN/|  | | |");
    strcpy(cartas->linhas[13].linha, "|     /       \\ | | |");
    strcpy(cartas->linhas[14].linha, "|    /---(@)---\\| | |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1500| DEF:1000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1100;
    cartas->def = 2000;
    strcpy(cartas->nome, "Rellyon");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Rellyon foi sumonado             |");
    strcpy(cartas->nome_menu[2].linha, "| Rellyon em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Rellyon em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Rellyon foi destruido            |");
    strcpy(cartas->nome_menu[5].linha, "| Rellyon atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Rellyon foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Rellyon recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Rellyon foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Rellyon atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Rellyon       |  MONSTRO  |          1100/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Rellyon           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      RELLYON      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|     @@@@@@@@@     |");
    strcpy(cartas->linhas[4].linha, "|   @@@@@@@@@@@@    |");
    strcpy(cartas->linhas[5].linha, "|  @@@@@@@@@@@@@@   |");
    strcpy(cartas->linhas[6].linha, "| @@@@@@@@ \\ g \\__  |");
    strcpy(cartas->linhas[7].linha, "| @@@@@@@@@/     \\\\ |");
    strcpy(cartas->linhas[8].linha, "| @@@@@@@@@@@  ___/ |");
    strcpy(cartas->linhas[9].linha, "| /@@@@@@@@@\\____/  |");
    strcpy(cartas->linhas[10].linha, "|/****@@@@@@@***\\   |");
    strcpy(cartas->linhas[11].linha, "|***\\_______/****\\  |");
    strcpy(cartas->linhas[12].linha, "|***********\\ ___|  |");
    strcpy(cartas->linhas[13].linha, "|**\\*****/|_\\\\\\  /  |");
    strcpy(cartas->linhas[14].linha, "|**********//// /   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1100| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1500;
    cartas->def = 1200;
    strcpy(cartas->nome, "Strigo");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Strigo foi sumonado              |");
    strcpy(cartas->nome_menu[2].linha, "| Strigo em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| Strigo em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| Strigo foi destruido             |");
    strcpy(cartas->nome_menu[5].linha, "| Strigo atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| Strigo foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| Strigo recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| Strigo foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| Strigo atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| Strigo        |  MONSTRO  |          1500/1200 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Strigo            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       STRIGO      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|       ___         |");
    strcpy(cartas->linhas[4].linha, "|      /     \\      |");
    strcpy(cartas->linhas[5].linha, "|      | u u |      |");
    strcpy(cartas->linhas[6].linha, "|      |  v  |      |");
    strcpy(cartas->linhas[7].linha, "|       \\   /       |");
    strcpy(cartas->linhas[8].linha, "|      /    \\       |");
    strcpy(cartas->linhas[9].linha, "|     /   \\uu\\      |");
    strcpy(cartas->linhas[10].linha, "|    /     \\uu\\     |");
    strcpy(cartas->linhas[11].linha, "|    | /   /uuu\\    |");
    strcpy(cartas->linhas[12].linha, "|    |/ / /uuuu/    |");
    strcpy(cartas->linhas[13].linha, "|    | / /__/       |");
    strcpy(cartas->linhas[14].linha, "|     \\ /  | |      |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1500| DEF:1200|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1000;
    cartas->def = 1500;
    strcpy(cartas->nome, "Dailyzz");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Dailyzz foi sumonado             |");
    strcpy(cartas->nome_menu[2].linha, "| Dailyzz em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Dailyzz em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Dailyzz foi destruido            |");
    strcpy(cartas->nome_menu[5].linha, "| Dailyzz atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Dailyzz foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Dailyzz recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Dailyzz foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Dailyzz atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Dailyzz       |  MONSTRO  |          1000/1500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Dailyzz           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      DAILYZZ      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|   /\\ /\\           |");
    strcpy(cartas->linhas[5].linha, "|  /_   _\\          |");
    strcpy(cartas->linhas[6].linha, "| / e _ e \\         |");
    strcpy(cartas->linhas[7].linha, "| \\_______/         |");
    strcpy(cartas->linhas[8].linha, "|  \\\\\\|///          |");
    strcpy(cartas->linhas[9].linha, "|   /@@@@\\          |");
    strcpy(cartas->linhas[10].linha, "|  /@/@@\\@\\_______/\\|");
    strcpy(cartas->linhas[11].linha, "| /@/@@@@\\@\\@@@@@@@@|");
    strcpy(cartas->linhas[12].linha, "|/\\\\@@@@@//\\@@@@@@@||");
    strcpy(cartas->linhas[13].linha, "|    \\@\\@\\______\\@\\/|");
    strcpy(cartas->linhas[14].linha, "|   /@/ \\@\\      \\@\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1000| DEF:1500|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2100;
    cartas->def = 2000;
    strcpy(cartas->nome, "Zarboreas");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Zarboreas foi sumonado           |");
    strcpy(cartas->nome_menu[2].linha, "| Zarboreas em modo de defesa      |");
    strcpy(cartas->nome_menu[3].linha, "| Zarboreas em modo de ataque      |");
    strcpy(cartas->nome_menu[4].linha, "| Zarboreas foi destruido          |");
    strcpy(cartas->nome_menu[5].linha, "| Zarboreas atacou                 |");
    strcpy(cartas->nome_menu[6].linha, "| Zarboreas foi atacado            |");
    strcpy(cartas->nome_menu[7].linha, "| Zarboreas recebeu um buff        |");
    strcpy(cartas->nome_menu[8].linha, "| Zarboreas foi alvo de debuff     |");
    strcpy(cartas->nome_menu[9].linha, "| Zarboreas atacou diretamente     |");
    strcpy(cartas->nome_menu[10].linha, "| Zarboreas     |  MONSTRO  |          2100/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Zarboreas         |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     ZARBOREAS     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| _____\\_____/_____ |");
    strcpy(cartas->linhas[4].linha, "| \\     _   _     / |");
    strcpy(cartas->linhas[5].linha, "|  \\\\/  0   0  \\//  |");
    strcpy(cartas->linhas[6].linha, "|    \\    ^    /    |");
    strcpy(cartas->linhas[7].linha, "|     \\_  L  _/     |");
    strcpy(cartas->linhas[8].linha, "|     / \\___/ \\     |");
    strcpy(cartas->linhas[9].linha, "| ___/____ ____\\___ |");
    strcpy(cartas->linhas[10].linha, "|/        V        \\|");
    strcpy(cartas->linhas[11].linha, "|         |         |");
    strcpy(cartas->linhas[12].linha, "|      _  |  _      |");
    strcpy(cartas->linhas[13].linha, "|/  _____/ \\_____  \\|");
    strcpy(cartas->linhas[14].linha, "| \\     _____     / |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2100| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1700;
    cartas->def = 1000;
    strcpy(cartas->nome, "Emmpa");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Emmpa foi sumonada               |");
    strcpy(cartas->nome_menu[2].linha, "| Emmpa em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Emmpa em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Emmpa foi destruida              |");
    strcpy(cartas->nome_menu[5].linha, "| Emmpa atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Emmpa foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Emmpa recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Emmpa foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Emmpa atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Emmpa         |  MONSTRO  |          1700/1000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Emmpa             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       EMMPA       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|@@@@\\       *******|");
    strcpy(cartas->linhas[4].linha, "|@@@@@|        *****|");
    strcpy(cartas->linhas[5].linha, "||@@@@|           **|");
    strcpy(cartas->linhas[6].linha, "|@@@@/      /|______|");
    strcpy(cartas->linhas[7].linha, "|@@@@|      |@@@@@@@|");
    strcpy(cartas->linhas[8].linha, "||@@@@@\\    /@||@@|||");
    strcpy(cartas->linhas[9].linha, "| |@@@@|   /@@||@@|||");
    strcpy(cartas->linhas[10].linha, "||@@@@@/  /@@@@@@@@@|");
    strcpy(cartas->linhas[11].linha, "||@@@@@@@@@@@@@@@@@@|");
    strcpy(cartas->linhas[12].linha, "||@@@@@@@@@@@@/  \\@@|");
    strcpy(cartas->linhas[13].linha, "| \\@@@@@@@@@@|\\/\\/|@|");
    strcpy(cartas->linhas[14].linha, "| |@@@@@@@@@@@\\/\\/@@|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1700| DEF:1000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 3;
    cartas->atk = -1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Arrow Rain");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Arrow Rain foi sumonada          |");
    strcpy(cartas->nome_menu[2].linha, "| Arrow Rain em modo de defesa     |");
    strcpy(cartas->nome_menu[3].linha, "| Arrow Rain em modo de ataque     |");
    strcpy(cartas->nome_menu[4].linha, "| Arrow Rain foi destruida         |");
    strcpy(cartas->nome_menu[5].linha, "| Arrow Rain atacou                |");
    strcpy(cartas->nome_menu[6].linha, "| Arrow Rain foi atacado           |");
    strcpy(cartas->nome_menu[7].linha, "| Arrow Rain recebeu um buff       |");
    strcpy(cartas->nome_menu[8].linha, "| Arrow Rain foi alvo de debuff    |");
    strcpy(cartas->nome_menu[9].linha, "| Arrow Rain atacou diretamente    |");
    strcpy(cartas->nome_menu[10].linha, "| Arrow Rain    |  MAGICA   |            -1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Arrow Rain        |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     ARROW RAIN    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| YY             YY |");
    strcpy(cartas->linhas[4].linha, "| || YY YY YY YY || |");
    strcpy(cartas->linhas[5].linha, "| || || || || || || |");
    strcpy(cartas->linhas[6].linha, "| || || || || || || |");
    strcpy(cartas->linhas[7].linha, "| || || || || || || |");
    strcpy(cartas->linhas[8].linha, "| || || || || || || |");
    strcpy(cartas->linhas[9].linha, "| || || || || || || |");
    strcpy(cartas->linhas[10].linha, "| \\/ || || || || \\/ |");
    strcpy(cartas->linhas[11].linha, "|    \\/ \\/ \\/ \\/    |");
    strcpy(cartas->linhas[12].linha, "|***             ***|");
    strcpy(cartas->linhas[13].linha, "|********* *********|");
    strcpy(cartas->linhas[14].linha, "|*******************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 1500 v   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 3;
    cartas->atk = 1000;
    cartas->def = 0;
    strcpy(cartas->nome, "Flame of Life");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Flame of Life foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Flame of Life em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Flame of Life em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Flame of Life foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Flame of Life atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Flame of Life foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Flame of Life recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Flame of Life foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Flame of Life atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Flame of Life |  MAGICA   |             1000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Flame of Life     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "| THE FLAME OF LIFE |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|             ***   |");
    strcpy(cartas->linhas[4].linha, "|             ***   |");
    strcpy(cartas->linhas[5].linha, "|    @     *********|");
    strcpy(cartas->linhas[6].linha, "|   @@@    *********|");
    strcpy(cartas->linhas[7].linha, "|  @@@@@@     ***   |");
    strcpy(cartas->linhas[8].linha, "| @@OO@@@@@   ***   |");
    strcpy(cartas->linhas[9].linha, "| @@@OOO@@@@        |");
    strcpy(cartas->linhas[10].linha, "|  @@@@OO@@@@       |");
    strcpy(cartas->linhas[11].linha, "|   @@@@OO@@@    @  |");
    strcpy(cartas->linhas[12].linha, "|@   @@@@@@@   @@   |");
    strcpy(cartas->linhas[13].linha, "|@@   /@@@    @@@@@ |");
    strcpy(cartas->linhas[14].linha, "|@@@  //@\\  @@@@@@@ |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 1000 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 3;
    cartas->atk = 2000;
    cartas->def = 0;
    strcpy(cartas->nome, "Goblet of Ages");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Goblet of Ages foi sumonada      |");
    strcpy(cartas->nome_menu[2].linha, "| Goblet of Ages em modo de defesa |");
    strcpy(cartas->nome_menu[3].linha, "| Goblet of Ages em modo de ataque |");
    strcpy(cartas->nome_menu[4].linha, "| Goblet of Ages foi destruida     |");
    strcpy(cartas->nome_menu[5].linha, "| Goblet of Ages atacou            |");
    strcpy(cartas->nome_menu[6].linha, "| Goblet of Ages foi atacado       |");
    strcpy(cartas->nome_menu[7].linha, "| Goblet of Ages recebeu um buff   |");
    strcpy(cartas->nome_menu[8].linha, "| Goblet of Ages foi alvo de debuff|");
    strcpy(cartas->nome_menu[9].linha, "| Goblet of Ages atacou diretamente|");
    strcpy(cartas->nome_menu[10].linha, "| Goblet of Ages|  MAGICA   |             2000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Goblet of Ages    |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  GOBLET OF AGES   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|**               **|");
    strcpy(cartas->linhas[4].linha, "|*  @___________@  *|");
    strcpy(cartas->linhas[5].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[6].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[7].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[8].linha, "|*  \\@@@@@@@@@@@/  *|");
    strcpy(cartas->linhas[9].linha, "|**     @@@@@     **|");
    strcpy(cartas->linhas[10].linha, "|***    @@@@@    ***|");
    strcpy(cartas->linhas[11].linha, "|***    @@@@@    ***|");
    strcpy(cartas->linhas[12].linha, "|***  @@@@@@@@@  ***|");
    strcpy(cartas->linhas[13].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[14].linha, "|*                 *|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 2000 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1300;
    cartas->def = 0;
    strcpy(cartas->nome, "Flame Dagger");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Flame Dagger foi sumonada        |");
    strcpy(cartas->nome_menu[2].linha, "| Flame Dagger em modo de defesa   |");
    strcpy(cartas->nome_menu[3].linha, "| Flame Dagger em modo de ataque   |");
    strcpy(cartas->nome_menu[4].linha, "| Flame Dagger foi destruida       |");
    strcpy(cartas->nome_menu[5].linha, "| Flame Dagger atacou              |");
    strcpy(cartas->nome_menu[6].linha, "| Flame Dagger foi atacado         |");
    strcpy(cartas->nome_menu[7].linha, "| Flame Dagger recebeu um buff     |");
    strcpy(cartas->nome_menu[8].linha, "| Flame Dagger foi alvo de debuff  |");
    strcpy(cartas->nome_menu[9].linha, "| Flame Dagger atacou diretamente  |");
    strcpy(cartas->nome_menu[10].linha, "| Flame Dagger  |  MAGICA   |             1300/0 |");

    strcpy(cartas->nome_menu[0].linha, "|# - Flame Dagger      |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   FLAME  DAGGER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|        ~/\\~       |");
    strcpy(cartas->linhas[4].linha, "|       ~//\\\\~      |");
    strcpy(cartas->linhas[5].linha, "|       ~//\\\\~      |");
    strcpy(cartas->linhas[6].linha, "|       ~//\\\\~      |");
    strcpy(cartas->linhas[7].linha, "|   ~~   ~||~  ~~   |");
    strcpy(cartas->linhas[8].linha, "|  ~/\\~  ~||~ ~/\\~  |");
    strcpy(cartas->linhas[9].linha, "| ~//\\\\~ ~\\/~~//\\\\~ |");
    strcpy(cartas->linhas[10].linha, "| ~//\\\\~  ~~ ~//\\\\~ |");
    strcpy(cartas->linhas[11].linha, "| ~//\\\\~     ~//\\\\~ |");
    strcpy(cartas->linhas[12].linha, "|  ~||~       ~||~  |");
    strcpy(cartas->linhas[13].linha, "|  ~||~       ~||~  |");
    strcpy(cartas->linhas[14].linha, "|  ~\\/~       ~\\/~  |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1300^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 400;
    cartas->def = 0;
    strcpy(cartas->nome, "Slagga");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Slagga foi sumonada              |");
    strcpy(cartas->nome_menu[2].linha, "| Slagga em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| Slagga em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| Slagga foi destruida             |");
    strcpy(cartas->nome_menu[5].linha, "| Slagga atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| Slagga foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| Slagga recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| Slagga foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| Slagga atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| Slagga        |  MAGICA   |              400/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Slagga            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       SLAGGA      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|        _____      |");
    strcpy(cartas->linhas[5].linha, "|      /   |\\/|\\    |");
    strcpy(cartas->linhas[6].linha, "|      \\|  |   /    |");
    strcpy(cartas->linhas[7].linha, "|       \\_____/     |");
    strcpy(cartas->linhas[8].linha, "|        /</        |");
    strcpy(cartas->linhas[9].linha, "|       /</         |");
    strcpy(cartas->linhas[10].linha, "|      /</          |");
    strcpy(cartas->linhas[11].linha, "|     /</           |");
    strcpy(cartas->linhas[12].linha, "|    (__)           |");
    strcpy(cartas->linhas[13].linha, "|                   |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|       ATK:400 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1400;
    cartas->def = 0;
    strcpy(cartas->nome, "Slagga");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Slagga foi sumonada              |");
    strcpy(cartas->nome_menu[2].linha, "| Slagga em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| Slagga em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| Slagga foi destruida             |");
    strcpy(cartas->nome_menu[5].linha, "| Slagga atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| Slagga foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| Slagga recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| Slagga foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| Slagga atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| Slagga        |  MAGICA   |             1400/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Slagga            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       SLAGGA      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|        _____      |");
    strcpy(cartas->linhas[5].linha, "|      /   |\\/|\\    |");
    strcpy(cartas->linhas[6].linha, "|      \\|  |   /    |");
    strcpy(cartas->linhas[7].linha, "|       \\_____/     |");
    strcpy(cartas->linhas[8].linha, "|        /</        |");
    strcpy(cartas->linhas[9].linha, "|       /</         |");
    strcpy(cartas->linhas[10].linha, "|      /</          |");
    strcpy(cartas->linhas[11].linha, "|     /</           |");
    strcpy(cartas->linhas[12].linha, "|    (__)           |");
    strcpy(cartas->linhas[13].linha, "|                   |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1400^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 0;
    cartas->def = 1300;
    strcpy(cartas->nome, "Skold");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Skold foi sumonada               |");
    strcpy(cartas->nome_menu[2].linha, "| Skold em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Skold em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Skold foi destruida              |");
    strcpy(cartas->nome_menu[5].linha, "| Skold atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Skold foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Skold recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Skold foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Skold atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Skold         |  MAGICA   |             0/1300 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Skold             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       SKOLD       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|     _________     |");
    strcpy(cartas->linhas[5].linha, "|    /@@@@@@@@@\\    |");
    strcpy(cartas->linhas[6].linha, "|   /@/@@@@@@@\\@\\   |");
    strcpy(cartas->linhas[7].linha, "|  /@/@@@@@@@@@\\@\\  |");
    strcpy(cartas->linhas[8].linha, "| /@/@@@@@@@@@@@\\@\\ |");
    strcpy(cartas->linhas[9].linha, "| \\@\\@@@@@@@@@@@/@/ |");
    strcpy(cartas->linhas[10].linha, "|  \\@\\@@@@@@@@@/@/  |");
    strcpy(cartas->linhas[11].linha, "|   \\@\\@@@@@@@/@/   |");
    strcpy(cartas->linhas[12].linha, "|    \\@\\@@@@@/@/    |");
    strcpy(cartas->linhas[13].linha, "|     \\@@@@@@@/     |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    DEF: 1300 ^    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1300;
    cartas->def = 0;
    strcpy(cartas->nome, "Samehada");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Samehada foi sumonada            |");
    strcpy(cartas->nome_menu[2].linha, "| Samehada em modo de defesa       |");
    strcpy(cartas->nome_menu[3].linha, "| Samehada em modo de ataque       |");
    strcpy(cartas->nome_menu[4].linha, "| Samehada foi destruida           |");
    strcpy(cartas->nome_menu[5].linha, "| Samehada atacou                  |");
    strcpy(cartas->nome_menu[6].linha, "| Samehada foi atacado             |");
    strcpy(cartas->nome_menu[7].linha, "| Samehada recebeu um buff         |");
    strcpy(cartas->nome_menu[8].linha, "| Samehada foi alvo de debuff      |");
    strcpy(cartas->nome_menu[9].linha, "| Samehada atacou diretamente      |");
    strcpy(cartas->nome_menu[10].linha, "| Samehada      |  MAGICA   |             1300/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Samehada          |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     SAMEHADA      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|        /_\\        |");
    strcpy(cartas->linhas[4].linha, "|        |_|        |");
    strcpy(cartas->linhas[5].linha, "|        |_|        |");
    strcpy(cartas->linhas[6].linha, "|     /\\ |_| /\\     |");
    strcpy(cartas->linhas[7].linha, "|    /  \\|_|/  \\    |");
    strcpy(cartas->linhas[8].linha, "|   /    | |    \\   |");
    strcpy(cartas->linhas[9].linha, "|   \\    | |    /   |");
    strcpy(cartas->linhas[10].linha, "|    \\   | |   /    |");
    strcpy(cartas->linhas[11].linha, "|     | /   \\ |     |");
    strcpy(cartas->linhas[12].linha, "|     | |   | |     |");
    strcpy(cartas->linhas[13].linha, "|     | |   | |     |");
    strcpy(cartas->linhas[14].linha, "|     | |   | |     |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1300 ^  |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 800;
    cartas->def = 0;
    strcpy(cartas->nome, "Shuriken");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Shuriken foi sumonada            |");
    strcpy(cartas->nome_menu[2].linha, "| Shuriken em modo de defesa       |");
    strcpy(cartas->nome_menu[3].linha, "| Shuriken em modo de ataque       |");
    strcpy(cartas->nome_menu[4].linha, "| Shuriken foi destruida           |");
    strcpy(cartas->nome_menu[5].linha, "| Shuriken atacou                  |");
    strcpy(cartas->nome_menu[6].linha, "| Shuriken foi atacado             |");
    strcpy(cartas->nome_menu[7].linha, "| Shuriken recebeu um buff         |");
    strcpy(cartas->nome_menu[8].linha, "| Shuriken foi alvo de debuff      |");
    strcpy(cartas->nome_menu[9].linha, "| Shuriken atacou diretamente      |");
    strcpy(cartas->nome_menu[10].linha, "| Shuriken      |  MAGICA   |              800/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Shuriken          |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     SHURIKEN      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|****    /O\\    ****|");
    strcpy(cartas->linhas[4].linha, "|**     /OOO\\     **|");
    strcpy(cartas->linhas[5].linha, "|      /OOOOO\\      |");
    strcpy(cartas->linhas[6].linha, "|   /OOOOO_OOOOO\\   |");
    strcpy(cartas->linhas[7].linha, "|\\OOOOOO|   |OOOOOO/|");
    strcpy(cartas->linhas[8].linha, "|   \\OOOOO_OOOOO/   |");
    strcpy(cartas->linhas[9].linha, "|      \\OOOOO/      |");
    strcpy(cartas->linhas[10].linha, "| **    \\OOO/       |");
    strcpy(cartas->linhas[11].linha, "| ***    \\O/     *  |");
    strcpy(cartas->linhas[12].linha, "|  ****        ***  |");
    strcpy(cartas->linhas[13].linha, "|    *****   ***    |");
    strcpy(cartas->linhas[14].linha, "|       ******      |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 800^    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Sword");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Sword foi sumonada               |");
    strcpy(cartas->nome_menu[2].linha, "| Sword em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Sword em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Sword foi destruida              |");
    strcpy(cartas->nome_menu[5].linha, "| Sword atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Sword foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Sword recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Sword foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Sword atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Sword         |  MAGICA   |             1500/0 |");
    //strcpy(cartas->nome_menu[10].linha, "| Golyan        |  MONSTRO  |          1800/3000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Sword             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       SWORD       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|     ___(o)___     |");
    strcpy(cartas->linhas[5].linha, "|    /       | |    |");
    strcpy(cartas->linhas[6].linha, "|    |      <(o)>   |");
    strcpy(cartas->linhas[7].linha, "|    |       | |    |");
    strcpy(cartas->linhas[8].linha, "|    |       | |    |");
    strcpy(cartas->linhas[9].linha, "|    |       | |    |");
    strcpy(cartas->linhas[10].linha, "|    U    *  | |  * |");
    strcpy(cartas->linhas[11].linha, "|   /*\\      | |    |");
    strcpy(cartas->linhas[12].linha, "|   |*|   *  \\ / *  |");
    strcpy(cartas->linhas[13].linha, "|   \\*/     * V *   |");
    strcpy(cartas->linhas[14].linha, "|                   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1500 ^  |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");

    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3100;
    cartas->def = 3000;
    strcpy(cartas->nome, "Three-tails");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Three-tails foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Three-tails em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Three-tails em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Three-tails foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Three-tails atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Three-tails foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Three-tails recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Three-tails foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Three-tails atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Three-tails   |  MONSTRO  |          3100/3000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Three-tails       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "| THREE TAILS BEAST |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|          @@@@   @@|");
    strcpy(cartas->linhas[4].linha, "|  @@@   @@@@@@@  @ |");
    strcpy(cartas->linhas[5].linha, "| @@@@@  @    @@    |");
    strcpy(cartas->linhas[6].linha, "|@@@  @      @@@   @|");
    strcpy(cartas->linhas[7].linha, "|@@@        @@@   @@|");
    strcpy(cartas->linhas[8].linha, "|@@@@      @@    @@@|");
    strcpy(cartas->linhas[9].linha, "| @@@ _/|___|\\_ @@  |");
    strcpy(cartas->linhas[10].linha, "|  @@/@|8   8|@\\@   |");
    strcpy(cartas->linhas[11].linha, "|  @/@@\\  .  /@@\\   |");
    strcpy(cartas->linhas[12].linha, "|  /@/@@\\_-_/@@\\@\\  |");
    strcpy(cartas->linhas[13].linha, "|  \\@\\ @@@@@@@ /@/  |");
    strcpy(cartas->linhas[14].linha, "|   \\@\\ @@@@@ /@/   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3100| DEF:3000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2500;
    cartas->def = 2300;
    strcpy(cartas->nome, "Unknow W");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Unknow W foi sumonado            |");
    strcpy(cartas->nome_menu[2].linha, "| Unknow W em modo de defesa       |");
    strcpy(cartas->nome_menu[3].linha, "| Unknow W em modo de ataque       |");
    strcpy(cartas->nome_menu[4].linha, "| Unknow W foi destruido           |");
    strcpy(cartas->nome_menu[5].linha, "| Unknow W atacou                  |");
    strcpy(cartas->nome_menu[6].linha, "| Unknow W foi atacado             |");
    strcpy(cartas->nome_menu[7].linha, "| Unknow W recebeu um buff         |");
    strcpy(cartas->nome_menu[8].linha, "| Unknow W foi alvo de debuff      |");
    strcpy(cartas->nome_menu[9].linha, "| Unknow W atacou diretamente      |");
    strcpy(cartas->nome_menu[10].linha, "| Unknow W      |  MONSTRO  |          2500/2300 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Unknow W          |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  UNKNOW  WARRIOR  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|#/@@@@@@@@@\\#  ****|");
    strcpy(cartas->linhas[4].linha, "|/@@@@@@@@@@@\\#  ***|");
    strcpy(cartas->linhas[5].linha, "|@@@@@@@@(0)@@|   **|");
    strcpy(cartas->linhas[6].linha, "|@@@@@@@@@@@@@|    *|");
    strcpy(cartas->linhas[7].linha, "|\\@@@@@@@@@@@@/     |");
    strcpy(cartas->linhas[8].linha, "| \\@@@@@@@@@@/      |");
    strcpy(cartas->linhas[9].linha, "| /\\@@@@@@@@/\\      |");
    strcpy(cartas->linhas[10].linha, "|/**\\@@@@@/***\\     |");
    strcpy(cartas->linhas[11].linha, "|*****\\ /******\\__  |");
    strcpy(cartas->linhas[12].linha, "|******|**********\\ |");
    strcpy(cartas->linhas[13].linha, "|******|***********\\|");
    strcpy(cartas->linhas[14].linha, "|******|************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2500| DEF:2300|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3100;
    cartas->def = 2900;
    strcpy(cartas->nome, "Darttasyr");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Darttasyr foi sumonado           |");
    strcpy(cartas->nome_menu[2].linha, "| Darttasyr em modo de defesa      |");
    strcpy(cartas->nome_menu[3].linha, "| Darttasyr em modo de ataque      |");
    strcpy(cartas->nome_menu[4].linha, "| Darttasyr foi destruido          |");
    strcpy(cartas->nome_menu[5].linha, "| Darttasyr atacou                 |");
    strcpy(cartas->nome_menu[6].linha, "| Darttasyr foi atacado            |");
    strcpy(cartas->nome_menu[7].linha, "| Darttasyr recebeu um buff        |");
    strcpy(cartas->nome_menu[8].linha, "| Darttasyr foi alvo de debuff     |");
    strcpy(cartas->nome_menu[9].linha, "| Darttasyr atacou diretamente     |");
    strcpy(cartas->nome_menu[10].linha, "| Darttasyr     |  MONSTRO  |          3100/2900 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Darttasyr         |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     DARTTASYR     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|***** ^\\___/^      |");
    strcpy(cartas->linhas[4].linha, "|**    \\@u u@/      |");
    strcpy(cartas->linhas[5].linha, "|*   ___\\@@@/___    |");
    strcpy(cartas->linhas[6].linha, "|\\  |@@@@\\_/@@@@|   |");
    strcpy(cartas->linhas[7].linha, "|\\\\ |@ |@@@@@| \\@|  |");
    strcpy(cartas->linhas[8].linha, "| \\\\@| |@@@@@| |@|  |");
    strcpy(cartas->linhas[9].linha, "||@@\\  /@@@@@@\\\\@/  |");
    strcpy(cartas->linhas[10].linha, "|   \\/@@@@@@@@@\\    |");
    strcpy(cartas->linhas[11].linha, "|  |@@@\\@@@@@/@@@|  |");
    strcpy(cartas->linhas[12].linha, "|   \\@@@\\@@@/@@@/   |");
    strcpy(cartas->linhas[13].linha, "|     \\@@| |@@/     |");
    strcpy(cartas->linhas[14].linha, "|   |@@@\\\\  \\@@@|   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3100| DEF:2900|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2800;
    cartas->def = 3300;
    strcpy(cartas->nome, "Underhunter");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Underhunter foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Underhunter em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Underhunter em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Underhunter foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Underhunter atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Underhunter foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Underhunter recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Underhunter foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Underhunter atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Underhunter   |  MONSTRO  |          2800/3300 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Underhunter       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    UNDERHUNTER    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|@@  ___/|/|   @@@@@|");
    strcpy(cartas->linhas[4].linha, "|@  /****//\\    @@@@|");
    strcpy(cartas->linhas[5].linha, "|  |*******e|    @@@|");
    strcpy(cartas->linhas[6].linha, "|  |********\\     @@|");
    strcpy(cartas->linhas[7].linha, "|   \\******_|      @|");
    strcpy(cartas->linhas[8].linha, "|  /*****__/        |");
    strcpy(cartas->linhas[9].linha, "| /*L****\\          |");
    strcpy(cartas->linhas[10].linha, "|/********\\____     |");
    strcpy(cartas->linhas[11].linha, "|**************\\___ |");
    strcpy(cartas->linhas[12].linha, "|***I**************\\|");
    strcpy(cartas->linhas[13].linha, "|***|***************|");
    strcpy(cartas->linhas[14].linha, "|***|***************|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2800| DEF:3300|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3000;
    cartas->def = 3000;
    strcpy(cartas->nome, "Demon Soldier");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Demon Soldier foi sumonado       |");
    strcpy(cartas->nome_menu[2].linha, "| Demon Soldier em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Demon Soldier em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Demon Soldier foi destruido      |");
    strcpy(cartas->nome_menu[5].linha, "| Demon Soldier atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Demon Soldier foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Demon Soldier recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Demon Soldier foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Demon Soldier atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Demon Soldier |  MONSTRO  |          3000/3000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Demon Soldier     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   DEMON SOLDIER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|***              **|");
    strcpy(cartas->linhas[4].linha, "|* /\\ /\\ /\\        *|");
    strcpy(cartas->linhas[5].linha, "|  || || ||         |");
    strcpy(cartas->linhas[6].linha, "|  \\| || |/  /|  |\\ |");
    strcpy(cartas->linhas[7].linha, "|   \\====/   \\\\||// |");
    strcpy(cartas->linhas[8].linha, "|     ||     |O  O| |");
    strcpy(cartas->linhas[9].linha, "|     @@   __@\\^ /@ |");
    strcpy(cartas->linhas[10].linha, "|     |@@__@@@ W/@@@|");
    strcpy(cartas->linhas[11].linha, "|     ||@@@@@@@@@@@@|");
    strcpy(cartas->linhas[12].linha, "|     ||\\@@|@@@@@@@@|");
    strcpy(cartas->linhas[13].linha, "|*    ||   |@@@@@@| |");
    strcpy(cartas->linhas[14].linha, "|**   ||   /@@@@@@@\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3000| DEF:3000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2500;
    cartas->def = 2000;
    strcpy(cartas->nome, "Hell-Reaper");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Hell-Reaper foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Hell-Reaper em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Hell-Reaper em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Hell-Reaper foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Hell-Reaper atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Hell-Reaper foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Hell-Reaper recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Hell-Reaper foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Hell-Reaper atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Hell-Reaper   |  MONSTRO  |          2500/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Hell-Reaper       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    HELL-REAPER    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|** /@|  ***  |@\\ **|");
    strcpy(cartas->linhas[4].linha, "|* /@@|   *   |@@\\ *|");
    strcpy(cartas->linhas[5].linha, "| /@@@@\\     /@@@@\\ |");
    strcpy(cartas->linhas[6].linha, "|/@@@@@@|\\_/|@@@@@@\\|");
    strcpy(cartas->linhas[7].linha, "|@@@@@@| |*| |@@@@@@|");
    strcpy(cartas->linhas[8].linha, "|\\@@@@@\\ /*\\ /@@@@@/|");
    strcpy(cartas->linhas[9].linha, "|  \\@@@@@***@@@@@/  |");
    strcpy(cartas->linhas[10].linha, "|   \\@@@@@*@@@@@/   |");
    strcpy(cartas->linhas[11].linha, "|*  \\// \\***/ \\\\/  *|");
    strcpy(cartas->linhas[12].linha, "|*     /*****\\     *|");
    strcpy(cartas->linhas[13].linha, "|**   /*******\\   **|");
    strcpy(cartas->linhas[14].linha, "|***  |*/   \\*|  ***|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2500| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 4000;
    cartas->def = 2500;
    strcpy(cartas->nome, "Fallen King");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Fallen King foi sumonado         |");
    strcpy(cartas->nome_menu[2].linha, "| Fallen King em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Fallen King em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Fallen King foi destruido        |");
    strcpy(cartas->nome_menu[5].linha, "| Fallen King atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Fallen King foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Fallen King recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Fallen King foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Fallen King atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Fallen King   |  MONSTRO  |          4000/2500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Fallen King       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|KING  OF THE FALLEN|");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|****    ***    ****|");
    strcpy(cartas->linhas[4].linha, "|** |\\|\\|\\|\\|\\|\\| **|");
    strcpy(cartas->linhas[5].linha, "|*  |===========|  *|");
    strcpy(cartas->linhas[6].linha, "|*   |@/\\@@@/\\@|   *|");
    strcpy(cartas->linhas[7].linha, "|    \\@\\/@@@\\/@/    |");
    strcpy(cartas->linhas[8].linha, "|     \\@@ w @@/     |");
    strcpy(cartas->linhas[9].linha, "|      |@|@|@|      |");
    strcpy(cartas->linhas[10].linha, "|===___\\@|^|@/___===|");
    strcpy(cartas->linhas[11].linha, "|/~~~~~~\\-I-/~~~~~~\\|");
    strcpy(cartas->linhas[12].linha, "|~~~~~~~|-I-|~~~~~~~|");
    strcpy(cartas->linhas[13].linha, "|~~~~~~~|-I-|~~~~~~~|");
    strcpy(cartas->linhas[14].linha, "|~~~~~~~|-I-|~~~~~~~|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:4000| DEF:2500|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3500;
    cartas->def = 3500;
    strcpy(cartas->nome, "Cursed Warrior");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Cursed Warrior foi sumonado      |");
    strcpy(cartas->nome_menu[2].linha, "| Cursed Warrior em modo de defesa |");
    strcpy(cartas->nome_menu[3].linha, "| Cursed Warrior em modo de ataque |");
    strcpy(cartas->nome_menu[4].linha, "| Cursed Warrior foi destruido     |");
    strcpy(cartas->nome_menu[5].linha, "| Cursed Warrior atacou            |");
    strcpy(cartas->nome_menu[6].linha, "| Cursed Warrior foi atacado       |");
    strcpy(cartas->nome_menu[7].linha, "| Cursed Warrior recebeu um buff   |");
    strcpy(cartas->nome_menu[8].linha, "| Cursed Warrior foi alvo de debuff|");
    strcpy(cartas->nome_menu[9].linha, "| Cursed Warrior atacou diretamente|");
    strcpy(cartas->nome_menu[10].linha, "| Cursed Warrior|  MONSTRO  |          3500/3500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Cursed Warrior    |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  CURSED  WARRIOR  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|\\L\\           *****|");
    strcpy(cartas->linhas[4].linha, "| \\L\\            ***|");
    strcpy(cartas->linhas[5].linha, "|  \\L\\    _______  *|");
    strcpy(cartas->linhas[6].linha, "|   \\L\\  /^___^  \\  |");
    strcpy(cartas->linhas[7].linha, "|    \\L\\/ /   \\   \\ |");
    strcpy(cartas->linhas[8].linha, "|     \\L\\/#  # \\   \\|");
    strcpy(cartas->linhas[9].linha, "|      \\L\\ c   |   ||");
    strcpy(cartas->linhas[10].linha, "|   ___|\\L\\ _ /\\  /@|");
    strcpy(cartas->linhas[11].linha, "|  /###\\/\\L\\@@@@\\/@@|");
    strcpy(cartas->linhas[12].linha, "| |###/###\\//#\\@@@@@|");
    strcpy(cartas->linhas[13].linha, "| |###__/##/#|@@@@@@|");
    strcpy(cartas->linhas[14].linha, "|  \\##########/@@@@@|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3500| DEF:3500|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2100;
    cartas->def = 3000;
    strcpy(cartas->nome, "Zarboreas");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Zarboreas foi sumonado           |");
    strcpy(cartas->nome_menu[2].linha, "| Zarboreas em modo de defesa      |");
    strcpy(cartas->nome_menu[3].linha, "| Zarboreas em modo de ataque      |");
    strcpy(cartas->nome_menu[4].linha, "| Zarboreas foi destruido          |");
    strcpy(cartas->nome_menu[5].linha, "| Zarboreas atacou                 |");
    strcpy(cartas->nome_menu[6].linha, "| Zarboreas foi atacado            |");
    strcpy(cartas->nome_menu[7].linha, "| Zarboreas recebeu um buff        |");
    strcpy(cartas->nome_menu[8].linha, "| Zarboreas foi alvo de debuff     |");
    strcpy(cartas->nome_menu[9].linha, "| Zarboreas atacou diretamente     |");
    strcpy(cartas->nome_menu[10].linha, "| Zarboreas     |  MONSTRO  |          2100/3000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Zarboreas         |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     ZARBOREAS     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| _____\\_____/_____ |");
    strcpy(cartas->linhas[4].linha, "| \\     _   _     / |");
    strcpy(cartas->linhas[5].linha, "|  \\\\/  0   0  \\//  |");
    strcpy(cartas->linhas[6].linha, "|    \\    ^    /    |");
    strcpy(cartas->linhas[7].linha, "|     \\_  L  _/     |");
    strcpy(cartas->linhas[8].linha, "|     / \\___/ \\     |");
    strcpy(cartas->linhas[9].linha, "| ___/____ ____\\___ |");
    strcpy(cartas->linhas[10].linha, "|/        V        \\|");
    strcpy(cartas->linhas[11].linha, "|         |         |");
    strcpy(cartas->linhas[12].linha, "|      _  |  _      |");
    strcpy(cartas->linhas[13].linha, "|/  _____/ \\_____  \\|");
    strcpy(cartas->linhas[14].linha, "| \\     _____     / |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2100| DEF:3000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 1800;
    cartas->def = 2400;
    strcpy(cartas->nome, "Caves");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Caves foi sumonado               |");
    strcpy(cartas->nome_menu[2].linha, "| Caves em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Caves em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Caves foi destruido              |");
    strcpy(cartas->nome_menu[5].linha, "| Caves atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Caves foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Caves recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Caves foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Caves atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Caves         |  MONSTRO  |          1800/2400 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Caves             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       CAVES       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|      @@@@@@@@     |");
    strcpy(cartas->linhas[4].linha, "|    @@@ \\@@/@@@    |");
    strcpy(cartas->linhas[5].linha, "|    @@  z z  @@    |");
    strcpy(cartas->linhas[6].linha, "|    @@  ---  @@    |");
    strcpy(cartas->linhas[7].linha, "|    @@@@\\@@/@@@    |");
    strcpy(cartas->linhas[8].linha, "|    @/@@@@@@@\\@    |");
    strcpy(cartas->linhas[9].linha, "| ___/@@@@@@@@@\\___ |");
    strcpy(cartas->linhas[10].linha, "|/   __       __   \\|");
    strcpy(cartas->linhas[11].linha, "|        \\v/        |");
    strcpy(cartas->linhas[12].linha, "|         |         |");
    strcpy(cartas->linhas[13].linha, "| /  _    |    _  \\ |");
    strcpy(cartas->linhas[14].linha, "|/\\     _/ \\_     /\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:1800| DEF:2400|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 3;
    cartas->atk = -3000;
    cartas->def = 0;
    strcpy(cartas->nome, "Mystic Secret");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Mystic Secret foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Mystic Secret em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Mystic Secret em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Mystic Secret foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Mystic Secret atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Mystic Secret foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Mystic Secret recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Mystic Secret foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Mystic Secret atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Mystic Secret |  MAGICA   |            -3000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Mystic Secret     |");
    strcpy(cartas->linhas[0].linha,  "+-------------------+");
    strcpy(cartas->linhas[1].linha,  "|   MYSTIC SECRET   |");
    strcpy(cartas->linhas[2].linha,  "+-------------------+");
    strcpy(cartas->linhas[3].linha,  "|  _______________  |");
    strcpy(cartas->linhas[4].linha,  "| /\\01101101011001| |");
    strcpy(cartas->linhas[5].linha,  "| |@\\0101101100011| |");
    strcpy(cartas->linhas[6].linha,  "| \\_/\\010000110111| |");
    strcpy(cartas->linhas[7].linha,  "|    |101110010001| |");
    strcpy(cartas->linhas[8].linha,  "|    |000000110000| |");
    strcpy(cartas->linhas[9].linha,  "|    |101110000011| |");
    strcpy(cartas->linhas[10].linha, "|    |100110000101| |");
    strcpy(cartas->linhas[11].linha, "|    |001101000011| |");
    strcpy(cartas->linhas[12].linha, "|*   |001010110100| |");
    strcpy(cartas->linhas[13].linha, "|**  \\0011001012222\\|");
    strcpy(cartas->linhas[14].linha, "|***                |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 3000 v   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = -4000;
    cartas->def = 0;
    strcpy(cartas->nome, "Instakill");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Instakill foi sumonada           |");
    strcpy(cartas->nome_menu[2].linha, "| Instakill em modo de defesa      |");
    strcpy(cartas->nome_menu[3].linha, "| Instakill em modo de ataque      |");
    strcpy(cartas->nome_menu[4].linha, "| Instakill foi destruida          |");
    strcpy(cartas->nome_menu[5].linha, "| Instakill atacou                 |");
    strcpy(cartas->nome_menu[6].linha, "| Instakill foi atacado            |");
    strcpy(cartas->nome_menu[7].linha, "| Instakill recebeu um buff        |");
    strcpy(cartas->nome_menu[8].linha, "| Instakill foi alvo de debuff     |");
    strcpy(cartas->nome_menu[9].linha, "| Instakill atacou diretamente     |");
    strcpy(cartas->nome_menu[10].linha, "| Instakill     |  MAGICA   |            -4000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Instakill         |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     INSTAKILL     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                 ##|");
    strcpy(cartas->linhas[4].linha, "|    @@@@@@@@     ##|");
    strcpy(cartas->linhas[5].linha, "|   @@@@@@@@@@  ####|");
    strcpy(cartas->linhas[6].linha, "|  @@@@@@@@@@@@  ###|");
    strcpy(cartas->linhas[7].linha, "|  @  @@@@@@  @   ##|");
    strcpy(cartas->linhas[8].linha, "|  @    @@    @    #|");
    strcpy(cartas->linhas[9].linha, "|  @@@@@@@@@@@@   ##|");
    strcpy(cartas->linhas[10].linha, "|   @@@@  @@@@    ##|");
    strcpy(cartas->linhas[11].linha, "|    @@@@@@@@   ####|");
    strcpy(cartas->linhas[12].linha, "|    @@ @@ @@    ###|");
    strcpy(cartas->linhas[13].linha, "|    @@ @@ @@     ##|");
    strcpy(cartas->linhas[14].linha, "|                  #|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    DEF: 4000 v    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 0;
    cartas->def = -2000;
    strcpy(cartas->nome, "Shieldbreak");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Shieldbreak foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Shieldbreak em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Shieldbreak em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Shieldbreak foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Shieldbreak atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Shieldbreak foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Shieldbreak recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Shieldbreak foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Shieldbreak atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Shieldbreak   |  MAGICA   |            0/-2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Shieldbreak       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SHIELDBREAK    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| __________***_____|");
    strcpy(cartas->linhas[4].linha, "|||       _/*_|     |");
    strcpy(cartas->linhas[5].linha, "|||  @@@@\\***\\ @@@@@|");
    strcpy(cartas->linhas[6].linha, "||| @@@@@|**/ @@@@@@|");
    strcpy(cartas->linhas[7].linha, "|||  @@@/* /@@@@@@@ |");
    strcpy(cartas->linhas[8].linha, "|||   @/* |@@@@@@@  |");
    strcpy(cartas->linhas[9].linha, "|\\\\   |* /@@@@@@@   |");
    strcpy(cartas->linhas[10].linha, "| \\\\ /* /  @@@@     |");
    strcpy(cartas->linhas[11].linha, "|  \\/* \\    @@     /|");
    strcpy(cartas->linhas[12].linha, "|  ** *\\\\         / |");
    strcpy(cartas->linhas[13].linha, "|  * ** \\\\_______/  |");
    strcpy(cartas->linhas[14].linha, "|    *              |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    DEF: 2000 v    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 3;
    cartas->atk = 2000;
    cartas->def = 0;
    strcpy(cartas->nome, "Goblet Ages");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Goblet Ages foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Goblet Ages em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Goblet Ages em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Goblet Ages foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Goblet Ages atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Goblet Ages foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Goblet Ages recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Goblet Ages foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Goblet Ages atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Goblet Ages   |  MAGICA   |             2000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Goblet Ages       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  GOBLET OF AGES   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|**               **|");
    strcpy(cartas->linhas[4].linha, "|*  @___________@  *|");
    strcpy(cartas->linhas[5].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[6].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[7].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[8].linha, "|*  \\@@@@@@@@@@@/  *|");
    strcpy(cartas->linhas[9].linha, "|**     @@@@@     **|");
    strcpy(cartas->linhas[10].linha, "|***    @@@@@    ***|");
    strcpy(cartas->linhas[11].linha, "|***    @@@@@    ***|");
    strcpy(cartas->linhas[12].linha, "|***  @@@@@@@@@  ***|");
    strcpy(cartas->linhas[13].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[14].linha, "|*                 *|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 2000 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1100;
    cartas->def = 0;
    strcpy(cartas->nome, "Poison Dagger");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Poison Dagger foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Poison Dagger em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Poison Dagger em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Poison Dagger foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Poison Dagger atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Poison Dagger foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Poison Dagger recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Poison Dagger foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Poison Dagger atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Poison Dagger |  MAGICA   |             1100/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Poison Dagger     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   POISON  DAGGER  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|         /\\        |");
    strcpy(cartas->linhas[4].linha, "|        //\\\\       |");
    strcpy(cartas->linhas[5].linha, "|        /*\\\\       |");
    strcpy(cartas->linhas[6].linha, "|        **\\\\       |");
    strcpy(cartas->linhas[7].linha, "|         *|        |");
    strcpy(cartas->linhas[8].linha, "|   /\\   *||   *\\   |");
    strcpy(cartas->linhas[9].linha, "|  */\\\\  *\\/  /**\\  |");
    strcpy(cartas->linhas[10].linha, "|  //\\\\    *  //*\\  |");
    strcpy(cartas->linhas[11].linha, "|  /***   **  //\\\\  |");
    strcpy(cartas->linhas[12].linha, "|   ||*   *    ||   |");
    strcpy(cartas->linhas[13].linha, "|   ||*   *    |*   |");
    strcpy(cartas->linhas[14].linha, "|   \\/         \\/   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1100^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1700;
    cartas->def = 0;
    strcpy(cartas->nome, "Soul Sickle");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Soul Sickle foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Soul Sickle em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Soul Sickle em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Soul Sickle foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Soul Sickle atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Soul Sickle foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Soul Sickle recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Soul Sickle foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Soul Sickle atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Soul Sickle   |  MAGICA   |             1700/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Soul Sickle       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SOUL SICKLE    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|**   ________   ***|");
    strcpy(cartas->linhas[4].linha, "|*   /SSSSSSSS\\   **|");
    strcpy(cartas->linhas[5].linha, "| /SSSSSS/\\SSSSS\\  *|");
    strcpy(cartas->linhas[6].linha, "|/SSS/       \\SSS\\  |");
    strcpy(cartas->linhas[7].linha, "| \\\\   **     \\SS/  |");
    strcpy(cartas->linhas[8].linha, "|* \\\\  *****   \\/  *|");
    strcpy(cartas->linhas[9].linha, "|** \\\\  ******    **|");
    strcpy(cartas->linhas[10].linha, "|**  \\\\  ***********|");
    strcpy(cartas->linhas[11].linha, "|***  \\\\  **********|");
    strcpy(cartas->linhas[12].linha, "|****  \\\\  *********|");
    strcpy(cartas->linhas[13].linha, "|*****  \\\\  ********|");
    strcpy(cartas->linhas[14].linha, "|******  \\|  *******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1700^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1800;
    cartas->def = 0;
    strcpy(cartas->nome, "Tridentale");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Tridentale foi sumonada          |");
    strcpy(cartas->nome_menu[2].linha, "| Tridentale em modo de defesa     |");
    strcpy(cartas->nome_menu[3].linha, "| Tridentale em modo de ataque     |");
    strcpy(cartas->nome_menu[4].linha, "| Tridentale foi destruida         |");
    strcpy(cartas->nome_menu[5].linha, "| Tridentale atacou                |");
    strcpy(cartas->nome_menu[6].linha, "| Tridentale foi atacado           |");
    strcpy(cartas->nome_menu[7].linha, "| Tridentale recebeu um buff       |");
    strcpy(cartas->nome_menu[8].linha, "| Tridentale foi alvo de debuff    |");
    strcpy(cartas->nome_menu[9].linha, "| Tridentale atacou diretamente    |");
    strcpy(cartas->nome_menu[10].linha, "| Tridentale    |  MAGICA   |             1800/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Tridentale        |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    TRIDENTALE     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|     _  /|\\  _     |");
    strcpy(cartas->linhas[4].linha, "|     \\\\_| |_//     |");
    strcpy(cartas->linhas[5].linha, "|      | | | |      |");
    strcpy(cartas->linhas[6].linha, "|      | | | |      |");
    strcpy(cartas->linhas[7].linha, "|      | | | |      |");
    strcpy(cartas->linhas[8].linha, "|      | | | |      |");
    strcpy(cartas->linhas[9].linha, "|      \\     /      |");
    strcpy(cartas->linhas[10].linha, "|       |   |       |");
    strcpy(cartas->linhas[11].linha, "|*      |   |      *|");
    strcpy(cartas->linhas[12].linha, "|***    |___|    ***|");
    strcpy(cartas->linhas[13].linha, "|****** (VVV) ******|");
    strcpy(cartas->linhas[14].linha, "|******* ||| *******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1800^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1400;
    cartas->def = 0;
    strcpy(cartas->nome, "Hache");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Hache foi sumonada               |");
    strcpy(cartas->nome_menu[2].linha, "| Hache em modo de defesa          |");
    strcpy(cartas->nome_menu[3].linha, "| Hache em modo de ataque          |");
    strcpy(cartas->nome_menu[4].linha, "| Hache foi destruida              |");
    strcpy(cartas->nome_menu[5].linha, "| Hache atacou                     |");
    strcpy(cartas->nome_menu[6].linha, "| Hache foi atacado                |");
    strcpy(cartas->nome_menu[7].linha, "| Hache recebeu um buff            |");
    strcpy(cartas->nome_menu[8].linha, "| Hache foi alvo de debuff         |");
    strcpy(cartas->nome_menu[9].linha, "| Hache atacou diretamente         |");
    strcpy(cartas->nome_menu[10].linha, "| Hache         |  MAGICA   |             1400/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Hache             |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|       HACHE       |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|****               |");
    strcpy(cartas->linhas[4].linha, "|**       /\\        |");
    strcpy(cartas->linhas[5].linha, "|*    /\\ /* \\       |");
    strcpy(cartas->linhas[6].linha, "|     ||/ *  \\      |");
    strcpy(cartas->linhas[7].linha, "|     |(( *  /      |");
    strcpy(cartas->linhas[8].linha, "|     ||\\ * /       |");
    strcpy(cartas->linhas[9].linha, "|     || \\*/        |");
    strcpy(cartas->linhas[10].linha, "|     ||  V         |");
    strcpy(cartas->linhas[11].linha, "|     ||           *|");
    strcpy(cartas->linhas[12].linha, "|     TT          **|");
    strcpy(cartas->linhas[13].linha, "|    |--|       ****|");
    strcpy(cartas->linhas[14].linha, "|    |__|    *******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1400^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1300;
    cartas->def = 0;
    strcpy(cartas->nome, "Flame Dagger");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Flame Dagger foi sumonada        |");
    strcpy(cartas->nome_menu[2].linha, "| Flame Dagger em modo de defesa   |");
    strcpy(cartas->nome_menu[3].linha, "| Flame Dagger em modo de ataque   |");
    strcpy(cartas->nome_menu[4].linha, "| Flame Dagger foi destruida       |");
    strcpy(cartas->nome_menu[5].linha, "| Flame Dagger atacou              |");
    strcpy(cartas->nome_menu[6].linha, "| Flame Dagger foi atacado         |");
    strcpy(cartas->nome_menu[7].linha, "| Flame Dagger recebeu um buff     |");
    strcpy(cartas->nome_menu[8].linha, "| Flame Dagger foi alvo de debuff  |");
    strcpy(cartas->nome_menu[9].linha, "| Flame Dagger atacou diretamente  |");
    strcpy(cartas->nome_menu[10].linha, "| Flame Dagger  |  MAGICA   |             1300/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Flame Dagger      |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   FLAME  DAGGER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|        ~/\\~       |");
    strcpy(cartas->linhas[4].linha, "|       ~//\\\\~      |");
    strcpy(cartas->linhas[5].linha, "|       ~//\\\\~      |");
    strcpy(cartas->linhas[6].linha, "|       ~//\\\\~      |");
    strcpy(cartas->linhas[7].linha, "|   ~~   ~||~  ~~   |");
    strcpy(cartas->linhas[8].linha, "|  ~/\\~  ~||~ ~/\\~  |");
    strcpy(cartas->linhas[9].linha, "| ~//\\\\~ ~\\/~~//\\\\~ |");
    strcpy(cartas->linhas[10].linha, "| ~//\\\\~  ~~ ~//\\\\~ |");
    strcpy(cartas->linhas[11].linha, "| ~//\\\\~     ~//\\\\~ |");
    strcpy(cartas->linhas[12].linha, "|  ~||~       ~||~  |");
    strcpy(cartas->linhas[13].linha, "|  ~||~       ~||~  |");
    strcpy(cartas->linhas[14].linha, "|  ~\\/~       ~\\/~  |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1300^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1000;
    cartas->def = 0;
    strcpy(cartas->nome, "Neo Shuriken");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Neo Shuriken foi sumonada        |");
    strcpy(cartas->nome_menu[2].linha, "| Neo Shuriken em modo de defesa   |");
    strcpy(cartas->nome_menu[3].linha, "| Neo Shuriken em modo de ataque   |");
    strcpy(cartas->nome_menu[4].linha, "| Neo Shuriken foi destruida       |");
    strcpy(cartas->nome_menu[5].linha, "| Neo Shuriken atacou              |");
    strcpy(cartas->nome_menu[6].linha, "| Neo Shuriken foi atacado         |");
    strcpy(cartas->nome_menu[7].linha, "| Neo Shuriken recebeu um buff     |");
    strcpy(cartas->nome_menu[8].linha, "| Neo Shuriken foi alvo de debuff  |");
    strcpy(cartas->nome_menu[9].linha, "| Neo Shuriken atacou diretamente  |");
    strcpy(cartas->nome_menu[10].linha, "| Neo Shuriken  |  MAGICA   |             1000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Neo Shuriken      |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   NEO SHURIKEN    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|      *  *  *      |");
    strcpy(cartas->linhas[5].linha, "|        * *        |");
    strcpy(cartas->linhas[6].linha, "|        / \\        |");
    strcpy(cartas->linhas[7].linha, "|  *     | |    *   |");
    strcpy(cartas->linhas[8].linha, "| * /|___| |___|\\ * |");
    strcpy(cartas->linhas[9].linha, "|  <-----(o)---->   |");
    strcpy(cartas->linhas[10].linha, "| * \\|   | |   |/ * |");
    strcpy(cartas->linhas[11].linha, "|  *     | |    *   |");
    strcpy(cartas->linhas[12].linha, "|        \\ /        |");
    strcpy(cartas->linhas[13].linha, "|        * *        |");
    strcpy(cartas->linhas[14].linha, "|      *  *  *      |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1000^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3000;
    cartas->def = 1500;
    strcpy(cartas->nome, "Satella");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Satella foi sumonada             |");
    strcpy(cartas->nome_menu[2].linha, "| Satella em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Satella em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Satella foi destruida            |");
    strcpy(cartas->nome_menu[5].linha, "| Satella atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Satella foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Satella recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Satella foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Satella atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Satella       |  MONSTRO  |          3000/1500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Satella           |");
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


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3100;
    cartas->def = 2000;
    strcpy(cartas->nome, "Katherine");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Katherine foi sumonada           |");
    strcpy(cartas->nome_menu[2].linha, "| Katherine em modo de defesa      |");
    strcpy(cartas->nome_menu[3].linha, "| Katherine em modo de ataque      |");
    strcpy(cartas->nome_menu[4].linha, "| Katherine foi destruida          |");
    strcpy(cartas->nome_menu[5].linha, "| Katherine atacou                 |");
    strcpy(cartas->nome_menu[6].linha, "| Katherine foi atacado            |");
    strcpy(cartas->nome_menu[7].linha, "| Katherine recebeu um buff        |");
    strcpy(cartas->nome_menu[8].linha, "| Katherine foi alvo de debuff     |");
    strcpy(cartas->nome_menu[9].linha, "| Katherine atacou diretamente     |");
    strcpy(cartas->nome_menu[10].linha, "| Katherine     |  MONSTRO  |          3100/2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Katherine         |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     KATHERINE     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|      @@@@@@@      |");
    strcpy(cartas->linhas[4].linha, "|     @@@@@@@@@     |");
    strcpy(cartas->linhas[5].linha, "|    @@@@@@ O @@    |");
    strcpy(cartas->linhas[6].linha, "|    \\@@@ _   @/    |");
    strcpy(cartas->linhas[7].linha, "|    \\**\\   /**/    |");
    strcpy(cartas->linhas[8].linha, "|   __\\***Y***/__   |");
    strcpy(cartas->linhas[9].linha, "| _/******|******\\_ |");
    strcpy(cartas->linhas[10].linha, "|/********|********\\|");
    strcpy(cartas->linhas[11].linha, "|*********|*********|");
    strcpy(cartas->linhas[12].linha, "|*********|*********|");
    strcpy(cartas->linhas[13].linha, "|*********|*********|");
    strcpy(cartas->linhas[14].linha, "|********/ \\********|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3100| DEF:2000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3300;
    cartas->def = 2800;
    strcpy(cartas->nome, "Death-Bringer");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Death-Bringer foi sumonado       |");
    strcpy(cartas->nome_menu[2].linha, "| Death-Bringer em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Death-Bringer em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Death-Bringer foi destruido      |");
    strcpy(cartas->nome_menu[5].linha, "| Death-Bringer atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Death-Bringer foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Death-Bringer recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Death-Bringer foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Death-Bringer atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Death-Bringer |  MONSTRO  |          3300/2800 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Death-Bringer     |");
    strcpy(cartas->linhas[0].linha,  "+-------------------+");
    strcpy(cartas->linhas[1].linha,  "|   DEATH-BRINGER   |");
    strcpy(cartas->linhas[2].linha,  "+-------------------+");
    strcpy(cartas->linhas[3].linha,  "|       *********   |");
    strcpy(cartas->linhas[4].linha,  "|     ******   **** |");
    strcpy(cartas->linhas[5].linha,  "|     *****      ***|");
    strcpy(cartas->linhas[6].linha,  "|       \\\\  /@@@\\  *|");
    strcpy(cartas->linhas[7].linha,  "|        \\\\ @@@@@   |");
    strcpy(cartas->linhas[8].linha,  "|         \\\\@   @_  |");
    strcpy(cartas->linhas[9].linha,  "|         /\\\\@|@@@\\ |");
    strcpy(cartas->linhas[10].linha, "|*        |@\\\\|@@@| |");
    strcpy(cartas->linhas[11].linha, "|**       |@@\\|@@@| |");
    strcpy(cartas->linhas[12].linha, "|***      |@@@|@@@| |");
    strcpy(cartas->linhas[13].linha, "|****     /@@@|@@@| |");
    strcpy(cartas->linhas[14].linha, "|*****   /@@@@|@@@@\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3300| DEF:2800|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3900;
    cartas->def = 4000;
    strcpy(cartas->nome, "Thunder Disc");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Thunder Disc foi sumonado        |");
    strcpy(cartas->nome_menu[2].linha, "| Thunder Disc em modo de defesa   |");
    strcpy(cartas->nome_menu[3].linha, "| Thunder Disc em modo de ataque   |");
    strcpy(cartas->nome_menu[4].linha, "| Thunder Disc foi destruido       |");
    strcpy(cartas->nome_menu[5].linha, "| Thunder Disc atacou              |");
    strcpy(cartas->nome_menu[6].linha, "| Thunder Disc foi atacado         |");
    strcpy(cartas->nome_menu[7].linha, "| Thunder Disc recebeu um buff     |");
    strcpy(cartas->nome_menu[8].linha, "| Thunder Disc foi alvo de debuff  |");
    strcpy(cartas->nome_menu[9].linha, "| Thunder Disc atacou diretamente  |");
    strcpy(cartas->nome_menu[10].linha, "| Thunder Disc  |  MONSTRO  |          3900/4000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Thunder Disc      |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|DISCIPLE OF THUNDER|");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|        ****       |");
    strcpy(cartas->linhas[4].linha, "|    @@   ****      |");
    strcpy(cartas->linhas[5].linha, "|   @@@@    ***     |");
    strcpy(cartas->linhas[6].linha, "|  @@--@@@ //****   |");
    strcpy(cartas->linhas[7].linha, "|  /@@@@@@//  ***   |");
    strcpy(cartas->linhas[8].linha, "| /++@@@@//    ***  |");
    strcpy(cartas->linhas[9].linha, "| |++@@@@@|      *  |");
    strcpy(cartas->linhas[10].linha, "| |+++@@@+|         |");
    strcpy(cartas->linhas[11].linha, "| |+++|@@@|         |");
    strcpy(cartas->linhas[12].linha, "| |+++|+@@|         |");
    strcpy(cartas->linhas[13].linha, "| |+++|@++|         |");
    strcpy(cartas->linhas[14].linha, "| |+++|+++|         |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3900| DEF:4000|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3000;
    cartas->def = 3800;
    strcpy(cartas->nome, "Hylddir");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Hylddir foi sumonada             |");
    strcpy(cartas->nome_menu[2].linha, "| Hylddir em modo de defesa        |");
    strcpy(cartas->nome_menu[3].linha, "| Hylddir em modo de ataque        |");
    strcpy(cartas->nome_menu[4].linha, "| Hylddir foi destruida            |");
    strcpy(cartas->nome_menu[5].linha, "| Hylddir atacou                   |");
    strcpy(cartas->nome_menu[6].linha, "| Hylddir foi atacado              |");
    strcpy(cartas->nome_menu[7].linha, "| Hylddir recebeu um buff          |");
    strcpy(cartas->nome_menu[8].linha, "| Hylddir foi alvo de debuff       |");
    strcpy(cartas->nome_menu[9].linha, "| Hylddir atacou diretamente       |");
    strcpy(cartas->nome_menu[10].linha, "| Hylddir       |  MONSTRO  |          3000/3800 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Hylddir           |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|      HYLDDIR      |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|        ___        |");
    strcpy(cartas->linhas[4].linha, "|       (___)       |");
    strcpy(cartas->linhas[5].linha, "| //     ___     \\\\ |");
    strcpy(cartas->linhas[6].linha, "|\\//\\   /***\\   /\\\\/|");
    strcpy(cartas->linhas[7].linha, "|\\//\\\\  *- -*  //\\\\/|");
    strcpy(cartas->linhas[8].linha, "|/\\\\\\\\ /* - *\\ ////\\|");
    strcpy(cartas->linhas[9].linha, "|/ \\\\\\\\***Y***//// \\|");
    strcpy(cartas->linhas[10].linha, "|   \\\\\\***|***///   |");
    strcpy(cartas->linhas[11].linha, "|    \\****|****/    |");
    strcpy(cartas->linhas[12].linha, "|    *****|*****    |");
    strcpy(cartas->linhas[13].linha, "|    *****|*****    |");
    strcpy(cartas->linhas[14].linha, "|  *******|*******  |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3000| DEF:3800|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 4500;
    cartas->def = 2300;
    strcpy(cartas->nome, "Fallen Warrior");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Fallen Warrior foi sumonado      |");
    strcpy(cartas->nome_menu[2].linha, "| Fallen Warrior em modo de defesa |");
    strcpy(cartas->nome_menu[3].linha, "| Fallen Warrior em modo de ataque |");
    strcpy(cartas->nome_menu[4].linha, "| Fallen Warrior foi destruido     |");
    strcpy(cartas->nome_menu[5].linha, "| Fallen Warrior atacou            |");
    strcpy(cartas->nome_menu[6].linha, "| Fallen Warrior foi atacado       |");
    strcpy(cartas->nome_menu[7].linha, "| Fallen Warrior recebeu um buff   |");
    strcpy(cartas->nome_menu[8].linha, "| Fallen Warrior foi alvo de debuff|");
    strcpy(cartas->nome_menu[9].linha, "| Fallen Warrior atacou diretamente|");
    strcpy(cartas->nome_menu[10].linha, "| Fallen Warrior|  MONSTRO  |          4500/2300 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Fallen Warrior    |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  FALLEN  WARRIOR  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|                   |");
    strcpy(cartas->linhas[4].linha, "|    ###       /\\   |");
    strcpy(cartas->linhas[5].linha, "|   #####     ///   |");
    strcpy(cartas->linhas[6].linha, "|  #_####    ///    |");
    strcpy(cartas->linhas[7].linha, "|  /\\_###\\  ///     |");
    strcpy(cartas->linhas[8].linha, "| ///###//\\///      |");
    strcpy(cartas->linhas[9].linha, "|/////##///\\/       |");
    strcpy(cartas->linhas[10].linha, "|///////////\\       |");
    strcpy(cartas->linhas[11].linha, "|////////////      *|");
    strcpy(cartas->linhas[12].linha, "|/\\////\\\\///      **|");
    strcpy(cartas->linhas[13].linha, "| @\\//  \\@@      ***|");
    strcpy(cartas->linhas[14].linha, "|@@@@    @@@    ****|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:4500| DEF:2300|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2100;
    cartas->def = 1900;
    strcpy(cartas->nome, "Darttasyr");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Darttasyr foi sumonado           |");
    strcpy(cartas->nome_menu[2].linha, "| Darttasyr em modo de defesa      |");
    strcpy(cartas->nome_menu[3].linha, "| Darttasyr em modo de ataque      |");
    strcpy(cartas->nome_menu[4].linha, "| Darttasyr foi destruido          |");
    strcpy(cartas->nome_menu[5].linha, "| Darttasyr atacou                 |");
    strcpy(cartas->nome_menu[6].linha, "| Darttasyr foi atacado            |");
    strcpy(cartas->nome_menu[7].linha, "| Darttasyr recebeu um buff        |");
    strcpy(cartas->nome_menu[8].linha, "| Darttasyr foi alvo de debuff     |");
    strcpy(cartas->nome_menu[9].linha, "| Darttasyr atacou diretamente     |");
    strcpy(cartas->nome_menu[10].linha, "| Darttasyr     |  MONSTRO  |          2100/1900 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Darttasyr         |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|     DARTTASYR     |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|***** ^\\___/^      |");
    strcpy(cartas->linhas[4].linha, "|**    \\@u u@/      |");
    strcpy(cartas->linhas[5].linha, "|*   ___\\@@@/___    |");
    strcpy(cartas->linhas[6].linha, "|\\  |@@@@\\_/@@@@|   |");
    strcpy(cartas->linhas[7].linha, "|\\\\ |@ |@@@@@| \\@|  |");
    strcpy(cartas->linhas[8].linha, "| \\\\@| |@@@@@| |@|  |");
    strcpy(cartas->linhas[9].linha, "||@@\\  /@@@@@@\\\\@/  |");
    strcpy(cartas->linhas[10].linha, "|   \\/@@@@@@@@@\\    |");
    strcpy(cartas->linhas[11].linha, "|  |@@@\\@@@@@/@@@|  |");
    strcpy(cartas->linhas[12].linha, "|   \\@@@\\@@@/@@@/   |");
    strcpy(cartas->linhas[13].linha, "|     \\@@| |@@/     |");
    strcpy(cartas->linhas[14].linha, "|   |@@@\\\\  \\@@@|   |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2100| DEF:1900|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 2500;
    cartas->def = 2800;
    strcpy(cartas->nome, "Demon Soldier");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Demon Soldier foi sumonado       |");
    strcpy(cartas->nome_menu[2].linha, "| Demon Soldier em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Demon Soldier em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Demon Soldier foi destruido      |");
    strcpy(cartas->nome_menu[5].linha, "| Demon Soldier atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Demon Soldier foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Demon Soldier recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Demon Soldier foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Demon Soldier atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Demon Soldier |  MONSTRO  |          2500/2800 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Demon Soldier     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   DEMON SOLDIER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|***              **|");
    strcpy(cartas->linhas[4].linha, "|* /\\ /\\ /\\        *|");
    strcpy(cartas->linhas[5].linha, "|  || || ||         |");
    strcpy(cartas->linhas[6].linha, "|  \\| || |/  /|  |\\ |");
    strcpy(cartas->linhas[7].linha, "|   \\====/   \\\\||// |");
    strcpy(cartas->linhas[8].linha, "|     ||     |O  O| |");
    strcpy(cartas->linhas[9].linha, "|     @@   __@\\^ /@ |");
    strcpy(cartas->linhas[10].linha, "|     |@@__@@@ W/@@@|");
    strcpy(cartas->linhas[11].linha, "|     ||@@@@@@@@@@@@|");
    strcpy(cartas->linhas[12].linha, "|     ||\\@@|@@@@@@@@|");
    strcpy(cartas->linhas[13].linha, "|*    ||   |@@@@@@| |");
    strcpy(cartas->linhas[14].linha, "|**   ||   /@@@@@@@\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:2500| DEF:2800|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 1;
    cartas->atk = 3300;
    cartas->def = 2800;
    strcpy(cartas->nome, "Death Bringer");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Death Bringer foi sumonado       |");
    strcpy(cartas->nome_menu[2].linha, "| Death Bringer em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Death Bringer em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Death Bringer foi destruido      |");
    strcpy(cartas->nome_menu[5].linha, "| Death Bringer atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Death Bringer foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Death Bringer recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Death Bringer foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Death Bringer atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Death Bringer |  MONSTRO  |          3300/2800 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Death Bringer     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   DEATH-BRINGER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|       *********   |");
    strcpy(cartas->linhas[4].linha, "|     ******   **** |");
    strcpy(cartas->linhas[5].linha, "|     *****      ***|");
    strcpy(cartas->linhas[6].linha, "|       \\\\  /@@@\\  *|");
    strcpy(cartas->linhas[7].linha, "|        \\\\ @@@@@   |");
    strcpy(cartas->linhas[8].linha, "|         \\\\@   @_  |");
    strcpy(cartas->linhas[9].linha, "|         /\\\\@|@@@\\ |");
    strcpy(cartas->linhas[10].linha, "|*        |@\\\\|@@@| |");
    strcpy(cartas->linhas[11].linha, "|**       |@@\\|@@@| |");
    strcpy(cartas->linhas[12].linha, "|***      |@@@|@@@| |");
    strcpy(cartas->linhas[13].linha, "|****     /@@@|@@@| |");
    strcpy(cartas->linhas[14].linha, "|*****   /@@@@|@@@@\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "| ATK:3300| DEF:2800|");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 3;
    cartas->atk = -3500;
    cartas->def = 0;
    strcpy(cartas->nome, "R.I.P.");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| R.I.P. foi sumonada              |");
    strcpy(cartas->nome_menu[2].linha, "| R.I.P. em modo de defesa         |");
    strcpy(cartas->nome_menu[3].linha, "| R.I.P. em modo de ataque         |");
    strcpy(cartas->nome_menu[4].linha, "| R.I.P. foi destruida             |");
    strcpy(cartas->nome_menu[5].linha, "| R.I.P. atacou                    |");
    strcpy(cartas->nome_menu[6].linha, "| R.I.P. foi atacado               |");
    strcpy(cartas->nome_menu[7].linha, "| R.I.P. recebeu um buff           |");
    strcpy(cartas->nome_menu[8].linha, "| R.I.P. foi alvo de debuff        |");
    strcpy(cartas->nome_menu[9].linha, "| R.I.P. atacou diretamente        |");
    strcpy(cartas->nome_menu[10].linha, "| R.I.P.        |  MAGICA   |            -3500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - R.I.P.            |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   REST IN PEACE   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|    _______        |");
    strcpy(cartas->linhas[4].linha, "|   /       \\       |");
    strcpy(cartas->linhas[5].linha, "|  /         \\      |");
    strcpy(cartas->linhas[6].linha, "| /   R.I.P   \\     |");
    strcpy(cartas->linhas[7].linha, "| \\           |     |");
    strcpy(cartas->linhas[8].linha, "| |\\          |    @|");
    strcpy(cartas->linhas[9].linha, "| \\ \\        @|   @@|");
    strcpy(cartas->linhas[10].linha, "|  \\ \\       @@@   @|");
    strcpy(cartas->linhas[11].linha, "| @ \\ \\    @@@@@   @|");
    strcpy(cartas->linhas[12].linha, "| @@ \\ \\  @@@@@@@  @|");
    strcpy(cartas->linhas[13].linha, "|@@@  \\@@@@@@@@@@@@@|");
    strcpy(cartas->linhas[14].linha, "|@@@@@@@@@@@@@@@@@@@|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|   VIDA: 3500 v    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 3;
    cartas->atk = 2000;
    cartas->def = 0;
    strcpy(cartas->nome, "Goblet Ages");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Goblet Ages foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Goblet Ages em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Goblet Ages em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Goblet Ages foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Goblet Ages atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Goblet Ages foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Goblet Ages recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Goblet Ages foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Goblet Ages atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Goblet Ages   |  MAGICA   |             2000/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Goblet Ages       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  GOBLET OF AGES   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|**               **|");
    strcpy(cartas->linhas[4].linha, "|*  @___________@  *|");
    strcpy(cartas->linhas[5].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[6].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[7].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[8].linha, "|*  \\@@@@@@@@@@@/  *|");
    strcpy(cartas->linhas[9].linha, "|**     @@@@@     **|");
    strcpy(cartas->linhas[10].linha, "|***    @@@@@    ***|");
    strcpy(cartas->linhas[11].linha, "|***    @@@@@    ***|");
    strcpy(cartas->linhas[12].linha, "|***  @@@@@@@@@  ***|");
    strcpy(cartas->linhas[13].linha, "|*  @@@@@@@@@@@@@  *|");
    strcpy(cartas->linhas[14].linha, "|*                 *|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 2000 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 0;
    cartas->def = -2000;
    strcpy(cartas->nome, "Shieldbreak");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Shieldbreak foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Shieldbreak em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Shieldbreak em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Shieldbreak foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Shieldbreak atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Shieldbreak foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Shieldbreak recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Shieldbreak foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Shieldbreak atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Shieldbreak   |  MAGICA   |            0/-2000 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Shieldbreak       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SHIELDBREAK    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| __________***_____|");
    strcpy(cartas->linhas[4].linha, "|||       _/*_|     |");
    strcpy(cartas->linhas[5].linha, "|||  @@@@\\***\\ @@@@@|");
    strcpy(cartas->linhas[6].linha, "||| @@@@@|**/ @@@@@@|");
    strcpy(cartas->linhas[7].linha, "|||  @@@/* /@@@@@@@ |");
    strcpy(cartas->linhas[8].linha, "|||   @/* |@@@@@@@  |");
    strcpy(cartas->linhas[9].linha, "|\\\\   |* /@@@@@@@   |");
    strcpy(cartas->linhas[10].linha, "| \\\\ /* /  @@@@     |");
    strcpy(cartas->linhas[11].linha, "|  \\/* \\    @@     /|");
    strcpy(cartas->linhas[12].linha, "|  ** *\\\\         / |");
    strcpy(cartas->linhas[13].linha, "|  * ** \\\\_______/  |");
    strcpy(cartas->linhas[14].linha, "|    *              |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    DEF: 2000 v    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 3;
    cartas->atk = -1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Mystic Secret");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Mystic Secret foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Mystic Secret em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Mystic Secret em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Mystic Secret foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Mystic Secret atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Mystic Secret foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Mystic Secret recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Mystic Secret foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Mystic Secret atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Mystic Secret |  MAGICA   |            -1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Mystic Secret     |");
    strcpy(cartas->linhas[0].linha,  "+-------------------+");
    strcpy(cartas->linhas[1].linha,  "|   MYSTIC SECRET   |");
    strcpy(cartas->linhas[2].linha,  "+-------------------+");
    strcpy(cartas->linhas[3].linha,  "|  _______________  |");
    strcpy(cartas->linhas[4].linha,  "| /\\01101101011001| |");
    strcpy(cartas->linhas[5].linha,  "| |@\\0101101100011| |");
    strcpy(cartas->linhas[6].linha,  "| \\_/\\010000110111| |");
    strcpy(cartas->linhas[7].linha,  "|    |101110010001| |");
    strcpy(cartas->linhas[8].linha,  "|    |000000110000| |");
    strcpy(cartas->linhas[9].linha,  "|    |101110000011| |");
    strcpy(cartas->linhas[10].linha, "|    |100110000101| |");
    strcpy(cartas->linhas[11].linha, "|    |001101000011| |");
    strcpy(cartas->linhas[12].linha, "|*   |001010110100| |");
    strcpy(cartas->linhas[13].linha, "|**  \\0011001012222\\|");
    strcpy(cartas->linhas[14].linha, "|***                |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|    VIDA: 1500 v   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Mystic Trident");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Mystic Trident foi sumonada      |");
    strcpy(cartas->nome_menu[2].linha, "| Mystic Trident em modo de defesa |");
    strcpy(cartas->nome_menu[3].linha, "| Mystic Trident em modo de ataque |");
    strcpy(cartas->nome_menu[4].linha, "| Mystic Trident foi destruida     |");
    strcpy(cartas->nome_menu[5].linha, "| Mystic Trident atacou            |");
    strcpy(cartas->nome_menu[6].linha, "| Mystic Trident foi atacado       |");
    strcpy(cartas->nome_menu[7].linha, "| Mystic Trident recebeu um buff   |");
    strcpy(cartas->nome_menu[8].linha, "| Mystic Trident foi alvo de debuff|");
    strcpy(cartas->nome_menu[9].linha, "| Mystic Trident atacou diretamente|");
    strcpy(cartas->nome_menu[10].linha, "| Mystic Trident|  MAGICA   |             1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Mystic Trident    |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  MYSTIC  TRIDENT  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|*******   /| /| /| |");
    strcpy(cartas->linhas[4].linha, "|******   // // //  |");
    strcpy(cartas->linhas[5].linha, "|*****   //_//_//   |");
    strcpy(cartas->linhas[6].linha, "|****      //      *|");
    strcpy(cartas->linhas[7].linha, "|***      //      **|");
    strcpy(cartas->linhas[8].linha, "|***     //      ***|");
    strcpy(cartas->linhas[9].linha, "|**     //      ****|");
    strcpy(cartas->linhas[10].linha, "|*     //      *****|");
    strcpy(cartas->linhas[11].linha, "|.____//__.   ******|");
    strcpy(cartas->linhas[12].linha, "|####//###|   ******|");
    strcpy(cartas->linhas[13].linha, "|####/####|  *******|");
    strcpy(cartas->linhas[14].linha, "|#########| ********|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1500^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 1500;
    cartas->def = 0;
    strcpy(cartas->nome, "Mystic Hammer");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Mystic Hammer foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Mystic Hammer em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Mystic Hammer em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Mystic Hammer foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Mystic Hammer atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Mystic Hammer foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Mystic Hammer recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Mystic Hammer foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Mystic Hammer atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Mystic Hammer |  MAGICA   |             1500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Mystic Hammer     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   MYSTIC HAMMER   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| /===============\\ |");
    strcpy(cartas->linhas[4].linha, "| |//////|0|\\\\\\\\\\\\| |");
    strcpy(cartas->linhas[5].linha, "| |//////|0|\\\\\\\\\\\\| |");
    strcpy(cartas->linhas[6].linha, "| |//////|0|\\\\\\\\\\\\| |");
    strcpy(cartas->linhas[7].linha, "| |//////|0|\\\\\\\\\\\\| |");
    strcpy(cartas->linhas[8].linha, "| \\=======0=======/ |");
    strcpy(cartas->linhas[9].linha, "|**     \\\\0//     **|");
    strcpy(cartas->linhas[10].linha, "|*****   |||   *****|");
    strcpy(cartas->linhas[11].linha, "|*****   |||   *****|");
    strcpy(cartas->linhas[12].linha, "|*****   |||   *****|");
    strcpy(cartas->linhas[13].linha, "|*****   |||   *****|");
    strcpy(cartas->linhas[14].linha, "|****   \\\\0//   ****|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 1500^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 2200;
    cartas->def = 0;
    strcpy(cartas->nome, "Blade of Chaos");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Blade of Chaos foi sumonada      |");
    strcpy(cartas->nome_menu[2].linha, "| Blade of Chaos em modo de defesa |");
    strcpy(cartas->nome_menu[3].linha, "| Blade of Chaos em modo de ataque |");
    strcpy(cartas->nome_menu[4].linha, "| Blade of Chaos foi destruida     |");
    strcpy(cartas->nome_menu[5].linha, "| Blade of Chaos atacou            |");
    strcpy(cartas->nome_menu[6].linha, "| Blade of Chaos foi atacado       |");
    strcpy(cartas->nome_menu[7].linha, "| Blade of Chaos recebeu um buff   |");
    strcpy(cartas->nome_menu[8].linha, "| Blade of Chaos foi alvo de debuff|");
    strcpy(cartas->nome_menu[9].linha, "| Blade of Chaos atacou diretamente|");
    strcpy(cartas->nome_menu[10].linha, "| Blade of Chaos|  MAGICA   |             2200/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Blade of Chaos    |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|  BLADE OF CHAOSS  |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|****  __/*\\   *****|");
    strcpy(cartas->linhas[4].linha, "|**  _/****/    ****|");
    strcpy(cartas->linhas[5].linha, "|   _|****/      ***|");
    strcpy(cartas->linhas[6].linha, "|  _|****/*\\_     **|");
    strcpy(cartas->linhas[7].linha, "| _|****/****\\     *|");
    strcpy(cartas->linhas[8].linha, "| \\***_/ \\****|_    |");
    strcpy(cartas->linhas[9].linha, "| ()#/    \\****|_   |");
    strcpy(cartas->linhas[10].linha, "|()#/      \\****|_  |");
    strcpy(cartas->linhas[11].linha, "|#()        \\_***/  |");
    strcpy(cartas->linhas[12].linha, "|#/()         \\()\\  |");
    strcpy(cartas->linhas[13].linha, "|   ()         ()#\\ |");
    strcpy(cartas->linhas[14].linha, "|    ()       ()\\##\\|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 2200^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 0;
    cartas->def = 2500;
    strcpy(cartas->nome, "Mystic Shield");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Mystic Shield foi sumonada       |");
    strcpy(cartas->nome_menu[2].linha, "| Mystic Shield em modo de defesa  |");
    strcpy(cartas->nome_menu[3].linha, "| Mystic Shield em modo de ataque  |");
    strcpy(cartas->nome_menu[4].linha, "| Mystic Shield foi destruida      |");
    strcpy(cartas->nome_menu[5].linha, "| Mystic Shield atacou             |");
    strcpy(cartas->nome_menu[6].linha, "| Mystic Shield foi atacado        |");
    strcpy(cartas->nome_menu[7].linha, "| Mystic Shield recebeu um buff    |");
    strcpy(cartas->nome_menu[8].linha, "| Mystic Shield foi alvo de debuff |");
    strcpy(cartas->nome_menu[9].linha, "| Mystic Shield atacou diretamente |");
    strcpy(cartas->nome_menu[10].linha, "| Mystic Shield |  MAGICA   |             0/2500 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Mystic Shield     |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|   MYSTIC SHIELD   |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "| ._______________. |");
    strcpy(cartas->linhas[4].linha, "| |o=============o| |");
    strcpy(cartas->linhas[5].linha, "| ||SSSSSSSSSSSSS|| |");
    strcpy(cartas->linhas[6].linha, "| ||SSSSSSSSSSSSS|| |");
    strcpy(cartas->linhas[7].linha, "| ||SSSSSSSSSSSSS|| |");
    strcpy(cartas->linhas[8].linha, "| ||SSSSSSSSSSSSS|| |");
    strcpy(cartas->linhas[9].linha, "| ||SSSSSSSSSSSSS|| |");
    strcpy(cartas->linhas[10].linha, "| \\oSSSSSSSSSSSSSo/ |");
    strcpy(cartas->linhas[11].linha, "|* \\\\SSSSSSSSSSS// *|");
    strcpy(cartas->linhas[12].linha, "|** \\\\SSSSSSSSS// **|");
    strcpy(cartas->linhas[13].linha, "|*** \\oSSSSSSSo/ ***|");
    strcpy(cartas->linhas[14].linha, "|****           ****|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|     DEF: 2500 ^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 2500;
    cartas->def = 0;
    strcpy(cartas->nome, "Evenstormer");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Evenstormer foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Evenstormer em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Evenstormer em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Evenstormer foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Evenstormer atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Evenstormer foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Evenstormer recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Evenstormer foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Evenstormer atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Evenstormer   |  MAGICA   |             2500/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Evenstormer       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    EVENSTORMER    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|     \\\\  |  //     |");
    strcpy(cartas->linhas[4].linha, "|     _\\\\ | //_     |");
    strcpy(cartas->linhas[5].linha, "|     \\\\  |  //     |");
    strcpy(cartas->linhas[6].linha, "|     _\\\\ | //_     |");
    strcpy(cartas->linhas[7].linha, "|     \\\\  |  //     |");
    strcpy(cartas->linhas[8].linha, "|      \\\\ | //      |");
    strcpy(cartas->linhas[9].linha, "| ______\\\\|//______ |");
    strcpy(cartas->linhas[10].linha, "|/\\____@@\\V/@@____/\\|");
    strcpy(cartas->linhas[11].linha, "|\\/_____@@V@@_____\\/|");
    strcpy(cartas->linhas[12].linha, "|       \\|||/       |");
    strcpy(cartas->linhas[13].linha, "|        |||        |");
    strcpy(cartas->linhas[14].linha, "|        |||        |");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|     ATK: 2500^    |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


    cartas++;
    cartas->tipo = 2;
    cartas->atk = 2700;
    cartas->def = 0;
    strcpy(cartas->nome, "Soul Sickle");
    strcpy(cartas->desc, "");
    strcpy(cartas->nome_menu[1].linha, "| Soul Sickle foi sumonada         |");
    strcpy(cartas->nome_menu[2].linha, "| Soul Sickle em modo de defesa    |");
    strcpy(cartas->nome_menu[3].linha, "| Soul Sickle em modo de ataque    |");
    strcpy(cartas->nome_menu[4].linha, "| Soul Sickle foi destruida        |");
    strcpy(cartas->nome_menu[5].linha, "| Soul Sickle atacou               |");
    strcpy(cartas->nome_menu[6].linha, "| Soul Sickle foi atacado          |");
    strcpy(cartas->nome_menu[7].linha, "| Soul Sickle recebeu um buff      |");
    strcpy(cartas->nome_menu[8].linha, "| Soul Sickle foi alvo de debuff   |");
    strcpy(cartas->nome_menu[9].linha, "| Soul Sickle atacou diretamente   |");
    strcpy(cartas->nome_menu[10].linha, "| Soul Sickle   |  MAGICA   |             2700/0 |");
    strcpy(cartas->nome_menu[0].linha, "|# - Soul Sickle       |");
    strcpy(cartas->linhas[0].linha, "+-------------------+");
    strcpy(cartas->linhas[1].linha, "|    SOUL SICKLE    |");
    strcpy(cartas->linhas[2].linha, "+-------------------+");
    strcpy(cartas->linhas[3].linha, "|**   ________   ***|");
    strcpy(cartas->linhas[4].linha, "|*   /SSSSSSSS\\   **|");
    strcpy(cartas->linhas[5].linha, "| /SSSSSS/\\SSSSS\\  *|");
    strcpy(cartas->linhas[6].linha, "|/SSS/       \\SSS\\  |");
    strcpy(cartas->linhas[7].linha, "| \\\\   **     \\SS/  |");
    strcpy(cartas->linhas[8].linha, "|* \\\\  *****   \\/  *|");
    strcpy(cartas->linhas[9].linha, "|** \\\\  ******    **|");
    strcpy(cartas->linhas[10].linha, "|**  \\\\  ***********|");
    strcpy(cartas->linhas[11].linha, "|***  \\\\  **********|");
    strcpy(cartas->linhas[12].linha, "|****  \\\\  *********|");
    strcpy(cartas->linhas[13].linha, "|*****  \\\\  ********|");
    strcpy(cartas->linhas[14].linha, "|******  \\|  *******|");
    strcpy(cartas->linhas[15].linha, "+-------------------+");
    strcpy(cartas->linhas[16].linha, "|      ATK: 2700^   |");
    strcpy(cartas->linhas[17].linha, "+-------------------+");


}
// Função responsável por aumentar ou diminuir um determinado atributo de uma carta.
void Buff(int indice, int indice_buffado , TEMP_CARTA * temp_carta, CARTA * cartas, int *mao) {


    int indice_buff = mao[indice];



    mao[indice] = -1;

    temp_carta[indice_buffado].atk += cartas[indice_buff].atk;

    temp_carta[indice_buffado].def += cartas[indice_buff].def;



    if (temp_carta[indice_buffado].atk > 9999) {

        temp_carta[indice_buffado].atk = 9999;
    }
    if (temp_carta[indice_buffado].def > 9999) {

        temp_carta[indice_buffado].def = 9999;
    }
    if (temp_carta[indice_buffado].atk < 0) {

        temp_carta[indice_buffado].atk = 0;
    }
    if (temp_carta[indice_buffado].def < 0) {

        temp_carta[indice_buffado].def = 0;
    }

    char temp_atk[5];

    char temp_def[5];

    sprintf(temp_atk, "%d", temp_carta[indice_buffado].atk);

    sprintf(temp_def, "%d", temp_carta[indice_buffado].def);

    temp_atk[4] = '\0';

    temp_def[4] = '\0';

    for (int i = 0; i < 4; i++) {

        if (temp_atk[i] == 0) {

            temp_atk[i] = 32;
        }
        if (temp_def[i] == 0) {

            temp_def[i] = 32;
        }
    }

    for (int i = 0; i < 4; i++) {

        temp_carta[indice_buffado].inf.linha[6 + i] = temp_atk[i];

        temp_carta[indice_buffado].inf.linha[16 + i] = temp_def[i];
    }


}
// Função responsável por aumentar ou diminuir os atributos de vida.
void BuffVida(int *vida, CARTA * cartas, int indice, int *mao) {

    int temp_ind = mao[indice];

    mao[indice] = -1;

    *vida += cartas[temp_ind].atk;

}

// Função que cria as telas de início do jogo.
void CriarTelas(TELA * telas) {
    // 109 largura 34 altura


    // 0
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
    strcpy(telas->linhas[14].linha, "|                                      |     1 INICIAR      |                                            |");
    strcpy(telas->linhas[15].linha, "|                                      +--------------------+                                            |");
    strcpy(telas->linhas[16].linha, "|                                                                                                        |");
    strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");
    // 1
    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[3].linha, "|                                            |  1 DUELO   |                                                 |");
    strcpy(telas->linhas[4].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[5].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[6].linha, "|                                            | 2 DECK     |                                                 |");
    strcpy(telas->linhas[7].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[8].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[9].linha, "|                                            | 3 CRÉDITOS |                                                 |");
    strcpy(telas->linhas[10].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[11].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[12].linha, "|                                            | 4 MANUAL   |                                                 |");
    strcpy(telas->linhas[13].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[14].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[15].linha, "|                                            | 5 SAIR     |                                                 |");
    strcpy(telas->linhas[16].linha, "|                                            +------------+                                                 |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------------------------------------------------------------+");
    // 2
    telas++;
    strcpy(telas->linhas[0].linha, "+------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                      |");
    strcpy(telas->linhas[2].linha, "|                           __________________ _______  _______ _________ _______  _                   |");
    strcpy(telas->linhas[3].linha, "|                  +\\     /+\\__   __/\\__   __/(  ___  )(  ____ )\\__   __/(  ___  )( )                  |");
    strcpy(telas->linhas[4].linha, "|                  | )   ( |   ) (      ) (   + (   ) ++ (    )+   ) (   + (   ) ++ +                  |");
    strcpy(telas->linhas[5].linha, "|                  + +   + +   + +      + +   | +   + || (____)+   + +   | (___) || |                  |");
    strcpy(telas->linhas[6].linha, "|                  ( (   ) )   | |      | |   | |   | ||     __)   | |   |  ___  ++ +                  |");
    strcpy(telas->linhas[7].linha, "|                   \\ \\_/ /    + +      | |   | +   + || (\\ (      + +   | (   ) |(_)                  |");
    strcpy(telas->linhas[8].linha, "|                    \\   /  ___) (___   + +   + (___) ++ ) \\ \\_____) (___| )   ( | _                   |");
    strcpy(telas->linhas[9].linha, "|                     \\_/   \\_______/   )_(   (_______)+/   \\__/\\_______/+/     \\+(_)                  |");
    strcpy(telas->linhas[10].linha, "|                                                                                                      |");
    strcpy(telas->linhas[11].linha, "|                                                                                                      |");
    strcpy(telas->linhas[12].linha, "|                                                                                                      |");
    strcpy(telas->linhas[13].linha, "|                                                                                                      |");
    strcpy(telas->linhas[14].linha, "|                                                                                                      |");
    strcpy(telas->linhas[15].linha, "|                                                                                                      |");
    strcpy(telas->linhas[16].linha, "|                                                                                                      |");
    strcpy(telas->linhas[17].linha, "+------------------------------------------------------------------------------------------------------+");


    // 3
    telas++;
    strcpy(telas->linhas[0].linha, "+----------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                    |");
    strcpy(telas->linhas[2].linha, "|                                                                                                    |");
    strcpy(telas->linhas[3].linha, "|                                                                                                    |");
    strcpy(telas->linhas[4].linha, "|           _______  _______  _______  _______    _______           _______  _______                 |");
    strcpy(telas->linhas[5].linha, "|          (  ____ \\(  ___  )(       )(  ____ \\  (  ___  )+\\     /+(  ____ \\(  ____ )                |");
    strcpy(telas->linhas[6].linha, "|          + (    \\/+ (   ) ++ () () ++ (    \\/  + (   ) ++ )   ( ++ (    \\/+ (    )+                |");
    strcpy(telas->linhas[7].linha, "|          | +      | (___) || ++ ++ || (__      | +   + ++ +   + ++ (__    | (____)+                |");
    strcpy(telas->linhas[8].linha, "|          | | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)                |");
    strcpy(telas->linhas[9].linha, "|          | + \\_  )| (   ) || +   + || (        | +   + | \\ \\_/ / | (      | (\\ (                   |");
    strcpy(telas->linhas[10].linha, "|          + (___) ++ )   ( || )   ( ++ (____/\\  + (___) +  \\   /  + (____/\\| ) \\ \\__                |");
    strcpy(telas->linhas[11].linha, "|          (_______)+/     \\++/     \\+(_______/  (_______)   \\_/   (_______/+/   \\__/                |");
    strcpy(telas->linhas[12].linha, "|                                                                                                    |");
    strcpy(telas->linhas[13].linha, "|                                                                                                    |");
    strcpy(telas->linhas[14].linha, "|                                                                                                    |");
    strcpy(telas->linhas[15].linha, "|                                                                                                    |");
    strcpy(telas->linhas[16].linha, "|                                                                                                    |");
    strcpy(telas->linhas[17].linha, "+----------------------------------------------------------------------------------------------------+");

    // 4
    telas++;
    strcpy(telas->linhas[0].linha, "+----------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                    |");
    strcpy(telas->linhas[2].linha, "|                                                                                                    |");
    strcpy(telas->linhas[3].linha, "|                                                                                                    |");
    strcpy(telas->linhas[4].linha, "|           _______  _______  _______  _______    _______           _______  _______                 |");
    strcpy(telas->linhas[5].linha, "|          (  ____ \\(  ___  )(       )(  ____ \\  (  ___  )+\\     /+(  ____ \\(  ____ )                |");
    strcpy(telas->linhas[6].linha, "|          + (    \\/+ (   ) ++ () () ++ (    \\/  + (   ) ++ )   ( ++ (    \\/+ (    )+                |");
    strcpy(telas->linhas[7].linha, "|          | +      | (___) || ++ ++ || (__      | +   + ++ +   + ++ (__    | (____)+                |");
    strcpy(telas->linhas[8].linha, "|          | | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)                |");
    strcpy(telas->linhas[9].linha, "|          | + \\_  )| (   ) || +   + || (        | +   + | \\ \\_/ / | (      | (\\ (                   |");
    strcpy(telas->linhas[10].linha, "|          + (___) ++ )   ( || )   ( ++ (____/\\  + (___) +  \\   /  + (____/\\| ) \\ \\__                |");
    strcpy(telas->linhas[11].linha, "|          (_______)+/     \\++/     \\+(_______/  (_______)   \\_/   (_______/+/   \\__/                |");
    strcpy(telas->linhas[12].linha, "|                                                                                                    |");
    strcpy(telas->linhas[13].linha, "|                                         +--------------+                                           |");
    strcpy(telas->linhas[14].linha, "|                                         | 1 CONTINUAR  |                                           |");
    strcpy(telas->linhas[15].linha, "|                                         +--------------+                                           |");
    strcpy(telas->linhas[16].linha, "|                                                                                                    |");
    strcpy(telas->linhas[17].linha, "+----------------------------------------------------------------------------------------------------+");


    // 5
    telas++;
    strcpy(telas->linhas[0].linha, "+------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                      |");
    strcpy(telas->linhas[2].linha, "|                           __________________ _______  _______ _________ _______  _                   |");
    strcpy(telas->linhas[3].linha, "|                  +\\     /+\\__   __/\\__   __/(  ___  )(  ____ )\\__   __/(  ___  )( )                  |");
    strcpy(telas->linhas[4].linha, "|                  | )   ( |   ) (      ) (   + (   ) ++ (    )+   ) (   + (   ) ++ +                  |");
    strcpy(telas->linhas[5].linha, "|                  + +   + +   + +      + +   | +   + || (____)+   + +   | (___) || |                  |");
    strcpy(telas->linhas[6].linha, "|                  ( (   ) )   | |      | |   | |   | ||     __)   | |   |  ___  ++ +                  |");
    strcpy(telas->linhas[7].linha, "|                   \\ \\_/ /    + +      | |   | +   + || (\\ (      + +   | (   ) |(_)                  |");
    strcpy(telas->linhas[8].linha, "|                    \\   /  ___) (___   + +   + (___) ++ ) \\ \\_____) (___| )   ( | _                   |");
    strcpy(telas->linhas[9].linha, "|                     \\_/   \\_______/   )_(   (_______)+/   \\__/\\_______/+/     \\+(_)                  |");
    strcpy(telas->linhas[10].linha, "|                                                                                                      |");
    strcpy(telas->linhas[11].linha, "|                                          +--------------+                                            |");
    strcpy(telas->linhas[12].linha, "|                                          | 1 CONTINUAR  |                                            |");
    strcpy(telas->linhas[13].linha, "|                                          +--------------+                                            |");
    strcpy(telas->linhas[14].linha, "|                                                                                                      |");
    strcpy(telas->linhas[15].linha, "|                                                                                                      |");
    strcpy(telas->linhas[16].linha, "|                                                                                                      |");
    strcpy(telas->linhas[17].linha, "+------------------------------------------------------------------------------------------------------+");


    // 6
    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                        BLOQUEADO       RANK: ***                                          |");
    strcpy(telas->linhas[3].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[4].linha, "|                                        |       XXXXXXXXXXXX      |                                        |");
    strcpy(telas->linhas[5].linha, "|                                        |       XXXXXXXXXXXX      |                                        |");
    strcpy(telas->linhas[6].linha, "|                                        |       XX        XX      |                                        |");
    strcpy(telas->linhas[7].linha, "|                                        |           XXXXXXXX      |                                        |");
    strcpy(telas->linhas[8].linha, "|                                        |           XX            |                                        |");
    strcpy(telas->linhas[9].linha, "|                                        |                         |                                        |");
    strcpy(telas->linhas[10].linha, "|                                        |           XX            |                                        |");
    strcpy(telas->linhas[11].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|  +------------+                                                                           +------------+  |");
    strcpy(telas->linhas[14].linha, "|  |1 Anterior  |                                                                           |  2 Próximo |  |");
    strcpy(telas->linhas[15].linha, "|  +------------+                                                                           +------------+  |");
    strcpy(telas->linhas[16].linha, "|                                                                                                           |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------------------------------------------------------------+");

    // 7
    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                        BLOQUEADO       RANK: *****                                        |");
    strcpy(telas->linhas[3].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[4].linha, "|                                        |       XXXXXXXXXXXX      |                                        |");
    strcpy(telas->linhas[5].linha, "|                                        |       XXXXXXXXXXXX      |                                        |");
    strcpy(telas->linhas[6].linha, "|                                        |       XX        XX      |                                        |");
    strcpy(telas->linhas[7].linha, "|                                        |           XXXXXXXX      |                                        |");
    strcpy(telas->linhas[8].linha, "|                                        |           XX            |                                        |");
    strcpy(telas->linhas[9].linha, "|                                        |                         |                                        |");
    strcpy(telas->linhas[10].linha, "|                                        |           XX            |                                        |");
    strcpy(telas->linhas[11].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|  +------------+                                                                                           |");
    strcpy(telas->linhas[14].linha, "|  |1 Anterior  |                                                                                           |");
    strcpy(telas->linhas[15].linha, "|  +------------+                                                                                           |");
    strcpy(telas->linhas[16].linha, "|                                                                                                           |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------------------------------------------------------------+");
    // 8
    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                        SETO PROCÓPIO     RANK:*                                           |");
    strcpy(telas->linhas[3].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[4].linha, "|                                        |      /////\\\\\\\\\\\\\\       |                                        |");
    strcpy(telas->linhas[5].linha, "|                                        |      /-[o]-[o]-\\\\\\      |                                        |");
    strcpy(telas->linhas[6].linha, "|                                        |      /|  c     |\\\\      |                                        |");
    strcpy(telas->linhas[7].linha, "|                                        |      /|  ___   |\\\\      |                                        |");
    strcpy(telas->linhas[8].linha, "|                                        |      /|________|\\\\\\     |                                        |");
    strcpy(telas->linhas[9].linha, "|                                        |      ////|___|\\\\\\\\      |                                        |");
    strcpy(telas->linhas[10].linha, "|                                        |       |         |       |                                        |");
    strcpy(telas->linhas[11].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|  +------------+                             +-------------+                               +------------+  |");
    strcpy(telas->linhas[14].linha, "|  |1 Anterior  |                             |   3 Duelar  |                               |  2 Próximo |  |");
    strcpy(telas->linhas[15].linha, "|  +------------+                             +-------------+                               +------------+  |");
    strcpy(telas->linhas[16].linha, "|                                                                                                           |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------------------------------------------------------------+");
    // 9
    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                         MAXIMILION ENIALE RANK: ***                                       |");
    strcpy(telas->linhas[3].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[4].linha, "|                                        |     (((((((((((((       |                                        |");
    strcpy(telas->linhas[5].linha, "|                                        |     (((\\    /(((((      |                                        |");
    strcpy(telas->linhas[6].linha, "|                                        |     (|(0\\  /0( ^(       |                                        |");
    strcpy(telas->linhas[7].linha, "|                                        |     (|   ^   ( (((      |                                        |");
    strcpy(telas->linhas[8].linha, "|                                        |     )\\ \\____/(|((       |                                        |");
    strcpy(telas->linhas[9].linha, "|                                        |     ))\\___    |(((      |                                        |");
    strcpy(telas->linhas[10].linha, "|                                        |       ))))|   |((       |                                        |");
    strcpy(telas->linhas[11].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|  +------------+                             +-------------+                               +------------+  |");
    strcpy(telas->linhas[14].linha, "|  |1 Anterior  |                             |   3 Duelar  |                               |  2 Próximo |  |");
    strcpy(telas->linhas[15].linha, "|  +------------+                             +-------------+                               +------------+  |");
    strcpy(telas->linhas[16].linha, "|                                                                                                           |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------------------------------------------------------------+");
    // 10

    telas++;
    strcpy(telas->linhas[0].linha, "+-----------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                                                                                           |");
    strcpy(telas->linhas[2].linha, "|                                        YAMI REDAJ       RANK:*****                                        |");
    strcpy(telas->linhas[3].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[4].linha, "|                                        |    @@@@@@@@@@@@@@       |                                        |");
    strcpy(telas->linhas[5].linha, "|                                        |    @| \\    /  |@@       |                                        |");
    strcpy(telas->linhas[6].linha, "|                                        |   @@| U    U  |@@       |                                        |");
    strcpy(telas->linhas[7].linha, "|                                        |    @|   ^     |@@       |                                        |");
    strcpy(telas->linhas[8].linha, "|                                        |   @@ \\   V   @ @ @      |                                        |");
    strcpy(telas->linhas[9].linha, "|                                        |      /\\_____/\\          |                                        |");
    strcpy(telas->linhas[10].linha, "|                                        |     /         \\         |                                        |");
    strcpy(telas->linhas[11].linha, "|                                        +-------------------------+                                        |");
    strcpy(telas->linhas[12].linha, "|                                                                                                           |");
    strcpy(telas->linhas[13].linha, "|  +------------+                             +-------------+                                               |");
    strcpy(telas->linhas[14].linha, "|  |1 Anterior  |                             |   3 Duelar  |                                               |");
    strcpy(telas->linhas[15].linha, "|  +------------+                             +-------------+                                               |");
    strcpy(telas->linhas[16].linha, "|                                                                                                           |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------------------------------------------------------------+");

    // 11
    telas++;
    strcpy(telas->linhas[0].linha, "+----------+----+-------------------+----------------------------------+--------------------+---------------+");
    strcpy(telas->linhas[1].linha, "| 5 VOLTAR |    |       DECK        |      |PAGINA  01|                |        BAU         |    |PAGINA  01|");
    strcpy(telas->linhas[2].linha, "+----------+    +-------------------+      +----------+                +--------------------+    +----------+");
    strcpy(telas->linhas[3].linha, "|                                                     |                                                     |");
    strcpy(telas->linhas[4].linha, "| +---------------+-----------+--------------------+  | +---------------+-----------+--------------------+  |");
    strcpy(telas->linhas[5].linha, "| |    NOME       |    TIPO   |           ATK/DEF  |  | |    NOME       |    TIPO   |           ATK/DEF  |  |");
    strcpy(telas->linhas[6].linha, "| +------------------------------------------------+  | +------------------------------------------------+  |");
    strcpy(telas->linhas[7].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[8].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[9].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[10].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[11].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[12].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[13].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[14].linha, "| +------------------------------------------------+  | +---------------+-----------+--------------------+  |");
    strcpy(telas->linhas[15].linha, "|       +----------+  +---------+ +---------+         |                                                     |");
    strcpy(telas->linhas[16].linha, "|       | 1 TROCAR |  | 2 CIMA  | | 3 BAIXO |         |                                                     |");
    strcpy(telas->linhas[17].linha, "+-------+----------+--+---------+ +---------+---------+-----------------------------------------------------+");
    //12
    telas++;
    strcpy(telas->linhas[0].linha, "+---------------+-------------------+----------------------------------+--------------------+---------------+");
    strcpy(telas->linhas[1].linha, "|               |       DECK        |      |PAGINA  01|                |        BAU         |    |PAGINA  01|");
    strcpy(telas->linhas[2].linha, "|               +-------------------+      +----------+                +--------------------+    +----------+");
    strcpy(telas->linhas[3].linha, "|                                                     |                                                     |");
    strcpy(telas->linhas[4].linha, "| +---------------+-----------+--------------------+  | +---------------+-----------+--------------------+  |");
    strcpy(telas->linhas[5].linha, "| |    NOME       |    TIPO   |           ATK/DEF  |  | |    NOME       |    TIPO   |           ATK/DEF  |  |");
    strcpy(telas->linhas[6].linha, "| +------------------------------------------------+  | +------------------------------------------------+  |");
    strcpy(telas->linhas[7].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[8].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[9].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[10].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[11].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[12].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[13].linha, "| |               |           |                    |  | |               |           |                    |  |");
    strcpy(telas->linhas[14].linha, "| +---------------+-----------+--------------------+  | +------------------------------------------------+  |");
    strcpy(telas->linhas[15].linha, "|                                                     |      +----------+  +---------+ +---------+          |");
    strcpy(telas->linhas[16].linha, "|                                                     |      | 1 TROCAR |  | 2 CIMA  | | 3 BAIXO |          |");
    strcpy(telas->linhas[17].linha, "+-----------------------------------------------------+------+----------+--+---------+-+---------+----------+");

    //13
    telas++;
    strcpy(telas->linhas[0].linha, "+--------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                             CREDITOS                                                   |");
    strcpy(telas->linhas[2].linha, "|--------------------------------------------------------------------------------------------------------|");
    strcpy(telas->linhas[3].linha, "|                                                                                                        |");
    strcpy(telas->linhas[4].linha, "|                                                                                                        |");
    strcpy(telas->linhas[5].linha, "|                              ARTHUR VINICIUS FOGAÇA DE ANDRADE   RA:1997343                            |");
    strcpy(telas->linhas[6].linha, "|                              FABIO LEONAM PEREIRA DE SOUZA  RA:1997394                                 |");
    strcpy(telas->linhas[7].linha, "|                              LUCAS DE ALMEIDA RA:1996762                                               |");
    strcpy(telas->linhas[8].linha, "|                              THIAGO ANGELO MARTINS RA:1997513                                          |");
    strcpy(telas->linhas[9].linha, "|                              VINICIUS AUGUSTO DE SOUZA RA:1997530                                      |");
    strcpy(telas->linhas[10].linha, "|                                                                                                        |");
    strcpy(telas->linhas[11].linha, "|                              DISCIPLINA: ALGORITMOS 2                                                  |");
    strcpy(telas->linhas[12].linha, "|                              PROFESSOR: JADER                                                          |");
    strcpy(telas->linhas[13].linha, "|                                                                                                        |");
    strcpy(telas->linhas[14].linha, "|                                                                                                        |");
    strcpy(telas->linhas[15].linha, "|                                          1-VOLTAR AO MENU                                              |");
    strcpy(telas->linhas[16].linha, "|                                          2-SAIR                                                        |");
    strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");

    //14
    telas++;
    strcpy(telas->linhas[0].linha, "+--------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                              MANUAL                                                    |");
    strcpy(telas->linhas[2].linha, "|--------------------------------------------------------------------------------------------------------|");
    strcpy(telas->linhas[3].linha, "|  OBJETIVO:                                                                                             |");
    strcpy(telas->linhas[4].linha, "|-> O objetivo principal do jogo é você vencer um duelo sobre três adversArios, estes com dificuldades   |");
    strcpy(telas->linhas[5].linha, "|diferentes.                                                                                             |");
    strcpy(telas->linhas[6].linha, "|                                                                                                        |");
    strcpy(telas->linhas[7].linha, "|  ESTRUTURA:                                                                                            |");
    strcpy(telas->linhas[8].linha, "|->Cada jogador tem seu deck que contém 20 cartas.                                                       |");
    strcpy(telas->linhas[9].linha, "|->A carta tem modo ataque e modo defesa,esses no quais estao contidos na descrição da carta.            |");
    strcpy(telas->linhas[10].linha, "|  DINAMICA DO DUELO:                                                                                    |");
    strcpy(telas->linhas[11].linha, "|-> Ao atacar a carta do adversArio, ela só serA destruída caso o seu ataque for maior que o ataque da   |");
    strcpy(telas->linhas[12].linha, "| carta atacada, ou que o ataque seja maior que a defesa, caso a carta atacada esteja em modo defesa.    |");
    strcpy(telas->linhas[13].linha, "|                                                                                                        |");
    strcpy(telas->linhas[14].linha, "|                                                                                                        |");
    strcpy(telas->linhas[15].linha, "|                                          1-VOLTAR AO MENU                                3-PROXIMO     |");
    strcpy(telas->linhas[16].linha, "|                                          2-SAIR                                                        |");
    strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");

    //15
    telas++;
    strcpy(telas->linhas[0].linha, "+--------------------------------------------------------------------------------------------------------+");
    strcpy(telas->linhas[1].linha, "|                                              MANUAL                                                    |");
    strcpy(telas->linhas[2].linha, "|--------------------------------------------------------------------------------------------------------|");
    strcpy(telas->linhas[3].linha, "|                                                                                                        |");
    strcpy(telas->linhas[4].linha, "|-> Se no campo do jogador não haver mais cartas, você pode ataca-ló diretamente, tirando pontos de sua  |");
    strcpy(telas->linhas[5].linha, "|de acordo com o ataque da carta.                                                                        |");
    strcpy(telas->linhas[6].linha, "|-> Caso a carta atacada não esteja no modo defesa, a difença do ataque das cartas é descontado no pontos|");
    strcpy(telas->linhas[7].linha, "|de vida do adversario, caso esteja em modo defesa, e o ataque seja maior que a defesa, a carta apenas é |");
    strcpy(telas->linhas[8].linha, "|destruida e diferença do ataque e defesa não é descontado na vida do adversArio.                        |");
    strcpy(telas->linhas[9].linha, "|->Se o ponto do adversArio chegar a 0, jogador vence o duelo.                                           |");
    strcpy(telas->linhas[10].linha, "|                                                                                                        |");
    strcpy(telas->linhas[11].linha, "|                                                                                                        |");
    strcpy(telas->linhas[12].linha, "|                                                                                                        |");
    strcpy(telas->linhas[13].linha, "|                                                                                                        |");
    strcpy(telas->linhas[14].linha, "|                                                                                                        |");
    strcpy(telas->linhas[15].linha, "|  4-VOLTAR                                1-VOLTAR AO MENU                                              |");
    strcpy(telas->linhas[16].linha, "|                                          2-SAIR                                                        |");
    strcpy(telas->linhas[17].linha, "+--------------------------------------------------------------------------------------------------------+");

}
// Função que desenha os gráficos quando na tela de editar o deck do jogador
void DesenharDeck(CARTA * cartas, int *deck_jogador, int *bau, TELA * telas, int *menu_state, int *menu_state2, int *deck_pag, int *deck_pag2, int *deck_side) {


    telas += 11;

    if (*deck_side) {

        strcpy(telas->linhas[15].linha, "|                                                     |      +----------+  +---------+ +---------+          |");
        strcpy(telas->linhas[16].linha, "|                                                     |      | 1 TROCAR |  | 2 CIMA  | | 3 BAIXO |          |");
        strcpy(telas->linhas[17].linha, "+-----------------------------------------------------+------+----------+--+---------+-+---------+----------+");

    } else {

        strcpy(telas->linhas[15].linha, "|       +----------+  +---------+ +---------+         |                                                     |");
        strcpy(telas->linhas[16].linha, "|       | 1 TROCAR |  | 2 CIMA  | | 3 BAIXO |         |                                                     |");
        strcpy(telas->linhas[17].linha, "+-------+----------+--+---------+ +---------+---------+-----------------------------------------------------+");

    }



    if (*menu_state < 0) {


        *deck_pag -= 1;

        if (*deck_pag < 0) {

            *deck_pag = 0;

            *menu_state = 0;

        } else {

            *menu_state = 6;
        }
        //Limpar tela
        for (int i = 0; i < 7; i++) {

            for (int n = 0; n < 50; n++) {



                telas->linhas[7 + i].linha[n + 2] = cartas[0].nome_menu[10].linha[n];

            }
        }

    }
    else if (*menu_state > 6) {

        *deck_pag += 1;

        if (*deck_pag > 3) {

            *deck_pag = 3;

            *menu_state = 6;

        } else {

            *menu_state = 0;

        }
        //Limpar tela
        for (int i = 0; i < 7; i++) {

            for (int n = 0; n < 50; n++) {



                telas->linhas[7 + i].linha[n + 2] = cartas[0].nome_menu[10].linha[n];

            }
        }

    }

    if (*menu_state2 < 0) {


        *deck_pag2 -= 1;

        if (*deck_pag2 < 0) {

            *deck_pag2 = 0;

            *menu_state2 = 0;

        } else {

            *menu_state2 = 6;
        }
        //Limpar tela
        for (int i = 0; i < 7; i++) {

            for (int n = 0; n < 50; n++) {



                telas->linhas[7 + i].linha[n + 56] = cartas[0].nome_menu[10].linha[n];

            }
        }

    }
    else if (*menu_state2 > 6) {

        *deck_pag2 += 1;

        if (*deck_pag2 > 3) {

            *deck_pag2 = 3;

            *menu_state2 = 6;

        } else {

            *menu_state2 = 0;

        }
        //Limpar tela
        for (int i = 0; i < 7; i++) {

            for (int n = 0; n < 50; n++) {



                telas->linhas[7 + i].linha[n + 56] = cartas[0].nome_menu[10].linha[n];

            }
        }

    }

    int multiplier2 = *deck_pag2 * 6;

    for (int i = 0; i < 7; i++) {

        for (int n = 0; n < 50; n++) {

            int ind = i + multiplier2;

            if (ind < 40) {

                if (bau[ind] != -1) {

                    telas->linhas[7 + i].linha[n + 56] = cartas[bau[ind]].nome_menu[10].linha[n];
                }


            }

        }
    }

    int multiplier = *deck_pag * 6;

    for (int i = 0; i < 7; i++) {

        for (int n = 0; n < 50; n++) {

            int ind = i + multiplier;

            if (ind < 20) {



                telas->linhas[7 + i].linha[n + 2] = cartas[deck_jogador[ind]].nome_menu[10].linha[n];
            }

        }

        if ( i == *menu_state) {

            telas->linhas[7 + i].linha[1] = 62;

        } else {

            telas->linhas[7 + i].linha[1] = 32;
        }

    }

    if (*deck_side) {

        for (int i = 0; i < 7; i++) {

            if ( i == *menu_state2) {

                telas->linhas[7 + i].linha[55] = 62;

            } else {

                telas->linhas[7 + i].linha[55] = 32;
            }

        }

    } else {

        for (int i = 0; i < 7; i++) {


            telas->linhas[7 + i].linha[55] = 62;



            telas->linhas[7 + i].linha[55] = 32;


        }

    }

    telas->linhas[1].linha[53] = (49 + *deck_pag);
    telas->linhas[1].linha[107] = (49 + *deck_pag2);

    LimparTela(SIS);

    for (int i = 0; i <= 17; i++) {

        printf("%s\n", telas->linhas[i].linha);

    }

}
// Função que pega os comandos do jogador e muda as variáveis que se referem a tela de editar o deck.
void MudarDeck(int comand, int *deck_edit, int *entrada, int *menu_state, int*menu_state2, int *tela_num, int *deck_side, int *deck_pag, int *deck_pag2, int *deck_jogador, int *bau, TELA * telas) {


    switch (comand) {


    case 1:

        if (*deck_side) {



            int multiplier = *menu_state + ( *deck_pag * 6);

            int multiplier2 = *menu_state2 + (*deck_pag2 * 6);

            if (bau[multiplier2] != -1) {

                int temp = deck_jogador[multiplier];

                deck_jogador[multiplier] = bau[multiplier2];

                bau[multiplier2] = temp;

                //Save(deck_jogador, bau);

                *deck_side = 0;
            }



        } else {


            *deck_side = 1;

        }

        break;

    case 2:

        if (*deck_side) {

            *menu_state2 -= 1;

        } else {

            *menu_state -= 1;

        }


        break;
    case 3:

        if (*deck_side) {

            *menu_state2 += 1;

        } else {
            *menu_state += 1;

        }
        break;

    case 5:



        telas += 11;
        strcpy(telas->linhas[0].linha, "+---------------+-------------------+----------------------------------+--------------------+---------------+");
        strcpy(telas->linhas[1].linha, "|               |       DECK        |      |PAGINA  01|                |        BAU         |    |PAGINA  01|");
        strcpy(telas->linhas[2].linha, "|               +-------------------+      +----------+                +--------------------+    +----------+");
        strcpy(telas->linhas[3].linha, "|                                                     |                                                     |");
        strcpy(telas->linhas[4].linha, "| +---------------+-----------+--------------------+  | +---------------+-----------+--------------------+  |");
        strcpy(telas->linhas[5].linha, "| |    NOME       |    TIPO   |           ATK/DEF  |  | |    NOME       |    TIPO   |           ATK/DEF  |  |");
        strcpy(telas->linhas[6].linha, "| +------------------------------------------------+  | +------------------------------------------------+  |");
        strcpy(telas->linhas[7].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[8].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[9].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[10].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[11].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[12].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[13].linha, "| |               |           |                    |  | |               |           |                    |  |");
        strcpy(telas->linhas[14].linha, "| +------------------------------------------------+  | +---------------+-----------+--------------------+  |");
        strcpy(telas->linhas[15].linha, "|  +---------+  +---------+ +---------+ +----------+  |                                                     |");
        strcpy(telas->linhas[16].linha, "|  |1 TROCAR |  | 2 CIMA  | | 3 BAIXO | | 4 INFO   |  |                                                     |");
        strcpy(telas->linhas[17].linha, "+- +---------+--+---------+ +---------+-+----------+--+-----------------------------------------------------+");

        *menu_state = 0;
        *menu_state2 = 0;
        *deck_pag = 0;
        *deck_pag2 = 0;
        *deck_side = 0;
        *entrada = 1;
        *deck_edit = 0;
        *tela_num = 1;

        break;

    }

}

// Desenhando a Mesa do Jogo.
void DesenharMesa(int *mesa_aliada, int *mesa_inimiga, int *mao_jogador, CARTA * cartas, HUD * hud, TEMP_CARTA * temp_mesa_jogador, TEMP_CARTA * temp_mesa_inimigo, int *menu) {



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
        if (count_hud >= 23) {

            printf("      %s", hud->linhas[count_hud].linha);
            count_hud++;
            printf("\n");

        } else {

            printf("%s", hud->linhas[count_hud].linha);
            count_hud++;
            printf("\n");
        }

    }
    hud ++;
    //Desenha 3 linhas para separar o campo do jogo das cartas na mão do jogador
    for (i = 0; i < 3; i++) {

        printf("%s", hud->linhas[i].linha);
        printf("      %s\n", (hud + 1)->linhas[i].linha);
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

            printf("      %s", hud->linhas[j + 3].linha);

            count_hud3++;

        }


        printf("\n");
    }

    printf("\n");


    count_hud = 0 ;

}

// Função responsAvel por exibir as escolhas na HUD.
void DesenharMenu(int escolha, HUD * hud, CARTA * cartas, int *mao_jogador, int *mesa_aliada, int *mesa_inimiga, int *menu, TEMP_CARTA * temp_carta) {

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
                if (temp_carta[i].modo == 0 && temp_carta[i].atacou == 0) {

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


    case 10:

        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Descartar         |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|                      |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|6 - Voltar            |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");

        break;

    case 11:

        strcpy(hud->linhas[26].linha, "|                      |");
        strcpy(hud->linhas[27].linha, "|1 - Usar Carta MAgica |");
        strcpy(hud->linhas[28].linha, "|                      |");
        strcpy(hud->linhas[29].linha, "|2 - Atacar            |");
        strcpy(hud->linhas[30].linha, "|                      |");
        strcpy(hud->linhas[31].linha, "|                      |");
        strcpy(hud->linhas[32].linha, "|                      |");
        strcpy(hud->linhas[33].linha, "|                      |");
        strcpy(hud->linhas[34].linha, "|                      |");

        break;

    }

}

// Função que conta quantos algarismos um número possui e retorna.
int ContaAlgarismos(int num) {

    int count = 0;

    int temp = num;

    while (temp > 0) {

        temp = temp / 10;



        count++;

    }


    return count;

}
// Função que rearranja o baú de forma que a última carta é perdida e todas as outras são jogadas para baixo
void ReaBau(int *bau) {


    for (int i = 39; i >= 0; i--) {

        if ((i - 1) >= 0) {

            bau[i] = bau[i - 1];
        }

    }

}

void AtualizarPlacar(HUD * hud, int *vida, int *atgame, int *entrada, int *tela_num, int *inimigo_escolha, int *blocked1, int*blocked2, int* bau, INIMIGO * inimigos) {

    int i;

    int vida_jogador = vida[0];
    int vida_inimigo = vida[1];

    srand(time(0));

    int random = 0;


    int tam_vidaJogador = ContaAlgarismos(vida_jogador);

    int tam_vidaInimigo = ContaAlgarismos(vida_inimigo);

    hud += 3;

    char str_jogador[10];

    char str_inimigo[10];

    sprintf(str_jogador, "%d", vida_jogador);
    sprintf(str_inimigo, "%d", vida_inimigo);

    strcpy(hud->linhas[4].linha, "|                      |");

    for (i = 0; i < tam_vidaJogador; i++) {

        hud->linhas[4].linha[11 + i] = str_jogador[i];
    }

    strcpy(hud->linhas[9].linha, "|                      |");

    for (i = 0; i < tam_vidaInimigo; i++) {

        hud->linhas[9].linha[11 + i] = str_inimigo[i];
    }

    if (vida_jogador <= 0) {


        *atgame = 0;

        *entrada = 1;

        *tela_num = 3;

    }

    if (vida_inimigo <= 0) {

        sleep(2);

        IniciarInimigos(inimigos);

        switch (*inimigo_escolha) {

        case 0:

            ReaBau(bau);

            random = rand() % 21;

            bau[0] = inimigos->deck[random];

            *blocked1 = 0;

            break;

        case 1:

            ReaBau(bau);

            random = rand() % 21;

            bau[0] = (inimigos + 1)->deck[random];

            *blocked2 = 0;
            break;

        case 2:

            ReaBau(bau);

            random = rand() % 21;

            bau[0] = (inimigos + 2)->deck[random];


            break;

        }

        *atgame = 0;

        *entrada = 1;

        *tela_num = 2;

    }

}

// Função responsAvel por desenhar as telas do jogo.
void DesenharTela(int tel, TELA * telas) {

    int i;

    LimparTela(SIS);

    telas += tel;

    for (i = 0; i <= 17; i++) {

        printf("%s\n", telas->linhas[i].linha);

    }

}


// Função que limpa a tela do console do sistema de acordo com o sistema operacional.
void LimparTela(int sistema) {

    if (sistema) {
        system("cls");

    } else {

        system("clear");

    }

}

// Função responsAvel por limpar o menu da HUD.
void LimparMenu(HUD * hud) {
    int i;
    hud++;
    for (i = HUD_INICIO; i <= HUD_FIM; i++) {

        strcpy(hud->linhas[i].linha, "|                      |");


    }

}

// Muda as telas do jogo baseado nos comando dados pelo jogador.
void MudarTela(int comand, int *tela_num, int *atgame, int *entrada, int blocked1, int blocked2, int *inimigo_escolha, int *deck_edit, int *tela_anterior, int *tela_criar, int *deck_jogador, int*bau) {


    switch (*tela_num) {

    case 0:

        switch (comand) {


        case 1:

            *tela_num = 1;
            break;




        default:

            printf("Comando invAlido.\n");
            break;

        }

        break;

    case 1:

        switch (comand) {

        case 1:

            *tela_num = 8;
            break;

        case 2:

            *entrada = 0;
            *deck_edit = 1;
            *tela_num = 387;
            *tela_anterior = 385;
            *tela_criar = 1;

            break;

        case 3:
            *tela_num = 13;
            break;

        case 4:
            *tela_num = 14;
            break;

        case 5:

            Save(deck_jogador, bau);

            exit(0);
            break;

        default:
            printf("Comando invAlido\n");
            break;

        }

        break;

    case 13:

        switch (comand) {

        case 1:

            *tela_num = 1;
            break;

        case 2:
            *tela_num = 0;
            break;
        }

        break;

    case 14:
        switch (comand) {

        case 1:
            *tela_num = 1;
            break;
        case 2:
            *tela_num = 0;
            break;

        case 3:
            *tela_num = 15;
            break;

        }
        break;

    case 15:
        switch (comand) {

        case 1:
            *tela_num = 1;
            break;
        case 2:
            *tela_num = 0;
            break;

        case 4:
            *tela_num = 14;
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
            printf("Comando invAlido\n");
            break;



        }

        break;

    case 5:


        switch (comand) {

        case 1:

            *tela_num = 1;

            break;

        default:

            printf("Comando invAlido\n");

            break;



        }

        break;

    case 4:


        switch (comand) {

        case 1:

            *tela_num = 1;

            break;

        default:

            printf("Comando invAlido\n");

            break;



        }

        break;

    case 6:

        switch (comand) {

        case 1:

            *tela_num = 8;

            break;

        case 2:
            if (blocked2) {

                *tela_num = 7;
            } else {

                *tela_num = 10;
            }
            break;


        }

        break;

    case 7:

        switch (comand) {

        case 1:

            if (blocked1) {

                *tela_num = 6;
            } else {

                *tela_num = 9;
            }

            break;

        }

        break;

    case 10:
        switch (comand) {

        case 1:

            if (blocked1) {

                *tela_num = 6;
            } else {

                *tela_num = 9;
            }

            break;
        case 3:

            *atgame = 1;
            *entrada = 0;
            *inimigo_escolha = 2;

            break;


        }

        break;

    case 9:

        switch (comand) {

        case 1:

            *tela_num = 8;

            break;

        case 2:
            if (blocked2) {

                *tela_num = 7;
            } else {

                *tela_num = 10;
            }
            break;

        case 3:

            *atgame = 1;
            *entrada = 0;
            *inimigo_escolha = 1;

            break;
        }
        break;

    case 8:
        switch (comand) {

        case 1:
            *tela_num = 1;
            break;

        case 2:
            if (blocked1) {

                *tela_num = 6;
            } else {

                *tela_num = 9;
            }
            break;

        case 3:

            *atgame = 1;
            *entrada = 0;
            *inimigo_escolha = 0;

            break;

        }

        break;



    }


}

// Desenha a nova tela se a mesma tiver mudado.
void TransicaoTela(int *tela_num, int *tela_anterior, int *tela_criar, TELA * telas) {


    if (!*tela_criar || *tela_anterior != *tela_num) {

        LimparTela(SIS);

        DesenharTela(*tela_num, telas);

        *tela_anterior = *tela_num;

        *tela_criar = 1;

    }

    if (*tela_num == 2) {

        sleep(5);

        *tela_num = 5;

        *tela_criar = 1;

        TransicaoTela(tela_num, tela_anterior, tela_criar, telas);
    }

    else if (*tela_num == 3) {

        sleep(5);

        *tela_num = 4;

        *tela_criar = 1;

        TransicaoTela(tela_num, tela_anterior, tela_criar, telas);

    }

}

// Função que inicializa os decks dos inimigos.
void IniciarInimigos(INIMIGO * inimigos) {

    inimigos->deck[0] = 21;
    inimigos->deck[1] = 22;
    inimigos->deck[2] = 23;
    inimigos->deck[3] = 24;
    inimigos->deck[4] = 25;
    inimigos->deck[5] = 26;
    inimigos->deck[6] = 27;
    inimigos->deck[7] = 28;
    inimigos->deck[8] = 29;
    inimigos->deck[9] = 30;
    inimigos->deck[10] = 31;
    inimigos->deck[11] = 32;
    inimigos->deck[12] = 33;
    inimigos->deck[13] = 34;
    inimigos->deck[14] = 35;
    inimigos->deck[15] = 36;
    inimigos->deck[16] = 37;
    inimigos->deck[17] = 38;
    inimigos->deck[18] = 39;
    inimigos->deck[19] = 40;

    strcpy(inimigos->nome, "Seto Procópio");

    inimigos++;

    inimigos->deck[0] = 41;
    inimigos->deck[1] = 42;
    inimigos->deck[2] = 43;
    inimigos->deck[3] = 44;
    inimigos->deck[4] = 45;
    inimigos->deck[5] = 46;
    inimigos->deck[6] = 47;
    inimigos->deck[7] = 48;
    inimigos->deck[8] = 49;
    inimigos->deck[9] = 50;
    inimigos->deck[10] = 51;
    inimigos->deck[11] = 52;
    inimigos->deck[12] = 53;
    inimigos->deck[13] = 54;
    inimigos->deck[14] = 55;
    inimigos->deck[15] = 56;
    inimigos->deck[16] = 57;
    inimigos->deck[17] = 58;
    inimigos->deck[18] = 59;
    inimigos->deck[19] = 60;

    strcpy(inimigos->nome, "Jono");

    inimigos++;

    inimigos->deck[0] = 61;
    inimigos->deck[1] = 61;
    inimigos->deck[2] = 62;
    inimigos->deck[3] = 63;
    inimigos->deck[4] = 64;
    inimigos->deck[5] = 65;
    inimigos->deck[6] = 66;
    inimigos->deck[7] = 67;
    inimigos->deck[8] = 68;
    inimigos->deck[9] = 69;
    inimigos->deck[10] = 70;
    inimigos->deck[11] = 71;
    inimigos->deck[12] = 72;
    inimigos->deck[13] = 73;
    inimigos->deck[14] = 74;
    inimigos->deck[15] = 75;
    inimigos->deck[16] = 76;
    inimigos->deck[17] = 77;
    inimigos->deck[18] = 78;
    inimigos->deck[19] = 79;

    strcpy(inimigos->nome, "Yami Redaj");

}

// Função que embaralha os decks de forma que a sequencia de cartas que viram seja imprevisível.
void EmbaralharDecks(int *deck_jogador, INIMIGO * inimigos) {

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

// Função que salva o deck do jogador e bau em um arquivo binario.
void Save(int *deck_jogador, int *bau) {



    FILE *save;

    save = fopen("save.bin", "wb");

    for (int i = 0; i < 20; i++) {

        fwrite(&deck_jogador[i], sizeof(int), 1, save);

    }

    for (int i = 0; i < 40; i++) {

        fwrite(&bau[i], sizeof(int), 1, save);

    }


    fclose(save);


}

// Função que somente le o arquivo binário de save e carrega os valores para o deck do jogador.
void LoadDeck(int *deck_jogador) {

    FILE *save;


    save = fopen("save.bin", "rb");



    for (int i = 0; i < 20; i++) {

        fread(&deck_jogador[i], sizeof(int), 1, save);
    }



    fclose(save);

}
// Função que carrega o deck inicial do jogador e cria um save binário se não existir um.
void Load(int *deck_jogador, int *bau) {



    FILE *save;


    if ((save = fopen("save.bin", "rb")))
    {


        for (int i = 0; i < 20; i++) {

            fread(&deck_jogador[i], sizeof(int), 1, save);
        }

        for (int i = 0; i < 40; i++) {

            fread(&bau[i], sizeof(int), 1, save);
        }


        fclose(save);

    } else {


        deck_jogador[0] = 1;
        deck_jogador[1] = 2;
        deck_jogador[2] = 3;
        deck_jogador[3] = 4;
        deck_jogador[4] = 5;
        deck_jogador[5] = 6;
        deck_jogador[6] = 7;
        deck_jogador[7] = 8;
        deck_jogador[8] = 9;
        deck_jogador[9] = 10;
        deck_jogador[10] = 11;
        deck_jogador[11] = 12;
        deck_jogador[12] = 13;
        deck_jogador[13] = 14;
        deck_jogador[14] = 15;
        deck_jogador[15] = 16;
        deck_jogador[16] = 17;
        deck_jogador[17] = 18;
        deck_jogador[18] = 19;
        deck_jogador[19] = 20;

        for (int i = 0; i < 40; i++) {

            bau[i] = -1;
        }

        bau[0] = 1;
        bau[1] = 2;
        bau[2] = 3;


        save = fopen("save.bin", "wb");

        for (int i = 0; i < 20; i++) {

            fwrite(&deck_jogador[i], sizeof(int), 1, save);

        }

        for (int i = 0; i < 40; i++) {

            fwrite(&bau[i], sizeof(int), 1, save);

        }


        fclose(save);

    }

}

// Inicia ou reseta todas as variaveis referentes ao inicio do jogo
void IniciarJogo(int *mesa_aliada, int *mesa_inimiga, int *mao_jogador, int *mao_inimiga, int *vida, TEMP_CARTA * temp_mesa_jogador, TEMP_CARTA * temp_mesa_inimigo, CARTA * cartas, INIMIGO * inimigos, int *deck_jogador, int *inimigo_escolha, int *primeiro_turno, HUD * hud, int *menu) {

    int i;


    LimparMenu(hud);

    DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

    *menu = 0;

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
            (temp_mesa_jogador + i)->atacou = 0;
            (temp_mesa_jogador + i)->atk = (cartas + mesa_aliada[i])->atk;
            (temp_mesa_jogador + i)->def = (cartas + mesa_aliada[i])->def;
            strcpy( (temp_mesa_jogador + i)->inf.linha, (cartas + mesa_aliada[i])->linhas[16].linha  );
        }
        if (mesa_inimiga[i] != -1) {

            (temp_mesa_inimigo + i)->modo = 0;
            (temp_mesa_jogador + i)->atacou = 0;
            (temp_mesa_inimigo + i)->atk = (cartas + mesa_inimiga[i])->atk;
            (temp_mesa_inimigo + i)->def = (cartas + mesa_inimiga[i])->def;
            strcpy( (temp_mesa_inimigo + i)->inf.linha, (cartas + mesa_inimiga[i])->linhas[16].linha  );
        }

    }


    vida[0] = 8000;

    vida[1] = 8000;

    hud++;

    strcpy(hud->linhas[7].linha, "+-------------+-------+------------+");
    strcpy(hud->linhas[8].linha, "|                                  |");
    strcpy(hud->linhas[9].linha, "|                                  |");
    strcpy(hud->linhas[10].linha, "|                                  |");
    strcpy(hud->linhas[11].linha, "|                                  |");
    strcpy(hud->linhas[12].linha, "|                                  |");
    strcpy(hud->linhas[13].linha, "|                                  |");
    strcpy(hud->linhas[14].linha, "|                                  |");
    strcpy(hud->linhas[15].linha, "|                                  |");
    strcpy(hud->linhas[16].linha, "|                                  |");
    strcpy(hud->linhas[17].linha, "|                                  |");
    strcpy(hud->linhas[18].linha, "|                                  |");
    strcpy(hud->linhas[19].linha, "|                                  |");
    strcpy(hud->linhas[20].linha, "|                                  |");
    strcpy(hud->linhas[21].linha, "|                                  |");
    strcpy(hud->linhas[22].linha, "+----------------------------------+");

    IniciarInimigos(inimigos);

    EmbaralharDecks(deck_jogador, (inimigos + *inimigo_escolha));

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

    DarCartas(1, deck_jogador, (inimigos + *inimigo_escolha), mao_jogador, mao_inimiga);

    *primeiro_turno = 1;

}

// Função responsável por dar somente uma carta na mão do jogador ou AI a cada jogada em ordem no deck.
void DarCartas(int inicio, int *deck_jogador, INIMIGO * inimigos, int *mao_jogador, int *mao_inimiga) {

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

                // Não hA mais cartas no baralho;
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

                // Não hA mais cartas no baralho;
            }

        }

    }

}

// Função que rearranja a mão deixando os espaços sem cartas de um lado e as cartas em outro.
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

// Função que retorna 1 se houver cartas mágicas no vetor.
int PossuiCartaMagica(int *mao_jogador, CARTA *cartas) {

    int ind = -1;

    for (int i = 0; i < 5; i++) {

        if (cartas[mao_jogador[i]].tipo == 2 ) {

            ind = i;
        }

    }

    if ( ind == -1) {

        return 0;
    } else {


        return 1;
    }


}


// Muda a hud e os elementos do jogo de acordo com os comandos do jogador
void Controle(int comand, HUD * hud, CARTA * cartas, int *atgame, int *entrada, int *tela_num, int *jogo_on, int *menu, int *mao_jogador, int *mao_inimiga, int *mesa_aliada, int *mesa_inimiga, TEMP_CARTA * temp_mesa_jogador, TEMP_CARTA * temp_mesa_inimigo, int *vida, int *deck_jogador, INIMIGO * inimigos, int *inimigo_escolha, int *blocked1, int *blocked2, int *bau, int *primeiro_turno) {


    static int mesa_aliada_escolha;

    static int mesa_inimiga_escolha;

    static int summon_escolha;

    static int buffando = 0;

    //printf("menu -> %i\n", *menu );

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
            PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame, inimigo_escolha, blocked1, blocked2, bau);

            break;


        }





        break;

    case 1:


        switch (comand) {

        case 1:


            switch (cartas[mao_jogador[comand - 1]].tipo) {

            case 1:


                summon_escolha = comand;
                DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 5;

                break;

            case 2:


                if (cartas[mao_jogador[comand - 1]].atk > 0 || cartas[mao_jogador[comand - 1]].def > 0) {

                    if (!EstaVazio(mesa_aliada)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(7, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 7;

                    } else {
                        summon_escolha = comand;
                        LimparMenu(hud);
                        DesenharMenu(10, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 10;

                    }

                } else {

                    if (!EstaVazio(mesa_inimiga)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 8;
                    }
                    else {
                        summon_escolha = comand;
                        LimparMenu(hud);
                        DesenharMenu(10, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 10;

                    }


                }



                break;

            case 3:


                if (cartas[mao_jogador[comand - 1]].atk > 0) {

                    BuffVida(vida, cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 1);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                    *menu = 3;

                } else {

                    BuffVida((vida + 1), cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 4);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;



            }



            break;

        case 2:

            switch (cartas[mao_jogador[comand - 1]].tipo) {

            case 1:


                summon_escolha = comand;
                DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 5;

                break;

            case 2:


                if (cartas[mao_jogador[comand - 1]].atk > 0 || cartas[mao_jogador[comand - 1]].def > 0) {

                    if (!EstaVazio(mesa_aliada)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(7, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 7;

                    }

                } else {

                    if (!EstaVazio(mesa_inimiga)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 8;
                    }


                }



                break;

            case 3:


                if (cartas[mao_jogador[comand - 1]].atk > 0) {

                    BuffVida(vida, cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 1);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                    *menu = 3;

                } else {

                    BuffVida((vida + 1), cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 4);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;



            }
            break;

        case 3:
            switch (cartas[mao_jogador[comand - 1]].tipo) {

            case 1:


                summon_escolha = comand;
                DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 5;

                break;

            case 2:


                if (cartas[mao_jogador[comand - 1]].atk > 0 || cartas[mao_jogador[comand - 1]].def > 0) {

                    if (!EstaVazio(mesa_aliada)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(7, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 7;

                    }

                } else {

                    if (!EstaVazio(mesa_inimiga)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 8;
                    }


                }



                break;

            case 3:


                if (cartas[mao_jogador[comand - 1]].atk > 0) {

                    BuffVida(vida, cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 1);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                    *menu = 3;

                } else {

                    BuffVida((vida + 1), cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 4);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;



            }
            break;

        case 4:
            switch (cartas[mao_jogador[comand - 1]].tipo) {

            case 1:


                summon_escolha = comand;
                DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 5;

                break;

            case 2:


                if (cartas[mao_jogador[comand - 1]].atk > 0 || cartas[mao_jogador[comand - 1]].def > 0) {

                    if (!EstaVazio(mesa_aliada)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(7, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 7;

                    }

                } else {

                    if (!EstaVazio(mesa_inimiga)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 8;
                    }


                }



                break;

            case 3:


                if (cartas[mao_jogador[comand - 1]].atk > 0) {

                    BuffVida(vida, cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 1);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                    *menu = 3;

                } else {

                    BuffVida((vida + 1), cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 4);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;



            }
            break;

        case 5:
            switch (cartas[mao_jogador[comand - 1]].tipo) {

            case 1:


                summon_escolha = comand;
                DesenharMenu(5, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 5;

                break;

            case 2:


                if (cartas[mao_jogador[comand - 1]].atk > 0 || cartas[mao_jogador[comand - 1]].def > 0) {

                    if (!EstaVazio(mesa_aliada)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(7, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 7;

                    }

                } else {

                    if (!EstaVazio(mesa_inimiga)) {

                        summon_escolha = comand;
                        buffando = 1;
                        LimparMenu(hud);
                        DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                        *menu = 8;
                    }


                }



                break;

            case 3:


                if (cartas[mao_jogador[comand - 1]].atk > 0) {

                    BuffVida(vida, cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 1);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

                    *menu = 3;

                } else {

                    BuffVida((vida + 1), cartas, (comand - 1), mao_jogador);
                    LogBuff(hud, 4);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

                    summon_escolha = comand;

                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;



            }
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
            LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;

            break;

        case 2:
            TrocarModo(comand, temp_mesa_jogador);
            LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 3:
            TrocarModo(comand, temp_mesa_jogador);
            LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 4:
            TrocarModo(comand, temp_mesa_jogador);
            LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
            DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 0;
            break;

        case 5:
            TrocarModo(comand, temp_mesa_jogador);
            LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
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

        if (EstaVazio(mesa_aliada)) {

            LimparMenu(hud);
            DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 6;

        } else {

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
                PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame, inimigo_escolha, blocked1, blocked2, bau);

                break;

            }

        }



        break;

    case 4:

        switch (comand) {

        case 1:

            if (mesa_aliada[comand - 1] != -1 && temp_mesa_jogador[comand - 1].atacou == 0 && temp_mesa_jogador[comand - 1].modo == 0) {

                mesa_aliada_escolha = comand;
                LimparMenu(hud);


                if (EstaVazio(mesa_inimiga)) {
                    DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 9;

                } else {
                    DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 8;

                }
            }



            break;

        case 2:
            if (mesa_aliada[comand - 1] != -1 && temp_mesa_jogador[comand - 1].atacou == 0 && temp_mesa_jogador[comand - 1].modo == 0) {

                mesa_aliada_escolha = comand;
                LimparMenu(hud);
                if (EstaVazio(mesa_inimiga)) {
                    DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 9;

                } else {
                    DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 8;

                }

            }

            break;

        case 3:
            if (mesa_aliada[comand - 1] != -1 && temp_mesa_jogador[comand - 1].atacou == 0 && temp_mesa_jogador[comand - 1].modo == 0) {

                mesa_aliada_escolha = comand;
                LimparMenu(hud);
                if (EstaVazio(mesa_inimiga)) {
                    DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 9;

                } else {
                    DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 8;

                }
            }

            break;

        case 4:
            if (mesa_aliada[comand - 1] != -1 && temp_mesa_jogador[comand - 1].atacou == 0 && temp_mesa_jogador[comand - 1].modo == 0) {

                mesa_aliada_escolha = comand;
                LimparMenu(hud);
                if (EstaVazio(mesa_inimiga)) {
                    DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 9;

                } else {
                    DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 8;

                }
            }

            break;

        case 5:
            if (mesa_aliada[comand - 1] != -1 && temp_mesa_jogador[comand - 1].atacou == 0 && temp_mesa_jogador[comand - 1].modo == 0) {

                mesa_aliada_escolha = comand;
                LimparMenu(hud);
                if (EstaVazio(mesa_inimiga)) {
                    DesenharMenu(9, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 9;

                } else {
                    DesenharMenu(8, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 8;

                }


            }

            break;

        case 6:


            LimparMenu(hud);
            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;

            break;


        }

        break;

    case 5:

        switch (comand) {

        case 1:
            SumonarCarta(0, summon_escolha, mesa_aliada, mao_jogador, temp_mesa_jogador, cartas, hud);
            LimparMenu(hud);

            if (*primeiro_turno) {

                /*

                if (PossuiCartaMagica(mao_jogador, cartas)) {

                    // fazer algo
                }
                */
                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;
                *primeiro_turno = 0;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }

            break;

        case 2:
            SumonarCarta(1, summon_escolha, mesa_aliada, mao_jogador, temp_mesa_jogador, cartas, hud);
            LimparMenu(hud);
            if (*primeiro_turno) {

                DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 6;
                *primeiro_turno = 0;

            } else {

                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
            }

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
            PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame, inimigo_escolha, blocked1, blocked2, bau);

            break;

        }
        break;

    case 7:

        if (buffando) {

            switch (comand) {

            case 1:

                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_aliada[comand - 1], 7);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_jogador, cartas, mao_jogador);

                    LimparMenu(hud);

                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }

                }

                break;

            case 2:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_aliada[comand - 1], 7);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_jogador, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }
                break;

            case 3:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_aliada[comand - 1], 7);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_jogador, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }
                break;

            case 4:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_aliada[comand - 1], 7);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_jogador, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }
                break;

            case 5:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_aliada[comand - 1], 7);
                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_jogador, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }

                break;

            case 6:
                LimparMenu(hud);
                DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 0;
                break;

            }

            buffando = 0;

        } else {
            switch (comand) {

            case 1:

                TrocarModo(comand, temp_mesa_jogador);
                LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
                LimparMenu(hud);
                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;

                break;

            case 2:
                TrocarModo(comand, temp_mesa_jogador);
                LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
                LimparMenu(hud);
                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
                break;

            case 3:
                TrocarModo(comand, temp_mesa_jogador);
                LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
                LimparMenu(hud);
                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
                break;

            case 4:
                TrocarModo(comand, temp_mesa_jogador);
                LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
                LimparMenu(hud);
                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
                break;

            case 5:
                TrocarModo(comand, temp_mesa_jogador);
                LogModo(temp_mesa_jogador, cartas, hud, (comand - 1), mesa_aliada);
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

        }


        break;

    case 8:

        if (buffando) {

            switch (comand) {

            case 1:

                if (mesa_inimiga[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_inimiga[comand - 1], 8);
                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_inimigo, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }

                break;

            case 2:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_inimiga[comand - 1], 8);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_inimigo, cartas, mao_jogador);

                    LimparMenu(hud);

                    if (*primeiro_turno) {

                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }
                break;

            case 3:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_inimiga[comand - 1], 8);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_inimigo, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }
                break;

            case 4:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_inimiga[comand - 1], 8);
                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_inimigo, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }
                break;

            case 5:
                if (mesa_aliada[comand - 1] != -1) {

                    LogSummon(cartas, hud, mesa_inimiga[comand - 1], 8);

                    Buff((summon_escolha - 1), (comand - 1), temp_mesa_inimigo, cartas, mao_jogador);
                    LimparMenu(hud);
                    if (*primeiro_turno) {
                        DesenharMenu(6, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 6;
                        *primeiro_turno = 0;

                    } else {
                        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                        *menu = 3;

                    }
                }

                break;

            case 6:
                LimparMenu(hud);
                DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 0;
                break;

            }
            buffando = 0;
        } else {

            switch (comand) {

            case 1:

                if (mesa_inimiga[comand - 1] != -1) {

                    mesa_inimiga_escolha = comand;
                    vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1), cartas, hud);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);
                    LimparMenu(hud);
                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;

                }



                break;

            case 2:

                if (mesa_inimiga[comand - 1] != -1) {

                    mesa_inimiga_escolha = comand;
                    vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1), cartas, hud);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);
                    LimparMenu(hud);
                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;

            case 3:

                if (mesa_inimiga[comand - 1] != -1) {


                    mesa_inimiga_escolha = comand;
                    vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1), cartas, hud);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);
                    LimparMenu(hud);
                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                    // checar se ainda hA cartas para atacar


                }
                break;

            case 4:

                if (mesa_inimiga[comand - 1] != -1) {


                    mesa_inimiga_escolha = comand;
                    vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1), cartas, hud);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);
                    LimparMenu(hud);
                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;
                }


                break;

            case 5:


                if (mesa_inimiga[comand - 1] != -1) {

                    mesa_inimiga_escolha = comand;
                    vida[0] -= AtacarCarta(mesa_aliada_escolha, mesa_inimiga_escolha, temp_mesa_jogador, temp_mesa_inimigo, mesa_aliada, mesa_inimiga, (vida + 1), cartas, hud);
                    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);
                    LimparMenu(hud);
                    DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                    *menu = 3;

                }


                break;

            case 6:

                LimparMenu(hud);
                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;
                break;


            }

        }


        break;

    case 9:
        switch (comand) {

        case 1:

            // Atacar pontos de vida

            LogSummon(cartas, hud, mesa_aliada[mesa_aliada_escolha - 1], 9);

            AtaqueDireto((vida + 1), mesa_aliada_escolha, temp_mesa_jogador);

            AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

            int ind = -1;

            for (int i = 0; i < 5; i++) {

                if (temp_mesa_jogador[i].atacou == 0) {

                    ind = i;
                }
            }

            if (ind != -1) {

                LimparMenu(hud);
                DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
                *menu = 3;

            }
            else if (ind == -1) {

                PassarVez(hud, vida, deck_jogador, mao_jogador, mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, inimigos, menu, entrada, tela_num, atgame, inimigo_escolha, blocked1, blocked2, bau);

            }


            break;

        case 6:

            DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);
            *menu = 3;

            break;

        }

        break;

    case 10:

        switch (comand) {

        case 1:

            mao_jogador[summon_escolha - 1] = -1;

            LimparMenu(hud);

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


    }



}

// Função responsável por chamar todas as outras funções que serão executadas quando o jogador passar a vez.
void PassarVez(HUD * hud, int *vida, int *deck_jogador, int *mao_jogador, int *mesa_aliada, int *mesa_inimiga, int *mao_inimiga, CARTA * cartas, TEMP_CARTA * temp_mesa_jogador, TEMP_CARTA * temp_mesa_inimigo, INIMIGO * inimigos, int *menu, int *entrada, int *tela_num, int *atgame, int *inimigo_escolha, int *blocked1, int *blocked2, int *bau) {

    for (int i = 0; i < 5; i++) {

        if (mesa_aliada[i] != -1) {

            if (temp_mesa_jogador[i].atacou == 1 ) {

                temp_mesa_jogador[i].atacou = 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {

        if (mesa_inimiga[i] != -1) {

            if (temp_mesa_inimigo[i].atacou == 1 ) {

                temp_mesa_inimigo[i].atacou = 0;
            }
        }
    }


    AI(mesa_aliada, mesa_inimiga, mao_inimiga, cartas, temp_mesa_jogador, temp_mesa_inimigo, vida, hud, mao_jogador, cartas, menu);

    DarCartas(0, deck_jogador, (inimigos + *inimigo_escolha), mao_jogador, mao_inimiga);

    AtualizarPlacar(hud, vida, atgame, entrada, tela_num, inimigo_escolha, blocked1, blocked2, bau, inimigos);

    if (EstaCheio(mesa_aliada)) {

        LimparMenu(hud);

        DesenharMenu(3, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

        *menu = 3;

    } else {

        LimparMenu(hud);

        DesenharMenu(0, hud, cartas, mao_jogador, mesa_aliada, mesa_inimiga, menu, temp_mesa_jogador);

        *menu = 0 ;


    }



}

// Função que diminui a vida do jogador ou AI com base no ataque da carta passada.
void AtaqueDireto(int *vida, int indice, TEMP_CARTA * temp) {


    temp[indice - 1].atacou = 1;

    *(vida) -= temp[indice - 1].atk;

}

// Função que retorna 1 se a mesa do jogador ou AI estiver vazia.
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
// Função que retorna 1 se a mesa do jogador ou AI estiver cheia.
int EstaCheio(int *mesa) {

    int ind = 0;

    for (int i = 0; i < 5; i++) {

        if (*(mesa + i) != -1) {

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
void SumonarCarta(int modo, int indice, int *mesa, int *mao, TEMP_CARTA * temp_carta, CARTA * cartas, HUD * hud) {

    int i;
    int space = -1;
    LogSummon(cartas, hud, mao[indice - 1], 1);


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
        (temp_carta + space)->atacou = 0;

        strcpy( (temp_carta + space)->inf.linha, (cartas + mesa[space])->linhas[16].linha );



        TrocarModo((space + 1), temp_carta);

        LogModo(temp_carta, cartas, hud, space, mesa);



    } else {

        // Sem espaço ( ALERTAR QUE NÃO HA ESPAÇO)

    }

}

// Função responsável por colocar no log sobre as mudanças de modo para ataque ou defesa.
void LogModo(TEMP_CARTA * temp_carta, CARTA * cartas, HUD * hud, int indice, int *mesa) {



    if (temp_carta[indice].modo == 1) {

        LogSummon(cartas, hud, mesa[indice], 2);

    } else {


        LogSummon(cartas, hud, mesa[indice], 3);
    }

}

// Ataca uma carta inimiga com a carta aliada seleciona e retorna a vida perdida
int AtacarCarta(int indice_1, int indice_2, TEMP_CARTA * temp_mesa_jogador, TEMP_CARTA * temp_mesa_inimigo, int *mesa_aliada, int *mesa_inimiga, int *vida, CARTA * cartas, HUD * hud) {


    // Se for ataque do AI inverter ordem de temp_mesa_aliada com inimigo e mesa_aliada
    LogSummon(cartas, hud, mesa_aliada[indice_1 - 1], 5);

    LogSummon(cartas, hud, mesa_inimiga[indice_2 - 1], 6);


    int num1 = indice_1 - 1;

    int num2 = indice_2 - 1;

    if (temp_mesa_jogador[num1].atacou == 0) {




        temp_mesa_jogador[num1].atacou = 1;

        if (temp_mesa_inimigo[num2].modo == 1) {




            int dano_carta_jogador = temp_mesa_jogador[num1].atk;

            int def_carta_inimigo  = temp_mesa_inimigo[num2].def;

            if (dano_carta_jogador > def_carta_inimigo) {

                LogSummon(cartas, hud, mesa_inimiga[num2], 4);

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

                LogSummon(cartas, hud, mesa_inimiga[num2], 4);

                mesa_inimiga[num2] = -1;




                return 0;
            }
            else if (dano_carta_jogador == dano_carta_inimigo) {

                LogSummon(cartas, hud, mesa_aliada[num1], 4);

                LogSummon(cartas, hud, mesa_inimiga[num2], 4);

                mesa_inimiga[num2] = -1;
                mesa_aliada[num1] = -1;





                return 0;
            }
            else if (dano_carta_jogador < dano_carta_inimigo) {

                int diff = dano_carta_inimigo - dano_carta_jogador;

                LogSummon(cartas, hud, mesa_aliada[num1], 4);

                mesa_aliada[num1] = -1;




                return diff;

            }
            else {



                return 0;
            }


        } else {


            return 0;
        }

    } else {

        return 0;
    }

}
// Função responsável por trocar o modo da carta.
void TrocarModo(int comand, TEMP_CARTA * temp_mesa) {



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

