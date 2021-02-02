#include "jogo.h"
#include "utils.h"
#include "utilizador.h"
#include "administracao.h"

int inserirParticipante(PARTICIPANTE participante[],int total) {
	int i=0, nomesIguais=0;
	char nome[100], sigla[5];
	FILE *file = NULL;
	file = fopen("ficheiros/ListaParticipantes.dat", "wb"); 
	if(file==NULL) {
		printf("Erro ao abrir ficheiro\n");
		return -1;
	}
	printf("\nDados do Utilizador\n");
	participante[total].numero = total;
	participante[total].dinheiro = 0;
	do {
		nomesIguais=0;
		printf("Introduza o nome: ");
		fflush(stdin);
		gets(participante[total].nome);
		printf("Introduza a sigla: ");
		fflush(stdin);
		gets(participante[total].sigla);
		
		for(i=0; i<total; i++) {
			if(strcmp(participante[i].nome, participante[total].nome)==0 && 
				strcmp(participante[i].sigla, participante[total].sigla)==0) {
				nomesIguais = 1;
			}
		}
		if(nomesIguais==1) {
			system("cls");
			printf("A combinação de nome e sigla que escolheu já existem!\n");
		}
	} while(nomesIguais == 1);
	
	total++;
	
	fwrite(&total,sizeof(int),1,file);
    fwrite(participante,sizeof(PARTICIPANTE),total,file);
	fclose(file);
	return total;
}

//calcula patamar das perguntas segundo valor acumulado
int calcularDificuldade(PARTICIPANTE participante[], int id) {
	if (participante[id].dinheiro < 500) return 1;
	else if (participante[id].dinheiro < 10000) return 2;	
	else return 3;
}

//Calcula os ganhos minimos ao alcançar os diversos patamares
int calcularGanhosMinimos(PARTICIPANTE participante[], int id) {
	if (participante[id].dinheiro < 500) return 0;
	else if (500 <= participante[id].dinheiro < 10000) return 500;
	else if (10000 <= participante[id].dinheiro < 250000) return 10000;
}

//funcao para desenvolver as 4 ajudas
int usarAjuda(PERGUNTAS perguntas[], int totalPerguntas, int nivelDificuldade, int id, int numeroAjuda) {
	int r=0, resposta=0, r1=0, r2=0;
	switch(numeroAjuda) {
		// 50/50 - procuram uma resposta random diferente da correta e mostramos ambas
		case 1: { 
			do {
				r = rand() % 5;
			} while (perguntas[id].respostaCorreta == r || r==0);
			
			//system("cls");
			printf(" ### QUESTÂO ###\n %s\n", perguntas[id].pergunta);
			if(perguntas[id].respostaCorreta == 1 || r == 1) printf("  1 - %s\n", perguntas[id].resposta1);	
			if(perguntas[id].respostaCorreta == 2 || r == 2) printf("  2 - %s\n", perguntas[id].resposta2);	
			if(perguntas[id].respostaCorreta == 3 || r == 3) printf("  3 - %s\n", perguntas[id].resposta3);	
			if(perguntas[id].respostaCorreta == 4 || r == 4) printf("  4 - %s\n", perguntas[id].resposta4);	
			
			do {		
				printf("Qual opção deseja bloquear?\n");
				scanf("%i", &resposta);
				if(resposta != perguntas[id].respostaCorreta && resposta != r){
					printf("Escolha uma opcao existente!\n");	
				} 
			} while (resposta != perguntas[id].respostaCorreta && resposta != r);
			return resposta; //salta para a funcao principal e leva o valor de r para escolhermos a certa e a random apenas
		}
		
		//telefonar - array com 7/10 respostas certas para cada respostaCorreta
		case 2: { 
			r1 = rand() % 10;
			if(perguntas[id].respostaCorreta == 1) {
				int respostaProbabilistica[10] = {1,1,1,1,1,1,1,2,3,4};
				return respostaProbabilistica[r1];
			}
			else if (perguntas[id].respostaCorreta == 2) {
				int respostaProbabilistica[10] = {1,2,2,2,2,2,2,2,3,4};	
				return respostaProbabilistica[r1];
			}
			else if (perguntas[id].respostaCorreta == 3) {
				int respostaProbabilistica[10] = {1,2,3,3,3,3,3,3,3,4};
				return respostaProbabilistica[r1];
			}
			else if (perguntas[id].respostaCorreta == 4) {
				int respostaProbabilistica[10] = {1,2,3,4,4,4,4,4,4,4};
				return respostaProbabilistica[r1];
			}
		}
		//ajudaPublico - array com 9/10 respostas certas para cada respostaCorreta
		case 3: {
			r2 = rand() % 10;
			if(perguntas[id].respostaCorreta == 1) {
				int respostaProbabilistica[10] = {1,1,1,1,1,1,1,1,1,4};
				return respostaProbabilistica[r2];
			}
			else if (perguntas[id].respostaCorreta == 2) {
				int respostaProbabilistica[10] = {2,2,2,2,2,2,2,2,2,4};
				return respostaProbabilistica[r2];
			}
			else if (perguntas[id].respostaCorreta == 3) {
				int respostaProbabilistica[10] = {3,3,3,3,3,3,3,3,3,4}; 
				return respostaProbabilistica[r2];
			}
			else if (perguntas[id].respostaCorreta == 4) {
				int respostaProbabilistica[10] = {1,4,4,4,4,4,4,4,4,4}; 
				return respostaProbabilistica[r2];
			}
		}
		//trocar Pergunta
		case 4: {
			//reseta respostaRecente em caso de todos terem sido vistos
			resetarPerguntas(perguntas, totalPerguntas, nivelDificuldade);
			do {
				r = rand() % totalPerguntas;
			} while (perguntas[r].nivelDificuldade != nivelDificuldade || perguntas[id].idPergunta == r || perguntas[r].respostaRecente==1);
				
			//indica que pergunta foi vista recentemente
			perguntas[r].respostaRecente = 1; 
			salvarPerguntas(perguntas, totalPerguntas);	
			
			printf(" ### QUESTÂO ###\n %s\n", perguntas[r].pergunta);
			printf("  1 - %s\n  2 - %s\n  3 - %s\n  4 - %s\n", perguntas[r].resposta1, perguntas[r].resposta2, perguntas[r].resposta3, perguntas[r].resposta4);
			scanf("%i", &resposta);
			
			if(perguntas[r].respostaCorreta == resposta) {
				printf("Resposta CORRETA!\n");
				return 1;
			}
			else {
				//informa qual a resposta correta quando erra
				printf("Resposta INCORRETA!\n");
				switch(perguntas[r].respostaCorreta){
					case 1:  printf("A reposta correta é 1 - %s\n", perguntas[r].resposta1); break;
					case 2:  printf("A reposta correta é 2 - %s\n", perguntas[r].resposta2); break;
					case 3:  printf("A reposta correta é 3 - %s\n", perguntas[r].resposta3); break;
					case 4:  printf("A reposta correta é 4 - %s\n", perguntas[r].resposta4); break;
				} 
			return 0;
			}
		}
		default: ("Algo correu mal a utilizar a ajuda\n");
	}
}

