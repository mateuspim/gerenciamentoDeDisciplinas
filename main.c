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
	char ls[50],ps[50];
	
	printf("Digite o usuario: ");
	//fgets(ls,50,stdin);
	scanf("%s",&ls);
	printf("Digite a senha: "); 
	//fgets(ps,50,stdin);
	scanf("%s",&ps);
	
	printf("%s,%s\n\n",ls,ps);
	sleep(3);
	
	char n[100],l[50],s[50];
	int ra;
	
	FILE *fp;
	
	fp = fopen("Alunos.txt","r");
	
	while (fscanf(fp,"%d,%s, %s, %s",&ra,n,l,s)!=EOF)
	{
		
		printf("%s - %s,%s\n\n",n,l,s);
		sleep(3);
		if (l==ls && s==ps)
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