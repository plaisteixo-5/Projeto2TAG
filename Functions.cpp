#include "Functions.h"
struct Professor{
    string cod_professor;
    int habilitacao;
    vector<string> escola_pref;

    string escola_ocupada;
};

struct Vagas{
    int habilitacao;
    bool ocupada;
    bool estavel;

    string codigo_professor;
    int habilitacao_professor;
};

struct Escola{
    string cod_escola;
    vector<Vagas> vagas;
};

struct Grafo{
    vector<Professor> professores;
    vector<Escola> escolas;
};

struct find_professor : unary_function<Professor, bool> {
    string cod_professor;
    find_professor(string cod_professor):cod_professor(cod_professor) { }
    bool operator()(Professor const& professor) const {
        return professor.cod_professor == cod_professor;
    }
};
struct find_vagas : unary_function<Escola, bool> {
    string cod_escola;
    find_vagas(string cod_escola):cod_escola(cod_escola) { }
    bool operator()(Escola const& escola) const {
        return escola.cod_escola == cod_escola;
    }
};

void ImprimeGrafo(Grafo grafo){

    for(auto x: grafo.escolas){
        cout << "Código da Escola: " << x.cod_escola << endl;

        for(auto y : x.vagas) {
            string aux = y.ocupada ? "Ocupada" : "Livre";

            cout << "Vaga para: " << y.habilitacao << endl;
            cout << "A vaga esta: " << aux << endl;
            cout << "O professor responsavel eh: " << y.codigo_professor << endl;
            cout << "Sua abilitacao eh: " << y.habilitacao_professor << endl;
        }
    }
}

void ImprimeProfessores(Grafo &grafo){
    int cont = 0;
    for(auto professor : grafo.professores){
        cout << "----------------- " << professor.cod_professor << " -----------------" << endl;
        cout << "Habilitacao: " << professor.habilitacao << endl;
        cout << "Escolas de preferencia: ";
        for(auto pref : professor.escola_pref){
            cout << pref << " ";
        }

        cout << endl;

        if(professor.escola_ocupada.empty()){
            cout << " Não está alocado" << endl;    
        }
        else if(!professor.escola_ocupada.empty()){
            cont++;
            cout << "Está alocado" << endl;
        }
    }
    cout << cont << " professores foram alocados" << endl;
}

void ImprimeEscola(Grafo &grafo){
    int cont = 0;

    for(auto escola : grafo.escolas){
        cout << "----------------- " << escola.cod_escola << " -----------------" << endl;
        cout << "Vagas: ";
        for(auto vaga : escola.vagas){
            if(vaga.ocupada){
                cout << "A vaga está ocupada pelo professor " << vaga.codigo_professor << "com habilitação " << vaga.habilitacao_professor;
            }
            string aux = vaga.ocupada ? "A vaga"
            cout << "Habilitacao necessaria: " << vaga.habilitacao;
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
                vaga.habilitacao = stoi(pieces);
                vaga.ocupada = false;
                vaga.habilitacao_professor = 0;
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
            else if(contador == 1) prof.habilitacao = stoi(pieces);
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
        if(!professor.escola_ocupada.empty()) {
            cont ++;
            cout << "O professor " << professor.cod_professor << " está alocado em " << professor.escola_ocupada << endl;
        }
    }
    cout << "O total de professores alocados é " << cont << endl;
    cont = 0;

    for(auto escola : grafo.escolas){
        for(auto vaga : escola.vagas){
            if(!vaga.ocupada) {
                cout << "A escola " << escola.cod_escola << " tem a vaga de valor " << vaga.habilitacao << " livre" << endl;
            } else cont++;
        }
    }
    cout << "O total de vagas ocupadas é " << cont << endl;
}

bool compareByLength(const Professor &a, const Professor &b){
    return a.habilitacao > b.habilitacao;
}

bool compareBySchool(const Escola &a, const Escola &b){
    return a.vagas[0].habilitacao > b.vagas[0].habilitacao;
}

void RealocaProfessor(string codigo_professor, Grafo& grafo){
    auto professor = find_if(grafo.professores.begin(), grafo.professores.end(), find_professor(codigo_professor));
    bool flag = true;

    professor->escola_ocupada = "";
    cout << "---------------------------------------------------------" << endl;
    cout << "Tá analisando o professor " << professor->cod_professor << endl;

    for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() && flag; escola_preferencia++){
        auto vagas_escola = find_if(grafo.escolas.begin(), grafo.escolas.end(), find_vagas(*escola_preferencia));

        cout << "Tá analisando a escola " << vagas_escola->cod_escola << endl;

        for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
            cout << "Tá analisando a vaga " << vaga_escola->habilitacao << endl;
            string aux = vaga_escola->ocupada ? "Ocupada" : "Livre";

            if(vaga_escola->habilitacao <= professor->habilitacao && !vaga_escola->ocupada){
                vaga_escola->codigo_professor = professor->cod_professor;
                vaga_escola->habilitacao_professor = professor->habilitacao;
                vaga_escola->ocupada = true;
                professor->escola_ocupada = vagas_escola->cod_escola;
                flag = false;

                cout << "Código da escola: " << vagas_escola->cod_escola << endl;
                cout << "Código da escola 2: " << professor->escola_ocupada << endl;

                cout << "Foi alocado o professor " << vaga_escola->codigo_professor << " na escola " << professor->escola_ocupada << endl;

                cout << "Realocou" << endl;
                return;
            }
        }
    }
}

