#include "PESSOA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





/*faz a procura de uma pessoa cadastrada pelo seu CPF comparando o CPF enviado aos CPFs já existentes,
 *caso exista, a funcao retorna
 *o numero do vetor dessa pessoa, caso não exista a funcao retorna -1*/
int search_by_CPF(char CPF[20], struct PESSOA *p[]) {
    int counter = 0; int flag = 0; int qts_cadas = 0;
    //quantidade de pessoas cadastradas
    for (int i = 0; i < MAX_P; i++) {
        if (p[i]->allow == 1) {
            qts_cadas++;
        }
    }
    /* flag conta se o CPF foi encontrado ao comparar, e counter conta caso não o encontre. como o MAX já é definido,
     * se counter for igual a quantidade de pessoas cadastradas +1 (ou seja já vai ter passado da quantidade possivel de cadastros),
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

//pode-se aplicar a mesma logia da funcao search_CPF para esta, são idênticas
int search_titulo(char titulo[25], struct PESSOA *p[]) {
    int counter = 0; int flag = 0; int qts_cadas = 0;
    for (int i = 0; i < MAX_P; i++) {
        if (p[i]->allow == 1) {
            qts_cadas++;
        }
    }

    //MAJOR bruhh moment, o que voce está olhando aqui, se claramente é igual ao search_by_CPF...? (ㆆ_ㆆ)
    while ( !flag && counter != (qts_cadas + 1)) {
        if (!(strcmp(p[counter]->titulo,titulo))&&(p[counter]->allow == 1)) {
            flag++;
        }else {
            counter++;
        }
    }
    if (counter == (qts_cadas + 1)) {
        return -1;
    }else {
        return counter;
    }
}



//a funcao imprime os dados de uma pessoa pelo CPF digitado utilizando a funcao Search_by_CPF já declarada
void mostrar_uma(struct PESSOA *p[]) {
    int counter; char titulo[25]; char aux;
    printf("Digite o TITULO da pessoa: ");
    fflush(stdin);
    gets(titulo);
    counter = search_titulo(titulo,p);
    if (counter == -1) {
        printf("Este TITULO nao foi cadastrado!\n");
        return;
    }
    printf("----------DADOS----------\n");
    printf("NOME: %s\n",p[counter]->nome);
    printf("CPF: %s\n",p[counter]->CPF);
    printf("TITULO: %s\n",p[counter]->titulo);
    printf("FONE: %s\n",p[counter]->fone);
    printf("ENDERECO: %s\n",p[counter]->endereco);
    printf("DATA NASCAC: %s\n",p[counter]->data_nascimento);
    if (p[counter]->comparecimento == 1)
        printf("Comparecimento: REGISTRADO\n");
    else
        printf("Comparecimento: NAO REGISTRADO!\n");
    printf("-------------------------\n\n");
    printf("Deseja ver mais alguma pessoa? (S/N)\n");
    scanf("%c", &aux);
    if (aux == 'S' || aux == 's') {
        mostrar_uma(p);
    }
}

void alterar_pessoa(struct PESSOA *p[]) {
    int choice; int pessoa;char nascimento[11]; int aux;  char CPF[20]; char titulo[25]; char telefone[20]; char endereco[100];
    printf("Digite o CPF ATUAL da pessoa a ser alterada: ");
    fflush(stdin);
    gets(CPF);
    //procura a pessoa pelo CPF digitado e retorna a posicao dela no vetor, na qual a variavel "Pessoa" recebe, e vira o indice do vetor no qual queremos modificar
    pessoa = search_by_CPF(CPF,p);
    if (pessoa == -1) {
        printf("Esse CPF nao esta cadastrado!\n");
        return;
    }
    printf("Digite:\n");
    printf("[1]para alterar NOME\n");
    printf("[2]para alterar CPF\n");
    printf("[3]para alterar TITULO\n");
    printf("[4]para alterar TELEFONE\n");
    printf("[5]para alterar ENDERECO\n");
    printf("[6]para alterar DATA NASCIMENTO\n");
    printf("Qualquer outra tecla para sair\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Digite o NOVO NOME: ");
            char nome[50];
            fflush(stdin);
            fgets(nome,50,stdin);
            strcpy(p[pessoa]->nome,nome);
            printf("NOME alterado com sucesso!\n");
            return;
        case 2:
            //a variavel CPF irá receber o novo CPF digitado, após isso o novo CPF será verificado na funcao search_by_CPF. Caso ela retorne -1 é porque esse CPF ainda não foi cadastrado, logo pode ser usado
            printf("Digite o NOVO CPF: ");
            fflush(stdin);
            gets(CPF);
            aux = search_by_CPF(CPF,p);
            if (aux != -1) {
                printf("CPF ja cadastrado!\n");
                return;
            }
            strcpy(p[pessoa]->CPF,CPF);
            printf("CPF alterado com sucesso!\n");
            return;
            case 3:
            //praticamente a mesma coisa do search_by_CPF, porem ao inves de CPF será o Titulo
                printf("Digite o NOVO TITULO: ");
                fflush(stdin);
                gets(titulo);
                aux = search_titulo(titulo,p);
                if (aux != -1) {
                    printf("TITULO ja existe!\n");
                    return;
                }
                strcpy(p[pessoa]->titulo,titulo);
                printf("TITULO alterado com sucesso!\n");
                return;
            case 4:
            //voce nao ta achando que TELEFONE é key, né? (●'◡'●)
                printf("Digite o NOVO TELEFONE: ");
                fflush(stdin);
                gets(telefone);
                strcpy(p[pessoa]->fone, telefone);
                printf("TELEFONE alterado com sucesso!\n");
            return;
            case 5:
            //(*/ω＼*) para-... isso também não é key ಥ_ಥ
                printf("Digite o NOVO ENDERECO: ");
                fflush(stdin);
                gets(endereco);
                strcpy(p[pessoa]->endereco, endereco);
                printf("ENDERECO alterado com sucesso!\n");
            return;
            case 6:
                //Será que a gente nasceu no mesmo dia...? (✿ ◕‿◕ ✿)
                printf("Digite a NOVA DATA de NASCIMENTO: ");
                fflush(stdin);
                gets(nascimento);
                strcpy(p[pessoa]->data_nascimento, nascimento);
                printf("DATA NASCIMENTO alterada com sucesso!\n");
            return;

    }

}

