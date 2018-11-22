#ifndef entrega2
#define entrega2

#define fAlunosD "AlunosDisciplinas.txt"

#define MAXCRED 32

typedef struct disciplinas{
    int top;
    int ini;
    int credTotal;
    int semestre;
    char d[32][10]; // array de string para 32 disciplinas com 10 caracteres
}stDisciplina;

stDisciplina * novaD;

void menuMatricula();

void inicializaDisciplina();

int checkAlunoDisciplinas(char *idRequisito);
int checkSemestre();
int checkDisciplina(char * idDisciplina);
int checkPreRequisitos(char * idDisciplina);

void getDiscAnterior();
void realizarMatricula();

#endif 