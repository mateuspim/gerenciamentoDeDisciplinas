#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "entrega1.h"
#include "entrega2.h"
#include "entrega21.h"
#include "entrega3.h"
#include "getSO.h"

void menu();
void printWait();

int main (int argc, char * argv)
{
	int op, erro;
    
	user = (usuarioLogado *) calloc(1,sizeof(usuarioLogado));
	system(CLEAR);
    
	printf("\nSistema de Gerencia de Disciplinas Semestrais\n\n");

	do
	{
		erro = fazerLogin(user);
	}while(erro!=0);
    
	do
	{	
		system(CLEAR);
        printf("\nUsuario logado -> RA: %ld   Nome: %s\n\n",user->ra,user->nome);
		menu();
		scanf("%d",&op);
        getchar();
		switch(op)
		{
			case 1:
				cadastroAluno();
				printWait();
				break;
			case 2:
                verificaDisciplina();
				printWait();
				break;
			case 3:
                menuMatricula();
				printWait();
				break;
			case 4:
				menuAlterarNotaFalta();
				printWait();
				break;
			case 5:
				menuHistoricoAluno();
				printWait();
				break;
			case 6:
				break;
			case 17:
				sortMatriculas();
				break;
			default:
				puts("\nOpcao Invalida!!!");
				printWait();
                break;
		}
	}while(op!=6);

	return 0;
}

void menu()
{
puts("1 -> Cadastro de Alunos");
puts("2 -> Consulta de Disciplinas");
puts("3 -> Realizar Matricula ");
puts("4 -> Atualizar Nota e Falta");
puts("5 -> Consultar Historico do Aluno");
puts("6 -> Sair.");
printf("\nDigite a opcao desejada: ");
}

void printWait()
{
	printf("\nPressione Enter para continuar . . . ");
	getchar();
	fflush(stdin);
}