#include "candidato.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UF.h"

void mostrar_todos_UF(struct candidato *c[]) {
    int UF, flag=0;
    printf("Digite a UF: ");
    scanf("%d", &UF);
    for (int i = 0; i < 10; i++) {
        if (c[i]->allow == 1 && c[i]->UF == UF) {
            printf("----------DADOS DO CANDIDATO [%d]----------\n",flag);
            printf("CPF: %s\n",c[i]->CPF);
            printf("ANO: %d\n",c[i]->ano);
            printf("NUMERO: %d\n",c[i]->numero);
            printf("-------------------------------------------\n\n");
            flag++;
        }
    }
    if (flag==0)
        printf("Nao foram cadastrados candidatos nessa UF!\n");
}

void mostrar_todos_ano(struct candidato *c[]) {
    int ANO, flag=0;
    printf("Digite o Ano: ");
    scanf("%d", &ANO);
    for (int i = 0; i < 10; i++) {
        if (c[i]->allow == 1 && c[i]->ano == ANO) {
            printf("----------DADOS DO CANDIDATO [%d]----------\n",flag);
            printf("CPF: %s\n",c[i]->CPF);
            printf("ANO: %d\n",c[i]->ano);
            printf("NUMERO: %d\n",c[i]->numero);
            printf("-------------------------------------------\n\n");
            flag++;
        }
    }
    if (flag==0)
        printf("Nao foram cadastrados candidatos nesse ANO!\n");
}



int search_by_CPF_Candidato(char CPF[20], struct candidato *p[]) {
    int counter = 0; int flag = 0; int qts_cadas = 0;
    //quantidade de candidatos cadastrados
    for (int i = 0; i < 10; i++) {
        if (p[i]->allow == 1) {
            qts_cadas++;
        }
    }
    /* flag conta se o CPF foi encontrado ao comparar, e counter conta caso não o encontre. como o MAX já é definido,
     * se counter for igual a quantidade de candidatos cadastrados +1 (ou seja já vai ter passado da quantidade possivel de cadastros),
     * o loop termina, pois não foi encontrado ninguem com aquele CPF, mesma coisa caso flag seja 1, pois já foi encontrado alguem com
     * o respectivo CPF */
    while ( !flag && (counter != (qts_cadas + 1))) {
        /*aqui flag serve para verificar se o CPF foi encontrado, caso não tenha sido, counter é acrescentado*/
        if (!(strcmp(p[counter]->CPF,CPF))&&(p[counter]->allow == 1)){
            flag++;
        }else {
            counter++;
        }
    }
    /*obviamente que, se counter for igual a quantidade de pessoas cadastradas +1, quer dizer que o loop terminou
     * sem termos encontrado alguem com o CPF, logo retorna-se -1
     */
    if (counter == (qts_cadas + 1)) {
        return -1;
    }else {
        return counter;
    }
}


void excluir_candidato(struct candidato *c[]) {
    char CPF[20]; int indice; int aux;
    printf("Digite o CPF do candidato a ser excluido: ");
    fflush(stdin);
    gets(CPF);
    indice   = search_by_CPF_Candidato(CPF,c);
    if (indice == -1) {
        printf("CPF nao cadastrado!\n"); return;
    }
    printf("----------DADOS DO CANDIDATO----------\n");
    printf("ANO: %d\n",c[indice]->ano);
    printf("CPF: %s\n",c[indice]->CPF);
    printf("UF: %d\n",c[indice]->UF);
    printf("Numero: %d\n",c[indice]->numero);
    printf("--------------------------------------\n");
    printf("Confirma exclusao?\n [1]SIM [Qualquer outro]NAO\n");
    scanf ("%d",&aux);
    if (aux == 1)
        c[indice]->allow = 0;
    else
        printf("Exclusao cancelada!"); return;
}

int verificar_v(int ano, int code) {
    struct eleicao {
        int a;
        int b;
        int c;
        char d[20];
    };
    struct eleicao *p = malloc(sizeof(struct eleicao));

    FILE *E = fopen("elc", "rb+");
    if(E == NULL) E = fopen("elc", "wb+");
    if(E == NULL) printf("erro ao abrir arquivo");// abro o arquivo de nome elc

    int flag = 0;
    for (int i = 0 ; 1 ; i++) {
        fseek(E, i * sizeof(struct eleicao), SEEK_SET);
        int count = fread(p, sizeof(struct eleicao), 1, E);

        if (count == 0) {
            free(p);
            fclose(E);
            return 0;
        }

        if ((p->b == ano) && (p->c == code)) {
            flag = 1;
            break;
        }
    }
    free(p);
    fclose(E);

    return flag;
}// se o fread retornar zero, significa que ele chegou ao final do arquivo e não encontrou o code. Assim que ele encontrar ele retorna 1.

