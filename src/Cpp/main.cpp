
#include <iostream>
#include <string>
#include <windows.h>

#include "Data.h"
#include "Hora.h"
#include "Cadeia.h"
#include "Cliente.h"
#include "Farmacia.h"
#include "Funcionario.h"
#include "ItemVenda.h"
#include "Medicamento.h"
#include "MedicamentoPassReceita.h"
#include "Outro.h"
#include "Pessoa.h"
#include "Produto.h"
#include "Receita.h"
#include "StockItem.h"
#include "Venda.h"
#include "import_export.h"

using namespace std;

Cadeia* cadeia;
Funcionario* func;

template<class dataType>
void inputHandler(dataType &input){

	while(!(cin>>input))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Input invalido. Tente novamente: ";
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void exportarFicheiros()
{
	exportarProdutos();
	cadeia->exportarCadeia();
}

int importarFicheiros(string nomeFicheiro, string nome)
{
	importarProdutos();
	try{
		cadeia = new Cadeia(nomeFicheiro,nome);
	} catch (CadeiaInexistente e) {
		cout << "Nao existe um ficheiro com esse nome\n";
		return 1;
	}
	catch (const std::out_of_range &) {
		cout << "Ficheiro inválido.\n";
		return 1;
	}
	return 0;
}

void displayLogo()
{
	cout << " _________________________________________________________ " << endl;
	cout << "| ______ _____ _   _______  __                            |" << endl;
	cout << "| |  ___|  ___| | | | ___ \\/ _|                           |" << endl;
	cout << "| | |_  | |__ | | | | |_/ / |_ __ _ _ __ _ __ ___   __ _  |" << endl;
	cout << "| |  _| |  __|| | | |  __/|  _/ _` | '__| '_ ` _ \\ / _` | |" << endl;
	cout << "| | |   | |___| |_| | |   | || (_| | |  | | | | | | (_| | |" << endl;
	cout << "| \\_|   \\____/ \\___/\\_|   |_| \\__,_|_|  |_| |_| |_|\\__,_| |" << endl;
	cout << "|_________________________________________________________|" << endl;
}

void login()
{
	string nome, password;
	bool loggedIn = false;
	while(!loggedIn)
	{
		cout << "Utilizador: ";
		getline(cin, nome);
		cout << "Password: ";
		getline(cin, password);
		try{
			func = cadeia->getFuncionarioComNome(nome);
		} catch (NaoExistePessoa e){
			cout << "Credenciais invalidas. Tente novamente.\n";
			continue;
		}
		if(func->getPassword() != password)
		{
			cout << "Credenciais invalidas. Tente novamente.\n";
			continue;
		}
		loggedIn = true;
	}
}

void criarFichaCliente()
{
	string nome, morada, distrito;
	unsigned int noContribuinte;
	cout << "Introduza o nome do cliente: ";
	getline(cin, nome);
	cout << "Introduza a morada do cliente: ";
	getline(cin, morada);
	cout << "Introduza o distrito do cliente: ";
	getline(cin, distrito);
	cout << "Introduza o numero de contribuinte do cliente: ";
	inputHandler(noContribuinte);
	Cliente* cl = new Cliente(nome, morada, noContribuinte, distrito);
	cadeia->addCliente(cl);
	cout << "Ficha de cliente criada com sucesso.\n";
}

void apagarFichaCliente()
{
	unsigned int noContribuinte;
	string nome, distrito;
	cout << "Introduza o nome do cliente: ";
	getline(cin, nome);
	cout << "Introduza o distrito do cliente: ";
	getline(cin, distrito);
	cout << "Introduza o numero de contribuinte do cliente: ";
	inputHandler(noContribuinte);
	try {
		cadeia->rmCliente(nome, noContribuinte, distrito);
	} catch(NaoExistePessoa e) {
		cout << "Nao existe nenhuma ficha de cliente com numero de contribuinte " << e.getContribuinte() << " associado.\n";
		return;
	}
	cout << "Ficha de cliente apagada com sucesso." << endl;
}

void verHistorialCliente()
{
	unsigned int noContribuinte;
	cout << "Introduza o numero de contribuinte do cliente: ";
	inputHandler(noContribuinte);
	cout << endl;
	Cliente* cl;
	try {
		cl = cadeia->getClienteComNoContribuinte(noContribuinte);
	} catch (NaoExistePessoa e) {
		cout << "Nao existe nenhuma ficha de cliente com numero de contribuinte " << e.getContribuinte() << " associado.\n";
		return;
	}
	vector<Venda*> historial = cl->getHistorial();
	for (unsigned int i = 0; i < historial.size(); i++)
	{
		cout << *historial[i];
	}
	cout << endl;
}

void contratarFuncionario(){

	string nome, morada, password, nomeFarm, distrito;
	unsigned int noContribuinte, salario;
	Farmacia* farm;
	cout << "Introduza o nome da farmacia: ";
	getline(cin, nomeFarm);
	try {
		farm = cadeia->getFarmaciaComNome(nomeFarm);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe nenhuma farmacia com nome " << e.getNome() << " associado.\n";
		return;
	}

	cout << "Introduza o nome do Funcionario: ";
	getline(cin, nome);
	cout << "Introduza a morada do Funcionario: ";
	getline(cin, morada);
	cout << "Introduza o distrito do Funcionario: ";
	getline(cin, distrito);
	cout << "Introduza o numero de contribuinte do Funcionario: ";
	inputHandler(noContribuinte);
	cout << "Introduza a password do Funcionario: ";
	getline(cin, password);
	cout << "Introduza o salario do Funcionario: ";
	inputHandler(salario);
	Funcionario* newFunc = new Funcionario(nome, morada, noContribuinte, distrito, salario, password);
	newFunc->setFarmacia(farm);
	cadeia->addFuncionario(newFunc);

	cout << "Funcionario contratado.\n";
}

void despedirFuncionario(){
	unsigned int noContribuinte;
	Funcionario* newFunc;
	Farmacia* newFarm;
	cout << "Introduza o numero de contribuinte do Funcionario: ";
	inputHandler(noContribuinte);
	try {
		newFunc = cadeia->getFuncionarioComNoContribuinte(noContribuinte);
	} catch(NaoExistePessoa e) {
		cout << "Nao existe nenhum Funcionario com numero de contribuinte " << e.getContribuinte() << " associado.\n";
		return;
	}
	newFarm = newFunc->getFarmacia();
	if(newFunc->getCargo() == "Gerente"){
		newFarm->setGerente("Nenhum");
	}
	newFunc->setFarmacia(NULL);
	newFunc->setCargo("Nenhum");
	cout << "Funcionario despedido com sucesso." << endl;
}

void transferirFuncionario(){
	unsigned int noContribuinte;
	Funcionario* newFunc;
	cout << "Introduza o numero de contribuinte do Funcionario: ";
	inputHandler(noContribuinte);
	try {
		newFunc = cadeia->getFuncionarioComNoContribuinte(noContribuinte);
	} catch(NaoExistePessoa e) {
		cout << "Nao existe nenhum Funcionario com numero de contribuinte " << e.getContribuinte() << " associado.\n";
		return;
	}

	string nomeFarm;
	Farmacia* farm;
	cout << "Introduza o nome da farmacia: ";
	getline(cin, nomeFarm);
	try {
		farm = cadeia->getFarmaciaComNome(nomeFarm);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe nenhuma farmacia com nome " << e.getNome() << " associado.\n";
		return;
	}

	if(newFunc->getCargo() == "Gerente"){
		newFunc->getFarmacia()->setGerente("Nenhum");
		newFunc->setCargo("Funcionario");
	}
	newFunc->setFarmacia(farm);


	cout << "Funcionario transferido com sucesso." << endl;

}

void promoverFuncionario(){

	unsigned int noContribuinte;
	Funcionario* newFunc;
	cout << "Introduza o numero de contribuinte do Funcionario: ";
	inputHandler(noContribuinte);
	try {
		newFunc = cadeia->getFuncionarioComNoContribuinte(noContribuinte);
	} catch(NaoExistePessoa e) {
		cout << "Nao existe nenhum Funcionario com numero de contribuinte " << e.getContribuinte() << " associado.\n";
		return;
	}

	Farmacia* farm = newFunc->getFarmacia();
	string exGerenteNome = farm->getGerente();

	if(exGerenteNome != "Nenhum"){
		Funcionario* exGerente = cadeia->getFuncionarioComNome(exGerenteNome);
		exGerente->setCargo("Funcionario");
	}

	newFunc->setCargo("Gerente");
	farm->setGerente(newFunc->getNome());
	cout << "Funcionario promovido com sucesso.\n" << endl;
}

void mostrarFuncionarios(){
	cout << "Funcionarios da Cadeia:" << endl << endl;
	vector<Funcionario*> funcs = cadeia->getFuncionarios();
	for(unsigned int i = 0; i < funcs.size(); i++){
		cout << *funcs.at(i) << endl;
	}
	cout << endl;
}

void mostrarClientes(){
	cout << "Clientes da Cadeia:" << endl << endl;
	vector<Cliente*> cli = cadeia->getClientes();
	for(unsigned int i = 0; i < cli.size(); i++){
		cout << *cli.at(i) << endl;
	}
	cout << endl;
}


void gestaoClientes()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Criar ficha de cliente\n";
		cout << "2. Apagar ficha de cliente\n";
		cout << "3. Ver historial do cliente\n";
		cout << "4. Mostrar clientes\n";
		cout << "5. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			criarFichaCliente();
			break;
		case 2:
			apagarFichaCliente();
			break;
		case 3:
			verHistorialCliente();
			break;
		case 4:
			mostrarClientes();
			break;
		case 5:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void gestaoFuncionarios()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Contratar Funcionario\n";
		cout << "2. Despedir Funcionario\n";
		cout << "3. Transferir Funcionario\n";
		cout << "4. Promover Funcionario\n";
		cout << "5. Mostrar Funcionarios\n";
		cout << "6. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			contratarFuncionario();
			break;
		case 2:
			despedirFuncionario();
			break;
		case 3:
			transferirFuncionario();
			break;
		case 4:
			promoverFuncionario();
			break;
		case 5:
			mostrarFuncionarios();
			break;
		case 6:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void adicionarProdutoReceita(Receita* rec){

	string codigo;
	Produto* prod;
	cout << "Introduza o codigo do produto: ";
	getline(cin, codigo);
	try {
		prod = prod->getProdutoComCodigo(codigo);

		try {
			rec->addProduto(prod);
		} catch(NaoPassivelAReceita e) {
			cout << "O produto com nome " << e.getNomeProduto() << " (codigo " << prod->getCodigo() << ") nao e passivel a receita. \n";
			return;
		}

	} catch(ProdutoInexistente e) {
		cout << "Nao existe nenhum Produto com codigo " << e.getCodigo() << " associado.\n";
		return;
	}

	cout << "Adicionado " << prod->getNome() << " a receita " << rec->getNoReceita() << "\n";

}

void criarReceita(){
	string nome, morada, nomeMed;
	unsigned int noContribuinte;
	cout << "Introduza o numero de contribuinte do cliente: ";
	inputHandler(noContribuinte);
	Cliente* cl;
	try{
		cl = cadeia->getClienteComNoContribuinte(noContribuinte);
	} catch (NaoExistePessoa e) {
		cout << "Não existe cliente com no. contribuinte " << e.getContribuinte() << endl;
		return;
	}

	cout << "Introduza o nome do medico: ";
	getline(cin, nomeMed);

	Receita* rec = new Receita(cl, nomeMed);

	cout << "Criada receita com codigo " << rec->getNoReceita() << "\n";

	cout << "Deseja adicionar produtos a receita?\n";

	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		cout << "1. Adicionar Produtos\n";
		cout << "2. Terminar a Receita\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			adicionarProdutoReceita(rec);
			break;
		case 2:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
	cout << "Criada receita com numero " << rec->getNoReceita() <<".\n";
}

void gestaoReceitas()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Criar Receita\n";
		cout << "2. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			criarReceita();
			break;
		case 2:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void comprarFarmacia(){

	string nome, morada;
	cout << "Introduza o nome da Farmacia: ";
	getline(cin, nome);
	cout << "Introduza a morada da Farmacia: ";
	getline(cin, morada);

	Farmacia* farm = new Farmacia(nome,morada);
	cadeia->addFarmacia(farm);

	cout << "Farmacia comprada com sucesso.\n";
}

void venderFarmacia(){
	Farmacia* farm;

	string nome;
	cout << "Introduza o nome da Farmacia: ";
	getline(cin, nome);

	try {
		farm = cadeia->getFarmaciaComNome(nome);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe farmacia com nome " << e.getNome() << "\n";
		return;
	}

	vector<Funcionario* > funcs;
	funcs = cadeia->getFuncionariosDaFarmacia(farm);

	for(unsigned int i=0; i < funcs.size(); i++){
		funcs.at(i)->setFarmacia(NULL);
		funcs.at(i)->setCargo("Funcionario");
	}

	try {
		cadeia->rmFarmacia(nome);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe farmacia com nome " << e.getNome() << "\n";
		return;
	}

	cout << "Farmacia comprada com sucesso.\n";

}

void mostrarFuncionariosDaFarmacia(){

	string nome, morada;
	cout << "Introduza o nome da Farmacia: ";
	getline(cin, nome);

	Farmacia * farm = cadeia->getFarmaciaComNome(nome);
	vector<Funcionario*> funcs = cadeia->getFuncionariosDaFarmacia(farm);
	cout << endl << "Funcionarios da farmacia " << nome << ":" << endl;
	for(unsigned int i = 0; i < funcs.size(); i++){
		cout << *funcs.at(i) << endl;
	}

	cout << endl;
}

void gestaoFarmacias()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Comprar farmacia\n";
		cout << "2. Vender farmacia\n";
		cout << "3. Mostrar funcionarios da farmacia\n";
		cout << "4. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			comprarFarmacia();
			break;
		case 2:
			venderFarmacia();
			break;
		case 3:
			mostrarFuncionariosDaFarmacia();
			break;
		case 4:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void adicionarMedicamento(){
	Produto* prod;
	string nome,descricao,passReceita,adqSemReceita;
	float preco;
	unsigned int taxaDesc;
	bool semReceita;

	cout << "Introduza o nome do medicamento: ";
	getline(cin, nome);

	try{
		prod = prod->getProdutoComNome(nome);
	}catch(ProdutoInexistente e){

		cout << "Introduza o preco do medicamento: ";
		inputHandler(preco);
		cout << "Introduza a descricao do medicamento: ";
		getline(cin, descricao);
		cout << "O medicamento e passivel a receita?(y/n)";
		do{
			getline(cin, passReceita);
		}while(passReceita != "y" && passReceita != "n");

		if(passReceita == "y"){
			cout << "O medicamento e adquirivel sem receita?(y/n)";
			do{
				getline(cin, adqSemReceita);
			}while(adqSemReceita != "y" && adqSemReceita != "n");

			if(adqSemReceita == "y"){
				semReceita = true;
			}
			else{
				semReceita = false;
			}

			cout << "Introduza a taxa de desconto do medicamento: ";
			inputHandler(taxaDesc);

			MedicamentoPassReceita* medP = new MedicamentoPassReceita(nome,preco,descricao,taxaDesc,semReceita);

			cout << "Medicamento " << medP->getNome() << " adicionado a lista de produtos com codigo " << medP->getCodigo() << "\n";
		}
		else{
			Medicamento* med = new Medicamento(nome,preco,descricao);
			cout << "Medicamento " << med->getNome() << " adicionado a lista de produtos com codigo " << med->getCodigo() <<"\n";
		}
		return;
	}

	cout << "Ja existe um produto com nome " << nome << "\n";
}

void adicionarOutro(){

	Produto* prod;
	string nome,descricao;
	float preco;

	cout << "Introduza o nome do produto: ";
	getline(cin, nome);

	try{
		prod = prod->getProdutoComNome(nome);
	}catch(ProdutoInexistente e){

		cout << "Introduza o preco do produto: ";
		inputHandler(preco);
		cout << "Introduza a descricao do produto: ";
		getline(cin, descricao);

		Outro* outro = new Outro(nome,preco,descricao);
		cout << "Medicamento " << outro->getNome() << " adicionado a lista de produtos com codigo " << outro->getCodigo() <<"\n";
		return;
	}

	cout << "Ja existe um produto com nome " << nome << "\n";

}

void adicionarProduto(){

	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Adicionar Medicamento\n";
		cout << "2. Adicionar Outro\n";
		cout << "3. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			adicionarMedicamento();
			break;
		case 2:
			adicionarOutro();
			reabrirMenu = false;
			break;
		case 3:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}

}

