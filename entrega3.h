#ifndef entrega3
#define entrega3

#define capAlunos 100

typedef struct coeficienteRendimento{
long int ra;
float cvTotal;
float credTotal;
float cr;
}cRendimento;

typedef struct coefRendDescritor{
    int tam;
    int top;
}crDescritor;

cRendimento *cRend;
crDescritor *crDesc;

void menuHistoricoAluno();
void menuRendimento(FILE *fp);

void writeDisciplinas(FILE *fp);

void swapNTDisc(ntDisciplina *a, ntDisciplina *b);
void quicksortNTDisc(ntDisciplina arr[], int l, int r);
void quicksortNTDiscRA(ntDisciplina arr[], int l, int r);
void sortMatriculas(int op);
void printArray();

void addAlunosCoefRend();
void inicializaCoefRend();
void calcCoefRend();
void reallocCoefRend();

void swapCRend(cRendimento *a, cRendimento *b);
void quicksortCRend(cRendimento *arr, int l, int r);
void printAlunos();


#endif 