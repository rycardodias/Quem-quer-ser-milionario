#include "administracao.h"
#include "utils.h"

int listarPerguntas(PERGUNTAS perguntas[], int total, int grauDificuldade) {	
	int nPerguntasGrau = 0, i=0;
	printf("\n ### LISTAGEM DE PERGUNTAS ###\n");
	for(i=0; i<total; i++) {
		if (grauDificuldade == 0) {
			printf("  ID: %i Recente: %i Dificuldade: %i Resposta Correta: %i Pergunta: %s\n", perguntas[i].idPergunta, perguntas[i].respostaRecente, perguntas[i].nivelDificuldade, 
			                perguntas[i].respostaCorreta, perguntas[i].pergunta);
		}
		else {
			//Lista apenas as perguntas do grau de dificuldade indicado
			if(perguntas[i].nivelDificuldade == grauDificuldade) {
				printf("  ID: %i Dificuldade: %i Resposta Correta: %i Pergunta: %s\n", perguntas[i].idPergunta, perguntas[i].nivelDificuldade, 
				            perguntas[i].respostaCorreta, perguntas[i].pergunta);
			nPerguntasGrau++;
			}
		}
	} 
	if (nPerguntasGrau == 0 && grauDificuldade !=0) printf(" Não existem perguntas de dificuldade %i!\n", grauDificuldade);
	return 0;
}

int inserirPergunta(PERGUNTAS perguntas[],int total) {
	if (total >= MAX_PERGUNTAS) {
		printf("Atingiu o limite de Perguntas!\n");
		return total;
	}
	printf("\n ### NOVA QUESTÃO ###\n");
	perguntas[total].idPergunta = total;
	perguntas[total].respostaRecente=0;
	printf("Indique o grau de dificuldade: ");
	scanf("%i", &perguntas[total].nivelDificuldade);
	printf("Indique a opção correta: ");
	scanf("%i", &perguntas[total].respostaCorreta);
	printf("Introduza a pergunta: ");
	fflush(stdin);
	gets(perguntas[total].pergunta);
	printf("Introduza a opção 1: ");
	fflush(stdin);
	gets(perguntas[total].resposta1);
	printf("Introduza a opção 2: ");
	fflush(stdin);
	gets(perguntas[total].resposta2);
	printf("Introduza a opção 3: ");
	fflush(stdin);
	gets(perguntas[total].resposta3);
	printf("Introduza a opção 4: ");
	fflush(stdin);
	gets(perguntas[total].resposta4);
	total++;
	return salvarPerguntas(perguntas, total);
}

//remover perguntas e mover valores array  
int removerPergunta(PERGUNTAS perguntas[], int total, int id) {
	PERGUNTAS aux;
	int i=0;
	for(i=id; i<total; i++) {
		perguntas[i] = perguntas[i+1];
		perguntas[i].idPergunta = i;
	}
	total--;
	salvarPerguntas(perguntas, total);
	return total;
}

//alterar valor do array
int alterarPergunta(PERGUNTAS perguntas[],int total, int id) {
	int opcao = 0;	
	do {
		//system("cls");
		printf("\nQual informação deseja alterar? (Pergunta %i)\n 1 - Nivel Dificuldade\n 2 - Resposta Correta\n 3 - Pergunta\n 4 - Opções de resposta\n 9 - Salvar e sair\n 0 - Sair sem alterar\n", id);
		scanf("%i", &opcao);
		//system("cls");
		switch(opcao) {
			case 1: {
				printf("Qual nivel de dificuldade deseja atribuir à questão %i?\n", id);
				scanf("%i", &perguntas[id].nivelDificuldade);
				break;
			}
			case 2: {
				printf("Qual a alinea correta da questão %i?\n", id);
				scanf("%i", &perguntas[id].respostaCorreta);
				break;
			}
			case 3: {
				printf("Indique qual é a questão para o ID %i\n", id);
				fflush(stdin);
				gets(perguntas[id].pergunta);
				break;
			}
			case 4: {
				int opcaoEscolha = 0;
				printf("Qual opção de resposta deseja alterar? 0 - Sair\n");
				scanf("%i", &opcaoEscolha);
				printf("Qual novo valor deve ser atribuido à opção?\n");
				int valorAlterado =0;
				do {
					
					switch(opcaoEscolha) {
						case 1: {
							fflush(stdin); 
							gets(perguntas[id].resposta1);
							break;
						}
						case 2: {
							fflush(stdin);
							gets(perguntas[id].resposta2);
							printf("escolha: %s", perguntas[id].resposta2);
							valorAlterado = 1;
							break;
						}
						case 3: {
							fflush(stdin);
							gets(perguntas[id].resposta3);
							break;
						}
						case 4: {
							fflush(stdin);
							gets(perguntas[id].resposta4);
							break;
						}
						case 0: break;
						default: printf("\nIntroduza um valor válido!");
					}
				} while (opcaoEscolha!=0 && valorAlterado!=1);
				break;
			}
			case 9: {
				salvarPerguntas(perguntas, total);
				break;
			} 
			case 0:{
				lerPerguntas(perguntas);
				break;
			} 
			default : printf("Introduza uma opção válida!\n");
		}
	} while (opcao!=0 && opcao!=9);
	return 0;
}

