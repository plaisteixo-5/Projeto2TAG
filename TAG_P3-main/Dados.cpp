#include "Dados.h"

vector<S_Professor> L_Professor;
vector<S_Escola> L_Escolas;

void Coloca_global(vector<S_Professor> Lista_Professor, vector<S_Escola> Lista_Escolas){
	for(int i = 0; i < Lista_Professor.size(); i++)
		L_Professor.push_back(Lista_Professor[i]);
	for(int i = 0; i < Lista_Escolas.size(); i++)
		L_Escolas.push_back(Lista_Escolas[i]);
}

void Preenche_Vetor_Vagas(vector<S_Vagas_Escola> *Lista_Vagas_Escola, vector<S_Escola> L_Escolas){
	int j = 0;
	S_Vagas_Escola Atual;
	for(int i = 0; i < L_Escolas.size(); i++){
		for(int j = 0; j < L_Escolas[i].preferencia.size(); j++){
			Atual.codigo_escola = L_Escolas[i].codigo;
			Atual.habilidade_pretendida = L_Escolas[i].preferencia[j];
			Lista_Vagas_Escola->push_back(Atual);
		}
	}
}

void Atribuir_Professor_livre(){ // Define todos os professores livres
	for(int i = 0; i < L_Professor.size(); i++){
		L_Professor[i].Livre = true;
		L_Professor[i].Onde_trabalha = -1;
	}
}

void Atribuir_Escola_livre(){ // Define todas as escolas livres
	for(int i = 0; i < L_Escolas.size(); i++){
		L_Escolas[i].Vaga1_ocupado = false;
		L_Escolas[i].Vaga2_ocupado = false;
		L_Escolas[i].Professor1 = -2;
		L_Escolas[i].Professor2 = -2;
	}
}

int Substituir_Professor(int codigo_professor){
	int professor_antigo;
	for(int i = 0; i < L_Professor[codigo_professor].escolas.size(); i++){ // Percorre pelas escolas de preferencia
		int cod = (L_Professor[codigo_professor].escolas[i])-1;
		if(L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga1 || (L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga2 && L_Escolas[cod].Hab_vaga2 != -1)){ //Qualificado pra vaga 1 ou 2
			if(L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga1 && L_Escolas[cod].Tem_margem1 == true){
				// cout << "aqui"  << "\t";
				L_Professor[codigo_professor].Livre = false;
				L_Professor[codigo_professor].Onde_trabalha = L_Escolas[cod].codigo;
				L_Escolas[cod].Vaga1_ocupado = true;
				if(L_Professor[codigo_professor].habilitacao > L_Escolas[cod].Hab_vaga1)
					L_Escolas[cod].Tem_margem1 = true;
				else if(L_Professor[codigo_professor].habilitacao == L_Escolas[cod].Hab_vaga1)
					L_Escolas[cod].Tem_margem1 = false;
				professor_antigo = L_Escolas[cod].Professor1;	// Quem estava na vaga
				L_Escolas[cod].Professor1 = L_Professor[codigo_professor].codigo;
				return professor_antigo;
			}
			if((L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga2 && L_Escolas[cod].Hab_vaga2 != -1) && L_Escolas[cod].Tem_margem2 == true){
				// cout << "esse"  << "\t";
				L_Professor[codigo_professor].Livre = false;
				L_Professor[codigo_professor].Onde_trabalha = L_Escolas[cod].codigo;
				L_Escolas[cod].Vaga2_ocupado = true;
				if(L_Professor[codigo_professor].habilitacao > L_Escolas[cod].Hab_vaga2)
					L_Escolas[cod].Tem_margem2 = true;
				else if(L_Professor[codigo_professor].habilitacao == L_Escolas[cod].Hab_vaga2)
					L_Escolas[cod].Tem_margem2 = false;
				professor_antigo = L_Escolas[cod].Professor2;	// Quem estava na vaga
				L_Escolas[cod].Professor2 = L_Professor[codigo_professor].codigo;
				return professor_antigo;
			}
		}
	}
	return -1;
}

