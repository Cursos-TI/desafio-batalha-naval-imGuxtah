#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY 0
#define SHIP 3
#define AFFECT 5
#define SHIP_AND_AFFECT 8

const char linhas[SIZE] = {'A','B','C','D','E','F','G','H','I','J'};

/* --- util: verifica se coordenada está dentro do tabuleiro --- */
int dentro(int r, int c) {
    return (r >= 0 && r < SIZE && c >= 0 && c < SIZE) ? 1 : 0;
}

/* --- verificações de posicionamento (retornam 1 se pode, 0 se não) --- */
int pode_colocar_horizontal(int tab[][SIZE], int r, int c, int len) {
    int i;
    for (i = 0; i < len; i++) {
        int cc = c + i;
        if (!dentro(r, cc) || tab[r][cc] != EMPTY) return 0;
    }
    return 1;
}
void colocar_horizontal(int tab[][SIZE], int r, int c, int len) {
    int i;
    for (i = 0; i < len; i++) tab[r][c + i] = SHIP;
}

int pode_colocar_vertical(int tab[][SIZE], int r, int c, int len) {
    int i;
    for (i = 0; i < len; i++) {
        int rr = r + i;
        if (!dentro(rr, c) || tab[rr][c] != EMPTY) return 0;
    }
    return 1;
}
void colocar_vertical(int tab[][SIZE], int r, int c, int len) {
    int i;
    for (i = 0; i < len; i++) tab[r + i][c] = SHIP;
}

int pode_colocar_diagonal(int tab[][SIZE], int r, int c, int len, int dir) {
    int i;
    for (i = 0; i < len; i++) {
        int rr = r + i;
        int cc = c + dir * i;
        if (!dentro(rr, cc) || tab[rr][cc] != EMPTY) return 0;
    }
    return 1;
}
void colocar_diagonal(int tab[][SIZE], int r, int c, int len, int dir) {
    int i;
    for (i = 0; i < len; i++) tab[r + i][c + dir * i] = SHIP;
}

/* --- construir matrizes de habilidade L x L (0/1) --- */
void construir_cone(int L, int mat[L][L]) {
    int center = L / 2;
    int r, c;
    for (r = 0; r < L; r++) {
        for (c = 0; c < L; c++) {
            if (abs(c - center) <= r) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

void construir_cruz(int L, int mat[L][L]) {
    int center = L / 2;
    int r, c;
    for (r = 0; r < L; r++) {
        for (c = 0; c < L; c++) {
            if (r == center || c == center) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

void construir_octaedro(int L, int mat[L][L]) {
    int center = L / 2;
    int radius = center;
    int r, c;
    for (r = 0; r < L; r++) {
        for (c = 0; c < L; c++) {
            if (abs(r - center) + abs(c - center) <= radius) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

/* --- aplicar habilidade (mat LxL com 0/1) no camada 'layer' centrando em origin --- */
void aplicar_habilidade(int layer[][SIZE], int L, int mat[L][L], int origin_r, int origin_c) {
    int center = L / 2;
    int r, c;
    for (r = 0; r < L; r++) {
        for (c = 0; c < L; c++) {
            if (mat[r][c] == 1) {
                int board_r = origin_r + (r - center);
                int board_c = origin_c + (c - center);
                if (dentro(board_r, board_c)) layer[board_r][board_c] = 1;
            }
        }
    }
}

/* --- exibição do tabuleiro com prioridade de símbolos --- */
void exibir_tabuleiro(int tab[][SIZE], int layer[][SIZE]) {
    int r, c;
    printf("    ");
    for (c = 0; c < SIZE; c++) printf("%d ", c);
    printf("\n");
    for (r = 0; r < SIZE; r++) {
        printf("%c | ", linhas[r]);
        for (c = 0; c < SIZE; c++) {
            int out_val;
            if (tab[r][c] == SHIP && layer[r][c] == 1) out_val = SHIP_AND_AFFECT;
            else if (layer[r][c] == 1) out_val = AFFECT;
            else if (tab[r][c] == SHIP) out_val = SHIP;
            else out_val = EMPTY;
            printf("%d ", out_val);
        }
        printf("\n");
    }
    printf("\nLegenda:\n0 = Agua\n3 = Navio\n5 = Area afetada (habilidade)\n8 = Navio + Area afetada (sobreposicao)\n");
}

int main() {
    int tabuleiro[SIZE][SIZE];
    int habilidade_layer[SIZE][SIZE];
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
            tabuleiro[i][j] = EMPTY;
            habilidade_layer[i][j] = 0;
        }

    const int ship_size = 3;
    /* coordenadas fixas (exemplos) */
    int h1_r = 1, h1_c = 2;     /* horizontal */
    int v1_r = 4, v1_c = 7;     /* vertical */
    int d1_r = 2, d1_c = 2, d1_dir = 1;   /* diagonal down-right */
    int d2_r = 1, d2_c = 8, d2_dir = -1;  /* diagonal down-left */

    /* posiciona navios validando limites e sobreposição */
    if (pode_colocar_horizontal(tabuleiro, h1_r, h1_c, ship_size)) colocar_horizontal(tabuleiro, h1_r, h1_c, ship_size);
    else printf("Erro: nao foi possivel posicionar H1 em (%d,%d)\n", h1_r, h1_c);

    if (pode_colocar_vertical(tabuleiro, v1_r, v1_c, ship_size)) colocar_vertical(tabuleiro, v1_r, v1_c, ship_size);
    else printf("Erro: nao foi possivel posicionar V1 em (%d,%d)\n", v1_r, v1_c);

    if (pode_colocar_diagonal(tabuleiro, d1_r, d1_c, ship_size, d1_dir)) colocar_diagonal(tabuleiro, d1_r, d1_c, ship_size, d1_dir);
    else printf("Erro: nao foi possivel posicionar D1 em (%d,%d)\n", d1_r, d1_c);

    if (pode_colocar_diagonal(tabuleiro, d2_r, d2_c, ship_size, d2_dir)) colocar_diagonal(tabuleiro, d2_r, d2_c, ship_size, d2_dir);
    else printf("Erro: nao foi possivel posicionar D2 em (%d,%d)\n", d2_r, d2_c);

    /* --- construir matrizes de habilidade (L x L) --- */
    const int L = 5;
    int cone[L][L], cruz[L][L], octa[L][L];
    construir_cone(L, cone);
    construir_cruz(L, cruz);
    construir_octaedro(L, octa);

    /* --- definir origens das habilidades no tabuleiro (fixas) --- */
    int cone_origin_r = 0, cone_origin_c = 4;
    int cruz_origin_r = 6, cruz_origin_c = 3;
    int octa_origin_r = 3, octa_origin_c = 5;

    /* aplicar habilidades na camada separada (1 = afetado) */
    aplicar_habilidade(habilidade_layer, L, cone, cone_origin_r, cone_origin_c);
    aplicar_habilidade(habilidade_layer, L, cruz, cruz_origin_r, cruz_origin_c);
    aplicar_habilidade(habilidade_layer, L, octa, octa_origin_r, octa_origin_c);

    /* exibir tabuleiro combinando navios e habilidades */
    exibir_tabuleiro(tabuleiro, habilidade_layer);

    return 0;
}
