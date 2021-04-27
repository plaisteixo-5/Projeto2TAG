#include "iostream"
#include "fstream"
#include "string"
#include "algorithm"
#include "vector"
#include "cstring"

using namespace std;

struct Professor{
    string cod_professor;
    int num_ablt;
    vector<string> preferencias;

    string escola_ocupada;
};

struct Escola{
    string cod_escola;
    vector<int> vagas;

    vector<bool> vaga_ocupada;
};

struct Grafo{
    vector<Professor> prof;
    vector<Escola> esc;
};

void ImprimeGrafo(Grafo grafo){

    for(auto x: grafo.prof){
        cout << "Código do Professor: " << x.cod_professor << endl;
        cout << "Número de Abilitações: " << x.num_ablt << endl;
        for(auto y : x.preferencias) cout << "Preferência: " << y << endl;
    }

    for(auto x: grafo.esc){
        cout << "Código da Escola: " << x.cod_escola << endl;
        for(auto y: x.vagas) cout << "Vaga para: " << y << endl;
    }

}

void AlimentaGrafo(string value, int flag, Grafo* grf){
    // Verifica se a linha é vazia
    if(int(value[0]) == 0) return;

    // Usa a variável flag para verificar se o que está sendo
    // analisado é uma escola ou professor
    if(flag == 2){
        // Remove caracteres
        replace(value.begin(), value.end(), ':', ' ');
        value.erase(remove(value.begin(), value.end(), '('), value.end());
        value.erase(remove(value.begin(), value.end(), ')'), value.end());

        Escola esc;
        int contador = 0;

        char* converted_value = const_cast<char*>(value.c_str());
        char* pieces = strtok(converted_value, " ");

        while(pieces != NULL){
            if(contador == 0) esc.cod_escola = pieces;
            else {
                esc.vagas.push_back(stoi(pieces));
                esc.vaga_ocupada.push_back(false);
            }
            pieces = strtok(NULL, " ");

            contador++;
        }
        
        // Insere a escola no grafo
        grf->esc.push_back(esc); 
        
    } else {
        // Remove caracteres
        value.erase(remove(value.begin(), value.end(), '('), value.end());
        value.erase(remove(value.begin(), value.end(), ')'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());
        value.erase(remove(value.begin(), value.end(), ':'), value.end());

        Professor prof;
        int contador = 0;

        char* converted_value = const_cast<char*>(value.c_str());
        char* pieces = strtok(converted_value, " ");

        while(pieces != NULL){
            if(contador == 0) prof.cod_professor = pieces;
            else if(contador == 1) prof.num_ablt = stoi(pieces);
            else prof.preferencias.push_back(pieces);
            pieces = strtok(NULL, " ");

            contador++;
        }

        prof.escola_ocupada = "";
        
        // Insere o professor no grafo
        grf->prof.push_back(prof); 
    }
}

int main(){

    Grafo grafo;

    ifstream file("entradaProj2TAG.txt");

    string input_file;
    int flag = 0;

    while(getline(file, input_file)){
        if(input_file[0] == '/') {
            file.ignore(2048, '\n');
            flag++;
        }
        else AlimentaGrafo(input_file, flag, &grafo);
    }
    file.close();

    for(auto x: grafo.prof){
        cout << "Código do Professor: " << x.cod_professor << endl;
        cout << "Número de Abilitações: " << x.num_ablt << endl;
        for(auto y : x.preferencias) cout << "Preferência: " << y << endl;
    }

    for(auto x: grafo.esc){
        cout << "Código da Escola: " << x.cod_escola << endl;
        for(auto y: x.vagas) cout << "Vaga para: " << y << endl;
    }

    return 0;
}