int verificar_cpf(char cpf[]) {
    struct pessoa {
        int a;
        int x;
        char b[20];
        char c[25];
        char d[50];
        char e[20];
        char f[100];
        char g[11];
    };
    //struct modelo pessoas para permitir navergarmos corretamente com o fseek no arquivo pessoas

    struct pessoa *p = malloc(sizeof(struct pessoa));

    FILE *f = fopen("pessoas", "rb+");
    if (f == NULL) f = fopen("pessoas", "wb+");
    if (f == NULL) {
        printf("erro ao abrir arquivo, tente novamente\n");
        return 0;
    }

    int flag = 0;
    for (int i = 0 ; 1 ; i++) {
        fseek(f, i * sizeof(struct pessoa), SEEK_SET);
        int count = fread(p, sizeof(struct pessoa), 1, f);

        if (count == 0) {
            free(p);
            fclose(f);
            return 0;
        }

        p->b[strcspn(p->b, "\n")] = '\0';
        cpf[strcspn(cpf, "\n")] = '\0';

        if (!strcmp(p->b, cpf)) {
            flag = 1;
            break;
        }
    }
    free(p);
    fclose(f);

    return flag;
}

void inserir_candidato(struct candidato *c[]) {
    FILE *u = fopen("ufs", "rb+"); struct UF *uf[27];
    fseek(u, 0, SEEK_SET);
    for (int i = 0; i < 27; i++) {
        uf[i] = malloc(sizeof(struct UF));
        fread(uf[i], sizeof(struct UF), 1, u);
    }

    fflush(stdin);
    for (int indice = 0; indice < 10; indice++) {
        int UF; int flag = 0; char CPF[3]; int numero;
        if (c[indice]->allow == 0) {
            printf("-------------------------------------------------------------------------------------\n");
            printf("Escolhendo ELEICAO existente.");

            printf("Digite o ANO: ");
            scanf("%d", &c[indice]->ano);

            printf("Digite o NUMERO da UF: ");
            fflush(stdin);
            scanf("%d", &UF);


            if (!verificar_v(c[indice]->ano, UF)) {
                printf("\n\nConjunto Eleicao nao existe!\n\n");
                return;
            }
            printf("\n\nConjunto eleicao existe!\n\n");

            flag = find_for_code(uf,UF);
            if (flag == -1) {
                printf("UF nao cadastrada!\n");
                return;
            }
            c[indice]->UF = UF;


            printf("Digite o CPF do candidato: ");
            fflush(stdin);
            fgets(c[indice]->CPF, sizeof(c[indice]->CPF) ,stdin);


            if (!verificar_cpf(c[indice]->CPF)) {
                printf("\n\nPessoa com esse CPF nao existe\n\n");
                return;
            }

            printf("Digite o numero do candidato(Ex.: 51, 87): ");
            scanf("%d", &numero);
            flag = 0;
            for (int j = 0; j < 10; j++) {
                if ((c[j]->numero) == (numero)&&(c[j]->allow == 1)) {
                    flag++;
                    printf("ops\n");
                }
            }
            if (flag) {
                printf("Numero ja cadastrado!\n");
                return;
            }
            c[indice]->numero = numero;
            for (int k = 0; k < 27; k++) {
                free(uf[k]);
            }
            printf("cadastrado com sucesso!\n");
            c[indice]->allow = 1;
            fclose(u);
            return;
        }
    }
    for (int indice = 0; indice < 10; indice++) {
        printf("%d\n",c[indice]->allow);
    }
    for (int k = 0; k < 27; k++) {
        free(uf[k]);
    }
    fclose(u);
    printf("nao há espaço!"); return;
}



void campo_candidato() {
    struct candidato *c[20];
    for (int i = 0; i < 10; i++) {
        c[i]=(struct candidato *)malloc(sizeof(struct candidato));
        c[i]->allow = 0;
    }
    FILE *f = fopen("candidato", "rb+");
    if (f == NULL) {
        f = fopen("candidato", "wb+");
        for (int i = 0; i < 10; i++) {
            fwrite(c[i], sizeof(struct candidato), 1, f);
        }
    }else if (f == NULL){
            printf("ERRO AO ABRIR O ARQUIVO KKKKKKKKK"); return;
    }else {
        for (int i = 0; i < 10; i++) {
            fread(c[i], sizeof(struct candidato), 1, f);
            if (c[i]->allow != 1)
                c[i]->allow = 0;
        }
    }
    int choice = 1, flag = 0;

    do {
        printf("[1]INSERIR Candidato\n");
        printf("[2]EXCLUIR Candidato\n");
        printf("[3]MOSTRAR todos os Candidatos por Codigo da UF\n");
        printf("[4]MOSTRAR todos os Candidatos por ANO \n");
        printf("[5]SAIR & SALVAR\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inserir_candidato(c);
                break;
            case 2:
                excluir_candidato(c);
                break;
            case 3:
                mostrar_todos_UF(c);
                break;
            case 4:
                mostrar_todos_ano(c);
                break;
            case 5: flag++; break;
                default: printf("Digite um numero valido!\n"); break;
        }
    }while (!flag);
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < 10; i++) {
        fwrite(c[i], sizeof(struct candidato), 1, f);
        free(c[i]);
    }
    fclose(f);
    return;
}