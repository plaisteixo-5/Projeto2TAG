#ifndef DADOS_H
#define DADOS_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

#ifdef _WIN32
	# define CLEAR "cls"
#else
	# define CLEAR "clear"
#endif

typedef struct Escola{
    int codigo;
    vector<int> preferencia;
    
    // Habilitacao requerida por vaga
    int Hab_vaga1;
    int Hab_vaga2;
    
    // Se ha vagas disponíveis
    int Vaga1_ocupado;
    int Vaga2_ocupado;

    // Professores ligados a escola	
    int Professor1;
    int Professor2;

    // Possibilita substituicao
    int Tem_margem1;
    int Tem_margem2;
}S_Escola;

typedef struct Professor{
    int codigo;
    int habilitacao;
    vector<int> escolas; //preferencias
    
    // Se ele esta livre
    bool Livre = true;

    // Escola que o professor está ligado
    int Onde_trabalha;
}S_Professor;

typedef struct Vagas_Escola{
    int codigo_escola;
    int habilidade_pretendida;
}S_Vagas_Escola;

void Coloca_global(vector<S_Professor> Lista_Professor, vector<S_Escola> Lista_Escolas);
void Preenche_Vetor_Vagas(vector<S_Vagas_Escola> *Lista_Vagas_Escola, vector<S_Escola> Lista_Escolas);

void Atribuir_Professor_livre();
void Atribuir_Escola_livre();
int Substituir_Professor(int codigo_professor);
bool Inserir_Professor_Escola_Vazia(int codigo_professor);
void Emparelhamento_estavel_para_professor();

int Vincular_Professor_Escola(S_Professor *Professor_atual, S_Escola *Escola_atual);
void Substituir_Professor(S_Escola Escola_atual, S_Professor Professor_atual, S_Professor Professor_Novo);
void Alocar_Professores_Escolas(vector<S_Professor> Lista_Professores, vector<S_Escola> Lista_Escolas);
void Inserir_professor_escola(S_Professor *professor_atual, S_Escola *escola_atual);


#endif //DADOS_H
