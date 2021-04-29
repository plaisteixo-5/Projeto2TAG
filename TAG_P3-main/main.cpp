#include "Input.h"
#include "Output.h"
#include "Dados.h"

void Menu(vector<S_Professor> Lista_Professores, vector<S_Escola> Lista_Escolas, vector<S_Vagas_Escola> Lista_Vagas_Escola){
    int op = -1;

    while(op != 0){
        system(CLEAR);

        cout << "\t==== MENU ====" << endl << endl;
        cout << "(1) Lista de professores." << endl;
        cout << "(2) Lista de escolas." << endl;
        cout << "(3) Lista de escolas em função das vagas." << endl;
        cout << "(0) Sair." << endl;
        
        cout << "Digite sua opcao: ";
        cin >> op;

        switch(op){

            case 1:
                system(CLEAR);

                Imprimir_lista_professores(Lista_Professores);

                printf("\nAperte ENTER para continuar\n");
                getchar();
                getchar();
                break;

            case 2:
                system(CLEAR);

                Imprimir_lista_escolas(Lista_Escolas);

                printf("\nAperte ENTER para continuar\n");
                getchar();
                getchar();
                break;

            case 3:

                system(CLEAR);

                Imprimir_lista_vagas_escola(Lista_Vagas_Escola);

                printf("\nAperte ENTER para continuar\n");
                getchar();
                getchar();
                break;

            case 4:
                system(CLEAR);

                Emparelhamento_estavel_para_professor();

                printf("\nAperte ENTER para continuar\n");
                getchar();
                getchar();
                break;

            case 5:
                system(CLEAR);

                

                printf("\nAperte ENTER para continuar\n");
                getchar();
                getchar();
                break;

            default:
                break;
        }

    }
}

int main(){
    vector<S_Professor> Lista_Professores;
    vector<S_Escola> Lista_Escolas;
    vector<S_Vagas_Escola> Lista_Vagas_Escola;

    cout << " NOVO" << endl;
    Receber_dados(&Lista_Professores, &Lista_Escolas);
    Preenche_Vetor_Vagas(&Lista_Vagas_Escola, Lista_Escolas);

    Coloca_global(Lista_Professores, Lista_Escolas);
    
    Menu(Lista_Professores, Lista_Escolas, Lista_Vagas_Escola);
    
    // Emparelhamento_estavel_para_professor(Lista_Professores, Lista_Escolas);
    // Imprimir_Escola_Professor(Lista_Professores, Lista_Escolas);

    return 0;
}
