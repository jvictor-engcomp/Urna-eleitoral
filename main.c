#include <stdio.h>


int main(){
    int escolha;

    while(1){
        printf("\n-----------------------------------------[URNA]------------------------------------------\n\n");
        printf("[1]UF\n");
        printf("[2]ELEICAO\n");
        printf("[3]CANDIDATO\n");
        printf("[4]PESSOA\n");
        printf("[5]VOTOS\n");
        printf("[6]COMPARECIMENTO\n");
        printf("[7]Sair\n\n");
        printf("Escolha a area de informacao:");
        scanf(" %d", &escolha);
        switch (escolha) {
            case 1: campo_UF();
                break;
            case 2: //campo_ELEICAO();
                break;
            case 3: //campo_candidato();
                break;
            case 4: //campo_PESSOA();
                break;
            case 5: //campo_VOTO();
                break;
            case 6: //campo_comparecimento();
                break;
            case 7:
                return 0;
            default:
                printf("\n\nDIGITE UMA OPCAO VALIDA\n\n");
        }
    }

    return 0;
}