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
    bool estavel;

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

    for(auto x: grafo.escolas){
        cout << "Código da Escola: " << x.cod_escola << endl;

        for(auto y : x.vagas) {
            string aux = y.ocupada ? "Ocupada" : "Livre";

            cout << "Vaga para: " << y.ablt << endl;
            cout << "A vaga esta: " << aux << endl;
            cout << "O professor responsavel eh: " << y.codigo_professor << endl;
            cout << "Sua abilitacao eh: " << y.ablt_professor << endl;
        }
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
                vaga.estavel = false;

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

void ImprimeDisponivel(Grafo grafo){
    int cont = 0;
    for(auto professor : grafo.professores){
        if(professor.escola_ocupada.empty()) {
            cont ++;
            cout << "O professor " << professor.cod_professor << " não está alocado" << endl;
        }
    }
    cout << "O total de professores livres é " << cont << endl;
    cont = 0;

    for(auto escola : grafo.escolas){
        for(auto vaga : escola.vagas){
            if(!vaga.ocupada) {
                cont++;
                cout << "A escola " << escola.cod_escola << " tem a vaga de valor " << vaga.ablt << " livre" << endl;
            }
        }
    }
    cout << "O total de vagas livres é " << cont << endl;
}

bool compareByLength(const Professor &a, const Professor &b){
    return a.num_ablt > b.num_ablt;
}

bool compareBySchool(const Escola &a, const Escola &b){
    return a.vagas[0].ablt > b.vagas[0].ablt;
}

void RealocaProfessor(string codigo_professor, Grafo* grafo){
    auto professor = find_if(grafo->professores.begin(), grafo->professores.end(), find_professor(codigo_professor));
    bool flag = true;

    professor->escola_ocupada = "";


    for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() && flag; escola_preferencia++){
        auto vagas_escola = find_if(grafo->escolas.begin(), grafo->escolas.end(), find_vagas(*escola_preferencia));

        for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
            string aux = vaga_escola->ocupada ? "Ocupada" : "Livre";

            if(vaga_escola->ablt <= professor->num_ablt && !vaga_escola->ocupada){
                vaga_escola->codigo_professor = professor->cod_professor;
                vaga_escola->ablt_professor = professor->num_ablt;
                vaga_escola->ocupada = true;
                professor->escola_ocupada = vagas_escola->cod_escola;
                flag = false;

                break;
            }
        }
    }
}

bool AlocaAbltIgual(Escola* escola, Professor* professor, bool igual){
    for(auto vaga : escola->vagas){
        if(igual){
            if(vaga.ablt == professor->num_ablt){
                vaga.codigo_professor = professor->cod_professor;
                vaga.ablt_professor = professor->num_ablt;
                vaga.ocupada = true;
                professor->escola_ocupada = escola->cod_escola;

                return true;
            }
        } else {
            if(vaga.ablt <= professor->num_ablt){
                vaga.codigo_professor = professor->cod_professor;
                vaga.ablt_professor = professor->num_ablt;
                vaga.ocupada = true;
                professor->escola_ocupada = escola->cod_escola;

                return true;
            }
        }
    }

    return false;
}

void Emparelha(Grafo* grafo){
    for(auto professor = grafo->professores.begin() ; professor != grafo->professores.end() ; professor++ ){
        bool flag = true;

        if(professor->escola_ocupada.empty()) {
            for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() && flag ; escola_preferencia++){
                auto vagas_escola = find_if(grafo->escolas.begin(), grafo->escolas.end(), find_vagas(*escola_preferencia));

                // flag = !AlocaAbltIgual(vagas_escola, *professor);
                for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
                    if(vaga_escola->ocupada){
                        if(vaga_escola->ablt_professor < professor->num_ablt){

                            string aux_codigo_professor = vaga_escola->codigo_professor;
                            vaga_escola->codigo_professor = professor->cod_professor;
                            vaga_escola->ablt_professor = professor->num_ablt;
                            professor->escola_ocupada = vagas_escola->cod_escola;

                            RealocaProfessor(aux_codigo_professor, grafo);
                            flag = false;
                            break;
                        }
                    } else if(vaga_escola->ablt <= professor->num_ablt && !vaga_escola->ocupada){
                        vaga_escola->codigo_professor = professor->cod_professor;
                        vaga_escola->ablt_professor = professor->num_ablt;
                        vaga_escola->ocupada = true;
                        professor->escola_ocupada = vagas_escola->cod_escola;

                        flag = false;
                        break;
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

    sort(grafo.escolas.begin(), grafo.escolas.end(), compareBySchool);


    Emparelha(&grafo);

    // ImprimeGrafo(grafo);
    ImprimeGrafo(grafo);
    ContaVagas(grafo);
    ImprimeDisponivel(grafo);

    return 0;
}
