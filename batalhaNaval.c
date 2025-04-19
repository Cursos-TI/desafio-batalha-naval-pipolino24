#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define TAMANHO_NAVIO 3

// Função para verificar se o posicionamento é válido (sem sobreposição e dentro dos limites)
int validar_posicionamento(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        if (nova_linha < 0 || nova_linha >= TAMANHO_TABULEIRO || nova_coluna < 0 || nova_coluna >= TAMANHO_TABULEIRO || tabuleiro[nova_linha][nova_coluna] != 0) {
            return 0; // Inválido
        }
    }
    return 1; // Válido
}

// Função para posicionar o navio no tabuleiro
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i * delta_linha][coluna + i * delta_coluna] = 3;
    }
}

// Função para aplicar a matriz de habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna) {
    int offset = TAMANHO_HABILIDADE / 2; // Offset para centralizar a matriz de habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha = origem_linha + i - offset;
            int coluna = origem_coluna + j - offset;
            if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO && habilidade[i][j] == 1) {
                tabuleiro[linha][coluna] = 5; // Marca a área afetada pela habilidade
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com 0 (representando água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais e direções dos navios
    int navios[4][4] = {
        {2, 4, 0, 1},  // Navio horizontal (linha 2, coluna 4, direção direita)
        {6, 1, 1, 0},  // Navio vertical (linha 6, coluna 1, direção para baixo)
        {0, 0, 1, 1},  // Navio diagonal crescente (linha 0, coluna 0, direção diagonal para baixo-direita)
        {9, 9, -1, -1} // Navio diagonal decrescente (linha 9, coluna 9, direção diagonal para cima-esquerda)
    };

    // Posiciona os navios no tabuleiro
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int delta_linha = navios[i][2];
        int delta_coluna = navios[i][3];

        if (validar_posicionamento(tabuleiro, linha, coluna, delta_linha, delta_coluna)) {
            posicionar_navio(tabuleiro, linha, coluna, delta_linha, delta_coluna);
        } else {
            printf("Erro: Não foi possível posicionar o navio %d nas coordenadas iniciais (%d, %d).\n", i + 1, linha, coluna);
        }
    }

    // Matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    // Preenche a matriz de habilidade em cone
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = TAMANHO_HABILIDADE / 2 - i; j <= TAMANHO_HABILIDADE / 2 + i && j < TAMANHO_HABILIDADE; j++) {
            if (j >= 0) cone[i][j] = 1;
        }
    }

    // Preenche a matriz de habilidade em cruz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        cruz[i][TAMANHO_HABILIDADE / 2] = 1; // Linha central
        cruz[TAMANHO_HABILIDADE / 2][i] = 1; // Coluna central
    }

    // Preenche a matriz de habilidade em octaedro
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = abs(TAMANHO_HABILIDADE / 2 - i); j < TAMANHO_HABILIDADE - abs(TAMANHO_HABILIDADE / 2 - i); j++) {
            octaedro[i][j] = 1;
        }
    }

    // Aplica as habilidades no tabuleiro
    aplicar_habilidade(tabuleiro, cone, 2, 2);       // Habilidade em cone no centro (2, 2)
    aplicar_habilidade(tabuleiro, cruz, 5, 5);      // Habilidade em cruz no centro (5, 5)
    aplicar_habilidade(tabuleiro, octaedro, 7, 7);  // Habilidade em octaedro no centro (7, 7)

    // Exibe o tabuleiro no console
    printf("Tabuleiro de Batalha Naval com Habilidades:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // Lista as coordenadas dos navios
    printf("\nCoordenadas dos navios:\n");
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int delta_linha = navios[i][2];
        int delta_coluna = navios[i][3];
        printf("Navio %d: ", i + 1);
        for (int j = 0; j < TAMANHO_NAVIO; j++) {
            printf("(%d, %d) ", linha + j * delta_linha, coluna + j * delta_coluna);
        }
        printf("\n");
    }

    return 0;
}