void menuAdministrador() {
	//verificar dados administrador
	char login[15], password[15];
	int limiteTentativas =0;
	//system("cls");
	
	do {
		if (limiteTentativas > 2) {
			printf("\nLimite de tentativas excedido!\nPor motivos de segurança o programa vai encerrar!\n"); return;
		}
		
		printf("\nPAINEL DE ADMINISTRADOR\n  Introduza o login: ");
		scanf("%s", &login);
		printf("  Introduza a password: ");
		scanf("%s", &password);
		limiteTentativas++;
	} while(strcmp(login, loginAdministrador) != 0 && strcmp(password, passwordAdministrador) != 0);
	
	
	//MENU DE ADMINISTRACAO
	PERGUNTAS perguntas[MAX_PERGUNTAS];
	int opcao = 0, totalPerguntas = 0, totalRegras =0;
	totalPerguntas = lerPerguntas(perguntas);
	
	ELEMENTO *iniLista=NULL;
	REGRAS aux;
	totalRegras = lerRegras(&iniLista);
	
	system("cls");
	do {
		printf("\n ### FERRAMENTAS DE ADMINISTRAÇÃO ###\n");
		if(totalPerguntas>0) {
			printf(" 1 - Adicionar Pergunta\n 2 - Listar Perguntas\n 3 - Listar perguntas por dificuldade\n 4 - Alterar Pergunta\n 5 - Remover Pergunta\n 6 - Adicionar Regra\n 7 - Listar Regras\n 8 - Remover regra\n 0 - Sair\n");
			scanf("%i", &opcao);
			system("cls");
			switch(opcao) {
				case 1: {
					totalPerguntas = inserirPergunta(perguntas, totalPerguntas); 
					break;
				}
				case 2: {
					listarPerguntas(perguntas, totalPerguntas, 0); 
					break;
				}
				case 3: {
					int grauDificuldade = 0;				
					printf("\nDeseja ver as perguntas de qual grau de dificuldade?\n");
					scanf("%i", &grauDificuldade);
					listarPerguntas(perguntas, totalPerguntas, grauDificuldade);
					break;
				}
				case 4: {
					int idPergunta = 0;
					printf("Introduza o ID da pergunta que deseja alterar: ");
					scanf("%i", &idPergunta);
					alterarPergunta(perguntas, totalPerguntas, idPergunta);
					break;
				}
				case 5: {
					int idPerguntaR = 0;
					printf("Introduza o ID da pergunta que deseja alterar: ");
					scanf("%i", &idPerguntaR);
					totalPerguntas = removerPergunta(perguntas, totalPerguntas, idPerguntaR);
					break;
				}
				case 6: { // adicionar regra
					aux.id = totalRegras+1;
					printf("\nIntroduza a nova regra:\n");
					fflush(stdin);
					gets(aux.descricao);
					
					inserirIniLista(&iniLista, aux);
					totalRegras++;
					salvarRegras(iniLista, totalRegras);
					break;
				}
				case 7: { //listar regras
					listarRegras(iniLista);
					break;
				}
				case 8: { // remover regra
					totalRegras += removerRegra(&iniLista);
					salvarRegras(iniLista, totalRegras);
					break;
				}
				case 0: return;
				default: printf("\nIntroduza uma opção válida!\n");
			}
		}
		//caso nao existam perguntas so mostrar a opcao de adicionar, poupando codigo nas funcoes
		else {
			printf(" 1 - Adicionar Pergunta\n 0 - Sair\n");
			scanf("%i", &opcao);
			system("cls");
			switch(opcao) {
				case 1: {
					totalPerguntas = inserirPergunta(perguntas, totalPerguntas);  
					break;
				}
				case 0: return;
				default:  printf("\nIntroduza uma opção válida!\n");
			}
		}
	} while(opcao !=0);
}
