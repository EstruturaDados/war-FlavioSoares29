#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// ================= FUNÇÕES =================

// Cadastro automático (você pode trocar por manual se quiser)
void inicializarTerritorios(Territorio *t) {
    char *nomes[MAX] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
    char *cores[MAX] = {"Azul", "Verde", "Vermelho", "Amarelo", "Preto"};

    for (int i = 0; i < MAX; i++) {
        strcpy(t[i].nome, nomes[i]);
        strcpy(t[i].cor, cores[i]);
        t[i].tropas = rand() % 10 + 1;
    }
}

// Mostrar mapa
void mostrarMapa(Territorio *t) {
    printf("\n===== MAPA =====\n");
    for (int i = 0; i < MAX; i++) {
        printf("\n[%d] %s\n", i + 1, t[i].nome);
        printf("Exército: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\nVocê precisa de mais tropas para atacar!\n");
        return;
    }

    int atk = rand() % 6 + 1;
    int def = rand() % 6 + 1;

    printf("\nDado Ataque: %d | Dado Defesa: %d\n", atk, def);

    if (atk > def) {
        defensor->tropas--;
        printf("Defensor perdeu 1 tropa!\n");

        if (defensor->tropas <= 0) {
            printf("Território conquistado!\n");
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas--;
        }
    } else {
        atacante->tropas--;
        printf("Ataque falhou! Você perdeu 1 tropa.\n");
    }
}

// Verificar missão
int verificarMissao(Territorio *t) {
    int conquistados = 0;
    int verdeExiste = 0;

    for (int i = 0; i < MAX; i++) {
        if (strcmp(t[i].cor, "Verde") == 0) {
            verdeExiste = 1;
        }

        if (strcmp(t[i].cor, "Azul") == 0) {
            conquistados++;
        }
    }

    if (!verdeExiste) {
        printf("\nMISSÃO COMPLETA: Exército Verde destruído!\n");
        return 1;
    }

    if (conquistados >= 3) {
        printf("\nMISSÃO COMPLETA: Você conquistou 3 territórios!\n");
        return 1;
    }

    printf("\nMissão ainda não concluída.\n");
    return 0;
}

// Menu principal
void menu(Territorio *t) {
    int opcao, atk, def;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("3 - Mostrar Mapa\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                mostrarMapa(t);

                printf("\nEscolha território atacante: ");
                scanf("%d", &atk);

                printf("Escolha território defensor: ");
                scanf("%d", &def);

                if (atk >= 1 && atk <= MAX && def >= 1 && def <= MAX && atk != def) {
                    atacar(&t[atk - 1], &t[def - 1]);
                } else {
                    printf("\nEscolha inválida!\n");
                }
                break;

            case 2:
                if (verificarMissao(t)) {
                    printf("\n🏆 PARABÉNS, VOCÊ VENCEU!\n");
                    return;
                }
                break;

            case 3:
                mostrarMapa(t);
                break;
        }

    } while(opcao != 0);
}

// ================= MAIN =================

int main() {
    srand(time(NULL));

    Territorio *territorios = (Territorio*) calloc(MAX, sizeof(Territorio));

    inicializarTerritorios(territorios);

    menu(territorios);

    free(territorios);

    return 0;
}