#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>

using namespace std;

class Data {

private:
	/**
	 * @brief Guarda o dia
	 */
	unsigned int dia;

	/**
	 * @brief Guarda o mes
	 */
	unsigned int mes;

	/**
	 * @brief Guarda o ano
	 */
	unsigned int ano;

public:
	/**
	 * @brief Construtor da classe "Data"
	 * @param d Dia
	 * @param m Mes
	 * @param a Ano
	 */
	Data(unsigned int d, unsigned int m, unsigned int a);

	/**
	 * @brief Construtor da classe "Data"
	 */
	Data();

	/**
	 * @return Retorna o dia
	 */
	unsigned int getDia();

	/**
	 * @brief Altera o dia
	 * @param d Novo valor do dia
	 */
	void setDia(unsigned int d);

	/**
	 * @return Retorna o mes
	 */
	unsigned int getMes();

	/**
	 * @brief Altera o mes
	 * @param m Novo valor do mes
	 */
	void setMes(unsigned int m);

	/**
	 * @return Retorna o ano
	 */
	unsigned int getAno();

	/**
	 * @brief Altera o ano
	 * @param a Novo valor do ano
	 */
	void setAno(unsigned int a);

	/**
	 * @brief Overload do operator << (para display no ecra)
	 * @param o Output stream
	 * @param d Data a guardar na output stream
	 * @return Data no formato DD/MM/YYYY (dia, mes, ano)
	 */
	friend ostream & operator<<(ostream & o, const Data & d);
};

#endif
