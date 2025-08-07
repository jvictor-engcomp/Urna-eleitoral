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
    FILE *f = fopen("quantidade", "rb+");
    if (f == NULL) f = fopen("quantidade", "wb+");
    if (f == NULL) {
        printf("Erro ao abrir arquivo estados\n");
        return -1;
    }
    /* Função para abrir um arquivo de nome estados, se ele não existir, ele é criado. Caso não seja possível
     * criar, o programa fecha.
     */

    int *p = malloc(sizeof(int));
    if (p == NULL) {
        printf("Erro ao alocar memoria\n");
        free(p);// liberação de memória apenas porque a IDE reclama, mas não é necessário já que o programa se fecha ao entrar no if.
        return -1;
    }

    fseek(f, 0, SEEK_SET);
    if (fread(p, sizeof(int), 1, f) == 0) {
        *p = 0;
    }// p guardará quantidade de ufs

    /////////////////////////////////////////// para as informações das ufs
    FILE *r = fopen("ufss", "rb+");
    if (r == NULL) r = fopen("ufss", "wb+");
    if (r == NULL) {
        printf("Erro ao abrir arquivo UFs\n");
        return -1;
    }

    struct uf **q;
    if (*p == 0) q = NULL;
    else {
        q = malloc(*p * sizeof(struct uf*));
        if (q == NULL) {
            printf("Erro ao alocar memoriaaaaaaaaaaaa\n");
            return -1;
        }
        for (int i = 0; i < *p; i++) {
            q[i] = malloc(sizeof(struct uf));
            if (q[i] == NULL) {
                printf("Erro ao alocar memoria\n");
                return -1;
            }
        }
    }


    fseek(r, 0, SEEK_SET);
    for (int i = 0; i < *p; i++) {
        fread(q[i], sizeof(struct uf), 1, r);
    }

    adicionar( &q, p );
    printf("%d", *p);
    // printf("codigo: %d\n", q);

    mostrar(&q, p);

    //////////////////////////////////// fechando e salvando
    fseek(r, 0, SEEK_SET);
    for (int i = 0; i < *p; i++) {
        fwrite(q[i], sizeof(struct uf), 1, r);
    }
    fseek(f, 0, SEEK_SET);
    fwrite(p, sizeof(int), 1, f);

    fclose(r);
    fclose(f);
    free(p);
    for (int i = 0; i < *p; i++) {
        free(q[i]);
    }
    free(q);
    return 0;

}

void adicionar( struct uf * **c, int *tam) {// irá mexer no valor real
    (*tam)++;
    printf("%d\n", *tam);

    struct uf **teste = realloc(*c, (*tam) * sizeof(struct uf*));
    if (teste == NULL) {
        printf("Erro ao realocar memoria\n");
        return;
    }
    *c = teste;

    (*c)[(*tam) - 1] = malloc(sizeof(struct uf));// malloc para a nova uf
    if ((*c)[(*tam) - 1] == NULL) {
        printf("Erro ao alocar memória para nova UF\n");
        return;
    }


    printf("Digite o codigo da UF: ");
    scanf("%d", &((*c)[(*tam)-1]->codigo));
    /* Aqui deve haver uma análise minuciosa: (*c) == q, (*c)[(*tam) - 1] entra em qual posição de interesse
     * do vetor. Sendo essa última parte um endereço, usamos -> para entrar em código, que é um inteiro, por isso
     * o &*/

    printf("Digite a sigla: ");
    fflush(stdin);// Evitar problemas com buffer.
    fgets((*c)[(*tam)-1]->sigla, 3, stdin);

    printf("Pessoa adicionada com sucesso\n");
}

void mostrar(struct uf * **c, int *tam) {
    for (int i = 0; i < *tam; i++) {
        printf("UF[%d]: %s\n", (*c)[i]->codigo, (*c)[i]->sigla);
    }
}