bool Inserir_Professor_Escola_Vazia(int codigo_professor){
	for(int i = 0; i < L_Professor[codigo_professor].escolas.size(); i++){ // Percorre pelas escolas de preferencia
		int cod = (L_Professor[codigo_professor].escolas[i])-1;
		if(L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga1 || (L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga2 && L_Escolas[cod].Hab_vaga2 != -1)){ //Qualificado pra vaga 1 ou 2
			if(L_Escolas[cod].Vaga1_ocupado == false && L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga1){ // Vaga disponivel
				// cout << "\t1" << endl;
				// cout << "1- \t" << L_Escolas[cod].codigo << endl;
				/*Inserir_professor*/
				L_Professor[codigo_professor].Livre = false;
				L_Professor[codigo_professor].Onde_trabalha = L_Escolas[cod].codigo;
				L_Escolas[cod].Vaga1_ocupado = true;
				L_Escolas[cod].Professor1 = L_Professor[codigo_professor].codigo;
				if(L_Professor[codigo_professor].habilitacao > L_Escolas[cod].Hab_vaga1)
					L_Escolas[cod].Tem_margem1 = true;
				else if(L_Professor[codigo_professor].habilitacao == L_Escolas[cod].Hab_vaga1)
					L_Escolas[cod].Tem_margem1 = false;
				return true;
			}
			else if(L_Escolas[cod].Vaga2_ocupado == false && (L_Professor[codigo_professor].habilitacao >= L_Escolas[cod].Hab_vaga2 && L_Escolas[cod].Hab_vaga2 != -1)){ // Vaga disponivel
				// cout << "\t2" << endl;
				// cout << "2- \t" << L_Escolas[cod].codigo << " " << L_Escolas[cod].Hab_vaga2 << endl;
				/*Inserir_professor*/
				L_Professor[codigo_professor].Livre = false;
				L_Professor[codigo_professor].Onde_trabalha = L_Escolas[cod].codigo;
				L_Escolas[cod].Vaga2_ocupado = true;
				L_Escolas[cod].Professor2 = L_Professor[codigo_professor].codigo;
				if(L_Professor[codigo_professor].habilitacao > L_Escolas[cod].Hab_vaga2)
					L_Escolas[cod].Tem_margem1 = true;
				else if(L_Professor[codigo_professor].habilitacao == L_Escolas[cod].Hab_vaga2)
					L_Escolas[cod].Tem_margem1 = false;
				return true;
			}
		}
	}
	return false;
}

void Emparelhamento_estavel_para_professor(){
	queue<S_Professor> Fila_professor;													// Fila de professores vazia

	Atribuir_Professor_livre();															// Define todos os professores livres
	Atribuir_Escola_livre();															// Define todas as escolas livres

	for(int i = 0; i < L_Professor.size(); i++){										// Coloca todos os professores na fila
		S_Professor Professor_atual = L_Professor[i];								
		
		if(Professor_atual.Livre == true)												// Se o professor está livre, então ele entra na fila
			Fila_professor.push(Professor_atual);
	}
	
		cout << "saida" << endl;
	int contador = 0;
	while(Fila_professor.empty() != true){												// Enquanto a fila não está vazia
		S_Professor professor_atual = Fila_professor.front(); 							// Pega o professor na frente da fila
		Fila_professor.pop();															// Remove ele da fila
		
		bool Foi_acolado = Inserir_Professor_Escola_Vazia(professor_atual.codigo-1);

		if(Foi_acolado == false){
			int Quem_saiu = Substituir_Professor(professor_atual.codigo-1);
			if(Quem_saiu != -1 && contador < 20){
				S_Professor Professor_atual = L_Professor[Quem_saiu-1];

				Fila_professor.push(Professor_atual);
				contador++;
			}
		}
	}

	cout << "Professores:" << endl;
	for(int i = 0; i < L_Professor.size(); i++){
		cout << L_Professor[i].codigo << " - " << L_Professor[i].Onde_trabalha << endl;
	}
	
	cout << "\nEscolas:" << endl;
	for(int i = 0; i < L_Escolas.size(); i++){
		cout << L_Escolas[i].codigo << " - " << L_Escolas[i].Professor1 << " ";
		if(L_Escolas[i].Hab_vaga2 != -1)
			cout << L_Escolas[i].Professor2 << endl;
		else
			cout << endl;
	}
	
}