//função para mostrar as perguntas
int mostrarPergunta(PERGUNTAS perguntas[], int totalPerguntas, int nivelDificuldade, int ajudas[]) {
	int r=0, resposta=0, opcaoResposta=0, auxResposta, escolha=0, escolhaCorreta=0;
	
	//reseta respostaRecente em caso de todos terem sido vistos
	resetarPerguntas(perguntas, totalPerguntas, nivelDificuldade);
	// faz um random entre 0 e total de pertuntas até encontrar o nivel pretendido no array
	do {
		r = rand() % totalPerguntas;
	} while (perguntas[r].nivelDificuldade != nivelDificuldade || perguntas[r].respostaRecente==1);
		
	
	//indica que pergunta foi vista recentemente
	perguntas[r].respostaRecente = 1; 
	salvarPerguntas(perguntas, totalPerguntas);
	
	printf(" ### QUESTÂO ###\n Nivel %i - %s\n", perguntas[r].nivelDificuldade, perguntas[r].pergunta);
	printf("  1 - %s\n  2 - %s\n  3 - %s\n  4 - %s\n", perguntas[r].resposta1, perguntas[r].resposta2, perguntas[r].resposta3, perguntas[r].resposta4);
	
	if(ajudas[0]==0 || ajudas[1]==0 || ajudas[3]==0 || (ajudas[4]==0 && nivelDificuldade>1)) {
		printf("\nDeseja usar ajudas?\n 1 - Sim\n 0 - Não\n");
		scanf("%i", &opcaoResposta);
		
		if(opcaoResposta==1){ //controla se deseja usar ajuda
			do { //ciclo para verificar se a escolha é possivel
				printf("\nAjudas disponiveis:\n");
				if (ajudas[0]==0) printf("1 - 50/50\n");
				if (ajudas[1]==0) printf("2 - Telefonar\n");
				if (ajudas[2]==0) printf("3 - Ajuda Público\n");
				if (ajudas[3]==0 && nivelDificuldade>1) printf("4 - Trocar Pergunta\n");
				scanf("%i", &escolha);
				system("cls");
				if(escolha==1 && ajudas[0]==0) {
					ajudas[0]=1;
					auxResposta = usarAjuda(perguntas, totalPerguntas, nivelDificuldade, perguntas[r].idPergunta, escolha);
					escolhaCorreta=1;
				}	
				else if(escolha==2 && ajudas[1]==0) {
					ajudas[1]=1;
					escolhaCorreta=1;
					auxResposta = usarAjuda(perguntas, totalPerguntas, nivelDificuldade, perguntas[r].idPergunta, escolha);
					printf("\nA resposta dada ao telefone foi a %i\n\n", auxResposta);
					
				}	
				else if(escolha==3 && ajudas[2]==0) {
					ajudas[2]=1;
					escolhaCorreta=1;
					auxResposta = usarAjuda(perguntas, totalPerguntas, nivelDificuldade, perguntas[r].idPergunta, escolha);
					printf("\nA resposta do público foi a %i\n\n", auxResposta);
					
				}	
				else if(escolha==4 && ajudas[3]==0 && nivelDificuldade>1) {
					ajudas[3]=1;
					escolhaCorreta=1;
					//retorna 0 ou 1 dependendo se acertou ou nao a nova resposta mostrada na função
					return usarAjuda(perguntas, totalPerguntas, nivelDificuldade, perguntas[r].idPergunta, escolha);
				}
				else printf("\nA escolha que enumerada não está disponivel!\n");
				
			} while(escolhaCorreta!=1);
			resposta = auxResposta;
		}
		else { // caso nao deseje ajudas pergunta a reposta
			do {
				printf("Qual opção deseja bloquear?\n");
				scanf("%i", &resposta);
				system("cls");
				if (resposta > 4 || resposta < 1) printf("Escolha uma opção válida!\n");
			} while (resposta > 4 || resposta < 1);
		}
	}
	else { // caso nao tenha ajudas disponiveis pergunta a resposta
		do {
			printf("Qual opção deseja bloquear?\n");
			scanf("%i", &resposta);
			system("cls");
			if (resposta > 4 || resposta < 1) printf("Escolha uma opção válida!\n");
		} while (resposta > 4 || resposta < 1);
	}
	
	//controlar se acertou a resposta ou não
	
	if(perguntas[r].respostaCorreta == resposta) {
		printf("Resposta CORRETA!\n");
		return 1;
	}
	else {
		//informa qual a resposta correta quando erra
		printf("Resposta INCORRETA!\n");
		switch(perguntas[r].respostaCorreta){
			case 1:  printf("A reposta correta é 1 - %s\n", perguntas[r].resposta1); break;
			case 2:  printf("A reposta correta é 2 - %s\n", perguntas[r].resposta2); break;
			case 3:  printf("A reposta correta é 3 - %s\n", perguntas[r].resposta3); break;
			case 4:  printf("A reposta correta é 4 - %s\n", perguntas[r].resposta4); break;
		} 
		return 0;
	}
}

