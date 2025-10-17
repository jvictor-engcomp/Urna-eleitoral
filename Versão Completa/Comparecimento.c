#include "Comparecimento.h"
#include "PESSOA.h"
#include <stdio.h>
#include <stdlib.h>



void verificar_comparecimento(struct PESSOA *p[]){
    int titulo;
    printf("Digite o TITULO da pessoa a ser verificada: ");
    scanf("%d", &titulo);
    int indice = search_titulo(titulo,p);
    if(indice == -1){
        printf("TITULO NAO REGISTRADO!!\n");
        return;
    }
    if(p[indice]->comparecimento==0){
        printf("O comparecimento de [%s] NAO foi registrado!\n",p[indice]->nome);
        return;
    }else{
        printf("O comparecimento de [%s] foi registrado!\n",p[indice]->nome);
        return;
    }
}


//funcao para cadastrar comparecimentos por titulo
void cadastrar_comparecimento(struct PESSOA *p[]) {
    char titulo[25]; int indice = 0;
    printf("Digite o TITULO do eleitor que quer cadastrar que votou");
    fflush(stdin);
    //aqui ela pega o titulo e joga na funcao search_titulo na PESSOA.h, que pode retornar -1 se nao encontrar o titulo,
    //ou retorna o indice de onde o titulo foi encontrado, ex p[2]
    gets(titulo);
    indice = search_titulo(titulo, p);
    if (indice == -1) {
        printf("Titulo nao encontrado!\n");
        return;
    }
    //se o comparecimento já estiver preenchido, a funcao é encerrada
    if (p[indice]->comparecimento == 1 ) {
        printf("Comparecimento ja registrado!\n");
        return;
    }
    //ao final, se o comparecimento do usuario nao estiver preenchido e o titulo tiver sido encontrado
    //ela o preenche mudando o conteudo do ponteiro para 1
    p[indice]->comparecimento = 1;
    printf("Comparecimento Registrado!\n");
}

void campo_comparecimento() {
    //temos que abrir o arquivo pessoas, pois vamos mudar diretamente na struct PESSOA o inteiro
    //COMPARECIMENTO de 0, para 1, não é necessário fazer o contrario pois não faz sentido "Remover Comparecimentos"
    FILE *arquivo = fopen("pessoas","rb+");
    if (arquivo == NULL) {
        printf("ainda nao foram registradas pessoas!\n");
        return;
    }
    //aqui criamos um ponteiro para struct PESSOA, que irá receber os dados escritos no arquivo "pessoas",
    //criado na funcao PESSOAS.c
    struct PESSOA *pessoa[MAX_P];
    for (int i = 0; i < MAX_P; i++) {
        pessoa[i] = malloc(sizeof(struct PESSOA));
        pessoa[i]->comparecimento = 0;
        pessoa[i]->allow = 0;
    }
    fseek(arquivo,0,SEEK_SET);
    for (int i = 0; i < MAX_P; i++) {
        fread(pessoa[i], sizeof(struct PESSOA), 1, arquivo);
    }
    int choice, flag = 0;

    do {
        printf("Escolha sua opcao:\n");
        printf("[1]para cadastrar comparecimento\n");
        printf("[2]para verificar comparecimento\n");
        printf("[3]para SAIR e SALVAR\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                cadastrar_comparecimento(pessoa);
                break;
            case 2:
                verificar_comparecimento(pessoa);
                break;
            case 3:
                flag = 1;
                break;
            default:
                printf("opcao invalida\n");
                break;
        }
    }while (!flag);
    fseek(arquivo, 0, SEEK_SET);
    for (int i = 0; i < MAX_P; i++) {
        fwrite(pessoa[i], sizeof(struct PESSOA), 1, arquivo);
    }
    fclose(arquivo);
}
