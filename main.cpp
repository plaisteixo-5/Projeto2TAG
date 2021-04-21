#include "iostream"
#include "fstream"
#include "string"
#include "algorithm"

using namespace std;

int main(){

    ifstream file("entradaProj2TAG.txt");

    string input_file;
    int flag = 0;

    while(getline(file, input_file)){
        if(input_file[0] == '/') {
            file.ignore(2048, '\n');
            flag++;
        }
        else {
            if(flag == 2){
                replace(input_file.begin(), input_file.end(), ':', ' ');
                input_file.erase(remove(input_file.begin(), input_file.end(), '('), input_file.end());
                input_file.erase(remove(input_file.begin(), input_file.end(), ')'), input_file.end());
            } else {
                input_file.erase(remove(input_file.begin(), input_file.end(), '('), input_file.end());
                input_file.erase(remove(input_file.begin(), input_file.end(), ')'), input_file.end());
                input_file.erase(remove(input_file.begin(), input_file.end(), ','), input_file.end());
                input_file.erase(remove(input_file.begin(), input_file.end(), ':'), input_file.end());
            }
            cout << input_file << "\n";
        }
    }
    file.close();

    return 0;
}