#ifndef _MEGALIB_
#define _MEGALIB_

// Criando constantes
#define TAM_CARTA 17
// Criando estrtura que irá armazenar os caracteres de uma linha para todo o resto dos gráficos.
typedef struct {

	char linha[300];
} LINHA;

/* Os "objetos gráficos" do jogo (Cartas, Inimigos, Menus, HUD's, entre outros)
serão definidos através dos structs abaixo, cada qual com suas devidas variáveis. */

typedef struct {
// Tipo : 1 - Monstro, 2 - Mágica, 3 - Armadilha;
	int tipo;

	int atk;

	int def;
// Modo : 1 - Ataque, 2 - Defesa;
	int modo;

	char nome[50];


	char desc[500];


	LINHA linhas[20];

	LINHA nome_menu[1];
} CARTA;

typedef struct {

	int deck[40];

	char nome[50];

	LINHA linhas[17];
} INIMIGO;

typedef struct {

	LINHA linhas[20];
} TELA;

typedef struct {
	LINHA linhas[40];
} HUD;

typedef struct {
	LINHA linhas[10];
} MENU;

// Definindo os Headers das funções
int Comando(char*);
void DesenharMesa(int*, int*, int*, CARTA*, HUD*);
void DesenharMenu(int, HUD*);
void DesenharTela(int, TELA*);
void CriarHUD(HUD*);
void CriarCartas(CARTA*);
void CriarTelas(TELA*);
void LimparMenu(HUD*);
void MudarTela(int, int*, int*, int*);
void MudarHud(int, HUD*, CARTA*, int*, int*, int*);
void TransicaoTela(int, int*, int*, TELA*);
void IniciarJogo(int*, int*, int*, int*);

#endif