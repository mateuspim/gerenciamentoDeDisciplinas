#ifndef entrega2
#define entrega2

#define fAlunosD "AlunosDisciplinas.txt"

void menuMatricula();

void inicializaDisciplina();

void checkAlunosDisciplinas();
int checkSemestre(int semestre);
int checkDisciplina(char * idDisciplina);
int checkPreRequisitos(char * idDisciplina);

void getDiscAnterior(int semestre);
void realizarMatricula(int semestre);

#endif 