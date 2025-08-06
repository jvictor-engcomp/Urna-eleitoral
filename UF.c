
#include "UF.h"
/*
 * Nesse header MAX é definido como 27
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciar_structs(struct UF **q){
    for(int i = 0 ; i < MAX ; i++){
        q[i]->alow = 0;
    }
}
/*
 *  recebe um ponteiro para ponteiro p, que foi criada dentro da função campo_UF.
 *  p tem o endereço retornado pelo malloc para as 27 structs de UF.
*/


int achar_livre(struct UF **q){
        for (int i = 0; i < MAX; i++){
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


void introduzir(){
    printf("-----------------------------------------[UF]--------------------------------------------\n");
    printf("O que deseja fazer?\n\n");
    printf("[1]Adicionar UFs\n");
    printf("[2]Mostrar UFs\n");
    printf("[3]Excluir UFs\n");
    printf("[4]Alterar UF\n");
    printf("[5]Pesquisar UF\n");
    printf("[6]Salvar e Voltar\n\n");
}
/*
 *  Introdução utilizada na função campo_uf.
 */


int find_for_code(struct UF **q, int x){
    int indice = -1;

    for(int i = 0 ; i < MAX ; i++) {
            if ((q[i]->codigo == x)&(q[i]->alow != 0)) {
                indice = i;
                break;
            }
        }// acha a casinha do vetor que o codigo bate

    return indice;
}
/*
 * Também recebe p e recebe um inteiro x. A função procura o código x dentro das structs trazidas para a ram e retorna o
 * índice de localização dentro do vetor p. Quando não acha o inteiro x, ele retorna -1;
 */


int find_for_sigla(struct UF **q, char sigla[]){
    int indice = -1;

    for(int i = 0 ; i < MAX ; i++) {
            if ((!strcmp(q[i]->sigla, sigla))&(q[i]->alow != 0)) {
                indice = i;
                break;
            }
        }// acha a casinha do vetor que a sigla bate e se a caixinha está livre;

    return indice;
}
/*
 * Faz o mesmo, mas para a string sigla.
 */


void pesquisar(struct UF **q) {
    int escolha;
    int code;
    char sigla[3];
    int indice;
    /*
     * Variáveis usadas dentro da função.
     */

    while (1) {
        printf("\nQuem voce quer achar?\n\n");
        printf("[1]Achar por codigo\n");
        printf("[2]Achar por Sigla\n");
        printf("[3]Voltar\n");
        scanf("%d", &escolha);
        // Introdução

        switch (escolha) {
            // Para achar por código
            case 1:

                while (1) {
                    printf("Digite o Codigo: ");

                    fflush(stdin);
                    if (scanf("%d", &code) == 1) break;

                    printf("\nInsira um codigo valido.\n\n");

                }
                /*
                 *  Scanf retorna a quantidade de inteiros lidos, se algo diferente disso for informado, ele retorna 0.
                 *  Assim, a função só permite a entrada de números para a variável code.
                 */


                indice = find_for_code(q, code);
                if (indice == -1) {
                    printf("\nCodigo nao cadastrado\n");
                    break;
                }// Caso a função find_for_code não ache a variável code, esse if retorna para a introdução da função.



                printf("\ncodigo: %02d\n", (q[indice]->codigo));
                printf("Descricao: %s\n", q[indice]->descricao);
                printf("Sigla: %s\n", q[indice]->sigla);
                printf("\n");
                // mostrar a UF com determinado código.

                break;

            // Para achar por sigla
            case 2:
                while (1) {
                    fflush(stdin);
                    printf("Digite a Sigla: ");

                    fgets(sigla, sizeof(sigla), stdin);

                    int flag = 0;
                    for (int i = 0 ; sigla[i] != '\0' ; i++) {
                        if (isdigit(sigla[i]) != 0) {
                            printf("\nCampo nao aceita numeros\n");
                            flag++;
                            break;
                        }
                    }// Funçao isdigit analisa se o caractere é um decimal, se sim, ele retorna diferente de 0
                    if (flag ==1) continue;// Esse if faz com que o while recomece.

                    for (int i = 0 ; sigla[i] != '\0' ; i++) {
                        if (sigla[i] == '\n') sigla[i] = '\0';
                    }// Tiramos o \n da string

                    for (int i = 0 ; sigla[i] != '\0' ; i++) {
                        sigla[i] = toupper(sigla[i]);
                    }//Deixamos tudo maiúsculo.

                    break;
                }

                indice = find_for_sigla(q, sigla);
                if (indice == -1) {
                    printf("\nSigla nao cadastrada\n");
                    break;
                }
                // mostrar a UF com determinado codigo
                printf("\ncodigo: %02d\n", (q[indice]->codigo));
                printf("Descricao: %s\n", q[indice]->descricao);
                printf("Sigla: %s\n", q[indice]->sigla);
                printf("\n");


                break;
            case 3: return;
            default: printf("Insira um opcao valida");
        }
    }
}
/*
 * recebe p
 */


void adicionar(struct UF **q){
    int livre = achar_livre(q);
    if(livre == -1) {
        printf("Lista Cheia\n");
        return;
    }
    printf("Digite as informacoes.\n");

    while (1) {
        printf("Codigo*:");
        fflush(stdin);
        if (scanf("%d", &(q[livre]->codigo)) == 1) break;

        else {
            printf("\nInsira um codigo valido.\n\n");
        }

    }// se o usuário digitar uma letra, entra no else, pois o scanf só lê inteiros e retorna o número de inteiros que leu. Quando não lê, retorna

    //testar se o codigo se repete
    for (int i = 0 ; i < MAX ; i++) {
        if ((q[i]->alow != 0)&&(q[i]->codigo == q[livre]->codigo)){
            printf("\n\nERRO: O Codigo ja esta em uso\n\n");
            return;
        };
    }

    while (1) {
        fflush(stdin);
        printf("Descricao*:");

        fgets(q[livre]->descricao, sizeof(q[livre]->descricao), stdin);

        if (strcmp(q[livre]->descricao,"\n") == 0) {
                    printf("\nCampo obrigatorio.\n");
                    continue;
        }


        int flag = 0;
        for (int i = 0 ; q[livre]->descricao[i] != '\0' ; i++) {
            if (isdigit(q[livre]->descricao[i]) != 0) {
                printf("\nCampo nao aceita numeros\n");
                flag++;
                break;
            }
        }
        if (flag ==1) continue;

        for (int i = 0 ; q[livre]->descricao[i] != '\0' ; i++) {
            if (q[livre]->descricao[i] == '\n') q[livre]->descricao[i] = '\0';
        }
        break;
    }// area responsavel por garantir a entrada de dados na descrção sem numeros e que seja obrigatoria

    while (1) {
        fflush(stdin);
        printf("Sigla*:");

        fgets(q[livre]->sigla, sizeof(q[livre]->sigla), stdin);

        if (strcmp(q[livre]->sigla,"\n") == 0) {
            printf("\nCampo obrigatorio.\n");
            continue;
        }


        int flag = 0;
        for (int i = 0 ; q[livre]->sigla[i] != '\0' ; i++) {
            if (isdigit(q[livre]->sigla[i]) != 0) {
                printf("\nCampo nao aceita numeros\n");
                flag++;
                break;
            }
        }
        if (flag ==1) continue;

        for (int i = 0 ; q[livre]->sigla[i] != '\0' ; i++) {
            if (q[livre]->sigla[i] == '\n') q[livre]->sigla[i] = '\0';
        }

        for (int i = 0 ; q[livre]->sigla[i] != '\0' ; i++) {
                q[livre]->sigla[i] = toupper(q[livre]->sigla[i]);
            }

        break;
    }



    //testar se a sigla se repete
    for (int i = 0 ; i < MAX ; i++) {
        if ((q[i]->alow == 1) & (strcmp(q[i]->sigla, q[livre]->sigla) == 0)){
            printf("\n\nERRO: A sigla ja esta em uso\n\n");
            return;
        };
    }

    (q[livre]->alow) = 2;
}


void mostrar(struct UF **q){
    int flag = 0;
    printf("-------------------------------------------------------------------------------------------");
    for (int i = 0; i < MAX; i++){
        if((q[i]->alow) != 0){
            printf("\ncodigo: %02d\n", (q[i]->codigo));
            printf("Descricao: %s\n", q[i]->descricao);
            printf("Sigla: %s\n", q[i]->sigla);
            printf("\n");
            flag++;
        }
    }
    if(flag == 0) printf("\n\nNao ha UFs cadastradas\n\n");
}
/*
 * O que for diferente de zero no alow, ou seja, 1(preenchido) e 2(preenchido e alterado) é mostrado.
 */

void excluir(struct UF **q){


    while (1) {
        int escolha;
        char sigla[3];
        int yesnot;
        int indice;
        int code;
        printf("Quem voce quer excluir?\n\n");
        printf("[1]Achar por Codigo\n");
        printf("[2]Achar por Sigla\n");
        printf("[3]Voltar\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:


                while (1) {
                    printf("Digite o Codigo: ");
                    fflush(stdin);
                    if (scanf("%d", &code) == 1) break;

                    else {
                        printf("\nInsira um codigo valido.\n\n");
                    }

                }// se o usuário digitar uma letra, entra no else, pois o scanf só lê inteiros e retorna o número de inteiros que leu. Quando não lê, retorna 0


                indice = find_for_code(q, code);
                if(indice == -1) { printf("\nCodigo nao cadastrado\n\n"); break;}

                printf("\ncodigo: %02d\n", (q[indice]->codigo));
                printf("Descricao: %s\n", q[indice]->descricao);
                printf("Sigla: %s\n", q[indice]->sigla);
                printf("\n");

                printf("Apagar?\n[1]Sim\n[2]Nao\n\n");
                scanf("%d", &yesnot);
                if(yesnot == 1){
                    q[indice]->alow = 0;
                    printf("\n\nAPAGADO COM SUCESSO\n\n");
                }

                break;
            case 2:

                while (1) {
                    fflush(stdin);
                    printf("Digite a Sigla: ");

                    fgets(sigla, sizeof(sigla), stdin);




                    int flag = 0;
                    for (int i = 0 ; sigla[i] != '\0' ; i++) {
                        if (isdigit(sigla[i]) != 0) {
                            printf("\nCampo nao aceita numeros\n");
                            flag++;
                            break;
                        }
                    }
                    if (flag ==1) continue;

                    for (int i = 0 ; sigla[i] != '\0' ; i++) {
                        if (sigla[i] == '\n') sigla[i] = '\0';
                    }

                    for (int i = 0 ; sigla[i] != '\0' ; i++) {
                        sigla[i] = toupper(sigla[i]);
                    }

                    break;
                }// refinando para ser obrigatorio e não aceitar numeros


                indice = find_for_sigla(q, sigla);
                if(indice == -1) { printf("Sigla nao cadastrada\n"); break;}

                printf("\ncodigo: %02d\n", (q[indice]->codigo));
                printf("Descricao: %s\n", q[indice]->descricao);
                printf("Sigla: %s\n", q[indice]->sigla);
                printf("\n");

                printf("Apagar?\n[1]Sim\n[2]Nao\n\n");
                scanf("%d", &yesnot);
                if(yesnot == 1){
                    q[indice]->alow = 0;
                    printf("\n\nAPAGADO COM SUCESSO\n\n");
                }


                break;
            case 3: return;
            default: printf("\nOpcao invalida\n");
        }
    }
}

void alterar(struct UF **q) {
    while (1) {
        int code;int new_choice;int new_code;char new_desc[15];char new_sigla[3];char sigla[3];int flag;
        int escolha;
        int indice;
        // Variáveis usadas

        printf("\nQuem voce quer alterar?\n");
        printf("[1]Achar por Codigo\n");
        printf("[2]Achar por Sigla\n");
        printf("[3]Voltar\n");
        scanf("%d", &escolha);
        //introdução do primeiro switch

        switch (escolha) { //alterar
            case 1:
                while (1) {
                    printf("Digite o Codigo:");
                    fflush(stdin);
                    if (scanf("%d", &code) == 1) break;

                    else {
                        printf("\nInsira um codigo valido.\n\n");
                    }

                }// se o usuário digitar uma letra, entra no else, pois o scanf só lê inteiros e retorna o número de inteiros que leu. Quando não lê, retorna
                indice  = find_for_code(q, code);
                if (indice == -1) { printf("Codigo nao cadastrado\n"); break;}

                // mostrar a UF com determinado codigo
                printf("\ncodigo: %02d\n", (q[indice]->codigo));
                printf("Descricao: %s\n", q[indice]->descricao);
                printf("Sigla: %s\n", q[indice]->sigla);
                printf("\n");

                //interage com usuario para segundo switch
                printf("\nO que deseja alterar dessa UF?\n");
                printf("[1]Codigo\n");
                printf("[2]Descricao\n");
                printf("[3]Sigla\n");
                printf("[4]Voltar\n");


                scanf("%d", &new_choice);

                switch (new_choice) {
                    case 1:// OK!!!!!!!!!

                        printf("\nDigite o novo codigo:");
                        scanf("%d", &new_code);

                        flag = 0;
                        for (int i = 0 ; i < MAX && q[i]->alow; i++) {
                            if (i == indice) continue;
                            if (q[i]->codigo == new_code) {
                                flag++;
                            }
                        }// for que anda em todas as structs mas pula a que estamos alterando(trata fora do for o caso em que o new_code é igual ao codigo que já lá)

                        if (flag > 0) {
                            printf("\nERRO: codigo ja usada por outra UF\n");
                            break;
                        }

                        if (q[indice]->codigo == new_code) {
                            printf("\n\nVoce digitou o Codigo que ja estava na UF.\n\n");
                            break;
                        }// aqui o caso em que a new_code é igual a que já está lá.

                        q[indice]->codigo = new_code;
                        //caso nenhum if seja acionado
                        printf("\nUF alterada com sucesso\n");
                        q[indice]->alow = 2;// pois foi alterado
                        break;
                    case 2:
                        printf("\nDigite a nova descricao:");
                        fflush(stdin);
                        gets(new_desc);

                        //fazer funcao para verificar se descrição já existe
                        strcpy(q[indice]->descricao,new_desc);

                        printf("\nUF alterada com sucesso\n");
                        q[indice]->alow = 2;// pois foi alterado
                        break;
                    case 3://OK!!!!!!!!!!!!!!
                        printf("\nDigite a nova sigla:");
                        fflush(stdin);
                        gets(new_sigla);

                        for (int i = 0 ; new_sigla[i] != '\0' ; i++) {
                            new_sigla[i] = toupper(new_sigla[i]);
                        }// aqui, cada char de new_sigla é subistiuido por sua versão maiúscula


                        flag = 0;
                        for (int i = 0 ; i < MAX & q[i]->alow; i++) {
                            if (i == indice) continue;
                            if (strcmp(q[i]->sigla, new_sigla) == 0) {
                                flag++;
                            }
                        }//for que anda em todas as structs procurando pela new_sigla. O continue serve para pular a propria struct caso a new_sigla seja igual a que já estava, e a flag conta.

                        if (flag > 0) {
                            printf("\nERRO: sigla ja usada por outra UF\n");
                            break;
                        }

                        if (strcmp(q[indice]->sigla, new_sigla) == 0) {
                            printf("\n\nVoce digitou a Sigla que ja estava na UF.\n\n");
                            break;
                        }// aqui o caso em que a new_sigla é igual a que já está lá.

                        strcpy(q[indice]->sigla, new_sigla);
                        //caso nenhum if seja ativado, a new_sigla vai para dentro da struct

                        printf("\nUF alterada com sucesso\n");
                        q[indice]->alow = 2;// pois foi alterado
                        break;
                    case 4:
                        break;

                    default: printf("\nOpcao invalida\n");
                }

                break;
            case 2:

                printf("\nDigite a SIGLA:");
                fflush(stdin);
                gets(sigla);

                for (int i = 0 ; sigla[i] != '\0' ; i++) {
                    sigla[i] = toupper(sigla[i]);
                }

                indice  = find_for_sigla(q, sigla);
                if (indice == -1) { printf("Sigla nao cadastrada\n"); break;}

                // mostrar a UF com determinado sigla
                printf("\ncodigo: %02d\n", (q[indice]->codigo));
                printf("Descricao: %s\n", q[indice]->descricao);
                printf("Sigla: %s\n", q[indice]->sigla);
                printf("\n");

                //interage com usuario
                printf("\nO que deseja alterar nessa UF?\n");
                printf("[1]Codigo\n");
                printf("[2]Descricao\n");
                printf("[3]Sigla\n");
                printf("[4]Voltar\n");


                scanf("%d", &new_choice);

                switch (new_choice) {
                    case 1:// OK!!!!!!!!!

                        printf("\nDigite o novo codigo:");
                        scanf("%d", &new_code);

                        flag = 0;
                        for (int i = 0 ; i < MAX & q[i]->alow; i++) {
                            if (i == indice) continue;
                            if (q[i]->codigo == new_code) {
                                flag++;
                            }
                        }// for que anda em todas as structs mas pula a que estamos alterando(trata fora do for o caso em que o new_code é igual ao codigo que já lá)

                        if (flag > 0) {
                            printf("\nERRO: codigo ja usada por outra UF\n");
                            break;
                        }

                        if (q[indice]->codigo == new_code) {
                            printf("\n\nVoce digitou o Codigo que ja estava na UF.\n\n");
                            break;
                        }// aqui o caso em que a new_code é igual a que já está lá.

                        q[indice]->codigo = new_code;
                        //caso nenhum if seja acionado
                        printf("\nUF alterada com sucesso\n");
                        q[indice]->alow = 2;// pois foi alterado
                        break;
                    case 2:
                        printf("\nDigite a nova descricao:");
                        fflush(stdin);
                        gets(new_desc);

                        //fazer funcao para verificar se descrição já existe
                        strcpy(q[indice]->descricao,new_desc);

                        printf("\nUF alterada com sucesso\n");
                        q[indice]->alow = 2;// pois foi alterado
                        break;
                    case 3://OK!!!!!!!!!!!!!!
                        printf("\nDigite a nova sigla:");
                        fflush(stdin);
                        gets(new_sigla);

                        for (int i = 0 ; new_sigla[i] != '\0' ; i++) {
                            new_sigla[i] = toupper(new_sigla[i]);
                        }// aqui, cada char de new_sigla é subistiuido por sua versão maiúscula


                        flag = 0;
                        for (int i = 0 ; i < MAX & q[i]->alow; i++) {
                            if (i == indice) continue;
                            if (strcmp(q[i]->sigla, new_sigla) == 0) {
                                flag++;
                            }
                        }//for que anda em todas as structs procurando pela new_sigla. O continue serve para pular a propria struct caso a new_sigla seja igual a que já estava, e a flag conta.

                        if (flag > 0) {
                            printf("\nERRO: sigla ja usada por outra UF\n");
                            break;
                        }

                        if (strcmp(q[indice]->sigla, new_sigla) == 0) {
                            printf("\n\nVoce digitou a Sigla que ja estava na UF.\n\n");
                            break;
                        }// aqui o caso em que a new_sigla é igual a que já está lá.

                        strcpy(q[indice]->sigla, new_sigla);
                        //caso nenhum if seja ativado, a new_sigla vai para dentro da struct

                        printf("\nUF alterada com sucesso\n");
                        q[indice]->alow = 2;// pois foi alterado
                        break;
                    case 4:
                        break;
                }

                break;
            case 3: return;
                break;

        }
    }
}

void campo_UF(){


    struct UF *p[MAX];
    for(int i = 0 ; i < MAX ; i++){
        p[i] =(struct UF*) malloc(sizeof(struct UF));
    }//crio um vetor de ponteiro para struct UF e aloco um espaço struc UF para cada ponteiro 

    iniciar_structs(p); //inicia todos os campos alow em 0

    FILE *U = fopen("ufs", "rb+");
    if(U == NULL) U = fopen("ufs", "wb+");
    if(U == NULL) printf("erro ao abrir arquivo");// abro o arquivo de nome ufs



    fseek(U, 0, SEEK_SET);
    for (int i = 0; i < MAX; i++){
        fread(p[i], sizeof(struct UF), 1, U);
    }// lê para a memória alocada o tamanho de uma struct UF uma vez do arquivo U

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    

    while(1){

        introduzir();

        int escolha;
        scanf("%d", &escolha);

        switch(escolha){
            case 1: adicionar(p);
            break;

            case 2: mostrar(p);
            break;

            case 3: excluir(p);
                break;

            case 4: alterar(p);
                break;

            case 5: pesquisar(p);
                break;
            case 6:
            fseek(U, 0, SEEK_SET);
            for (int i = 0; i < MAX; i++){
                if (p[i]->alow == 2) {
                    p[i]->alow = 1;//quando salvo, deixa de ser tratado como alterado
                    fseek(U, i * sizeof(struct UF), SEEK_SET);
                    fwrite(p[i], sizeof(struct UF), 1, U);
                }
                else {
                    fseek(U, i * sizeof(struct UF), SEEK_SET);
                    fwrite(p[i], sizeof(struct UF), 1, U);
                }
            }
            for(int i = 0 ; i < MAX ; i++) free(p[i]);
            fclose(U); 
            return;

            default: printf("\nOpcao invalida\n");

        }
    }

 }