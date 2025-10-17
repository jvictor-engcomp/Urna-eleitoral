#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "realloc.h"



struct uf {
    int codigo;
    char sigla[3];
};

int main() {
    ///////////////////// para as quantidades
    FILE *fq = fopen("quantidade", "rb+");
    if (fq == NULL) fq = fopen("quantidade", "wb+");
    if (fq == NULL) {
        printf("Erro ao abrir arquivo estados\n");
        return -1;
    }
    /* Função para abrir um arquivo de nome quantidade, se ele não existir, ele é criado. Caso não seja possível
     * criar, o programa fecha.
     */

    int *q = malloc(sizeof(int));
    if (q == NULL) {
        printf("Erro ao alocar memoria\n");
        free(q);// liberação de memória apenas porque a IDE reclama, mas não é necessário já que o programa se fecha ao entrar no if.
        return -1;
    }

    fseek(fq, 0, SEEK_SET);
    if (fread(q, sizeof(int), 1, fq) == 0) {
        *q = 0;
    }// q aponta para espaço que guarda quantidade de ufs

    /////////////////////////////////////////// para as informações das ufs
    FILE *fu = fopen("ufss", "rb+");
    if (fu == NULL) fu = fopen("ufss", "wb+");
    if (fu == NULL) {
        printf("Erro ao abrir arquivo UFs\n");
        return -1;
    }

    struct uf *u;
    if (*q == 0) u = NULL;
    else {
        u = malloc(*q * sizeof(struct uf));
        if (u == NULL) {
            printf("Erro ao alocar memoriaaaaaaaaaaaa\n");
            free(u);
            return -1;
        }
    }



    fseek(fu, 0, SEEK_SET);
    fread(u, sizeof(struct uf), *q, fu);


    adicionar( &u, q );
    // printf("codigo: %d\n", q);

    mostrar(u, q);

    //////////////////////////////////// fechando e salvando
    fseek(fu, 0, SEEK_SET);
    for (int i = 0; i < *q; i++) {
        fwrite(u + i, sizeof(struct uf), 1, fu);
    }
    fseek(fq, 0, SEEK_SET);
    fwrite(q, sizeof(int), 1, fq);

    fclose(fu);
    fclose(fq);
    free(u);
    free(q);

    return 0;

}

void adicionar( struct uf * *c, int *tam) {// irá mexer no valor real. obs: na função eu mexo no endereço de
    (*tam)++;
    printf("%d\n", *tam);

    struct uf *teste = realloc(*c, (*tam) * sizeof(struct uf));
    if (teste == NULL) {
        printf("Erro ao realocar memoria\n");
        return;
    }
    *c = teste;



    printf("Digite o codigo da UF: ");
    scanf("%d", &((*c + (*tam - 1))->codigo));
    /* Aqui deve haver uma análise minuciosa: (*c) == q, (*c)[(*tam) - 1] entra em qual posição de interesse
     * do vetor. Sendo essa última parte um endereço, usamos -> para entrar em código, que é um inteiro, por isso
     * o &*/

    printf("Digite a sigla: ");
    fflush(stdin);// Evitar problemas com buffer.
    fgets((*c + (*tam - 1))->sigla, 3, stdin);

    printf("Pessoa adicionada com sucesso\n");
}

void mostrar(struct uf *c, int *tam) {
    for (int i = 0; i < *tam; i++) {
        printf("UF[%d]: %s\n", c[i].codigo, c[i].sigla);
    }
}