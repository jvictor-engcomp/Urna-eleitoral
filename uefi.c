#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uefi.h"

void campo_UF() {
    // início do pré-processamento(trazer as informações para a memória)
    FILE *fq = fopen("quantidade_uf", "rb+");
    if (fq == NULL) fq = fopen("quantidade_uf", "wb+");
    if (fq == NULL) {
        printf("Erro ao abrir arquivo da quantidade de UFs\n");
        return ;
    }
    /* Função para abrir um arquivo de nome quantidade, se ele não existir, ele é criado. Caso não seja possível
     * criar, o programa fecha.
     */

    int *q_uf = malloc(sizeof(int));
    if (q_uf == NULL) {
        printf("Erro ao alocar memoria\n");
        free(q_uf);// liberação de memória apenas porque a IDE reclama, mas não é necessário já que o programa se fecha ao entrar no if.
        return ;
    }
    /*
     * memoria alocada para guardar o número de ufs
     */

    fseek(fq, 0, SEEK_SET);
    if (fread(q_uf, sizeof(int), 1, fq) == 0) {
        *q_uf = 0;
    }// q_uf aponta para espaço que guarda quantidade de ufs

    /////////////////////////////////////////// para as informações das ufs////////////////

    FILE *fu = fopen("ufss", "rb+");
    if (fu == NULL) fu = fopen("ufss", "wb+");
    if (fu == NULL) {
        printf("Erro ao abrir arquivo UFs\n");
        return;
    }// tenta abrir um arquivo com as informações das ufs

    struct uf *u;
    if (*q_uf == 0) u = NULL;
    else {
        u = malloc(*q_uf * sizeof(struct uf));
        if (u == NULL) {
            printf("Erro ao alocar memoriaaaaaaaaaaaa\n");
            free(u);
            return ;
        }
    }// aloca espaço somente necessário


    fseek(fu, 0, SEEK_SET);
    fread(u, sizeof(struct uf), *q_uf, fu);
    //traz para memória alocada

    //fim do pré-processamento

    //conversa com o usuário
    while(1){

        conversa_uf();

        int escolha;
        scanf("%d", &escolha);

        switch(escolha){
            case 1: adicionar_uf( &u, q_uf);
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;
            case 6:
                return;
            default: printf("\nOpcao invalida\n");

        }
    }

}

void conversa_uf() {
    printf("-----------------------------------------[UF]--------------------------------------------\n");
    printf("O que deseja fazer?\n\n");
    printf("[1]Adicionar UFs\n");
    printf("[2]Mostrar UFs\n");
    printf("[3]Excluir UFs\n");
    printf("[4]Alterar UF\n");
    printf("[5]Pesquisar UF\n");
    printf("[6]Salvar e Voltar\n\n");
}

void adicionar_uf(struct uf * *c, int *tam) {
    // * *c pois irei alterar o endereço que U quarda. *tam pois só irei alterar o que há no endereço de q_uf
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
    /* */

    printf("Digite a sigla: ");
    fflush(stdin);// Evitar problemas com buffer.
    fgets((*c + (*tam - 1))->sigla, 3, stdin);

    printf("Pessoa adicionada com sucesso\n");
}