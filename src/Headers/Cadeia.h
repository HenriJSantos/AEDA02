#ifndef CADEIA_H
#define CADEIA_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <stack>
#include "Farmacia.h"
#include "Funcionario.h"
#include "Cliente.h"
#include "Data.h"
#include "Hora.h"

using namespace std;

struct clientLess{
	bool operator()(const Cliente * c1, const Cliente * c2) const
	{
		if(c1->getDistrito() != c2->getDistrito())
			return (c1->getDistrito() < c2->getDistrito());
		else if (c1->getNome() != c2->getNome())
			return (c1->getNome() < c2->getNome());
		else return (c1->getNoContribuinte() < c2->getNoContribuinte());
	}
};

struct funcHash{

	int operator()(const Funcionario* func) const{
		unsigned hash, contrib = func->getNoContribuinte();
		stack<int> numberStack;
		while (contrib > 0)
		{
		    numberStack.push(contrib % 10);
		    contrib /= 10;
		}
		while (!numberStack.empty())
		{
		    hash = hash * 37 + numberStack.top();
		    numberStack.pop();
		}
		return hash;
	}

	bool operator()(const Funcionario* func1, const Funcionario* func2) const{
		return (*func1 == *func2);
	}
};

typedef unordered_set<Funcionario*,funcHash,funcHash> funcTable;

class Cadeia {
	//Nome da cadeia
	string nome;
	//Vetor de apontadores para farmacias pertencentes a cadeia
	vector<Farmacia*> farmacias;
	//Unordered_set de apontadores para funcionarios pertencentes a cadeia
	funcTable funcionarios;
	//Set de apontadores para clientes da cadeia
	set<Cliente*, clientLess> clientes;
	//Vetor de apontadores para todas as vendas da cadeia
	vector<Venda*> vendas;

public:
	/**
	 * @brief Construtor da cadeia
	 * @param nome Nome da cadeia de farmacias
	 */
	Cadeia(string nome);

	/**
	 * @brief Construtor da cadeia, dando import aos dados de um text file
	 * @param nomeFicheiro Nome do ficheiro com os dados da cadeia
	 * @param nome Nome da cadeia de farmacias
	 */
	Cadeia(string nomeFicheiro, string nome);

	/**
	 * @brief Retorna o string com o nome da cadeia
	 * @return Nome da cadeia
	 */
	string getNome();

	/**
	 * @brief Altera o nome da cadeia
	 * @param nome Nome da cadeia de farmacias
	 */
	void setNome(string nome);

	/**
	 * @brief Adiciona uma farmacia
	 * @param farm Apontador para a farmacia a adicionar
	 */
	void addFarmacia(Farmacia* farm);

	/**
	 * @brief Remove uma farmacia
	 * @param nomeFarm Nome da farmacia a remover
	 */
	void rmFarmacia(string nomeFarm);

	/**
	 * @brief Adiciona um funcionario
	 * @param func Apontador para o funcionario a adicionar
	 */
	void addFuncionario(Funcionario* func);

	/**
	 * @brief Remover um funcionario
	 * @param contribFunc Numero de contribuinte do funcionario a remover
	 */
	void rmFuncionario(unsigned int contribFunc);

	/**
	 * @brief Adiciona um cliente
	 * @param cliente Apontador para o cliente a adicionar
	 */
	void addCliente(Cliente* cliente);

	/**
	 * @brief Remove um cliente
	 * @param nome Nome do cliente a remover
	 * @param contribCliente Numero de contribuinte do cliente a remover
	 * @param distrito Distrito do cliente a remover
	 */
	void rmCliente(string nome, unsigned int contribCliente, string distrito);

	/**
	 * @brief Adiciona uma venda
	 * @param venda Apontador para a venda a adicionar
	 */
	void addVenda(Venda* venda);

	/**
	 * @brief Remove uma venda
	 * @param id Identificador da venda a remover
	 */
	void rmVenda(unsigned int id);

	/**
	 * @param nomeFarm Nome da farmacia
	 * @return Apontador para a farmacia com nome "nomeFarm"
	 */
	Farmacia* getFarmaciaComNome(string nomeFarm);

