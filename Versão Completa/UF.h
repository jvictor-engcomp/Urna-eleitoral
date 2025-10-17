#ifndef MAX
#define MAX 27
#endif

struct UF{
    int alow;
    int codigo;
    char descricao[20];
    char sigla[3];
};
void iniciar_structs();
int achar_livre();
void introduzir();
int find_for_code();
int find_for_sigla();
void adicionar();
void pesquisar();
void adicionar();
void exluir();
void alterar();
void campo_UF();
void mostrar();