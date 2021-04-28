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
    vector<string> escola_pref;

    string escola_ocupada;
};

struct Vagas{
    int ablt;
    bool ocupada;

    string codigo_professor;
    int ablt_professor;
};

struct Escola{
    string cod_escola;
    vector<Vagas> vagas;
};

struct Grafo{
    vector<Professor> professores;
    vector<Escola> escolas;
};

struct find_vagas : unary_function<Escola, bool> {
    string cod_escola;
    find_vagas(string cod_escola):cod_escola(cod_escola) { }
    bool operator()(Escola const& escola) const {
        return escola.cod_escola == cod_escola;
    }
};

struct find_professor : unary_function<Professor, bool> {
    string cod_professor;
    find_professor(string cod_professor):cod_professor(cod_professor) { }
    bool operator()(Professor const& professor) const {
        return professor.cod_professor == cod_professor;
    }
};

void ImprimeGrafo(Grafo grafo){

    // FILE* fd;
    // char file[] = "visualizacao_saida.txt";
    // fd = fopen(file, "w");

    for(auto x: grafo.professores){
        // fprintf(fd, "Código do Professor: %s\n", x.cod_professor);
        // fprintf(fd, "Número de Abilitações: %d\n", x.num_ablt);

        cout << "Código do Professor: " << x.cod_professor << endl;
        cout << "Número de Abilitações: " << x.num_ablt << endl;

        for(auto y : x.escola_pref) {
            cout << "Preferência: " << y << endl;
            // fprintf(fd, "Preferência: %s\n", y);
        }
    }

    for(auto x: grafo.escolas){
        cout << "Código da Escola: " << x.cod_escola << endl;

        // fprintf(fd, "Código da Escola: %s\n", x.cod_escola);

        for(auto y : x.vagas) {
            string aux = y.ocupada ? "Ocupada" : "Livre";
            // fprintf(fd, "Vaga para: %d\n", y.ablt);
            // fprintf(fd, "A vaga está: %d\n", aux);
            // fprintf(fd, "O professor responsável é: %d\n", y.professor.cod_professor);

            cout << "Vaga para: " << y.ablt << endl;
            cout << "A vaga está: " << aux << endl;
            cout << "O professor responsável é: " << y.codigo_professor << endl;
        }
    }

    // fclose(fd);
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
                Vagas vaga ;
                vaga.ablt = stoi(pieces);
                vaga.ocupada = false;
                vaga.ablt_professor = 0;
                vaga.codigo_professor = "";

                escola.vagas.push_back(vaga);
            }
            pieces = strtok(NULL, " ");

            contador++;
        }
        
        // Insere a escola no grafo
        grf->escolas.push_back(escola); 
        
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
            else prof.escola_pref.push_back(pieces);
            pieces = strtok(NULL, " ");

            contador++;
        }

        prof.escola_ocupada = "";
        
        // Insere o professor no grafo
        grf->professores.push_back(prof); 
    }
}

void ContaVagas(Grafo grafo){
    int contador = 0;

    for(auto escolas : grafo.escolas){
        for(auto vaga : escolas.vagas){
            if(vaga.ocupada) contador++;
        }
    }

    cout << contador << endl;
}

void RealocaProfessor(string codigo_professor, Grafo* grafo){
    auto professor = find_if(grafo->professores.begin(), grafo->professores.end(), find_professor(codigo_professor));

    for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() ; escola_preferencia++){
        // cout << "Tá no for das escolas do professor" << endl;
        auto vagas_escola = find_if(grafo->escolas.begin(), grafo->escolas.end(), find_vagas(*escola_preferencia));

        for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
            // cout << "Tá no for das vagas da escola" << endl;
            if(vaga_escola->ocupada){
                if(vaga_escola->ablt_professor < professor->num_ablt){
                    cout << "Trocou" << endl;
                    
                    string aux_codigo_professor = vaga_escola->codigo_professor;
                    vaga_escola->codigo_professor = professor->cod_professor;
                    vaga_escola->ablt_professor = professor->num_ablt;
                    professor->escola_ocupada = vagas_escola->cod_escola;

                    RealocaProfessor(aux_codigo_professor, grafo);
                }
            } else if(vaga_escola->ablt <= professor->num_ablt && !vaga_escola->ocupada){

                vaga_escola->codigo_professor = professor->cod_professor;
                vaga_escola->ablt_professor = professor->num_ablt;
                vaga_escola->ocupada = true;
                professor->escola_ocupada = vagas_escola->cod_escola;
            }
        }
    }
}

void Emparelha(Grafo* grafo){
    for(auto professor = grafo->professores.begin() ; professor != grafo->professores.end() ; professor++ ){
        // cout << professor.cod_professor << endl;
        bool flag = true;

        if(professor->escola_ocupada.empty()) {
            for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() && flag ; escola_preferencia++){
                // cout << "Tá no for das escolas do professor" << endl;
                auto vagas_escola = find_if(grafo->escolas.begin(), grafo->escolas.end(), find_vagas(*escola_preferencia));

                for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
                    // cout << "Tá no for das vagas da escola" << endl;
                    if(vaga_escola->ocupada){
                        if(vaga_escola->ablt_professor < professor->num_ablt){
                            cout << "Trocou 2" << endl;
                                    cout << "---------- Atualização ----------" << endl;

                            cout << "Professor que vai subsitituir: " << professor->cod_professor << endl;
                            cout << "Professor que vai ser substituido: " << vaga_escola->codigo_professor << endl;
                            cout << "Escola: " << vagas_escola->cod_escola << endl;
                            
                            string aux_codigo_professor = vaga_escola->codigo_professor;
                            vaga_escola->codigo_professor = professor->cod_professor;
                            vaga_escola->ablt_professor = professor->num_ablt;
                            professor->escola_ocupada = vagas_escola->cod_escola;

                            cout << "Professor: " << vaga_escola->codigo_professor << endl;
                            cout << "Abilitação: " << vaga_escola->ablt_professor << endl;

                            RealocaProfessor(aux_codigo_professor, grafo);
                        }
                    } else if(vaga_escola->ablt <= professor->num_ablt && !vaga_escola->ocupada){

                        vaga_escola->codigo_professor = professor->cod_professor;
                        vaga_escola->ablt_professor = professor->num_ablt;
                        vaga_escola->ocupada = true;
                        professor->escola_ocupada = vagas_escola->cod_escola;

                        flag = false;
                    }
                }
            }
        }
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

    Emparelha(&grafo);


    ImprimeGrafo(grafo);
    ContaVagas(grafo);

    return 0;
}
