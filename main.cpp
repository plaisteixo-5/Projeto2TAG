#include "Functions.cpp"

using namespace std;

void menu(Grafo& grafo){
    int op;

    do{
        system(clear);

        cout << endl << "\t\tMENU" << endl << endl;
        cout << "(1) - Imprimir lista de professores" << endl;
        cout << "(2) - Imprimir lista de escolas" << endl;
        cout << "(3) - Imprimir emparelhamento estavel" << endl;
        cout << "(4) - Imprimir emparelhamento estavel e maximo" << endl;
        cout << "(5) - Resetar informacoes" << endl;
        cout << "(0) - Sair" << endl;

        cin >> op;
    
        switch (op){
            case 0:
                system(clear);
                break;
            case 1:
                system(clear);
                ImprimeProfessores(grafo);

                getchar();
                getchar();
                break;
            case 2:
                system(clear);
                ImprimeEscola(grafo);

                getchar();
                getchar();
                break;
            case 3:
                system(clear);
                Emparelha(grafo, false);  
                
                getchar();
                getchar();
                break;
            case 4:
                system(clear);
                Emparelha(grafo, true); 
                
                getchar();
                getchar();
                break;
            case 5:
                system(clear);
                ResetaGrafo(grafo);
                cout << "As informacoes foram resetadas" << endl;
                cout << "Pressione alguma tecla para continuar...";

                getchar();
                getchar();
                break;
            default:
                break;
        }
    }while(op != 0);
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

    menu(grafo);

    return 0;
}
