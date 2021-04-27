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
    vector<Vagas> vagas;
};

struct Vagas{
    int habilitacao;
    bool ocupada;
    Professor professor;
};

struct Grafo{
    vector<Professor> prof;
    vector<Escola> esc;
};

void ImprimeGrafo(Grafo grafo){

    FILE* fd;
    char file[] = "visualizacao_saida.txt";
    fd = fopen(file, "w");

    for(auto x: grafo.prof){
        fprintf(fd, "Código do Professor: %s\n", x.cod_professor);
        fprintf(fd, "Número de Abilitações: %d\n", x.num_ablt);

        cout << "Código do Professor: " << x.cod_professor << endl;
        cout << "Número de Abilitações: " << x.num_ablt << endl;

        for(auto y : x.preferencias) {
            cout << "Preferência: " << y << endl;
            fprintf(fd, "Preferência: %s\n", y);
        }
    }

    for(auto x: grafo.esc){
        cout << "Código da Escola: " << x.cod_escola << endl;

        fprintf(fd, "Código da Escola: %s\n", x.cod_escola);

        for(auto y : x.vagas) {
            fprintf(fd, "Vaga para: %d\n", y.habilitacao);
            fprintf(fd, "A vaga está: %d\n", y.ocupada);
            fprintf(fd, "O professor responsável é: %d\n", y.professor.cod_professor);

            cout << "Vaga para: " << y.habilitacao << endl;
            cout << "A vaga está: " << y.ocupada ? "Ocupada" : "Livre" << endl;
            cout << "O professor responsável é: " << y.professor.cod_professor << endl;
        }
    }

    fclose(fd);
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

        Escola escola;
        int contador = 0;

        char* converted_value = const_cast<char*>(value.c_str());
        char* pieces = strtok(converted_value, " ");

        while(pieces != NULL){
            if(contador == 0) escola.cod_escola = pieces;
            else { 
                Vagas vaga = new Vagas();
                vaga.habilitacao = stoi(pieces);
                vaga.ocupada = false;
                vaga.professor = NULL;

                escola.vagas.pushback(vaga);
            }
            pieces = strtok(NULL, " ");

            contador++;
        }
        
        // Insere a escola no grafo
        grf->escola.push_back(escola); 
        
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

    return 0;
}
