#include "iostream"
#include "fstream"
#include "string"
#include "algorithm"
#include "vector"

using namespace std;

struct Professor{
    string cod_professor;
    int num_ablt;
    vector<string> preferencias;
};

struct Escola{
    string cod_escola;  
};

struct Graph{
    vector<Professor> prof;
    vector<Escola> esc;
};

int main(){

    Graph grafo;

    Professor prof;
    prof.cod_professor = "P1";
    prof.num_ablt = 1;
    prof.preferencias.push_back("E20");
    prof.preferencias.push_back("E10");
    prof.preferencias.push_back("E3");

    Escola esc;
    esc.cod_escola = "E1";

    grafo.prof.push_back(prof);
    grafo.esc.push_back(esc);

    // ifstream file("entradaProj2TAG.txt");

    // string input_file;
    // int flag = 0;

    // while(getline(file, input_file, ',')){
    //     if(input_file[0] == '/') {
    //         file.ignore(2048, '\n');
    //         flag++;
    //     }
    //     else {
            // if(flag == 2){
            //     replace(input_file.begin(), input_file.end(), ':', ' ');
            //     input_file.erase(remove(input_file.begin(), input_file.end(), '('), input_file.end());
            //     input_file.erase(remove(input_file.begin(), input_file.end(), ')'), input_file.end());
            // } else {
            //     input_file.erase(remove(input_file.begin(), input_file.end(), '('), input_file.end());
            //     input_file.erase(remove(input_file.begin(), input_file.end(), ')'), input_file.end());
            //     input_file.erase(remove(input_file.begin(), input_file.end(), ','), input_file.end());
            //     input_file.erase(remove(input_file.begin(), input_file.end(), ':'), input_file.end());
            // }
    //         cout << input_file << "\n";
    //     }
    // }
    // file.close();

    return 0;
}