#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrega1.h"
#include "entrega2.h"

void menuMatricula(void *user)
{
    user = (usuarioLogado *) user;
    int semestre,erro,credTotal = 0,credito = 0;
    char disciplina[10];

    puts("Para sair, digite XX000");

    do
    {
    printf("Digite o semestre: ");
    scanf("%d",&semestre);
    getchar();
    erro = checkSemestre(semestre,user);
        if (erro==1)
            puts("Semestre invalido!!");
        if (erro==2)
            puts("Aluno nao matriculado anteriormente!!");
    }while(erro!=0);

    do
    {
    printf("Digite a disciplina: ");
    fgets(disciplina,10,stdin);
    limpaChar(disciplina);
    upperChar(disciplina);

    erro = realizarMatricula(disciplina);

    }while(strcmp(disciplina,"XX000")!=0);
    
    puts("Transaco efetuada com sucesso");
}


int realizarMatricula(char *disciplina)
{

}


int checkSemestre(int semestre,void *user)
{

    usuarioLogado * u = (usuarioLogado *) user;
    int ultSem =0,auxSem;
    long int ra;
    char buffer[100];

    FILE *fp = fopen(fAlunosD,"r");

        if (fp == NULL)
        {
            puts("ERRO AO ABRIR O ARQUIVO AlunosDisciplinas.txt");
            return 3;
        }

    //RA,CódigodaDisciplina,Semestre,Nota,Faltas
    while(fscanf(fp,"%ld,%[^,],%d,%[^,],%[^,\n]\n",&ra,buffer,&auxSem,buffer,buffer)!=EOF)
    {
        
        if (ra==u->ra)
        {
            if (ultSem<auxSem)
                ultSem = auxSem;
        }

    }

    fclose(fp);

    if(ultSem == 0)
        return 2;
    
    if(ultSem < semestre)
        return 0;
    else   
        return 1;

}