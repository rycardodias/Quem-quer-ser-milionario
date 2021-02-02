//#ifndef utils_h
//#define utils_h

#define MAX_PARTICIPANTES 150
#define MAX_PERGUNTAS 100

#include <stdio.h>
#include <stdlib.h>

typedef struct perguntas {
	int idPergunta, nivelDificuldade, respostaCorreta, respostaRecente;
	char pergunta[100], resposta1[100], resposta2[100], resposta3[100], resposta4[100];
} PERGUNTAS;

typedef struct participante {
	int numero, dinheiro;
	char nome[100];
	char sigla[5];
} PARTICIPANTE;

typedef struct regras {
	int id;
	char descricao[255];
} REGRAS;

typedef struct Elem {
	REGRAS info;
	struct Elem *seguinte;
} ELEMENTO;


int menu();

//REGRAS
int lerRegras(ELEMENTO **iniLista);

void salvarRegras(ELEMENTO *iniLista, int total);

int inserirIniLista(ELEMENTO **iniLista, REGRAS info);

int removerRegra(ELEMENTO **iniLista);

int inserirRegras(REGRAS regras[], int total);

void listarRegras(ELEMENTO *iniLista);

void libertaMemoria(ELEMENTO **iniLista);

// PERGUNTAS
int lerPerguntas(PERGUNTAS perguntas[]);

int salvarPerguntas(PERGUNTAS perguntas[], int total);

void resetarPerguntas(PERGUNTAS perguntas[], int totalPerguntas, int nivel);

// PARTICIPANTES
int lerParticipantes(PARTICIPANTE participante[]);

int guardarParticipantes(PARTICIPANTE participante[], int total);

void guardarParticipantesTxt(PARTICIPANTE participante[], int total);

void verificarTop10(PARTICIPANTE participante[], int total);

//#endif /* utils_h */
