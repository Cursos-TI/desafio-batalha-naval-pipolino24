#include <stdio.h>

#define TAMANHO_TABULEIRO 10
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

    // Exibe o tabuleiro no console
    printf("Tabuleiro de Batalha Naval:\n");
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
