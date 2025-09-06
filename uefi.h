#ifndef UEFI_H
#define UEFI_H

struct uf {
    int codigo;
    char sigla[3];
};

//Funções
void conversa_uf();
void adicionar_uf();
void mostrar_uf();
#endif //UEFI_H
