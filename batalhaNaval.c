#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // Inicializa o tabuleiro com 0 (representando água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais dos navios
    int navio_horizontal_linha = 2, navio_horizontal_coluna = 4;
    int navio_vertical_linha = 6, navio_vertical_coluna = 1;

    // Validação de limites e posicionamento do navio horizontal
    if (navio_horizontal_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_horizontal_linha][navio_horizontal_coluna + i] != 0) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_horizontal_linha][navio_horizontal_coluna + i] = 3;
            }
        } else {
            printf("Erro: Sobreposição detectada para o navio horizontal.\n");
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites do tabuleiro.\n");
    }

    // Validação de limites e posicionamento do navio vertical
    if (navio_vertical_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] != 0) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] = 3;
            }
        } else {
            printf("Erro: Sobreposição detectada para o navio vertical.\n");
        }
    } else {
        printf("Erro: Navio vertical fora dos limites do tabuleiro.\n");
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
    printf("Navio horizontal: ");
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("(%d, %d) ", navio_horizontal_linha, navio_horizontal_coluna + i);
    }
    printf("\nNavio vertical: ");
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("(%d, %d) ", navio_vertical_linha + i, navio_vertical_coluna);
    }
    printf("\n");

    return 0;
}