void removerProduto(){
	string codigo;

	cout << "Introduza o codigo do produto: ";
	getline(cin, codigo);

	try{
		Produto::removeProdutoComCodigo(codigo);
	}catch(ProdutoInexistente e){
		cout << "Nao existe produto com codigo  " << e.getCodigo() << "\n";
		return;
	}
	cout << "Produto com codigo " << codigo << " removido com sucesso.\n";

}

void gestaoProdutos()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Adicionar Produto\n";
		cout << "2. Remover Produto\n";
		cout << "3. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			adicionarProduto();
			break;
		case 2:
			removerProduto();
			reabrirMenu = false;
			break;
		case 3:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void criarVenda(){
	Cliente* client;
	Venda* venda;
	Farmacia* farm;
	string nomeFarm;
	cout << "Introduza o nome da farmacia que quer gerir: ";
	inputHandler(nomeFarm);
	try{
		farm = cadeia->getFarmaciaComNome(nomeFarm);
	} catch (NaoExisteFarmacia) {
		cout << "Farmácia Inexistente.";
		return;
	}
	string  criarFicha;
	unsigned int noContribuinte;
	cout << "Introduza o numero de contribuinte do cliente: ";
	inputHandler(noContribuinte);
	string nomeFunc = func->getNome();
	venda = new Venda(nomeFunc);

	try {
		client = cadeia->getClienteComNoContribuinte(noContribuinte);
	} catch(NaoExistePessoa e) {

		cout << "Nao existe ficha para o cliente com numero de contribuinte " << noContribuinte << ". Deseja criar uma?(y/n)";

		do{
			getline(cin, criarFicha);
		}while(criarFicha != "y" && criarFicha != "n");

		if(criarFicha == "y"){
			string nome, morada, distrito;
			cout << "Introduza o nome do cliente: ";
			getline(cin, nome);
			cout << "Introduza a morada do cliente: ";
			getline(cin, morada);
			cout << "Introduza o distrito do cliente: ";
			getline(cin, distrito);
			client = new Cliente(nome, morada, noContribuinte, distrito);
			cadeia->addCliente(client);
			cout << "Ficha de cliente criada com sucesso.\n";
		}
		else{
			cout << "Impossivel criar uma venda para um cliente sem ficha.\n";
			return;
		}
	}
	string temReceita;

	cout << "Possui alguma receita que pretenda utilizar nesta compra?(y/n)";

	do{
		getline(cin, temReceita);
	}while(temReceita != "y" && temReceita != "n");

	if(temReceita == "y"){
		string numReceita,codigo,maisItem;
		Produto* prod;
		bool maisItens = true;
		unsigned int quant;

		cout << "Introduza o numero da receita: ";
		getline(cin,numReceita);

		try {
			Receita::getReceitaComNumero(numReceita);
			venda->addReceita(numReceita);
		} catch(ReceitaInexistente e) {
			cout << "Nao existe receita com numero " << e.getNoReceita() << ".\n";
			return;
		}

		do{
			cout << "Introduza o codigo do produto: ";
			getline(cin, codigo);

			try{
				prod = Produto::getProdutoComCodigo(codigo);
			}catch(ProdutoInexistente e){
				cout << "Nao existe produto com codigo  " << e.getCodigo() << "\n";
				continue;
			}

			cout << "Introduza o numero de produtos que pretende comprar: ";
			inputHandler(quant);

			try{
			farm->vendeItem(prod, quant);
			} catch (StockInexistente) {
				cout << "Nao temos esse produto em stock\n";
				cout << "Deseja adicionar mais itens a venda?(y/n)";
				do{
					getline(cin, maisItem);
				}while(maisItem != "y" && maisItem != "n");
				if(maisItem == "y"){
					continue;
				}
				else{
					break;
				}
			} catch (StockInsuficiente)
			{
				cout << "Deseja adicionar mais itens a venda?(y/n)";
				do{
					getline(cin, maisItem);
				}while(maisItem != "y" && maisItem != "n");
				if(maisItem == "y"){
					continue;
				}
				else{
					break;
				}
			}
			venda->addItem(prod, quant);

			cout << "Deseja adicionar mais itens a venda?(y/n)";
			do{
				getline(cin, maisItem);
			}while(maisItem != "y" && maisItem != "n");
			if(maisItem == "y"){
				maisItens = true;
			}
			else{
				maisItens = false;
			}
		}while(maisItens);
	}
	else{
		string numReceita,codigo,maisItem;
		Produto* prod;
		bool maisItens = true;
		unsigned int quant;
		do{
			cout << "Introduza o codigo do produto: ";
			getline(cin, codigo);

			try{
				prod = Produto::getProdutoComCodigo(codigo);
			}catch(ProdutoInexistente e){
				cout << "Nao existe produto com codigo  " << e.getCodigo() << "\n";
				continue;
			}

			cout << "Introduza o numero de produtos que pretende comprar: ";
			inputHandler(quant);

			try{
				farm->vendeItem(prod, quant);
			} catch (StockInexistente) {
				cout << "Nao temos esse produto em stock\n";
				cout << "Deseja adicionar mais itens a venda?(y/n)";
				do{
					getline(cin, maisItem);
				}while(maisItem != "y" && maisItem != "n");
				if(maisItem == "y"){
					continue;
				}
				else{
					break;
				}
				continue;
			} catch (StockInsuficiente) {
				cout << "Nao temos suficiente desse produto em stock\n";
				cout << "Deseja adicionar mais itens a venda?(y/n)";
				do{
					getline(cin, maisItem);
				}while(maisItem != "y" && maisItem != "n");
				if(maisItem == "y"){
					continue;
				}
				else{
					break;
				}
			}
			venda->addItem(prod, quant);

			cout << "Deseja adicionar mais itens a venda?(y/n)";
			do{
				getline(cin, maisItem);
			}while(maisItem != "y" && maisItem != "n");
			if(maisItem == "y"){
				maisItens = true;
			}
			else{
				maisItens = false;
			}
		}while(maisItens);
	}

	client->addCompra(venda);
	cadeia->addVenda(venda);

	cout << "Transacao completa.\n";

}

