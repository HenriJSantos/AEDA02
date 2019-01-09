#ifndef MEDICAMENTO_H
#define MEDICAMENTO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Produto.h"

using namespace std;

class Medicamento : public Produto {

private:
	/**
	 * @brief Codigo a atribuir ao medicamento
	 */
	static unsigned int proxCodigo;

public:
	/**
	 * @brief Construtor da classe "Medicamento"
	 * @param nome Nome do medicamento
	 * @param preco Preco do medicamento
	 * @param descricao Descricao breve da funcao do medicamento
	 */
	Medicamento(string nome, float preco, string descricao);

	/**
	 * @brief Construtor da classe "Medicamento"
	 * @param codigo Codigo do medicamento
	 * @param nome Nome do medicamento
	 * @param preco Preco do medicamento
	 * @param descricao Descricao breve da funcao do medicamento
	 */
	Medicamento(string codigo, string nome, float preco, string descricao);

	/**
	 * @brief Cria um codigo de formato "M####". A letra M no início indica que é um medicamento, seguida do número do medicamento comprado
	 * @return Codigo criado
	 */
	string criarCodigoValido();

	/**
	 * @brief Retorna o codigo numerico do medicamento, a adicionar ao prefixo M, para ficar no formato "M####"
	 * @return Codigo do medicamento
	 */
	static unsigned int getProxCodigo();

	/**
	 * @brief Atribui o codigo numerico ao medicamento, a adicionar ao prefixo M, para ficar no formato "M####"
	 * @param codigo Codigo a atribuir
	 */
	static void setProxCodigo(unsigned int codigo);

	virtual ~Medicamento();
};

#endif
