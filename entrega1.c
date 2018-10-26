#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "entrega1.h"

void cadastroAluno()
{
	long int ra;
	char nome[100],login[50],senha[50];
	
	FILE *fp;
	
	printf("Digite o RA do Aluno: ");
	scanf("%ld",&ra);
	getchar();
	printf("Digite o Nome do Aluno: ");
	fgets(nome,100,stdin);
    limpaChar(nome);
	printf("Digite o login: ");
	fgets(login,50,stdin);
    limpaChar(login);
	printf("Digite a senha: ");
	fgets(senha,50,stdin);
    limpaChar(senha);
	
	fp = fopen(fAlunos,"a");
		
		if (fp = NULL)
        {
			puts("ERRO AO ABRIR ARQUIVO Alunos.txt");
        }
        
	fprintf(fp,"%ld,%s,%s,%s",ra,nome,login,senha);
	
	fclose(fp);
}

int fazerLogin()
{
	char login[50],senha[50];
	
	printf("Digite o usuario: ");
	fgets(login,50,stdin);
	limpaChar(login);
	printf("Digite a senha: "); 
	fgets(senha,50,stdin);
	limpaChar(senha);

	char nome[100],loginArquivo[50],senhaArquivo[50];
	long int ra;
	
	FILE *fp;
	
	fp = fopen(fAlunos,"r");

	if(fp == NULL){
		printf("Nao foi possivel encontrar o arquivo!\n");
		return 1;
	}
	
	while (fscanf(fp,"%ld,%[^,] ,%[^,] ,%[^\n]",&ra,nome,loginArquivo,senhaArquivo)!=EOF)
	{		
		if (strcmp(loginArquivo,login)==0 && strcmp(senhaArquivo,senha)==0)
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