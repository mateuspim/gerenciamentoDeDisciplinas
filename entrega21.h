#ifndef entrega21
#define entrega21

#define fAlunosD "AlunosDisciplinas.txt"

#define cap 100  //Capacidade do vetor struct ntDisciplina inicial

typedef struct discNotaFalta{
    float nota;
    float faltas;
    long int ra;
    int semestre;
    char disciplina[10];
}ntDisciplina;

typedef struct discNTDescritor{
    int tam;
    int top;
}ntDescritor;

ntDisciplina *novaNTD;
ntDescritor *novaDE;

void menuAlterarNotaFalta();
void showDisciplinas(int semestre,int *hasDisciplina);

void persisteDisciplinaStruct();
void modifyDisciplinaStruct(char *disciplina,int semestre,float nota,float falta);
int verificaDisciplinaStruct(char *disciplina,int semestre);

void inicializaDiscNotaFalta();
void addDiscNotaFalta();
void reallocDiscNotaFalta();

#endif 