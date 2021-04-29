#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <stdio.h>
#include "Dados.h"

using namespace std;

#ifdef _WIN32
	# define CLEAR "cls"
#else
	# define CLEAR "clear"
#endif

void Imprimir_lista_professores(vector<S_Professor> Lista_Professores);
void Imprimir_lista_escolas(vector<S_Escola> Lista_Escolas);
void Imprimir_lista_vagas_escola(vector<S_Vagas_Escola> Lista_Vagas_Escola);
void Imprimir_Escola_Professor(vector<S_Escola> Lista_Escolas);

#endif //OUTPUT_H