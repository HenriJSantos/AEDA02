#ifndef HORA_H
#define HORA_H

#include <iostream>
#include <vector>

using namespace std;

class Hora {

private:
	//Guarda as horas
	unsigned int hora;

	//Guarda os minutos
	unsigned int minuto;

	//Guarda os segundos
	unsigned int segundo;

public:
	/**
	 * @brief Construtor da classe "Hora"
	 * @param h Hora
	 * @param m Minutos
	 * @param s Segundos
	 */
	Hora(unsigned int h, unsigned int m, unsigned int s);

	/**
	 * @brief Construtor da classe "Data"
	 */
	Hora();

	/**
	 * @return Retorna a hora
	 */
	unsigned int getHora();

	 /**
	 * @brief Altera a hora
	 * @param h Novo valor da hora
	 */
	void setHora(unsigned int h);

	/**
	 * @return Retorna os minutos
	 */
	unsigned int getMinutos();

	 /**
	 * @brief Altera os minutos
	 * @param m Novo valor dos minutos
	 */
	void setMinutos(unsigned int m);

	/**
	 * @return Retorna os segundos
	 */
	unsigned int getSegundos();

	 /**
	 * @brief Altera os segundos
	 * @param s Novo valor dos segundos
	 */
	void setSegundos(unsigned int s);

	 /**
	 * @brief Overload do operator <<
	 * @param o Output stream para dar display a hora
	 * @param h Hora a guardar na output stream
	 * @return Hora no formato HH:MM:SS (hora, minutos, segundos)
	 */
	friend ostream & operator<<(ostream & o, const Hora & h);
};

#endif
