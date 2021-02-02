#include "utils.h"
#include <string.h>

// GUARDAR AS REGRAS NO FICHEIRO BIN
void salvarRegras(ELEMENTO *iniLista, int total){
    ELEMENTO *aux=NULL;
    FILE *file=NULL;
    
    file=fopen("ficheiros/ListaRegras.dat", "wb");
    if(file==NULL){
        printf("Erro ao abrir o ficheiro e gravar as regras!\n");
        return;
    }
    fwrite(&total, sizeof(int), 1, file);
    for(aux=iniLista;aux!=NULL;aux=aux->seguinte){
        fwrite(&(aux->info), sizeof(REGRAS), 1, file);
    }

    fclose(file);
}

//ler regras do ficheiro e colocar na lista
int lerRegras(ELEMENTO **iniLista) {
	FILE *file = NULL;
	REGRAS info;
	int total = 0, res =0, i=0;
	
	file = fopen("ficheiros/ListaRegras.dat", "rb");
	if(file==NULL) {
		printf("Erro ao abrir ficheiro!\n"); return -1;
	}
	
	fread(&total, sizeof(int), 1, file);
	
	if(total>0) {
		for(i=0; i<total; i++) {
			fread(&info, sizeof(REGRAS), 1, file);
			ELEMENTO *novo = NULL, *aux =NULL;
			novo = (ELEMENTO *)calloc(1, sizeof(ELEMENTO));
			
			if(novo==NULL) { printf("Erro ao reservar memoria!"); return 0; }
			
			novo->info = info;
			novo->seguinte = NULL;
			
			if(*iniLista==NULL) {
				*iniLista = novo;
			} else {
				aux = *iniLista;
				while(aux->seguinte != NULL) {
					aux = aux->seguinte;
				}
				aux->seguinte = novo;
			}
			res++;
		}
	}
	fclose(file);
	return res;
}

// INSERIR NOVOS ELEMENTOS NA LISTA
int inserirIniLista(ELEMENTO **iniLista, REGRAS info) {
	ELEMENTO *novo=NULL;
	
	novo = (ELEMENTO *)calloc(1, sizeof(ELEMENTO));
	if(novo==NULL) {
		printf("out of memory\n");
		return -1;
	}
	novo->info=info;
	novo->seguinte=NULL;
	
	if(*iniLista==NULL) {
		*iniLista=novo;
	}else {
		novo->seguinte=*iniLista;
		*iniLista=novo;
	}
	return 0;
}

int removerRegra(ELEMENTO **iniLista){
    ELEMENTO *aux=NULL, *ant=NULL;
    aux=*iniLista;
    int id;
    
	printf("\nIndique o ID da pergunta que deseja remover:\n");
	scanf("%i", &id);
	
    while(aux!=NULL && aux->info.id == id){
        ant=aux;
        aux=aux->seguinte;
    }
    if(aux==NULL){
        printf("O id indicado não existe!\n");
        return 0;
    }
    if(ant ==NULL){ //remove o primeiro elemento da lista
        *iniLista=aux->seguinte;
    }
    else{
        ant->seguinte=aux->seguinte;
    }
    free(aux);
    return -1; //serve para retirar um valor ao total
}

// LER AS REGRAS
void listarRegras(ELEMENTO *iniLista) {
	ELEMENTO *aux=NULL;
	if(iniLista==NULL) {
		printf("\nLista Vazia!\n");
		return;
	}
	system("cls");
	printf("\n # Lista de Regras #\n");
	for(aux=iniLista;aux!=NULL; aux=aux->seguinte) {
		printf("    - %s\n", aux->info.descricao); // regras mostradas em order decrescente
	}
}

//Liberta a memoria
void libertaMemoria(ELEMENTO **iniLista){
    ELEMENTO *aux=NULL, *proximo=NULL;
    aux=*iniLista;
    
    *iniLista=NULL;
    while(aux!=NULL){
        proximo=aux->seguinte;
        free(aux);
        aux=proximo;
    }
}


