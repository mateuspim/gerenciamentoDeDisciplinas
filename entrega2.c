#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrega1.h"
#include "entrega2.h"

#define MAXCRED 32

typedef struct disciplinas{
    int top;
    int ini;
    int credTotal;
    char d[32][10]; // array de string para 32 disciplinas com 10 caracteres
}stDisciplina;

stDisciplina * novaD;

void inicializaDisciplina()
{
    free(novaD);
    novaD = (stDisciplina *) calloc(1,sizeof(stDisciplina));
}

void menuMatricula()
{

    int semestre,erro,credTotal = 0,credito = 0;
    char disciplina[10];

    //Inicializando struct disciplina para futuras verificacoes
    inicializaDisciplina();

    //printf("%d %d %s",novaD->top,novaD->credTotal,novaD->d[1]);

    puts("Para sair, digite XX000");

    do
    {
    printf("Digite o semestre: ");
    scanf("%d",&semestre);
    getchar();

    if (semestre > 0)
        erro = checkSemestre(semestre);
    /*  
        erro = 0 -> aluno semestre valido
        erro = 1 -> aluno semestre invalido
        erro = 2 -> aluno nao cadastrado anteriormente
    */
        if (erro==1 || semestre<0)
            puts("Semestre invalido!!");

        if (erro == 3)
        {
            getDiscAnterior(semestre);
            erro =0;
        }
            
        
    }while(erro!=0);



    do
    {
    
    printf("\nDigite a disciplina: ");
    fgets(disciplina,10,stdin);
    limpaChar(disciplina);
    upperChar(disciplina);
    
    erro = checkDisciplina(disciplina);
    }while(strcmp(disciplina,"XX000")!=0);

    realizarMatricula(semestre);
    puts("Transaco efetuada com sucesso");
}

int checkDisciplina(char * idDisciplina)
{
    int erro,creditos;
    char nomeDisciplina[100];
    erro = consultaDisciplina(idDisciplina,nomeDisciplina,&creditos);

    if  (erro == 1)
    {
        puts("Disciplina nao encontrada");
        return 1;
    }
    else
    {
        if (novaD->credTotal + creditos <=MAXCRED) //VERIFICACAO DOS CREDITOS
        {
            erro = 0;
            for(int i = 0; i<MAXCRED;i++) // VERIFICACAO SE JA EXISTE A DISCIPLINA CADASTRADA NA STRUCT
            {
        
                if (strcmp(novaD->d[i],idDisciplina)==0)
                {
                    erro = 1;
                    break;
                }
                //else erro = 0;                     
            }

            if (erro == 0)
            {

                //erro = checkPreRequisitos(idDisciplina); // ainda em construcao
                
                    if (erro == 0)
                    {
                        novaD->credTotal+=creditos;
                
                        strcpy(novaD->d[novaD->top],idDisciplina);
                        novaD->top++;
                        printf("\nCreditos totais: %d  Disciplinas Cadastradas: %d   Ultima Disciplina: %s\n",novaD->credTotal,novaD->top,novaD->d[novaD->top]);
                    }
            }
            else
            {
                puts("DISCIPLINA JA INSCRITA!");
            }              
        }           
        else
        {
            puts("Cadastro de disciplina ultrassa o max de creditos por semestre!");
        }
    }

    return 0;

}
int checkPreRequisitos(char * idDisciplina)
{
    // ainda em construcao
    char idD[10],idRequisito[10],nomeRequisito[100];
	int creditos = 0, erro;

	FILE *fp;

	fp = fopen(fRequisitos,"r");

	if(fp == NULL)
	{
		printf("Nao foi possivel encontrar o arquivo!\n");
	}
    else
    {
	    while (fscanf(fp,"%[^,],%s\n",idDisciplina,idRequisito)!=EOF)
	    {
			
		    if (strcmp(idD,idD)==0 && idRequisito[0]!='n')
		    {
			    upperChar(idRequisito);
		    }
		    else if (strcmp(idDisciplina,idD)==0 && idRequisito[0]=='n')
		    {
			    return 0;
		    }		
	}
	}
	fclose(fp);   

}

void checkAlunosDisciplinas()
{
    // ainda em construcao
    FILE * fp;
    int ultSem =0,auxSem;
    long int ra;
    char idDisciplina[10];
    char buffer[100];
    
    fp = fopen(fAlunosD,"r");

    if (fp == NULL)
    {
            puts("ERRO AO ABRIR O ARQUIVO AlunosDisciplinas.txt");
            //return 3;
    }
    else
    {

        //RA,CódigodaDisciplina,Semestre,Nota,Faltas
        while(fscanf(fp,"%ld,%[^,],%d,%[^,],%[^,\n]\n",&ra,buffer,&auxSem,buffer,buffer)!=EOF)
        {
        
        }
    }
    fclose(fp);
}

// Funcao para pegar as disciplinas anteriores do semestre
void getDiscAnterior(int semestre)
{
    int erro = 0,creditos = 0,auxSem;
    char disciplina[10];//idDisciplina[10];
    char buffer[100];
    long int ra;

    FILE *fp;

    fp = fopen(fAlunosD,"r");

    if (fp==NULL)
    {
        puts("ERRO AO ABRIR O ARQUIVO: AlunosDisciplinas");
    }
    else
    {
        //RA,CódigodaDisciplina,Semestre,Nota,Faltas
        while(fscanf(fp,"%ld,%[^,],%d,%s\n",&ra,disciplina,&auxSem,buffer)!=EOF)
        {     
            if(ra==user->ra && auxSem==semestre)
            {
                //strcpy(idDisciplina,disciplina);
                erro = consultaDisciplina(disciplina,buffer,&creditos);

                if (erro==1)
                {

                }
                else
                {
                    strcpy(novaD->d[novaD->top++],disciplina);
                    novaD->credTotal += creditos;
                }
            }
        }
        novaD->ini = novaD->top;
    }

    fclose(fp);
}

//Funcao para checkagem do semestre
int checkSemestre(int semestre)
{

    int ultSem = 0,auxSem;
    long int ra;
    char buffer[100];

    FILE *fp = fopen(fAlunosD,"r");

    if (fp == NULL)
    {
        puts("ERRO AO ABRIR O ARQUIVO AlunosDisciplinas.txt");
        return 3;
    }

    //RA,CódigodaDisciplina,Semestre,Nota,Faltas
    while(fscanf(fp,"%ld,%[^,],%d,%s\n",&ra,buffer,&auxSem,buffer)!=EOF)
    {     
        if (ra==user->ra)
        {
            if (ultSem<=auxSem)
                ultSem = auxSem;
        }

    }

    fclose(fp);

    if(ultSem == 0) //Aluno nao cadastrado
        return 2;
    
    if(ultSem == semestre)  //Politica para cadastrar as disciplinas anteriores
        return 3;           //do semestre atual
    
    if(ultSem < semestre) //Semestre valido
        return 0;
    else   
        return 1;  //Semestre invalido

}

//Funcao para realizar matricula final 
void realizarMatricula(int semestre)
{
    FILE *fp;

	fp = fopen(fAlunosD,"a");

	if(fp == NULL)
	{
		printf("Nao foi possivel encontrar o arquivo: %s!\n",fRequisitos);
	}
    else
    {
        for (int i=novaD->ini;i<novaD->top;i++)
        {   
            //RA,CódigodaDisciplina,Semestre,Nota,Faltas
            fprintf(fp,"%ld,%s,%d,0.0,0.0\n",user->ra,novaD->d[i],semestre);
            fflush(fp);
        }
    }

	
	fclose(fp); 
}