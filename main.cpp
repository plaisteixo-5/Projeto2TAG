#include "Functions.cpp"

using namespace std;

void menu(Grafo& grafo){
    int op;

    do{
        system(clear);

        cout << endl << "\t\tMENU" << endl << endl;
        cout << "(1) - Imprimir lista de professores" << endl;
        cout << "(2) - Imprimir lista de escolas" << endl;
        cout << "(3) - Imprimir emparelhamento estável" << endl;
        cout << "(4) - Imprimir emparelhamento estável e máximo" << endl;
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
                break;
            case 3:
                break;
            case 4:
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

    // Emparelha(grafo, false);

    // ImprimeDisponivel(grafo);

    return 0;
}