void gestaoVendas()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Criar Venda\n";
		cout << "2. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			criarVenda();
			break;
		case 2:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void adicionarStock(){
	Farmacia* farm;
	string nomeFarm;
	cout << "Introduza o nome da farmacia: ";
	getline(cin, nomeFarm);
	try {
		farm = cadeia->getFarmaciaComNome(nomeFarm);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe nenhuma farmacia com nome " << e.getNome() << " associado.\n";
		return;
	}
	string codigo;
	Produto* prod;
	cout << "Introduza o codigo do produto a adicionar a stock: ";
	getline(cin, codigo);
	try {
		prod = prod->getProdutoComCodigo(codigo);
	} catch(ProdutoInexistente e) {
		cout << "Nao existe nenhum Produto com codigo " << e.getCodigo() << " associado.\n";
		return;
	}
	farm->addProductToStock(prod);
	unsigned int quant;
	cout << "Introduza a quantidade que deseja adicionar ao stock:";
	inputHandler(quant);
	farm->addStock(prod,quant);

	cout << "Produto adicionado ao stock com sucesso.\n";
}

void adicionarQuantAoStock(){
	Farmacia* farm;
	string nomeFarm;
	cout << "Introduza o nome da farmacia: ";
	getline(cin, nomeFarm);
	try {
		farm = cadeia->getFarmaciaComNome(nomeFarm);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe nenhuma farmacia com nome " << e.getNome() << " associado.\n";
		return;
	}
	string codigo;
	Produto* prod;
	cout << "Introduza o codigo do produto cujo stock deseja acrescentar: ";
	getline(cin, codigo);
	try {
		prod = prod->getProdutoComCodigo(codigo);
	} catch(ProdutoInexistente e) {
		cout << "Nao existe nenhum Produto com codigo " << e.getCodigo() << " associado.\n";
		return;
	}
	unsigned int quant;
	cout << "Introduza a quantidade que deseja adicionar ao stock:";
	inputHandler(quant);
	try {
		farm->addStock(prod,quant);
	} catch(StockInexistente e) {
		cout << "Nao existe nenhum Produto com codigo " << e.getProd()->getCodigo() << " em stock\n";
		return;
	}

	cout << "Quantidade adicionada com sucesso.\n";
}

