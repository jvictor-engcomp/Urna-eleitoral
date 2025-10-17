#define MAX_P 30

void campo_PESSOA();
struct PESSOA {
    int comparecimento;
    int allow;
    char CPF[20];
    char titulo[25];
    char nome[50];
    char fone[20];
    char endereco[100];
    char data_nascimento[11];
};

void iniciar_pessoas();
void inserir_pessoa();
void mostrar_uma();
void mostrar_todas();
void remover_pessoa();
void alterar_pessoa();
int search_by_CPF();
int search_titulo();