	/**
	 * @param nome Nome do funcionario
	 * @return Apontador para o funcionario com nome "nome"
	 */
	Funcionario* getFuncionarioComNome(string nome);

	/**
	 * @param nome Nome do cliente
	 * @return Apontador para o cliente com nome "nome"
	 */
	Cliente* getClienteComNome(string nome);

	/**
	 * @param noContribuinte Numero de contribuinte do cliente
	 * @return Apontador para o cliente com o numero de contribuinte "noContribuinte"
	 */
	Cliente* getClienteComNoContribuinte(unsigned int noContribuinte);

	/**
	 * @param noContribuinte Numero de contribuinte do funcionario
	 * @return Apontador para o funcionario com numero de contribuinte "noContribuinte"
	 */
	Funcionario* getFuncionarioComNoContribuinte(unsigned int noContribuinte);

	/**
	 * @param farm Apontador para a farmacia
	 * @return Vetor com apontadores para os funcionarios que trabalham na farmacia apontada por "farm"
	 */
	vector <Funcionario* > getFuncionariosDaFarmacia(Farmacia* farm);

	/**
	 * @brief Exporta a cadeia para um ficheiro txt
	 */
	void exportarCadeia();

	/**
	 * @brief Destrutor da classe "Cadeia"
	 */
	~Cadeia();

	/**
	 * @brief Overload do operator << (para display no ecra)
	 * @param out Output stream
	 * @param cadeia Cadeia de farmacias
	 * @return Cadeia de farmacias e respetiva informacao
	 */
	friend std::ostream& operator<< (ostream & out, Cadeia &cadeia);

};

class NaoExisteFarmacia {
	//Nome da farmacia
	string nome;
public:
	/**
	 * @brief Construtor da classe "NaoExisteFarmacia" (excecao)
	 * @param nome Nome da farmacia inexistente
	 */
	NaoExisteFarmacia(string nome) {this->nome = nome;}
	/**
	 * @return Nome da farmacia inexistente
	 */
	string getNome() {return this->nome;}
};

class NaoExistePessoa {
	//Numero de contribuinte da pessoa
	unsigned int contribuinte;
	//Nome da pessoa
	string nome;
	//Tipo de pessoa (funcionario ou cliente)
	string tipo;
public:
	/**
	 * @brief Construtor da classe "NaoExistePessoa" (excecao)
	 * @param contribuinte Numero de contribuinte da pessoa inexistente
	 * @param tipo Pode ser um "cliente" ou um "funcionario"
	 */
	NaoExistePessoa(unsigned int contribuinte, string tipo) {this->contribuinte = contribuinte; this->tipo = tipo;}
	/**
	 * @brief Construtor da classe "NaoExistePessoa" (excecao)
	 * @param nome Nome da pessoa inexistente
	 * @param tipo Pode ser um "cliente" ou um "funcionario"
	 */
	NaoExistePessoa(string nome, string tipo) {this->nome = nome; this->tipo = tipo;}
	/**
	 * @return Numero de contribuinte da pessoa inexistente
	 */
	unsigned int getContribuinte() {return this->contribuinte;}
	/**
	 * @return Nome da pessoa inexistente
	 */
	string getNome() {return this->nome;}
	/**
	 * @return "cliente" se a pessoa e um cliente e "funcionario" se a pessoa e um funcionario
	 */
	string getTipo() {return this->tipo;}
};

class NaoExisteVenda {
	unsigned int id;
public:
	/**
	 * @brief Construtor da classe "NaoExisteVenda" (excecao)
	 * @param id Identificador da venda inexistente
	 */
	NaoExisteVenda(unsigned int id) {this->id = id;}
	/**
	 * @return Identificador da venda inexistente
	 */
	unsigned int getId() {return this->id;}
};

class CadeiaInexistente {
	string nome;
public:
	/**
	 * @brief Construtor da classe "CadeiaInexistente" (excecao)
	 * @param nome Nome da cadeia inexistente
	 */
	CadeiaInexistente(string nome) {this->nome = nome;}
	/**
	 * @return Nome da cadeia inexistente
	 */
	string getNome() {return this->nome;}
};

#endif
