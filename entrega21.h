#ifndef entrega21
#define entrega21

#define fAlunosD "AlunosDisciplinas.txt"

void menuAlterarNotaFalta();
void showDisciplinas(int semestre,int *hasDisciplina);

void persisteDisciplinaStruct();
void modifyDisciplinaStruct(char *disciplina,int semestre,float nota,float falta);
int verificaDisciplinaStruct(char *disciplina,int semestre);

void inicializaDiscNotaFalta();
void addDiscNotaFalta();
void reallocDiscNotaFalta();

#endif 