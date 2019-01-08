#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <iostream>
#include <vector>
#include "Pessoa.h"
#include "Farmacia.h"

using namespace std;

class Funcionario : public Pessoa {

private:
	/**
	 * @brief Salario do funcionario
	 */
	unsigned int salario;
	/**
	 * @brief Apontador para a farmacia onde o funcionario trabalha
	 */
	Farmacia* farm;
	/**
	 * @brief Cargo do funcionario
	 */
	string cargo;
	/**
	 * @brief Password do funcionario para aceder ao sistema
	 */
	string password;
public:
	/**
	 * @brief Construtor da classe "Funcionario"
	 * @param nome Nome do funcionario
	 * @param morada Morada do funcionario
	 * @param noContribuinte Numero de contribuinte do funcionario
	 * @param distrito Distrito do funcionario
	 * @param salario Salario do funcionario
	 * @param password Password do funcionario para acesso ao sistema
	 */
	Funcionario(string nome, string morada, unsigned int noContribuinte, string distrito, unsigned int salario, string password);

	/**
	 * @return Salario do funcionario
	 */
	unsigned int getSalario();

	/**
	 * @brief Atribui um salario ao funcionario
	 * @param salario Salario a atribuir
	 */
	void setSalario(unsigned int salario);

	/**
	 * @return Apontador para a farmacia do funcionario
	 */
	Farmacia* getFarmacia();

	/**
	 * @brief Atribui uma farmacia ao funcionario
	 * @param farm Apontador para a farmacia a atribuir
	 */
	void setFarmacia(Farmacia* farm);

	/**
	 * @return Cargo do funcionario
	 */
	string getCargo();

	/**
	 * @brief Atribui um cargo ao funcionario
	 * @param cargo Cargo a atribuir
	 */
	void setCargo(string cargo);

	/**
	 * @return Password do funcionario
	 */
	string getPassword();

	/**
	 * @brief Atribui uma password ao funcionario
	 * @param password Password a atribuir
	 */
	void setPassword(string password);

	/**
	 * @brief Overload do operator ==
	 * @param f Funcionario
	 * @return True se os numeros de contribuinte dos funcionarios forem iguais, false caso contrario
	 */
	bool operator== (const Funcionario & f) const;

	/**
	 * @brief Overload do operator << (para display no ecra)
	 * @param out Output stream
	 * @param func Funcionario
	 * @return Funcionario e respetiva informacao
	 */
	friend std::ostream& operator<< (ostream & out, Funcionario & func);
};

#endif
