#ifndef entrega1
#define entrega1

typedef struct usuariologado{
long int ra;
char nome[100];
char login[50];
char senha[50];
}usuarioLogado;

usuarioLogado * user;

//Funcoes de controle
void limpaChar(char *v);
void upperChar(char *v);

void verificaDisciplina();
int consultaDisciplina(char *idDisciplina,char *nomeDisciplina, int *creditos);
void consultaPrerequisito(char *idD);

int verificaAlunoRA(long int ra);
int verificaAlunoLogin(char *login);
void cadastroAluno();

int fazerLogin();

#endif 