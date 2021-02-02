#include <stdio.h>
#include <locale.h>

#include "utils.h"
#include "jogo.h"
#include "utilizador.h"
#include "administracao.h"


int main() {
	setlocale(LC_ALL, "Portuguese");
	int tipoUtilizador = 0;

	//indica que tipo utilizador usar 1- Jogador 2- Administrador
	tipoUtilizador = menu();
	system("cls");
	
	if (tipoUtilizador == 1) {
		menuUtilizador();
	} 
	if (tipoUtilizador == 2) {
		menuAdministrador();
	}
		
	printf("\nA sair do programa... OBRIGADO PELA PARTICIPAÇÃO!\n");	
	return 0;
}
