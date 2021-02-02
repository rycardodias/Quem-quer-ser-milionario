#include "utilizador.h"
#include "utils.h"
#include "jogo.h"

//Listar o top10 por ordem de dinheiro - pesquisa ordenada
void listartop10(PARTICIPANTE participante[], int total) {
	int i, j;
	PARTICIPANTE aux;
	for(i=1;i<total; i++) {
		aux = participante[i];
		j=i-1;
		while(j>=0 && participante[j].dinheiro < aux.dinheiro) {
			participante[j+1]= participante[j];
			j--;
		}
		participante[j+1] = aux;
	}
	
	printf("\n # TOP 10 Participantes #\n");
	
	for(i=0;i<10 && i<total; i++) {
		printf("  Premio: %i  Sigla: %s  Nome: %s\n",participante[i].dinheiro, participante[i].sigla, participante[i].nome);
	}
}

//lista dos ultimos 15 jogadores
void listarUltimos15(PARTICIPANTE participante[], int total){
	int i, j, minimo =0;
	PARTICIPANTE aux;
	if (total > 15) {
		minimo = total-15;	
	}
	
	for(i=minimo; i<total; i++) {
		aux = participante[i];
		j=i-1;
		while(j>=0 && strcmp(participante[j+1].nome, participante[j].nome)>0) {
			participante[j+1]= participante[j];
			j--;
		}
		participante[j+1] = aux;
	}
	printf("\n # Ultimos Participantes #\n");
	
	for(i=0;i<10 && i<total; i++) {
		printf("  Premio: %i  Sigla: %s  Nome: %s\n",participante[i].dinheiro, participante[i].sigla, participante[i].nome);
	}
}

// menu principal de utilizador
void menuUtilizador() {
	PARTICIPANTE participante[MAX_PARTICIPANTES];
	int opcao=0, totalParticipantes, totalRegras;
	
	ELEMENTO *iniLista=NULL;
	REGRAS aux;
	totalRegras = lerRegras(&iniLista);
	
	do {
		//controlo se existe participantes para nao mostrar opçoes invalidas
		if (lerParticipantes(participante)>0) {
			printf("\n # MENU JOGADOR #\n 1 - Jogar\n 2 - Ver TOP 10 participantes\n 3 - Ver ultimos participantes registados\n 4 - Ler Regras\n 0 - Sair\n");
			scanf("%i", &opcao);
			system("cls");
			switch(opcao) {
				case 1: {
					iniciarJogo();
					return;
				}
				case 2: {
					listartop10(participante, lerParticipantes(participante));
					break;
				}
				case 3: {
					listarUltimos15(participante, lerParticipantes(participante));
					break;
				}
				case 4: {
					listarRegras(iniLista);
					break;
				}
				case 0: return;
				default: printf("Introduza uma opção válida!\n");
			}
		}
		else {
			printf("\n # MENU JOGADOR #\n 1 - Jogar\n 0 - Sair\n");
			scanf("%i", &opcao);
			system("cls");
			switch(opcao) {
				case 1: {
					iniciarJogo();
					return;
				}
				case 0: return;
				default: printf("Introduza uma opção válida!\n");
			}	
		}
	} while (opcao!=0);
}



