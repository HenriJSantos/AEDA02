#include "Venda.h"
#include "Receita.h"

unsigned int Venda::proxId = 1;

Venda::Venda(string funcionario) {
	Data d;
	this->data = d;
	Hora h;
	this->hora = h;
	this->id = proxId;
	proxId++;
	this->funcionario = funcionario;
	this->total = 0;
}

Venda::Venda(string funcionario, string data, string hora, unsigned int id) {
	Data d(stoi(data.substr(0,2)),stoi(data.substr(3,2)),stoi(data.substr(6)));
	this->data = d;
	Hora h(stoi(hora.substr(0,2)),stoi(hora.substr(3,2)), stoi(hora.substr(6,2)));
	this->hora = h;
	this->id = id;
	this->funcionario = funcionario;
	this->total = 0;
}

void Venda::addItem(Produto* prod, unsigned int quant) {
	bool receitado = false;
	for (unsigned int i = 0; i < this->produtosReceitados.size(); i++)
	{
		if (prod->getNome() == this->produtosReceitados[i])
			receitado = true;
	}
	if(!receitado & !prod->adquirivelSemReceita())
	{
		cout << "Precisa de receita para este produto.\n";
		return;
	}

	ItemVenda v1(prod->getCodigo(), quant, prod->getIva(), prod->getPreco(), receitado);
	this->itens.push_back(v1);
	total+=v1.getSubtotal();
}

void Venda::loadItem(ItemVenda i)
{
	this->itens.push_back(i);
}

unsigned int Venda::getId()
{
	return this->id;
}

string Venda::getFuncionario(){
	return this->funcionario;
}

Data Venda::getData(){
	return this->data;
}

Hora Venda::getHora(){
	return this->hora;
}

float Venda::getTotal(){
	return this->total;
}

void Venda::setTotal(float total)
{
	this->total = total;
}

void Venda::addReceita(string noReceita)
{
	Receita* r = Receita::getReceitaComNumero(noReceita);
	vector<Produto*> produtos = r->getProdutos();
	for (unsigned int i = 0; i < produtos.size(); i++)
	{
		this->produtosReceitados.push_back(produtos[i]->getNome());
	}
}

vector<ItemVenda> Venda::getItens(){
	return this->itens;
}

unsigned int Venda::getProxId()
{
	return proxId;
}

void Venda::setProxId(unsigned int id)
{
	proxId = id;
}

bool Venda::compare(Venda * p1, Venda * p2)
{
	if (p1->getId() < p2->getId())
		return true;
	else
		return false;
}

std::ostream& operator<< (ostream & out, Venda & venda)
{
	out << "Funcionário: " << venda.funcionario << endl;
	out << "Data: " << venda.data << endl;
	out << "Hora: " << venda.hora << endl;
	out << "Produtos:\n\n";
	for (unsigned int i = 0; i < venda.itens.size(); i++)
	{
		out << venda.itens[i] << endl;
	}
	out << "Total: " << venda.total << endl;
	return out;
}
