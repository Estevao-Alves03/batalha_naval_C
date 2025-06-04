#include <stdio.h>
#include <stdlib.h>

#define TAM_TAB 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // matriz 5x5 para habilidades
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5
#define ORIGEM (TAM_HABILIDADE / 2)

// Função para inicializar o tabuleiro
void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            tabuleiro[i][j] = 0;
}

// Função para posicionar navios
void posicionarNavios(int tabuleiro[TAM_TAB][TAM_TAB]) {
    int linhaH = 2, colH = 4; // navio horizontal
    int linhaV = 5, colV = 7; // navio vertical

    // Navio horizontal
    if (colH + TAM_NAVIO <= TAM_TAB) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaH][colH + i] != 0) return;
        }
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaH][colH + i] = VALOR_NAVIO;
        }
    }

    // Navio vertical
    if (linhaV + TAM_NAVIO <= TAM_TAB) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colV] != 0) return;
        }
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaV + i][colV] = VALOR_NAVIO;
        }
    }
}

// Função para construir habilidade tipo cone (ponta para baixo)
void construirCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (j >= ORIGEM - i && j <= ORIGEM + i) ? 1 : 0;
        }
    }
}

// Função para construir habilidade tipo cruz
void construirCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == ORIGEM || j == ORIGEM) ? 1 : 0;
        }
    }
}

// Função para construir habilidade tipo octaedro (losango)
void construirOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (abs(i - ORIGEM) + abs(j - ORIGEM) <= ORIGEM) ? 1 : 0;
        }
    }
}

// Função para aplicar habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int tabLinha = origemLinha + i - ORIGEM;
            int tabCol = origemColuna + j - ORIGEM;

            if (tabLinha >= 0 && tabLinha < TAM_TAB && tabCol >= 0 && tabCol < TAM_TAB) {
                if (habilidade[i][j] == 1 && tabuleiro[tabLinha][tabCol] == 0) {
                    tabuleiro[tabLinha][tabCol] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");        // Água
            else if (tabuleiro[i][j] == 3) printf("N ");    // Navio
            else if (tabuleiro[i][j] == 5) printf("* ");    // Habilidade
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa o tabuleiro e posiciona navios
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // Constrói matrizes de habilidade
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Define pontos de origem no tabuleiro (linha, coluna)
    aplicarHabilidade(tabuleiro, cone, 1, 2);
    aplicarHabilidade(tabuleiro, cruz, 6, 3);
    aplicarHabilidade(tabuleiro, octaedro, 4, 7);

    // Imprime o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}


