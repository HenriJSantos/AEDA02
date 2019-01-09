#include "Outro.h"

unsigned int Outro::proxCodigo = 1;

Outro::Outro(string nome, float preco, string descricao) : Produto(nome, preco, descricao)
{
	this->setCodigo(this->criarCodigoValido());
	vector<Produto*> temp = Produto::getProdutos();
	temp.push_back(this);
	sort(temp.begin(),temp.end(), Produto::compare);
	Produto::setProdutos(temp);
}

Outro::Outro(string codigo, string nome, float preco, string descricao) : Produto(codigo, nome, preco, descricao) {}

unsigned int Outro::getProxCodigo()
{
	return proxCodigo;
}

void Outro::setProxCodigo(unsigned int codigo)
{
	proxCodigo = codigo;
}

string Outro::criarCodigoValido()
{
	string codigo = "O";
	if (proxCodigo > 9999)
		throw(OverflowCodigos("Outros"));
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

Outro::~Outro() {}
