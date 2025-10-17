#include "ELEICAO.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciar_structs_elc(struct ELEICAO **q){
    for(int i = 0 ; i < 5 ; i++){
        q[i]->alow = 0;
    }
}
/*
 *  recebe um ponteiro para ponteiro p, que foi criada dentro da função campo_ELEICAO.
*/

void introduzir_elc() {
    printf("----------------------------------------[ELEICOES]---------------------------------------------\n");
    printf("O que deseja fazer?\n\n");
    printf("[1]Adicionar Eleicao\n");
    printf("[2]Mostrar Eleicao\n");
    printf("[3]Excluir Eleicao\n");
    printf("[4]Alterar Eleicao\n");
    printf("[5]Pesquisar Eleicao\n");
    printf("[6]Salvar e Voltar\n\n");
}
/*
 *  Introdução utilizada na função campo_uf.
 */

int achar_livre_elc(struct ELEICAO **q){
    for (int i = 0; i < 5; i++){
        if((q[i]->alow) == 0) return i;
    }
    return -1;
}
/*
 * Recebe o mesmo ponteiro pra ponteiro p. A função entra nas structs que foram trazidas para a ram e definem alow como 0.
 * Alow é uma flag que diz se a struct está sendo usada.
 * Futuramente alterar para nova função que mostra apenas as structs que foram alteradas dentro da ram para, na hora de gravar
 * no disco, não desperdiçar tempo. IDEIA: 0-vazio 1-preenchido 2-alterado na ram.
 */

int find_for_struct(struct ELEICAO **q,int year, int code) {
    for (int i = 0; i < 5; i++) {
        if ((q[i]->ano == year)&&(q[i]->codigo_uf == code)&&(q[i]->alow != 0)) {
            return i;
        }
    }
    return -1;
}//se achar uma struct com esse ano e codigo, retorna o indice da struct, se não, retorna -1

int verifica_cod_uf(int code) {
    struct uf {
        int a;
        int b;
        char c[20];
        char d[3];
    };
    struct uf *p = (struct uf *)malloc(sizeof(struct uf));

    FILE *U = fopen("ufs", "rb+");
    if(U == NULL) U = fopen("ufs", "wb+");
    if(U == NULL) { printf("erro ao abrir arquivo"); return 0; }

    int flag = 0;
    for (int i = 0 ; 1 ; i++) {
        fseek(U, i * sizeof(struct uf), SEEK_SET);
        int count = fread(p, sizeof(struct uf), 1, U);

        if (count == 0) {
            free(p);
            fclose(U);
            return 0;
        }

        if (p->b == code) {
            flag = 1;
            break;
        }
    }
    free(p);
    fclose(U);

    return flag;
}

void adicionar_elc(struct ELEICAO **q){
    int livre = achar_livre_elc(q);
    if(livre == -1) {
        printf("Lista Cheia\n");
        return;
    }
    printf("Digite as informacoes.\n");


    printf("Ano*:");
    fflush(stdin);
    scanf("%d", &(q[livre]->ano));

    while (1) {
        printf("Codigo da UF*:");
        fflush(stdin);
        scanf("%d", &(q[livre]->codigo_uf));

        if ( !verifica_cod_uf(q[livre]->codigo_uf) ) {
            printf("Codigo da UF nao existe\n");
            return;
        }
        break;
    }
    int indice = find_for_struct(q, (q[livre]->ano), q[livre]->codigo_uf);

    if (indice != -1) {
        printf("\nO conjunto ANO e Codigo da UF ja existem\n");
        return;
    }

    printf("Descricao*:");
    fflush(stdin);
    fgets(q[livre]->descricao, sizeof(q[livre]->descricao), stdin);

    for (int i = 0 ; q[livre]->descricao[i] != '\0' ; i++) {
        if (q[livre]->descricao[i] == '\n') q[livre]->descricao[i] = '\0';
    }

    printf("\n\nEleicao adicionada com sucesso\n\n");
    q[livre]->alow = 2;

}

void mostrar_elc(struct ELEICAO **q) {
    int flag = 0;
    printf("-------------------------------------------------------------------------------------------");
    for (int i = 0; i < 5; i++){
        if((q[i]->alow != 0) && (q[i]->alow !=3)){
            printf("\nAno: %d\n", (q[i]->ano));
            printf("Codigo UF: %d\n", q[i]->codigo_uf);
            printf("Descricao: %s\n", q[i]->descricao);
            printf("\n");
            flag++;
        }
    }
    if(flag == 0) printf("\n\nNao ha ELEICOES cadastradas\n\n");
}

void excluir_elc(struct ELEICAO **q) {

    while (1) {
        int year;
        int code;
        int indice;
        int escolha;

        printf("-------------------------------------------------------------------------------------\n");
        printf("Quem voce quer excluir?\n\n");
        printf("Digite o Ano:");
        scanf("%d", &year);

        printf("Digite o Codigo UF:");
        scanf("%d", &code);

        indice = find_for_struct(q, year, code);
        if (indice == -1) {
            printf("\nSem essa eleicao.\n");
            return;
        }
        printf("\n-------------------------------------------------------------------------------------\n");
        printf("Ano: %d\n", (q[indice]->ano));
        printf("Codigo UF: %d\n", (q[indice]->codigo_uf));
        printf("Descricao: %s\n", (q[indice]->descricao));

        printf("\nApagar?\n");
        printf("[1]Sim\n");
        printf("[2]Nao\n");

        scanf("%d", &escolha);
        if (escolha == 1) q[indice]->alow = 3;//3 é o estado de apagado
        printf("\n\nApagado com sucesso!!\n\n");
        return;
    }

}

