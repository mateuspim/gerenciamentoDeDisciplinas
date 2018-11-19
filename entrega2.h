#ifndef entrega2
#define entrega2

#define fAlunosD "AlunosDisciplinas.txt"

typedef struct disciplinas{
    int top;
    int ini;
    int credTotal;
    char d[32][10]; // array de string para 32 disciplinas com 10 caracteres
}stDisciplina;


void menuMatricula();

void inicializaDisciplina();

int checkAlunoDisciplinas(char *idRequisito);
int checkSemestre(int semestre);
int checkDisciplina(char * idDisciplina);
int checkPreRequisitos(char * idDisciplina);

void getDiscAnterior(int semestre);
void realizarMatricula(int semestre);

#endif 