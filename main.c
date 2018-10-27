#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "entrega1.h"
#include "entrega2.h"
//#include "entrega3.h"



void menu();



int main (int argc, char * argv)
{
	int op, erro;
    usuarioLogado user;
    
	do
	{
		erro = fazerLogin(&user);
		//sleep(3);
	}while(erro!=0);
    
	do
	{
        printf("Usuario logado -> RA: %ld   Login: %s\n",user.ra,user.login);
		menu();
		scanf("%d",&op);
        getchar();
		switch(op)
		{
			case 1:
				cadastroAluno();
				break;
			case 2:
                verificaDisciplina();
				break;
			case 3:
                menuMatricula(&user);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				puts("Opcao Invalida!!!");
                break;
		}
	}while(op!=6);

	return 0;
}

void menu()
{
puts("1 -> Cadastro de Alunos");
puts("2 -> Consultar de Disciplinas");
puts("3 -> Realizar Matricula ");
puts("4 -> Atualizar Nota e Falta");
puts("5 -> Consultar Historico do Aluno");
puts("6 -> Sair.");
printf("Digite a opcao desejada: ");
}