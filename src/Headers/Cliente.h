#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <vector>
#include "Pessoa.h"
#include "Venda.h"

using namespace std;

class Cliente : public Pessoa {
	//Vetor que guarda as compras realizadas pela pessoa
	vector<Venda*> historial;
public:
	/**
	 * @brief Construtor da classe Cliente
	 * @param nome Nome do cliente
	 * @param morada Morada do cliente
	 * @param noContribuinte Numero de contribuinte do cliente
	 */
	Cliente(string nome, string morada, unsigned int noContribuinte, string distrito);

	/**
	 * @brief Adiciona uma compra ao historial
	 * @param compra Apontador para a compra a adicionar
	 */
	void addCompra(Venda* compra);

	/**
	 * @brief Remove uma compra do historial
	 * @param idCompra Identificador da compra a remover
	 */
	void rmCompra(unsigned int idCompra);

	/**
	 * @return Vetor do historial de compras
	 */
	vector<Venda*> getHistorial();

	/**
	 * @brief Overload do operator << (para display no ecra)
	 * @param out Output stream
	 * @param cli Cliente
	 * @return Cliente e respetiva informacao
	 */
	friend std::ostream& operator<< (ostream & out, Cliente &cli);
	bool operator== (const Cliente & c) const;
	bool operator< (const Cliente & c) const;
};

class CompraInexistente
{
	//Código da compra
	unsigned int id;
public:
	/**
	 * @brief Construtor da classe "CompraInexistente" (excecao)
	 * @param idCompra Identificador da compra inexistente
	 */
	CompraInexistente(unsigned int idCompra) {this->id = idCompra;}
	/**
	 * @return Codigo da compra
	 */
	unsigned int getId() {return this->id;}
};

#endif
