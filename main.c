#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void menu();
void cadastroAluno();
int fazerLogin();

void menu()
{
puts("1 -> Cadastro de Alunos");
puts("2 -> Consultar de Disciplinas");
puts("3 -> Realizar Matrícula ");
puts("4 -> Atualizar Nota e Falta");
puts("5 -> Consultar Histórico do Aluno");
puts("6 -> Sair.");
printf("Digite a opcao desejada: ");
}

void cadastroAluno()
{

/*
	Alunos.txt
	RA,Nome,login,senha
	
	Digite o RA do Aluno:
	Digite o Nome do Aluno:
	Digite o login:
	Digite a senha:
*/
	long int ra;
	char n[100];
	char l[50];
	char p[50];
	
	FILE *fp;
	
	
	printf("Digite o RA do Aluno: ");
	scanf("%ld",&ra);
	getchar();
	printf("Digite o Nome do Aluno: ");
	fgets(n,100,stdin);
	printf("Digite o login: ");
	fgets(l,50,stdin);
	printf("Digite a senha: ");
	fgets(p,50,stdin);
	
	fp = fopen("Alunos.txt","a");
		
		if (fp = NULL)
		{
			puts("ERRO AO ABRIR ARQUIVO Alunos.txt");
		}
	//RA,Nome,login,senha
	fprintf(fp,"%ld,%s,%s,%s",ra,n,l,p);
	
	fclose(fp);
}

int fazerLogin()
{
	char login[50],senha[50];
	
	printf("Digite o usuario: ");
	//fgets(login,50,stdin);
	scanf("%s",login);
	printf("Digite a senha: "); 
	//fgets(senha,50,stdin);
	scanf("%s",senha);
	
	char nome[100],loginArquivo[50],senhaArquivo[50];
	int ra;
	
	FILE *fp;
	
	fp = fopen("Alunos.txt","r");
	if(fp == NULL){
		printf("Não foi possivel encontrar o arquivo!\n");
		return 1;
	}
	
	while (fscanf(fp,"%d,%s ,%s ,%s",&ra,nome,loginArquivo,senhaArquivo)!=EOF)
	{
		printf("%s - %s - %s\n",nome,loginArquivo,senhaArquivo);		
		if (strcmp(loginArquivo,login)==0 && strcmp(senhaArquivo,senha)==0)
		{
			fclose(fp);
			return 0;
		}
	}
	
	fclose(fp);
	return 1;
}


int main (int argc, char * argv)
{
	int op, erro;
	do
	{
		erro = fazerLogin();
		sleep(3);
	}while(erro!=0);
	
		
	do
	{
		menu();
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				cadastroAluno();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				puts("Opcao Invalida!!!");
		}
	}while(op!=6);
	return 0;
}