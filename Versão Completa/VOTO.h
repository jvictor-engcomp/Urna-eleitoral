#define MAX_V 100

struct VOTO {
    int alow;
    int ano;
    int codigo_uf;
    int numero_candidato;
    char dta_hora[20];
};
void campo_VOTO();
void mostrar_v();
int find_for_ano_code();
void iniciar_structs_v();
void adicionar_v();
int verificar();
int achar_livre_v();
void introduzir_v();
