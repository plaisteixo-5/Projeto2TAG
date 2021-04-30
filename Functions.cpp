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

/**
 * Desaloca todos os professores de todas escolas.
 * @param grafo contem todos os dados
 * @return void
*/
void ResetaGrafo(Grafo& grafo){
    for(auto escola = grafo.escolas.begin() ; escola != grafo.escolas.end() ; escola++){
        for(auto vaga = escola->vagas.begin() ; vaga != escola->vagas.end() ; vaga++){
            vaga->codigo_professor = "";
            vaga->habilitacao_professor = 0;
            vaga->ocupada = false;
        }
    }
    for(auto professor = grafo.professores.begin() ; professor != grafo.professores.end() ; professor++) professor->escola_ocupada = "";
}

/**
 * Imprime o resultado do emparelhamento
 * @param grafo grafo com todos os dados.
 * @return void
*/
void ImprimeResultado(Grafo grafo){
    int contador = 0;
    for(auto escola : grafo.escolas){
        cout << "Escola: " << escola.cod_escola << endl;
        for(auto vaga : escola.vagas){
            cout << "A vaga de habilitacao " << vaga.habilitacao;
            if(vaga.ocupada) {
                contador++;
                cout << " foi preenchida pelo professor " << vaga.codigo_professor << endl;
            }
            else cout << " nao foi preenchida" << endl;
        }
    }
    cout << "No total, foram " << contador << " alocadas." << endl;
}

/**
 * Metodo para imprimir os professores.
 * @param grafo contem o grafo contendo os professores e 
 *  escolas lidos do arquivo.
 * 
 * @return void
*/
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
            cout << "Não está alocado" << endl;    
        }
        else if(!professor.escola_ocupada.empty()){
            cont++;
            cout << "Está alocado" << endl;
        }
        cout << "---------------------------------------";
        cout << endl << endl;
    }

    cout << cont << " professores foram alocados" << endl;
}

/**
 * Metodo para imprimir as escolas.
 * @param grafo contem o grafo contendo os professores 
 *  e escolas lidos do arquivo.
 * 
 * @return void
*/
void ImprimeEscola(Grafo &grafo){
    int cont = 0;

    for(auto escola : grafo.escolas){
        cout << "--------------------------- " << escola.cod_escola << " ---------------------------" << endl;
        cout << "Vagas: " << endl;
        for(auto vaga : escola.vagas){
            cout << "   Habilitacao da vaga: " << vaga.habilitacao << endl;
            if(vaga.ocupada){
                cont++;
                cout << "   A vaga está ocupada pelo professor " << vaga.codigo_professor << " com habilitação " << vaga.habilitacao_professor;
            } else cout << "    A vaga esta livre";
            cout << endl;
        }
        cout << "------------------------------------------------------------";
        cout << endl << endl;
    }

    cout << cont << " vagas foram preenchidas" << endl;
}

/**
 * Metodo para gravar os valores do arquivo de entrada
 * @param value eh a linha em formato de string recebida
 *  do arquivo lido.
 * @param flag utilizado para verificar se o que esta
 *  sendo lido eh um professor ou uma escola.
 * @param grafo endereco de variavel que guardara toda
 *  informacao lida.
 * @return void
*/
void AlimentaGrafo(string value, int flag, Grafo* grafo){
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

                escola.vagas.push_back(vaga);
            }
            pieces = strtok(NULL, " ");

            contador++;
        }
        
        // Insere a escola no grafo
        grafo->escolas.push_back(escola); 
        
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
        grafo->professores.push_back(prof); 
    }
}

/**
 * Metodo principal que emparelha os professores
 *  e escolas.
 * @param grafo grafo contendo todas os dados.
 * @param estavel_max variavel utilizada para
 *  decidir se sera executado ou nao um bloco
 *  de codigo que faz o emparelhamento estavel
 *  maximo.
 * @return void 
*/
void Emparelha(Grafo& grafo, bool estavel_max){
    // Loop para percorrer todos os professores
    for(auto professor = grafo.professores.begin() ; professor != grafo.professores.end() ; professor++ ){
        // Flag utilizada para parar o loop de escolas de preferencia das escolas do professor
        bool flag = true;

        if(professor->escola_ocupada.empty()) {
            for(auto escola_preferencia = professor->escola_pref.begin(); escola_preferencia != professor->escola_pref.end() && flag ; escola_preferencia++){
                // Usa o metodo find_if para procurar a escola que esta sendo analisada
                auto vagas_escola = find_if(grafo.escolas.begin(), grafo.escolas.end(), find_vagas(*escola_preferencia));

                // Percorre as vagas da escola. Primeiro verifica se alguma das vagas eh estritamente igual ao que a vaga esta
                // exigindo e se a vaga esta livre. Se as condicoes forem aceitas ele aloca o professor na vaga. Se o professor
                // nao for alocado, ele vai para o segundo laco, verificando se a habilitacao da vaga eh menor ou igual a do
                // professor.
                for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() ; vaga_escola++){
                    if(vaga_escola->habilitacao == professor->habilitacao && !vaga_escola->ocupada){
                        vaga_escola->codigo_professor = professor->cod_professor;
                        vaga_escola->habilitacao_professor = professor->habilitacao;
                        vaga_escola->ocupada = true;
                        professor->escola_ocupada = vagas_escola->cod_escola;

                        flag = false;
                        break;
                    }
                }
                for(auto vaga_escola = vagas_escola->vagas.begin() ;  vaga_escola != vagas_escola->vagas.end() && flag; vaga_escola++){
                    if(vaga_escola->habilitacao <= professor->habilitacao && !vaga_escola->ocupada){
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
    
    // Faz o emparelhamento maximo estavel alocando os professores que sobraram.
    if(estavel_max){
        for(auto escola = grafo.escolas.begin() ; escola != grafo.escolas.end() ; escola++){
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
    
    ImprimeResultado(grafo);
}