#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "iostream"
#include "fstream"
#include "string"
#include "algorithm"
#include "vector"
#include "cstring"

#ifdef _WIN32
    #define clear "cls"
#else
    #define clear "clear"
#endif

using namespace std;

struct Professor;
struct Escola;
struct Vagas;
struct Grafo;
struct find_vagas;
struct find_professor;

void ImprimeProfessores(Grafo&);
void ImprimeEscola(Grafo&);
void AlimentaGrafo(string, int, Grafo*);
void Emparelha(Grafo&, bool);

#endif