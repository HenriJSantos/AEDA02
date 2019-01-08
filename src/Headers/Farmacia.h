#ifndef FARMACIA_H
#define FARMACIA_H

#include <iostream>
#include <vector>
#include <queue>

#include "Produto.h"
#include "StockItem.h"

using namespace std;

class Farmacia {

private:
	/**
	 * @brief Nome da farmacia
	 */
	string nome;
	/**
	 * @brief Morada da farmacia
	 */
	string morada;
	/**
	 * @brief Gerente da farmacia
	 */
	string gerente;
	/**
	 * @brief Fila de prioridade com o stock de produtos da farmacia
	 */
	priority_queue<StockItem> stock;

public:
	/**
	 * @brief Construtor da classe "Farmacia"
	 * @param nome Nome da farmacia
	 * @param morada Morada da farmacia
	 */
	Farmacia(string nome, string morada);

	/**
	 * @return Nome da farmacia
	 */
	string getNome() const;

	/**
	 * @brief Atribui um nome a farmacia
	 * @param nome Nome a atribuir a farmacia
	 */
	void setNome(string nome);

	/**
	 * @return Morada da farmacia
	 */
	string getMorada() const;

	/**
	 * @brief Atribui uma morada a farmacia
	 * @param morada Morada a atribuir a farmacia
	 */
	void setMorada(string morada);

	/**
	 * @return Gerente da farmacia
	 */
	string getGerente() const;

	/**
	 * @brief Atribui um gerente a farmacia
	 * @param gerente Gerente a atribuir a farmacia
	 */
	void setGerente(string gerente);

	/**
	 * @brief Compara duas farmacias para as colocar por ordem crescente
	 * @param farm1 Apontador para a primeira farmacia a comparar
	 * @param farm2 Apontador para a segunda farmacia a comparar
	 * @return "true" se o nome da farmacia "farm1" for menor que o da "farm2", "false" caso contrario
	 */
	static bool compare (Farmacia * farm1, Farmacia * farm2);

	/**
	 * @brief Overload do operator << (para display no ecra)
	 * @param out Output stream
	 * @param farm Farmacia
	 * @return Farmacia e respetiva informacao
	 */
	friend std::ostream& operator<< (ostream & out, Farmacia & farm);
	/**
	 * @brief Adiciona o produto a fila de prioridade de stock
	 * @param prod Apontador para o produto a adicionar
	 */
	void Farmacia::addProductToStock(Produto * prod);

	/**
	 * @brief Garante que o stock de cada produto farmacia tem o valor minimo indicado
	 * @param min Minimo de stock da farmacia
	 */
	void Farmacia::restoreStock(unsigned int min);

	/**
	 * @brief Garante que o stock de cada produto da farmacia tem o valor maximo indicado
	 * @param ammount Maximo de stock da farmacia
	 * @return Vetor cujo stock de cada produto nao ultrapassa o valor "ammount"
	 */
	vector<StockItem> Farmacia::stockWithLessThan(unsigned int ammount);
};

#endif
