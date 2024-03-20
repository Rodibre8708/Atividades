#include <stdio.h>

void CompVetor(int vetor[], int tamanho);
void VetorTodo(int conjunto[], int tamanho);
void ordem(int conjunto[], int tamanho);
void uniao(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB);
void intersecao(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB);
void diferencaAB(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB);
void diferencaBA(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB);

int main() {
    int tamanhoA, tamanhoB;

    printf("Digite o tamanho do primeiro vetor: ");
    scanf("%d", &tamanhoA);

    int vetorA[tamanhoA];
    printf("Digite os valores do primeiro vetor (sem repetir):\n");
    CompVetor(vetorA, tamanhoA);

    printf("Digite o tamanho do segundo vetor: ");
    scanf("%d", &tamanhoB);

    int vetorB[tamanhoB];
    printf("Digite os valores do segundo vetor (sem repetir):\n");
    CompVetor(vetorB, tamanhoB);

    printf("\nVetor A: ");
    VetorTodo(vetorA, tamanhoA);
    printf("\nVetor B: ");
    VetorTodo(vetorB, tamanhoB);

    printf("\nUniao de A e B: ");
    uniao(vetorA, tamanhoA, vetorB, tamanhoB);

    printf("\nIntersecao de A e B: ");
    intersecao(vetorA, tamanhoA, vetorB, tamanhoB);

    printf("\nDiferenca de A - B: ");
    diferencaAB(vetorA, tamanhoA, vetorB, tamanhoB);

    printf("\nDiferenca de B - A: ");
    diferencaBA(vetorA, tamanhoA, vetorB, tamanhoB);

    return 0;
}

void CompVetor(int vetor[], int tamanho) {
    int elemento, i, j, repetido;

    for (i = 0; i < tamanho; i++) {
        repetido = 0;
        scanf("%d", &elemento);

        for (j = 0; j < i; j++) {
            if (vetor[j] == elemento) {
                printf("Valor repetido! Digite outro: ");
                i--; 
                repetido = 1;
                break;
            }
        }

        if (!repetido) {
            vetor[i] = elemento;
        }
    }
}

void VetorTodo(int conjunto[], int tamanho) {
    ordem(conjunto, tamanho); 
    printf("{ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", conjunto[i]);
        if (i != tamanho - 1) {
            printf(", ");
        }
    }
    printf(" }");
}

void ordem(int conjunto[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (conjunto[j] > conjunto[j + 1]) {
                int temp = conjunto[j];
                conjunto[j] = conjunto[j + 1];
                conjunto[j + 1] = temp;
            }
        }
    }
}

void uniao(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB) {
    int conjuntoUniao[tamanhoA + tamanhoB];
    int tamanhoUniao = 0;

    for (int i = 0; i < tamanhoA; i++) {
        conjuntoUniao[tamanhoUniao++] = vetorA[i];
    }

    for (int i = 0; i < tamanhoB; i++) {
        int presente = 0;
        for (int j = 0; j < tamanhoA; j++) {
            if (vetorB[i] == vetorA[j]) {
                presente = 1;
                break;
            }
        }
        if (!presente) {
            conjuntoUniao[tamanhoUniao++] = vetorB[i];
        }
    }

    ordem(conjuntoUniao, tamanhoUniao);
    VetorTodo(conjuntoUniao, tamanhoUniao);
}

void intersecao(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB) {
    printf("{ ");
    for (int i = 0; i < tamanhoA; i++) {
        for (int j = 0; j < tamanhoB; j++) {
            if (vetorA[i] == vetorB[j]) {
                printf("%d", vetorA[i]);
                if (i != tamanhoA - 1) {
                    printf(", ");
                }
                break;
            }
        }
    }
    printf(" }");
}

void diferencaAB(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB) {
    printf("{ ");
    for (int i = 0; i < tamanhoA; i++) {
        if (i < tamanhoB) {
            printf("%d", vetorA[i] - vetorB[i]);
            if (i != tamanhoA - 1) {
                printf(", ");
            }
        } else {
            printf("%d", vetorA[i]);
            if (i != tamanhoA - 1) {
                printf(", ");
            }
        }
    }
    printf(" }");
}

void diferencaBA(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB) {
    printf("{ ");
    for (int i = 0; i < tamanhoB; i++) {
        if (i < tamanhoA) {
            printf("%d", vetorB[i] - vetorA[i]);
            if (i != tamanhoB - 1) {
                printf(", ");
            }
        } else {
            printf("%d", vetorB[i]);
            if (i != tamanhoB - 1) {
                printf(", ");
            }
        }
    }
    printf(" }");
}
