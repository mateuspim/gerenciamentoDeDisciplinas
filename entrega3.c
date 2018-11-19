#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrega1.h"
#include "entrega2.h"
#include "entrega21.h"
#include "entrega3.h"

void menuHistoricoAluno()
{
    FILE *fp;

    fp = fopen(fRAaluno,"w");

    if(fp==NULL)
    {
        puts("ERRO AO ABRIR ARQUIVO: RAdoAluno.txtt");
    }
    else
    {
        fprintf(fp,"Faculdade de Tecnologia – UNICAMP\n\n");
        fprintf(fp,"Relatório de Matrícula\n\n");
        fprintf(fp,"Nome Completo: %s\n",user->nome);
        fprintf(fp,"RA: %ld\n",user->ra);
        menuRendimento(fp);
        fprintf(fp,"Coeficiente de Rendimento: NULL\n");
        fprintf(fp,"Classificação do aluno na turma : 0 de NULL\n\n\n");
        fprintf(fp,"Disciplina	Nota    Faltas (%%)    Situação\n");
        writeDisciplinas(fp);

        fflush(fp);
    }

    fclose(fp);
    puts("\nArquivo (RAdoAluno.txt) foi gerado com sucesso");
}

void menuRendimento(FILE *fp)
{
    //TO DO
}

void writeDisciplinas(FILE *fp)
{
    inicializaDiscNotaFalta();  //Inicializa ambas as structs
    addDiscNotaFalta();         //Le o arquivo e adiciona para as structs

    //printArray(); Verificacao da struct antes do sort

    //5* Todas as disciplinas que o aluno cursou devem aparecer em ordem semestral
    quicksort(novaNTD,0,novaDE->top - 1); //Deixar os semestres em ordem crescente
    
    //printArray(); Verificacao da struct depois do sort

    if(fp==NULL)
    {
        puts("ERRO AO ABRIR ARQUIVO: RAdoAluno.txtt");
    }
    else
    {
        for(register int i = 0;i<novaDE->top;i++)
        {

            if(user->ra == novaNTD[i].ra)
            {

                //fprintf(fp,"\n\nSI200  		7.1 	10.4    	  Aprovado por Nota e Frequência\n"); //Exemplo de formatacao para pegar a tabulacao
                fprintf(fp,"%s  		%0.2f 	%0.2f    	  ",novaNTD[i].disciplina,novaNTD[i].nota,novaNTD[i].faltas);

                //Verifica os parametros de nota e falta para verificar se o aluno passou ou nao
                /*  Condicoes:
                3* Caso o número de faltas seja igual ou superior a 25%, o aluno deve ser reprovado por falta
                4* Caso o aluno possua nota abaixo de 5, o mesmo deve ser considerado reprovado por nota
                */
                if(novaNTD[i].nota >= 5 && novaNTD[i].faltas < 25)              
                    fprintf(fp,"Aprovado por Nota e Frequência\n");
                else if(novaNTD[i].nota < 5 && novaNTD[i].faltas < 25)
                    fprintf(fp,"Reprovado por Nota\n");
                else if(novaNTD[i].nota >= 5 && novaNTD[i].faltas >= 25)
                    fprintf(fp,"Reprovado por Faltas\n");
                else
                    fprintf(fp,"Reprovado por Nota e Faltas\n");

                fflush(fp);
            }
        }
    }
}

void printArray()
{
    for(register int i = 0;i<novaDE->top;i++)
    {
        printf("%ld,%s,%d,%0.2f,%0.2f\n",novaNTD[i].ra,novaNTD[i].disciplina,novaNTD[i].semestre,novaNTD[i].nota,novaNTD[i].faltas);
    }
}

void swap(ntDisciplina *a, ntDisciplina *b)
{
    ntDisciplina temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(ntDisciplina *arr, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int pivot = arr[r].semestre;
    int cnt = l;

    for (int i = l; i <= r; i++)
    {
        if (arr[i].semestre <= pivot)
        {
            swap(&arr[cnt], &arr[i]);            
            cnt++;
        }
    }

    quicksort(arr, l, cnt-2);
    quicksort(arr, cnt, r);
}