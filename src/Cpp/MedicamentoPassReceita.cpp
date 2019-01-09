#include "MedicamentoPassReceita.h"

MedicamentoPassReceita::MedicamentoPassReceita(string nome, float preco, string descricao, unsigned int taxaDesc, bool semReceita) : Medicamento(nome, preco, descricao)
{
	this->taxaDesc = taxaDesc;
	this->semReceita = semReceita;
}

MedicamentoPassReceita::MedicamentoPassReceita(string codigo, string nome, float preco, string descricao, unsigned int taxaDesc, bool semReceita) : Medicamento(codigo, nome, preco, descricao)
{
	this->taxaDesc = taxaDesc;
	this->semReceita = semReceita;
}

unsigned int MedicamentoPassReceita::getTaxaDesc()
{
	return this->taxaDesc;
}

bool MedicamentoPassReceita::adquirivelSemReceita()
{
	return this->semReceita;
}

MedicamentoPassReceita::~MedicamentoPassReceita() {}
