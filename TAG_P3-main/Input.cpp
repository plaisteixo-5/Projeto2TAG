#include "Input.h"

S_Professor Fornece_struct_professor(char linha[]){
    S_Professor Atual;
    
    //Para usar Atoi, precisa ser uma string com pelo menos 2 posicoes 
    char Codigo_professor[2];
    char Habilitacao[2];
    char cod_escola[2];

    /*Codigo*/
    Codigo_professor[0] = linha[2];
    Codigo_professor[1] = linha[3];
    if(linha[4] == '0')
        Codigo_professor[2] = linha[4];
    Atual.codigo = atoi(Codigo_professor);
    
    /*Habilitacao*/
    if(linha[3] == ','){
        Habilitacao[0] = linha[5];
        Habilitacao[1] = 0;
    }
    else if(linha[4] == ','){
        Habilitacao[0] = linha[6];
        Habilitacao[1] = 0;
    }
    else if(linha[5] == ','){
        Habilitacao[0] = linha[7];
        Habilitacao[1] = 0;
    }
    Atual.habilitacao = atoi(Habilitacao); 

    /*Escolas*/
    for(int i = 0; i < strlen(linha); i++){
        if(linha[i] == 'E'){
            cod_escola[0] = linha[i+1];
            cod_escola[1] = linha[i+2];
            Atual.escolas.push_back(atoi(cod_escola));
        }
    }

    Atual.Livre = true;
    return Atual;
}

S_Escola Fornece_struct_escola(char linha[]){
    S_Escola Atual;
    
    //Para usar Atoi, precisa ser uma string com pelo menos 2 posicoes 
    char Codigo_escola[2];
    char Preferencia[2];

    /*Codigo*/
    Codigo_escola[0] = linha[2];
    Codigo_escola[1] = linha[3];
    Atual.codigo = atoi(Codigo_escola);
    
    /*Escolas*/
    int k = 0;
    for(int i = 0; i < strlen(linha); i++){
        if(linha[i] == '(' && i != 0){
            Preferencia[0] = linha[i+1];
            Preferencia[1] = linha[i+2];
            int Num = atoi(Preferencia);
            Atual.preferencia.push_back(Num);
            if(k == 0){
                Atual.Hab_vaga1 = Num;
                Atual.Hab_vaga2 = -1;
            }
            else if(k == 1)
                Atual.Hab_vaga2 = Num;
            k++;
        }
    }
    Atual.Vaga1_ocupado = false;
    Atual.Vaga2_ocupado = false;
    return Atual;
}

void Pula_linha(FILE* fd){
    while(fgetc(fd) != '\n');
}

void Receber_dados(vector<S_Professor> *Lista_Professores, vector<S_Escola> *Lista_Escolas){
    FILE* fd;                                                               //Cria o ponteiro do arquivo;

    char file[] = "entradaProj3TAG.txt";                                             
    fd = fopen(file, "r");                                                  //Abre o arquivo Disciplinas.txt;

    if(fd == NULL){                                                         //Verifica se o arquivo abriu com sucesso;
        cout << "Erro abrir arquivo" << endl;
        exit(1);
    }

    while(fgetc(fd) == '/'){                                                //Pula cabecalho
        Pula_linha(fd);
    }
    Pula_linha(fd);
    
    /*Formato: (Codigo Professor, habitacoes), (escola em ordem decrescente de prioridade)*/
    char linha[50];
    
    while(fgetc(fd) == '('){
        fseek(fd, -1, SEEK_CUR);
        fgets(linha, 100, fd);
        Lista_Professores->push_back(Fornece_struct_professor(linha));
    }
    Pula_linha(fd);
    while(fgetc(fd) == '/'){                                                //Pula cabecalho
        Pula_linha(fd);
    }
    fseek(fd, -1, SEEK_CUR);

    while(fgetc(fd) == '('){
        fseek(fd, -1, SEEK_CUR);
        fgets(linha, 100, fd);
        Lista_Escolas->push_back(Fornece_struct_escola(linha));
    }

    fclose(fd);
}
