#include <stdio.h>

int main() {
    // Letras das linhas (como no seu exemplo)
    char linha[10] = {'A','B','C','D','E','F','G','H','I','J'};

    // Criando o Tabuleiro (matriz 10x10)
    int tabuleiro[10][10];

    // Inicializando o tabuleiro com 0 (água)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -------------------------------------------------------
    // 2. Definindo dois navios de tamanho 3 (fixo)
    //    Coordenadas definidas no código (como pedido)
    // -------------------------------------------------------

    // Navio 1 – horizontal (linha B = 1, coluna 2)
    int n1_linha = 1;
    int n1_coluna = 2;

    // Navio 2 – vertical (linha E = 4, coluna 7)
    int n2_linha = 4;
    int n2_coluna = 7;

    // Posicionar navio 1 (horizontal)
    for (int i = 0; i < 3; i++) {   // navio tamanho 3
        tabuleiro[n1_linha][n1_coluna + i] = 3;
    }

    // Posicionar navio 2 (vertical)
    for (int i = 0; i < 3; i++) {   // navio tamanho 3
        tabuleiro[n2_linha + i][n2_coluna] = 3;
    }

    // -------------------------------------------------------
    // 3. Exibir Tabuleiro
    // -------------------------------------------------------

    printf("    ");
    for (int c = 0; c < 10; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%c | ", linha[i]);  // letra da linha
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}
