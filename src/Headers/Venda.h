#ifndef VENDA_H
#define VENDA_H

#include <iostream>
#include <vector>
#include <string>
#include "ItemVenda.h"
#include "Data.h"
#include "Hora.h"

using namespace std;

class Venda {
	//Identificador da próxima compra
	static unsigned int proxId;
	//Identificador da compra
	unsigned int id;
	//Funcionario responsavel pela venda
	string funcionario;
	//Vetor de itens comprados na venda
	vector<ItemVenda> itens;
	//Data da venda
	Data data;
	//Hora da venda
	Hora hora;
	//Total da compra
	float total;
	//Vetor de produtos adquiridos com receita
	vector<string> produtosReceitados;
public:
	/**
	 * @brief Construtor da classe "Venda"
	 * @param funcionario Funcionario que efetuou a venda
	 */
	Venda(string funcionario);

	/**
	 * @brief Construtor da classe "Venda"
	 * @param funcionario Funcionario que efetuou a venda
	 * @param data Data da venda
	 * @param hora Hora da venda
	 * @param id Identificador da venda
	 */
	Venda(string funcionario, string data, string hora, unsigned int id);

	/**
	 * @brief Adiciona um produto ao vetor de itens
	 * @param prod Apontador para o produto que se quer adicionar
	 * @param quant Unidades de produto a adicionar
	 */
	void addItem(Produto* prod, unsigned int quant);

	/**
	 * @brief Da load a um item de um ficheiro de texto e adiciona-o ao vetor "itens"
	 * @param i Item a adicionar
	 */
	void loadItem(ItemVenda i);

	/**
	 * @return Identificador da venda
	 */
	unsigned int getId();

	/**
	 * @return Nome do funcionario que efetuou a venda
	 */
	string getFuncionario();

	/**
	 * @return Data da venda
	 */
	Data getData();

	/**
	 * @return Hora da venda
	 */
	Hora getHora();

	/**
	 * @return Total a pagar pela venda
	 */
	float getTotal();

	/**
	 * @brief Atribui um total a pagar a venda
	 * @param total Preco total a pagar
	 */
	void setTotal(float total);

	/**
	 * @brief Adiciona aos produtos receitados o nome do produto dado como paramentro
	 * @param noReceita Numero da receita relativa ao produto a adicionar
	 */
	void addReceita(string noReceita);

	/**
	 * @return Vetor de itens comprados
	 */
	vector<ItemVenda> getItens();

	/**
	 * @return Identificador da venda, incrementado a cada venda criada
	 */
	static unsigned int getProxId();

	/**
	 * @brief Atribui o valor de proxId ao identificador da venda
	 * @param id Identificador da venda
	 */
	static void setProxId(unsigned int id);

	//Compara duas vendas em relação às suas ids
	/**
	 * @brief Compara os identificadores de duas vendas, de modo a organiza-las por ordem crescente
	 * @param p1 Apontador para a primeira venda a comparar (p1)
	 * @param p2 Apontador para a segunda venda a comparar (p2)
	 * @return "true" se o id da venda "p1" for menor que o da venda "p2"
	 */
	static bool compare(Venda * p1, Venda * p2);

	//Overload do operador << para dar display à venda
	/**
	 * @brief Overload do operador << para dar display a venda
	 * @param in Output stream para mostrar a venda
	 * @param venda Venda a guardar na output stream
	 * @return Venda, com display ao funcionario, data, hora e produtos comprados
	 */
	friend std::ostream& operator<< (ostream & in, Venda & venda);
};

#endif