void Emparelha(Grafo& grafo, bool estavel_max){
    for(auto professor = grafo.professores.begin() ; professor != grafo.professores.end() ; professor++ ){
        bool flag = true;

        if(professor->escola_ocupada.empty()) {
            for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() && flag ; escola_preferencia++){
                auto vagas_escola = find_if(grafo.escolas.begin(), grafo.escolas.end(), find_vagas(*escola_preferencia));

                for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
                    if(vaga_escola->habilitacao == professor->habilitacao && !vaga_escola->ocupada){
                        if(vaga_escola->habilitacao == professor->habilitacao) vaga_escola->estavel = true;
                        vaga_escola->codigo_professor = professor->cod_professor;
                        vaga_escola->habilitacao_professor = professor->habilitacao;
                        vaga_escola->ocupada = true;
                        professor->escola_ocupada = vagas_escola->cod_escola;

                        flag = false;
                        break;
                    }
                }
                for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
                    if(vaga_escola->habilitacao <= professor->habilitacao && !vaga_escola->ocupada){
                        if(vaga_escola->habilitacao == professor->habilitacao) vaga_escola->estavel = true;
                        vaga_escola->codigo_professor = professor->cod_professor;
                        vaga_escola->habilitacao_professor = professor->habilitacao;
                        vaga_escola->ocupada = true;
                        professor->escola_ocupada = vagas_escola->cod_escola;

                        flag = false;
                        break;
                    }
                }
            }
        }
    }
if(estavel_max){
for(auto escola = grafo.escolas.begin() ; escola != grafo.escolas.end() ; escola++){
        bool flag = true;
        for(auto vaga = escola->vagas.begin() ; vaga != escola->vagas.end() ; vaga++){
            if(!vaga->ocupada){
                for(auto professor = grafo.professores.begin() ; professor != grafo.professores.end() ; professor++){
                    if((professor->habilitacao == vaga->habilitacao 
                    || professor->habilitacao >= vaga->habilitacao) 
                    && professor->escola_ocupada.empty()){
                        cout << "Alocou o professor " << professor->cod_professor << " na escola " << escola->cod_escola << endl;
                        vaga->codigo_professor = professor->cod_professor;
                        vaga->habilitacao_professor = professor->habilitacao;
                        vaga->ocupada = true;
                        professor->escola_ocupada = escola->cod_escola;
                        break;
                    }
                }
            }
        }
    }
}
    
    // for(auto escola = grafo.escolas.begin() ; escola != grafo.escolas.end() ; escola++){
    //     bool flag = true;
    //     for(auto vaga = escola->vagas.begin() ; vaga != escola->vagas.end() ; vaga++){
    //         if(!vaga->ocupada){
    //             for(auto professor = grafo.professores.begin() ; professor != grafo.professores.end() ; professor++){
    //                 if((professor->habilitacao == (vaga->habilitacao - 1) 
    //                 || professor->habilitacao >= (vaga->habilitacao - 1)) 
    //                 && professor->escola_ocupada.empty()){
    //                     cout << "Alocou o professor " << professor->cod_professor << " na escola " << escola->cod_escola << endl;
    //                     vaga->codigo_professor = professor->cod_professor;
    //                     vaga->habilitacao_professor = professor->habilitacao;
    //                     vaga->ocupada = true;
    //                     professor->escola_ocupada = escola->cod_escola;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    ImprimeProfessores(grafo);
}