void mostrarStockInferiorA(){
	Farmacia* farm;
	string nomeFarm;
	cout << "Introduza o nome da farmacia: ";
	getline(cin, nomeFarm);
	try {
		farm = cadeia->getFarmaciaComNome(nomeFarm);
	} catch(NaoExisteFarmacia e) {
		cout << "Nao existe nenhuma farmacia com nome " << e.getNome() << " associado.\n";
		return;
	}

	unsigned int quant;
	cout << "Introduza o limite superior dos items em stock que deseja mostrar:";
	inputHandler(quant);

	vector<StockItem> items = farm->stockWithLessThan(quant);

	if(items.size() == 0){
		cout << "Nao ha items com stock inferior a " << quant << " nesta farmacia." << endl;
	}else{
		for(unsigned int i = 0; i < items.size(); i++){
			cout << items.at(i) << endl;
		}
	}
}

void gestaoStocks()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Adicionar stock\n";
		cout << "2. Adicionar quantidade ao stock\n";
		cout << "4. Mostrar items com stock inferior a n\n";
		cout << "5. Voltar ao menu principal\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch(opcao)
		{
		case 1:
			adicionarStock();
			break;
		case 2:
			adicionarQuantAoStock();
			break;
		case 4:
			mostrarStockInferiorA();
			break;
		case 5:
			reabrirMenu = false;
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void comeceCadeia(){
	string nomeFarm, moradaFarm;
	string nome, morada, password, distrito;
	unsigned int noContribuinte, salario;
	cout << "Compre a sua primeira Farmacia.\n";
	cout << "Introduza o nome Farmacia: ";
	getline(cin, nomeFarm);
	cout << "Introduza a morada da Farmacia: ";
	getline(cin, moradaFarm);

	Farmacia* farm = new Farmacia(nomeFarm,moradaFarm);
	cadeia->addFarmacia(farm);

	cout << "Contrate o Gerente para a primeira Farmacia.\n";

	cout << "Introduza o nome do Funcionario: ";
	getline(cin, nome);
	cout << "Introduza a morada do Funcionario: ";
	getline(cin, morada);
	cout << "Introduza o distrito do Funcionario: ";
	getline(cin, distrito);
	cout << "Introduza o numero de contribuinte do Funcionario: ";
	inputHandler(noContribuinte);
	cout << "Introduza a password do Funcionario: ";
	getline(cin, password);
	cout << "Introduza o salario do Funcionario: ";
	inputHandler(salario);
	Funcionario* newFunc = new Funcionario(nome, morada, noContribuinte, distrito, salario, password);
	newFunc->setCargo("Gerente");
	newFunc->setFarmacia(farm);
	farm->setGerente(newFunc->getNome());
	cadeia->addFuncionario(newFunc);

	func = newFunc;

	cout << "Funcionario contratado.\n";

}

void menu()
{
	bool reabrirMenu = true;
	while(reabrirMenu)
	{
		displayLogo();
		cout << "1. Gestao de Farmacias\n";
		cout << "2. Gestao de Clientes\n";
		cout << "3. Gestao de Funcionarios\n";
		cout << "4. Gestao de Produtos\n";
		cout << "5. Gestao de Receitas\n";
		cout << "6. Gestao de Vendas\n";
		cout << "7. Gestao de Stocks\n";
		cout << "8. Gravar ficheiros\n";
		cout << "9. Mostrar Cadeia\n";
		cout << "10. Desligar sistema\n";
		cout << "Insira a sua opcao: ";
		unsigned int opcao;
		inputHandler(opcao);
		switch (opcao)
		{
		case 1:
			gestaoFarmacias();
			break;
		case 2:
			gestaoClientes();
			break;
		case 3:
			gestaoFuncionarios();
			break;
		case 4:
			gestaoProdutos();
			break;
		case 5:
			gestaoReceitas();
			break;
		case 6:
			gestaoVendas();
			break;
		case 7:
			gestaoStocks();
			break;
		case 8:
			exportarFicheiros();
			displayLogo();
			cout << "Sistema guardado.\n";
			break;
		case 9:
			cout << *cadeia << endl;
			break;
		case 10:
			reabrirMenu = false;
			cout << "Fechando sistema...\n";
			displayLogo();
			break;
		default:
			cout << "Opcao invalida.\n";
		}
	}
}

void start()
{
	cout << "1. Comecar uma nova cadeia\n";
	cout << "2. Importar uma cadeia de um ficheiro existente\n";
	cout << "Insira a sua opcao: ";
	unsigned int opcao;
	inputHandler(opcao);
	switch(opcao)
	{
	case 1:
	{
		importarProdutos();
		string nome;
		cout << "Introduza o nome da nova cadeia: ";
		getline(cin, nome);
		cadeia = new Cadeia(nome);
		comeceCadeia();
		break;
	}
	case 2:
	{
		string nomeFicheiro;
		bool valid = false;
		while(!valid)
		{
			cout << "Introduza o nome da cadeia:";
			getline(cin, nomeFicheiro);
			valid = !importarFicheiros(nomeFicheiro, nomeFicheiro);
		}
		login();
		break;
	}
	default:
		cout << "Opcao invalida, a desligar...\n";
	}
}

int main()
{
	start();
	menu();
}
