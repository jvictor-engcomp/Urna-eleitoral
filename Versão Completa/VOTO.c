#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VOTO.h"

void introduzir_v() {
    printf("--------------------------------------[VOTOS]-----------------------------------------\n");
    printf("[1]Adicionar Votos\n");
    printf("[2]Mostrar Votos\n");
    printf("[5]Salvar e Voltar\n");
}

int achar_livre_v(struct VOTO **q){
    for (int i = 0; i < MAX_V; i++){
        if((q[i]->alow) == 0) return i;
    }
    return -1;
}

int verificar(int ano, int code) {
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

        if ((p->b ==ano) && (p->c ==code)) {
            flag = 1;
            break;
        }
    }
    free(p);
    fclose(E);

    return flag;
}// se o fread retornar zero, significa que ele chegou ao final do arquivo e não encontrou o code. Assim que ele encontrar ele retorna 1.

void adicionar_v(struct VOTO **q) {
    int livre = achar_livre_v(q);
    if(livre == -1) {
        printf("Lista Cheia\n");
        return;
    }
    printf("Digite as informacoes.\n");


    printf("Insira o Ano do voto: ");
    scanf("%d", &q[livre]->ano);

    printf("Insira codigo da UF: ");
    scanf("%d", &q[livre]->codigo_uf);

    if (!verificar(q[livre]->ano, q[livre]->codigo_uf)) {
        printf("\n\nConjunto Eleicao nao existe\n\n");
        return;
    }
    printf("Conjunto eleicao existe\n\n");

    printf("Insira o numero do candidato: ");
    scanf("%d", &q[livre]->numero_candidato);

    printf("insira data e hora: ");
    char data_hora[20];
    fflush(stdin);
    gets(data_hora);

    (q[livre]->alow) = 2;
}

void iniciar_structs_v(struct VOTO **q) {
    for(int i = 0 ; i < MAX_V ; i++) {
        q[i]->alow = 0;
    }
}

int find_for_ano_code(struct VOTO **q, int y, int c) {
    for (int i = 0; i < MAX_V; i++) {
        if ((q[i]->alow != 0) && (q[i]->ano == y) && (q[i]->codigo_uf == c)) {
            return i;
        }
    }
}

void mostrar_v(struct VOTO **q) {
    printf("Digite o Ano: ");
    int year;
    scanf("%d", &year);

    printf("Digite o codigo da UF: ");
    int codigo;
    scanf("%d", &codigo);

    printf("Digite o numero do candidato: ");
    int numero;
    scanf("%d", &numero);

    printf("Votos do Candidato %d, no Ano %d e na UF %d\n", numero, year, codigo);
    int count = 0;
    for (int i = 0; i < MAX_V; i++) {
        if ((q[i]->alow != 0) && (q[i]->ano == year) && (q[i]->codigo_uf == codigo) && (q[i]->numero_candidato == numero)) {
            printf("voto: %d, %d, %d.\n", year, codigo, numero);
            count++;
        }
    }
    printf("Numero total de votos: %d\n\n", count);


}

void campo_VOTO() {
    struct VOTO *p[MAX_V];
    for(int i = 0 ; i < MAX_V ; i++) {
        p[i] = malloc(sizeof(struct VOTO));
    }

    iniciar_structs_v(p);

    FILE *V = fopen("votos", "rb+");
    if(V == NULL) V = fopen("votos", "wb+");
    if(V == NULL) printf("erro ao abrir arquivo");

    fseek(V, 0, SEEK_SET);
    for (int i = 0; i < MAX_V; i++) {
        fread(p[i], sizeof(struct VOTO), 1, V);
    }

    ///////////////////////////////////////////////////////////////////////////////////////

    while(1) {
        introduzir_v();

        int escolha;
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:adicionar_v(p);
                break;
            case 2: mostrar_v(p);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                fseek(V, 0, SEEK_SET);
                for (int i = 0; i < MAX_V; i++){
                    if (p[i]->alow == 2) {
                        p[i]->alow = 1;//quando salvo, deixa de ser tratado como alterado
                        fseek(V, i * sizeof(struct VOTO), SEEK_SET);
                        fwrite(p[i], sizeof(struct VOTO), 1, V);
                    }
                }
                for(int i = 0 ; i < MAX_V ; i++) free(p[i]);
                fclose(V);
                return;

            default: printf("\nOpcao invalida\n");
        }

    }
}




