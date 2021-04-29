#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <stdio.h>
#include "Dados.h"
using namespace std;

#ifdef _WIN32
	# define CLEAR "cls"
#else
	# define CLEAR "clear"
#endif

S_Professor Fornece_struct_professor(char linha[]);
S_Escola Fornece_struct_escola(char linha[]);
void Pula_linha(FILE* fd);
void Receber_dados(vector<S_Professor> *Lista_Professores, vector<S_Escola> *Lista_Escolas);

#endif //INPUT_H