//  ###   PERGUTNAS   ###   //
//ler lista perguntas
int lerPerguntas(PERGUNTAS perguntas[]) {
	FILE *file=NULL;
	int tamanho=0;
	file = fopen("ficheiros/ListaPerguntas.dat", "rb");
	if(file==NULL) {
		printf("Erro ao abrir ficheiro ListaPerguntas.dat");
		return 0;
	}
	fread(&tamanho, sizeof(int), 1, file);
	fread(perguntas, sizeof(PERGUNTAS), tamanho, file);
	fclose(file);
	return tamanho;
}

// funcao centralizada para gravar o array de perguntas no ficheiro BIN
int salvarPerguntas(PERGUNTAS perguntas[], int total) {
	FILE *file = NULL;
	file = fopen("ficheiros/ListaPerguntas.dat", "wb");
	if(file==NULL) {
		printf("Erro ao abrir ficheiro!\n");
		return -1;
	}
	
	fwrite(&total,sizeof(int),1,file);
    fwrite(perguntas,sizeof(PERGUNTAS),total,file);
	fclose(file);
	return total;
}

//reset das mais recentes caso ja tenha usado todas do nivel
void resetarPerguntas(PERGUNTAS perguntas[], int totalPerguntas, int nivel) {
	int i=0, aux=0;
	
	for (i=0; i<totalPerguntas; i++) {
		if (perguntas[i].nivelDificuldade == nivel && perguntas[i].respostaRecente==0) aux = 1;
	}
	if(aux!=1) {
		for (i=0; i<totalPerguntas; i++) {
			if (perguntas[i].nivelDificuldade == nivel) perguntas[i].respostaRecente=0;
		}
	}
	salvarPerguntas(perguntas, totalPerguntas);
}

//ler lista participantes
int lerParticipantes(PARTICIPANTE participante[]) {
	FILE *file=NULL;
	int tamanho=0;
	file = fopen("ficheiros/ListaParticipantes.dat", "rb");
	if(file==NULL) {
		printf("Erro ao abrir ficheiro ListaParticipantes.dat\n");
		return 0;
	}
	fread(&tamanho, sizeof(int), 1, file);
	fread(participante, sizeof(PARTICIPANTE), tamanho, file);
	fclose(file);
	return tamanho;
}

//escrever para ficheiro
int guardarParticipantes(PARTICIPANTE participante[], int total) {
	FILE *file = NULL;
	int res=0;
	file = fopen("ficheiros/ListaParticipantes.dat", "wb");
	if(file==NULL) {
		printf("Erro ao abrir ficheiro!\n");
		return -1;
	}
	fwrite(&total, sizeof(int), 1, file);
	res= fwrite(participante, sizeof(PARTICIPANTE), total, file);
	fclose(file);
	return total;
}

//inserir dados no array
void guardarParticipantesTxt(PARTICIPANTE participante[], int total) {
	FILE *file = NULL;
	int i;
	file = fopen("ficheiros/historicoParticipantes.txt", "w");
	if(file==NULL) {
		printf("Erro ao abrir ficheiro!");
		return;
	}
	//guarda os ultimos 10 participantes
	for(i=total; i>total-10 && i>0; i--){
		fprintf(file, "%i;%s;%i\n", participante[i].numero, participante[i].nome, participante[i].dinheiro);
	}
	fclose(file);
}

void verificarTop10(PARTICIPANTE participante[], int total) {
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
	
	for(i=0; i<10 && i<total;i++) {
		if(participante[i].numero == participante[total-1].numero) {
			printf("Parabéns, ficou no TOP 10!\n");
			return;
		}
	}
}

int menu() {
	int opcao = 0;
	printf("\t### QUEM QUER SER MILIONARIO ###\n\n");
	do {
		printf("Introduza o utilizador que pretende utilizar:\n 1 - Jogador\n 2 - Administrador\n 0 - Sair\n");
		scanf("%i", &opcao);
		switch(opcao) {
			case 1: return 1;
			case 2: return 2;
			case 0: return -1;
			default: printf("Introduza uma opção válida");
		}
	} while (opcao!=0);	
}