void iniciarJogo() {
	system("cls");
	int opcao, totalParticipantes, totalPerguntas, resultadoResposta, numeroRespostas=0;
	int premios[16] = {0,25,50,125,250,500,750,1500,2500,5000,10000,16000,32000,6400,125000,250000};
	int ajudas[4]={0,0,0,0};
	PARTICIPANTE participante[MAX_PARTICIPANTES];
	PERGUNTAS perguntas[MAX_PERGUNTAS];
	
	totalParticipantes = inserirParticipante(participante, lerParticipantes(participante));
	totalPerguntas = lerPerguntas(perguntas);
	
	//system("cls");
	printf("\nBem-vindo ao Quem quer se milionário, %s!\n", participante[totalParticipantes-1].nome);
	
	do {
		printf("\n # MENU JOGO #\n 1 - Próxima Pergunta\n 2 - Mostrar Resumo\n 0 - Terminar Jogo\n");
		scanf("%i", &opcao);
		system("cls");
		switch(opcao) {
			case 1: {
				resultadoResposta = mostrarPergunta(perguntas, totalPerguntas, calcularDificuldade(participante, totalParticipantes-1), ajudas);
				if(resultadoResposta == 1){
					numeroRespostas++; //vai somando valores para o array de premios
					participante[totalParticipantes-1].dinheiro = premios[numeroRespostas];
					printf("Atingiu os %i euros!\n", participante[totalParticipantes-1].dinheiro);
					
					//condicao para quando acerta todas perguntas
					if(numeroRespostas==15) {
						//system("cls");
						printf("\n\t#######################################################\n");
						printf("\t  Parabéns, é o VENCEDOR do QUEM QUER SER MILIONARIO!!!");
						printf("\n\t#######################################################\n");
						guardarParticipantes(participante, totalParticipantes);
						guardarParticipantesTxt(participante, totalParticipantes-1);
						return;
					}
				}
				else {
					printf("\nParabéns, ganhou %i euros!\n", calcularGanhosMinimos(participante, totalParticipantes-1));
					guardarParticipantes(participante, totalParticipantes);
					verificarTop10(participante, totalParticipantes);
					guardarParticipantesTxt(participante, totalParticipantes-1);
					return;
				}
				break;
			}
			//Resumo do jogo
			case 2: {
				printf("\n# RESUMO DO JOGO #\n  Jogador: %s\n  Dinheiro: %i\n  Dinheiro Seguro: %i\n  Respostas Acertadas: %i\n", 
				         participante[totalParticipantes-1].nome, participante[totalParticipantes-1].dinheiro, calcularGanhosMinimos(participante, totalParticipantes-1), numeroRespostas);
				break;
			}
			
			//sai do jogo + guarda participantes no ficheiro + verifica se ficou nos 10 primeiros(em caso de respostas>1)
			case 0: {
				guardarParticipantes(participante, totalParticipantes);
				if(numeroRespostas>0){ //controlar se respondeu a alguma perguntas para mostrar o top10
					verificarTop10(participante, totalParticipantes);
				}
				guardarParticipantesTxt(participante, totalParticipantes-1);
				return;
			}
			default: printf("\nOpção inválida!\n");
		}	
	} while(opcao!=0);
	
};
