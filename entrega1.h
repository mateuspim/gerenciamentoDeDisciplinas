#ifndef entrega1
#define entrega1

#define fAlunos "Alunos.txt"
#define fDisciplina "Disciplinas.txt"
#define fRequisitos "Prerequisitos.txt"

//Funcoes de controle
void limpaChar(char *v);
void upperChar(char *v);

void verificaDisciplina();
int consultaDisciplina(char *idDisciplina,char *nomeDisciplina, int *creditos);
void consultaPrerequisito(char *idD);


void cadastroAluno();
int fazerLogin();



#endif 