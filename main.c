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
				break;
			case 2:
                verificaDisciplina();
				break;
			case 3:
                menuMatricula();
				break;
			case 4:
				menuAlterarNotaFalta();
				break;
			case 5:
				menuHistoricoAluno();
				break;
			case 6:
				break;
			default:
				puts("\nOpcao Invalida!!!");
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