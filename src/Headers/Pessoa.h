#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include <vector>

using namespace std;

class Pessoa {

private:
	//Nome da pessoa
	string nome;
	//Morada da pessoa
	string morada;
	//Número de contribuinte da pessoa
	unsigned int noContribuinte;

	string distrito;

public:
	/**
	 * @brief Construtor da classe "Pessoa"
	 * @param nome Nome da pessoa
	 * @param morada Morada da pessoa
	 * @param noContribuinte Numero de contribuinte da pessoa
	 * @param distrito Distrito da pessoa
	 */
	Pessoa(string nome, string morada, unsigned int noContribuinte, string distrito);
	/**
	 * @brief Retorna o nome da pessoa
	 * @return Nome da pessoa
	 */
	string getNome() const;
	/**
	 * Retorna a morada da pessoa
	 * @return Morada da pessoa
	 */
	string getMorada() const;
	/**
	 * @brief Retorna o numero de contribuinte da pessoa
	 * @return Numero de contribuinte da pessoa
	 */
	unsigned int getNoContribuinte() const;

	/**
	 * @return Distrito da pessoa
	 */
	string getDistrito() const;
	/**
	 * @brief Altera o nome da pessoa
	 * @param nome Nome da pessoa
	 */
	void setNome(string nome);
	/**
	 * @brief Altera a morada da pessoa
	 * @param morada Morada da pessoa
	 */
	void setMorada(string morada);
	/**
	 * @brief Altera o numero de contribuinte da pessoa
	 * @param noContribuinte Numero de contribuinte da pessoa
	 */
	void setNoContribuinte(unsigned int noContribuinte);

	/**
	 * @brief Altera o distrito da pessoa
	 * @param distrito Distrito da pessoa
	 */
	void setDistrito(string distrito);

	/**
	 * @brief Usada para colocar as pessoas por ordem crescente
	 * @param p1 Apontador para a primeira pessoa a comparar
	 * @param p2 Apontador para a segunda pessoa a comparar
	 * @return "true" se o nome da pessoa "p1" for menor que o da pessoa "p2"
	 * @return "false" caso contrario
	 */
	static bool compare (Pessoa * p1, Pessoa * p2);
};

#endif