//mano aqui é bem fácil, só mudar o Allow de 1 pra 0 (〜￣▽￣)〜
void remover_pessoa(struct PESSOA *p[]) {
    char titulo[25]; int counter; char flag2;

        printf("Digite o CPF da pessoa a ser removida: ");
        fflush(stdin);
        gets(titulo);
        counter = search_titulo(titulo, p);
        if (counter == -1) {
            printf("Nao existem pessoas cadastradas com esse TITULO!\n");
            return;
        }
        //mostrar as informações da pessoa a ser removida
        printf("----------DADOS DA PESSOA A SER REMOVIDA----------\n");
        printf("NOME: %s\n",p[counter]->nome);
        printf("CPF: %s\n",p[counter]->CPF);
        printf("TITULO: %s\n",p[counter]->titulo);
        printf("FONE: %s\n",p[counter]->fone);
        printf("ENDERECO: %s\n",p[counter]->endereco);
        printf("DATA NASCIMENTO: %s\n",p[counter]->data_nascimento);
        printf("--------------------------------------------------\n");
        //Codigo para confirmar a exclusao da pessoa
        printf("CONFIRMA EXCLUSAO? (S/N):");
        fflush(stdin);
        scanf("%c", &flag2);
        //caso seja lida o caractere 'S' a funcao muda o valor de ALLOW da struct a ser removida para 0, indicando estar livre
        if (flag2 == 'S' || flag2 == 's') {
            p[counter]->allow = 0;
            printf("Pessoa removida com sucesso!\n");
            return;
        }else {
            printf("Operacao cancelada! \n");
            return;


    }
}



//funcao para inserir pessoas.
void inserir_pessoa(struct PESSOA *p[]) {
    int flag = 0;
    for (int i = 0; i < MAX_P; i++) {



        //Verifica o Allow de p[i]->allow, caso seja 0 é porque esse vetor está livre, caso contrário está cheio.
        if (p[i]->allow == 0) {
            printf("Digite o nome:\n");
            fflush(stdin);
            gets(p[i]->nome);
            fflush(stdin);

            printf("Digite o CPF: ");
            fflush(stdin);
            gets(p[i]->CPF);
            //laço para comparar CPFs e verificar se ja foi registrado, o for deve encontrar somente um CPF repetido(que é o próprio digitado), caso tenha mais de um, ele dá erro
                for (int k = 0; k <= MAX_P; k++) {
                    if (strcmp(p[i]->CPF, p[k]->CPF) == 0) {
                        flag++;
                    }
                }

            if (flag > 1) {
                printf("O CPF ja foi registrado!\n");
                return;
            }
            flag = 0;


            printf("Digite data de nascimento: ");
            fflush(stdin);
            gets(p[i]->data_nascimento);
            fflush(stdin);

            printf("Digite o Titulo: ");
            fflush(stdin);
            gets(p[i]->titulo);

            //laço para comparar titulos e verificar se ja foi registrado, o for deve encontrar somente um titulo repetido(que é o próprio digitado), caso tenha mais de um, ele dá erro
                for (int k = 0; k <= MAX_P; k++) {
                    if (strcmp(p[i]->titulo, p[k]->titulo) == 0) {
                        flag++;
                    }
                }

            if (flag>1) {
                printf("O titulo ja foi registrado!\n");
                return;
            }
            flag = 0;


            printf("[OPCIONAL] Digite o telefone: ");
            fflush(stdin);
            gets(p[i]->fone);
            fflush(stdin);
            /*if (!strcmp("\n",p[i]->fone)) {
                strcpy(p[i]->fone,"n/ infor.");
            }*/


            printf("[OPCIONAL] Digite o endereco: ");
            fflush(stdin);
            gets(p[i]->endereco);
            fflush(stdin);
            /*if (!strcmp("\n",p[i]->endereco)) {
                strcpy(p[i]->endereco,"n/ infor.");
            }*/

            printf("PESSOA INSERIDA COM SUCESSO!\n");

            p[i]->allow = 1;
            printf("Deseja adicionar mais alguma pessoa?\n");
            printf("[1]Sim\n[2]NAO\n");
            scanf("%d", &flag); if (flag == 1) { } else return;
            flag = 0;
        }

    }
    // caso nao encontre nenhum vetor com allow == 0, é porque não existe nenhum vetor disponivel, logo espaço lotado
    printf("Sem espaco!");
}

