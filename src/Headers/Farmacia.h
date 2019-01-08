#ifndef FARMACIA_H
#define FARMACIA_H

#include <iostream>
#include <vector>
#include <queue>

#include "Produto.h"
#include "StockItem.h"

using namespace std;

struct stockLess
{
	bool operator()(const pair<Produto*, unsigned> s1, const pair<Produto*, unsigned> s2) const
	{
		return (s1.second < s2.second);
	}
};

class Farmacia {

private:
	//Nome da farmácia
	string nome;
	//Morada da farmácia
	string morada;
	//Gerente da farmácia
	string gerente;
	//Stock
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
};

#endif