void alterar_elc(struct ELEICAO **q) {
    while (1) {
        int year,code;
        int indice;
        int escolha;

        int new_year, new_code;
        char new_descricao[20];
        int new_indice;

        printf("-------------------------------------------------------------------------------------\n");
        printf("Quem voce quer alterar?\n\n");

        printf("Ano: ");
        scanf("%d", &year);

        printf("Codigo da UF: ");
        scanf("%d", &code);

        indice = find_for_struct(q, year, code);
        if (indice == -1) {
            printf("-------------------------------------------------------------------------------------\n");
            printf("\n\nSem essa eleicao.\n\n");
            break;
        }

        printf("-------------------------------------------------------------------------------------\n");
        printf("Ano: %d\n", (q[indice]->ano));
        printf("Codigo UF: %d\n", (q[indice]->codigo_uf));
        printf("Descricao: %s\n\n", (q[indice]->descricao));

        printf("O que alterar?\n\n");
        printf("[1]Ano e Codigo\n");
        printf("[2]Descricao\n");
        printf("[3]Voltar\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o novo ano: ");
                scanf("%d", &new_year);
                printf("Digite o codigo UF: ");
                scanf("%d", &new_code);


                new_indice = find_for_struct(q, new_year, new_code);// se retornar diferente de zero, ele achou uma struct com essa combinacao
                if ((new_indice != 0) && (new_indice != indice)) {//essa condição garante que não haja duas eleicoes iguais. PODE( 0 e ser igual a ela mesma)
                    printf("-------------------------------------------------------------------------------------\n");
                    printf("\nJa existe eleicao com essa combinacao.\n");
                    return;
                }

                //caso não entre no if, ele altera normalmente
                q[indice]->ano = new_year;
                q[indice]->codigo_uf = new_code;

                printf("-------------------------------------------------------------------------------------\n");
                printf("\n\nEleicao alterada com sucesso!!\n\n");
                q[indice]->alow = 2; //torna como alterada
                break;

            case 2:
                printf("-------------------------------------------------------------------------------------\n");
                printf("Digite a nova descricao: ");
                fflush(stdin);
                gets(new_descricao);

                strcpy(q[indice]->descricao, new_descricao);
                printf("-------------------------------------------------------------------------------------\n");
                printf("\n\nEleicao alterada com sucesso!!\n\n");
                q[indice]->alow = 2;//torna como alterada
                break;

            case 3:

                break;

            default: printf("\nOpcao invalida.\n");
        }
    }
}

void pesquisar_elc(struct ELEICAO **q) {
    int year, code;
    int indice;

    while (1) {
        printf("-------------------------------------------------------------------------------------\n");
        printf("Quem voce quer Achar?\n\n");

        printf("Ano: ");
        scanf("%d", &year);

        printf("Codigo da UF: ");
        scanf("%d", &code);

        indice = find_for_struct(q, year, code);
        if (indice == -1) {
            printf("-------------------------------------------------------------------------------------\n");
            printf("\n\nSem essa eleicao.\n\n");
            break;
        }

        printf("-------------------------------------------------------------------------------------\n");
        printf("Ano: %d\n", (q[indice]->ano));
        printf("Codigo UF: %d\n", (q[indice]->codigo_uf));
        printf("Descricao: %s\n\n", (q[indice]->descricao));
    }
}

void campo_ELEICAO() {
    struct ELEICAO *p[20];
    for(int i = 0 ; i < 20 ; i++){
        p[i] = (struct ELEICAO *)malloc(sizeof(struct ELEICAO));
    }//crio um vetor de ponteiro para struct UF e aloco um espaço struc UF para cada ponteiro

    iniciar_structs_elc(p);

    FILE *E = fopen("elc", "rb+");
    if(E == NULL) E = fopen("elc", "wb+");
    if(E == NULL) printf("erro ao abrir arquivo");// abro o arquivo de nome elc

    fseek(E, 0, SEEK_SET);
    for (int i = 0; i < 5; i++){
        fread(p[i], sizeof(struct ELEICAO), 1, E);
    }// lê para a memória alocada o tamanho de uma struct UF uma vez do arquivo U

    /////////////////////////////////////////////////////////////////////////////////////


    while(1) {

        introduzir_elc();

        int escolha;
        scanf("%d", &escolha);

        switch(escolha){
            case 1: adicionar_elc(p);
                break;

            case 2: mostrar_elc(p);
                break;

            case 3: excluir_elc(p);
                break;

            case 4: alterar_elc(p);
                break;

            case 5: pesquisar_elc(p);
                break;
            case 6:
                fseek(E, 0, SEEK_SET);
                for (int i = 0; i < 5; i++){
                    if (p[i]->alow == 2) {
                        p[i]->alow = 1;//quando salvo, deixa de ser tratado como alterado
                        fseek(E, i * sizeof(struct ELEICAO), SEEK_SET);
                        fwrite(p[i], sizeof(struct ELEICAO), 1, E);
                    }
                    if (p[i]->alow == 3) {
                        p[i]->alow = 0;//quando salvo deixa de ser tratado como excluído
                        fseek(E, i * sizeof(struct ELEICAO), SEEK_SET);
                        fwrite(p[i], sizeof(struct ELEICAO), 1, E);
                    }
                    /*else {
                        fseek(E, i * sizeof(struct ELEICAO), SEEK_SET);
                        fwrite(p[i], sizeof(struct ELEICAO), 1, E);
                    }*/
                }
                for(int i = 0 ; i < 5 ; i++) free(p[i]);
                fclose(E);
                return;

            default: printf("\nOpcao invalida\n");

        }

    }
}