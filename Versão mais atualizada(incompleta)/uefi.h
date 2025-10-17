#ifndef UEFI_H
#define UEFI_H

struct uf {
    int estado;// Serve para o programa saber se foi adicionado, apagado...
    int codigo;
    char sigla[3];
};

//Funções
void conversa_uf();
void adicionar_uf();
void mostrar_uf();
void excluir_uf();
#endif //UEFI_H
