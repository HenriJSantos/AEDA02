#include "Medicamento.h"


unsigned int Medicamento::proxCodigo = 1;

Medicamento::Medicamento(string nome, float preco, string descricao) : Produto(nome, preco, descricao)
{
	this->setCodigo(criarCodigoValido());
	vector<Produto*> temp = Produto::getProdutos();
	temp.push_back(this);
	sort(temp.begin(),temp.end(), Produto::compare);
	Produto::setProdutos(temp);
}

Medicamento::Medicamento(string codigo, string nome, float preco, string descricao) : Produto(codigo, nome, preco, descricao) {}

unsigned int Medicamento::getProxCodigo()
{
	return proxCodigo;
}

void Medicamento::setProxCodigo(unsigned int codigo)
{
	proxCodigo = codigo;
}

string Medicamento::criarCodigoValido()
{
	string codigo = "M";
	if (proxCodigo > 9999)
		throw(OverflowCodigos("Medicamentos"));
	if (proxCodigo < 10)
		codigo += "000";
	else if (proxCodigo < 100)
		codigo += "00";
	else if (proxCodigo < 1000)
		codigo += "0";
	codigo += to_string(proxCodigo);
	proxCodigo++;
	return codigo;
}

Medicamento::~Medicamento() {}

