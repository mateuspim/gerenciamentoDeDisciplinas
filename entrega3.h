#ifndef entrega3
#define entrega3

#define fRAaluno "RAdoAluno.txt"

typedef struct coeficienteRendimento{
long int ra;
float cr;
}cRendimento;

void menuHistoricoAluno();
void menuRendimento(FILE *fp);
void writeDisciplinas(FILE *fp);

void swap(ntDisciplina *a, ntDisciplina *b);
void quicksort(ntDisciplina arr[], int l, int r);
void printArray();

#endif 