//funcao para iniciar os ALLOWs das structs em 0
void iniciar_pessoas(struct PESSOA *p[]) {
    for (int i = 0; i < MAX_P; i++) {
        p[i]->allow = 0;
        p[i]->comparecimento = 0;
    }
}

//funcao para listar todas as pessoas cadastradas, caso nao tenha ninguem cadastrado ele avisa
void mostrar_todas(struct PESSOA *p[]) {
    int aux = 0;
    for (int i = 0; i < MAX_P; i++) {
        if (p[i]->allow == 1) {
            printf("--------------------------------\n\n");
            printf("Nome: %s\n", p[i]->nome);
            printf("CPF: %s\n", p[i]->CPF);
            printf("Titulo: %s\n", p[i]->titulo);
            printf("Telefone: %s\n", p[i]->fone);
            printf("Endereco: %s\n", p[i]->endereco);
            printf("Data nascimento: %s\n", p[i]->data_nascimento);
            if (p[i]->comparecimento == 1)
                printf("Comparecimento: REGISTRADO\n");
            else
                printf("Comparecimento: NAO REGISTRADO\n");
            printf("--------------------------------\n\n");
            }else aux++;
        }
    if (aux == MAX_P) printf("Nenhuma pessoa na lista!\n");
}




void campo_PESSOA()
{
    struct PESSOA *p[MAX_P];
    for(int i = 0 ; i < MAX_P ; i++) {
        p[i] = (struct PESSOA *)malloc(sizeof(struct PESSOA));
    }
    iniciar_pessoas(p);

    //abrir arquivo e verificar se a abertura ocorreu corretamente
    FILE *f = fopen("pessoas", "rb+");
    if (f == NULL) f = fopen("pessoas", "wb+");
    if (f == NULL) {
        printf("erro ao abrir arquivo, tente novamente\n");
        return;
    }

    //escrever dados do arquivo no vetor
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < MAX_P; i++) {
        fread(p[i], sizeof(struct PESSOA), 1, f);
    }


    int choice;

    /*printf("Digite sua opcao para PESSOA:\n");
    printf("[1]Inserir Pessoa\n");
    printf("[2]Remover Pessoa\n");
    printf("[3]Alterar Pessoa\n");
    printf("[4]Mostrar Todas as Pessoas\n");
    printf("[5]Mostrar Uma Pessoa\n");
    printf("[6] Sair\n");*/

    //UI para escolhas
    do {
        printf("---------------------------------------[PESSOAS]----------------------------------------\n");
        printf("Digite sua opcao para PESSOA:\n");
        printf("[1]Inserir Pessoa\n");
        printf("[2]Remover Pessoa\n");
        printf("[3]Alterar Pessoa\n");
        printf("[4]Mostrar Todas as Pessoas\n");
        printf("[5]Mostrar Uma Pessoa\n");
        printf("[6] Salvar e Voltar\n");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inserir_pessoa(p); break;
            case 2:
                remover_pessoa(p); break;
            case 3:
                alterar_pessoa(p); break;
            case 4:
                mostrar_todas(p); break;
            case 5:
                mostrar_uma(p); break;
                case 6: break;
                default: printf("Opcao invalida\n");
        }

    }while(choice != 6);



    //escrever dados salvos das structs no arquivo e depois liberar o malloc
    fseek(f, 0, SEEK_SET);
    for(int i = 0 ; i < MAX_P ; i++) {
        fwrite(p[i], sizeof(struct PESSOA), 1, f);
        free(p[i]);
    }
    fclose(f);
}