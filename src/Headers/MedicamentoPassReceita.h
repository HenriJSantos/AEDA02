#ifndef MEDICAMENTOPASSRECEITA_H
#define MEDICAMENTOPASSRECEITA_H

#include <iostream>
#include <vector>
#include "Medicamento.h"

using namespace std;

class MedicamentoPassReceita : public Medicamento {

private:
	//Taxa de desconto
	unsigned int taxaDesc;
	//Medicamento passivel sem receita (se true)
	bool semReceita;

public:
	/**
	 * @brief Construtor da classe "MedicamentoPassReceita"
	 * @param nome Nome do medicamento
	 * @param preco Preco do medicamento
	 * @param descricao Descricao breve da funcao do medicamento
	 * @param taxaDesc Taxa de desconto a atribuir ao medicamento
	 * @param semReceita Se o medicamento pode ser adquirivel com receita ou nao
	 */
	MedicamentoPassReceita(string nome, float preco, string descricao, unsigned int taxaDesc, bool semReceita);

	/**
	 * @brief Construtor da classe "MedicamentoPassReceita"
	 * @param codigo Codigo do medicamento
	 * @param nome Nome do medicamento
	 * @param preco Preco do medicamento
	 * @param descricao Descricao breve da funcao do medicamento
	 * @param taxaDesc Taxa de desconto a atribuir ao medicamento
	 * @param semReceita Se o medicamento pode ser adquirivel com receita ou nao
	 */
	MedicamentoPassReceita(string codigo, string nome, float preco, string descricao, unsigned int taxaDesc, bool semReceita);

	/**
	 * @return Taxa de desconto a atribuir ao medicamento
	 */
	unsigned int getTaxaDesc();

	/**
	 * @return "true" se o medicamento e adquirivel sem receita, "false" caso contrario
	 */
	bool adquirivelSemReceita();

	/**
	 * @return "true" - o medicamento e passivel a receita
	 */
	bool passivelReceita() {return true;}
};

#endif
