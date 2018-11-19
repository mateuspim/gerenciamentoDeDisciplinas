#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrega1.h"
#include "entrega2.h"

#define MAXCRED 32

stDisciplina * novaD;

//Funcao para inicializar a struct
void inicializaDisciplina()
{
    free(novaD);
    novaD = (stDisciplina *) calloc(1,sizeof(stDisciplina));
}

//Funcao menu para matricula nas disciplinas
void menuMatricula()
{

    int semestre,erro,credTotal = 0,credito = 0;
    char disciplina[10];

    //Inicializando struct disciplina para futuras verificacoes
    inicializaDisciplina();

    puts("Para sair, digite XX000");
    puts("Para nao fazer cadastro das disciplinas, digite NN000");

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
            getDiscAnterior(semestre); //funcao para pegar as disciplinas anteriores e dando credito ao autor
            erro =0;
        }
            
        
    }while(erro!=0);

    do
    {
    
    printf("\nDigite a disciplina: ");
    fgets(disciplina,10,stdin);
    limpaChar(disciplina);
    upperChar(disciplina);


    erro = 1;

    if (strcmp(disciplina,"XX000")==0)
    {
        realizarMatricula(semestre);
        puts("\nTransacao efetuada com sucesso");
        erro = 0;
    }
    else if (strcmp(disciplina,"NN000")==0)
    {
        puts("\nTransacao suspensa com sucesso");
        erro = 0;
    }
    else
    {
        checkDisciplina(disciplina);
    }    
   
    }while(erro!=0); 


    
}

// Faz quase toda a vericacao para o cadastro da disciplina
int checkDisciplina(char * idDisciplina)
{
    int erro,creditos;
    char nomeDisciplina[100];
    erro = consultaDisciplina(idDisciplina,nomeDisciplina,&creditos); //primeira consulta para verificar se o que fora digitado existe no banco de dados

    if  (erro == 1)
    {
        puts("Disciplina nao encontrada dentro do banco de dados");
        return 1;
    }
    else
    {

        if (novaD->credTotal + creditos <=MAXCRED) //Verificacao dos creditos, caso ultrapasse nao cadastra e printa na tela
        {
            //puts("passou pelos creditos");
            erro = 0;
            for(int i = 0; i<MAXCRED;i++) // Verificacao se a disciplina digitada ja fora inserida na struct anteriormente
            {
                if (strcmp(novaD->d[i],idDisciplina)==0)
                {
                    erro = 1;
                    break;
                }                    
            }

            if (erro == 0)
            {
                //puts("passou pela duplicidade");
                erro = checkAlunoDisciplinas(idDisciplina); //Verificacao de duplicade da disciplina se ja fora cumprida satisfazendo nota e falta

                if (erro == 1)  //erro = 1 demonstra que a funcao nao encontrou a disciplina anteriormente e pode prosseguir
                {
                    //puts("passou pela duplicidade dupla");

                    erro = checkPreRequisitos(idDisciplina); // Verificacao dos pre-requesitos para se matricular na disciplina
                
                        if (erro == 0)
                        {
                            //puts("passou pela verificacao dos prerequisitos");
                        
                            //por fim o cadastro da disciplina na struct
                        
                            novaD->credTotal+=creditos;
                            strcpy(novaD->d[novaD->top++],idDisciplina);
                            printf("\nCreditos totais: %d   Disciplinas Cadastradas: %d   Ultima Disciplina: %s\n",novaD->credTotal,novaD->top,novaD->d[novaD->top - 1]);
                        }
                        else
                        {
                            puts("Disciplina nao pode ser cadastrada: pre-requisitos nao atendidos");
                        }
                }
                else
                {
                    puts("Disciplina ja cadastrada, cumprida e satisfeito as razoes de Nota e Falta");
                }
                    
            }
            else
            {
                puts("Disciplina ja cadastrada!");
            }              
        }           
        else
        {
            puts("Cadastro de disciplina ultrassa o max de creditos por semestre!");
        }
    }

    return 0;

}

//Funcao para verificar os pre-requisitos e retornar a funcao checkDisciplina()
int checkPreRequisitos(char * idDisciplina)
{
    
    char idD[10],idRequisito[10],nomeRequisito[100];
	int creditos = 0, erro = 0;

	FILE *fp;

	fp = fopen(fRequisitos,"r");

	if(fp == NULL)
	{
		printf("Nao foi possivel encontrar o arquivo!\n");
	}
    else
    {
	    while (fscanf(fp,"%[^,],%s\n",idD,idRequisito)!=EOF)
	    {
		    if (strcmp(idDisciplina,idD)==0 && idRequisito[0]!='n')
		    {
			    upperChar(idRequisito);
                erro += checkAlunoDisciplinas(idRequisito);                     //Caso haja + de 1 pre-requisito por disciplina

                if(strcmp(idRequisito,"AA200")==0 || strcmp(idRequisito,"AA410")==0 || strcmp(idRequisito,"AA465")==0)
                    puts("\nDisciplina com pre-requisitos especiais. Atente-se a eles!\n");
		    }
		    else if (strcmp(idDisciplina,idD)==0 && idRequisito[0]=='n')        //Se nao, retorna 0
		    {
			    return 0;
		    }		
	    }

        

    
        if (erro==0)    
            return 0;
        else
            return 1;
	}
	fclose(fp);   

}

/*  Funcao que verifica se o aluno cursou a disciplina assegurando as condicoes de nota e falta
    usada para verificar os pre-requisitos em checkPreRequisitos();
    e usada para verificar se x disciplina ja fora atentida e satisfeita em checkDisciplina();
*/
int checkAlunoDisciplinas(char *idRequisito)
{

    FILE * fp;
    int auxSem;
    long int ra;
    char idDisciplina[10];
    float nota,falta;

    fp = fopen(fAlunosD,"r");

    if (fp == NULL)
    {
            puts("ERRO AO ABRIR O ARQUIVO AlunosDisciplinas.txt");
    }
    else
    {
        
        //RA,CódigodaDisciplina,Semestre,Nota,Faltas
        while(fscanf(fp,"%ld,%[^,],%d,%f,%f\n",&ra,idDisciplina,&auxSem,&nota,&falta)!=EOF)
        {
            if(user->ra == ra && strcmp(idDisciplina,idRequisito)==0 && nota>=5 && falta<25)   //  Verificao do aluno logado com ra, se a disciplina na lista e o requisito passado            
                return 0;                                                                     //   no mínimo, conceito igual a 5 e faltas menor que 25% 
            else
                return 1;                 
        }
    }

    return 1;
    fclose(fp);
}

// Funcao para pegar as disciplinas anteriores do semestre do aluno caso seja digitado um semestre com disciplinas cadastradas
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

                    if (erro==0)
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
    else
    {
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

        //if(ultSem == 0) //Aluno nao cadastrado
        //    return 2;
    
        if(ultSem == semestre)  //Politica para cadastrar as disciplinas anteriores
            return 3;           //do semestre atual
    
        if(ultSem < semestre) //Semestre valido
            return 0;
        else   
            return 1;  //Semestre invalido
    }
}

//Funcao para realizar matricula final -> gravar a struct dentro do txt
void realizarMatricula(int semestre)
{
    FILE *fp;

	fp = fopen(fAlunosD,"a");

	if(fp == NULL)
	{
		printf("Nao foi possivel encontrar/abrir o arquivo: %s!\n",fRequisitos);
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