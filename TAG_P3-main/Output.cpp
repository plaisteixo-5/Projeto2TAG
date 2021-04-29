#include "Output.h"

void Imprimir_lista_professores(vector<S_Professor> Lista_Professores){
    cout << "Lista de professores: " << endl;
    cout << "Formato: codigo professor - habilitacoes - Escolas em ordem decrescente de prioridade" << endl;
    for(int i = 0; i < Lista_Professores.size(); i++){
        cout << Lista_Professores[i].codigo << " - " << Lista_Professores[i].habilitacao;
        for(int j = 0; j < Lista_Professores[i].escolas.size(); j++)
            cout << " - " << Lista_Professores[i].escolas[j];
        cout << endl;
    }
}

void Imprimir_lista_escolas(vector<S_Escola> Lista_Escolas){
    cout << endl << "Lista de escolas: " << endl;
    cout << "Formato: codigo escola - habilitacoes pretendidas - habilitacoes pretendidas, se houver segunda vaga" << endl;
    for(int i = 0; i < Lista_Escolas.size(); i++){
        cout << Lista_Escolas[i].codigo;
        for(int j = 0; j < Lista_Escolas[i].preferencia.size(); j++)
            cout << " - " << Lista_Escolas[i].preferencia[j];
        cout << endl;
    }
}

void Imprimir_lista_vagas_escola(vector<S_Vagas_Escola> Lista_Vagas_Escola){
    cout << endl << "Lista de vagas das escolas: " << endl;
    cout << "Formato: codigo escola - habilitacoes pretendidas" << endl;
    for(int i = 0; i < Lista_Vagas_Escola.size(); i++){
        cout << Lista_Vagas_Escola[i].codigo_escola << " - ";
        cout << Lista_Vagas_Escola[i].habilidade_pretendida;
        cout << endl;
    }
}

void Imprimir_Escola_Professor(vector<S_Escola> Lista_Escolas){
	for(int i = 0; i < Lista_Escolas.size(); i++){
        if(Lista_Escolas[i].Hab_vaga2 != -1){
            printf("A vaga 1 da escola %d ficou com o professor %d", Lista_Escolas[i].codigo, Lista_Escolas[i].Professor1);
            printf("A vaga 2 da escola %d ficou com o professor %d", Lista_Escolas[i].codigo, Lista_Escolas[i].Professor2);
        }
        else
            printf("A vaga da escola %d ficou com o professor %d", Lista_Escolas[i].codigo, Lista_Escolas[i].Professor1);
	}
}