#ifndef RECEITA_H
#define RECEITA_H

#include <iostream>
#include <vector>
#include "Produto.h"
#include "Cliente.h"

using namespace std;

class Receita {

private:
	/**
	 * @brief Vetor de apontadores para receitas validas
	 */
	static vector<Receita*> receitasValidas;
	/**
	 * @brief Numero da receita
	 */
	string noReceita;
	/**
	 * @brief Apontador para um cliente
	 */
	Cliente* cliente;
	/**
	 * @brief Nome do medico
	 */
	string nomeMedico;
	/**
	 * @brief Vetor de apontadores para os produtos
	 */
	vector<Produto*> produtos;
public:
	/**
	 * @brief Construtor da classe "Receita"
	 * @param cliente Apontador para o cliente correspondente da receita
	 * @param nomeMedico Nome do medico que receitou
	 */
	Receita(Cliente* cliente, string nomeMedico);

	/**
	 * @brief Adiciona um produto a receita
	 * @param produto Apontador para o produto a adicionar
	 */
	void addProduto(Produto* produto);

	/**
	 * @return Numero da receita
	 */
	string getNoReceita();

	/**
	 * @brief Cria um numero valido para atribuir a receita
	 * @return Numero criado
	 */
	static string criarNumeroValido();

	/**
	 * @brief Cria uma receita com o numero respetivo
	 * @param noReceita Numero a atribuir a receita
	 * @return Apontador para a receita criada
	 */
	static Receita* getReceitaComNumero(string noReceita);

	/**
	 * @return Vetor de apontadores para os produtos da receita
	 */
	vector<Produto*> getProdutos();

	/**
	 * @brief Da print da receita do cliente
	 */
	void printReceita();

	/**
	 * @brief Remove uma receita do vetor de receitas validas
	 * @param noReceita Numero da receita a remover
	 */
	static void removeReceitaComNo(string noReceita);

	/**
	 * @brief Destrutor da classe "Receita"
	 */
	~Receita();
};

class ReceitaInexistente
{
	/**
	 * @brief Numero da receita
	 */
	string noReceita;
public:
	/**
	 * @brief Construtor da classe "ReceitaInexistente" (excecao)
	 * @param noReceita Numero da receita inexistente
	 */
	ReceitaInexistente(string noReceita) {this->noReceita = noReceita;}

	/**
	 * @return Numero da receita inexistente
	 */
	string getNoReceita() {return this->noReceita;}
};

#endif
