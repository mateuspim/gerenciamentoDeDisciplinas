#ifndef entrega1
#define entrega1

#define fAlunos "Alunos.txt"
#define fDisciplina "Disciplinas.txt"
#define fRequisitos "Prerequisitos.txt"

typedef struct usuariologado{
long int ra;
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

int verificaAluno(long int ra);
void cadastroAluno();

int fazerLogin();



#endif 