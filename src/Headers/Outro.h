#ifndef OUTRO_H
#define OUTRO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Produto.h"

using namespace std;

class Outro : public Produto {
private:
	//"proxCodigo" será o código a atribuir ao produto
	static unsigned int proxCodigo;

public:
	/**
	 * @brief Construtor da classe "Outro"
	 * @param nome Nome do produto
	 * @param preco Preco do produto
	 * @param descricao Descricao breve da funcao do produto
	 */
	Outro(string nome, float preco, string descricao);

	/**
	 * @brief Construtor da classe "Outro"
	 * @param codigo Codigo do produto
	 * @param nome Nome do produto
	 * @param preco Preco do produto
	 * @param descricao Descricao breve da funcao do produto
	 */
	Outro(string codigo, string nome, float preco, string descricao);

	/**
	 * @brief Cria um codigo de formato "O####". A letra O no início indica que não é um medicamento, seguida do número do produto comprado
	 * @return Codigo criado
	 */
	string criarCodigoValido();

	/**
	 * @brief Retorna o codigo numerico do produto, a adicionar ao prefixo O, para ficar no formato "O####"
	 * @return Codigo do produto
	 */
	static unsigned int getProxCodigo();

	/**
	 * @brief Atribui o codigo numerico ao produto, a adicionar ao prefixo O, para ficar no formato "O####"
	 * @param codigo Codigo a atribuir
	 */
	static void setProxCodigo(unsigned int codigo);

	/**
	 * @brief Destrutor da classe "Outro"
	 */
	~Outro();
};

#endif
