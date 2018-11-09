#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "entrega1.h"


void verificaDisciplina()
{
	int erro;
	char disciplina[10],nomeDisciplina[100];
	int creditos;

	printf("\nCONSULTA DE DISCIPLINAS\n");
	printf("Digite a disciplina: ");
	fgets(disciplina,10,stdin);
	limpaChar(disciplina);
	upperChar(disciplina);	

	erro = consultaDisciplina(disciplina,nomeDisciplina,&creditos);

	if (erro == 1)
		puts("Disciplina nao registrada ou inexistente");
	else
	{
		printf("Nome: %s\n",nomeDisciplina);
		printf("Quantidade de Creditos: %d\n",creditos);
		consultaPrerequisito(disciplina);
	}

}

int consultaDisciplina(char *idDisciplina,char *nomeDisciplina, int *creditos)
{

	char idD[10],nomeD[100];
	FILE *fp;

	fp = fopen(fDisciplina,"r");

	if(fp == NULL)
	{
		printf("Nao foi possivel encontrar o arquivo!\n");
		return 2;
	}

	while (fscanf(fp,"%[^,],%[^,],%d\n",idD,nomeD,creditos)!=EOF)
	{	
		if (strcmp(idDisciplina,idD)==0)
		{
			strcpy(nomeDisciplina,nomeD);
			fclose(fp);
			return 0;
		}
		
	}
	
	fclose(fp);
	return 1;

}

void consultaPrerequisito(char *idD)
{
	char idDisciplina[10],idRequisito[10],nomeRequisito[100];
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
			if (strcmp(idDisciplina,idD)==0 && idRequisito[0]!='n')
			{				
				upperChar(idRequisito);
				erro = consultaDisciplina(idRequisito,nomeRequisito,&creditos);
				printf("Pre-requisitos: %s - %s\n",idRequisito,nomeRequisito);
			}
			else if (strcmp(idDisciplina,idD)==0 && idRequisito[0]=='n')
			{
				printf("Pre-requisito: Nenhum\n");
			}		
		}
	}
		

	fclose(fp);
}

void cadastroAluno()
{
	int erro = 3;
	long int ra;
	char nome[100],login[50],senha[50];
	
	FILE *fp = fopen(fAlunos,"a");
		
	if (fp == NULL)
	{
		puts("ERRO AO ABRIR ARQUIVO Alunos.txt");
	}
	else
	{

	printf("\nCADASTRO DE ALUNOS\n");
	do
	{

		printf("Digite o RA do Aluno: ");
		scanf("%ld",&ra);
		getchar();

		erro = verificaAluno(ra);

			if (erro==1)
				puts("RA ja cadastrado!");

	}while(erro!=0);
	printf("Digite o Nome do Aluno: ");
	fgets(nome,100,stdin);
    limpaChar(nome);
	printf("Digite o login: ");
	fgets(login,50,stdin);
    limpaChar(login);
	printf("Digite a senha: ");
	fgets(senha,50,stdin);
    limpaChar(senha);	

	fprintf(fp,"%ld,%s,%s,%s\n",ra,nome,login,senha);
	fflush(fp);

	printf("\nALUNO CADASTRADO COM SUCESSO!\n");
	
	}
	fclose(fp);
}

int verificaAluno(long int ra)
{
	long int ras;
	char buffer[200];
	FILE *fp = fopen(fAlunos,"r");
	
	while(fscanf(fp,"%ld,%[^\n]",&ras,buffer)!=EOF)
	{
		if (ras==ra)
			return 1;
	}

	return 0;
	fclose(fp);	


}

int fazerLogin()
{	
	printf("Digite o usuario: ");
	fgets(user->login,50,stdin);
	limpaChar(user->login);
	printf("Digite a senha: "); 
	fgets(user->senha,50,stdin);
	limpaChar(user->senha);

	char nome[100],loginArquivo[50],senhaArquivo[50];
	long int ra;
	
	FILE *fp;
	
	fp = fopen(fAlunos,"r");

	if(fp == NULL){
		printf("Nao foi possivel encontrar o arquivo!\n");
		return 1;
	}
	
	while (fscanf(fp,"%ld,%[^,] ,%[^,] ,%[^\n]",&user->ra,nome,loginArquivo,senhaArquivo)!=EOF)
	{		
		if (strcmp(loginArquivo,user->login)==0 && strcmp(senhaArquivo,user->senha)==0)
		{
			fclose(fp);
			return 0;
		}
	}
	
    puts("Usuario ou Senha invalidos.");
	fclose(fp);
	return 1;
}

void limpaChar(char *v)
{
    v[strlen(v)-1] = '\0';
}

void upperChar(char *v)
{
	int i = 0;
	while(v[i]) 
	{
    	v[i] = toupper(v[i]);
    	i++;
   }
}