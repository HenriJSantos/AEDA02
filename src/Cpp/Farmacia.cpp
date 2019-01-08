#include "Farmacia.h"

Farmacia::Farmacia(string nome, string morada) {
	this->nome = nome;
	this->morada = morada;
	this->gerente = "Nenhum";
}

string Farmacia::getNome() const {
	return this->nome;
}

void Farmacia::setNome(string nome) {
	this->nome = nome;
}

string Farmacia::getMorada() const {
	return this->morada;
}

void Farmacia::setMorada(string morada) {
	this->morada = morada;
}

string Farmacia::getGerente() const {
	return this->gerente;
}

void Farmacia::setGerente(string gerente) {
	this->gerente = gerente;
}

bool Farmacia::compare (Farmacia * farm1, Farmacia * farm2)
{
	if (farm1->getNome() < farm2->getNome())
		return true;
	else
		return false;
}

std::ostream& operator<< (ostream & out, Farmacia & farm){
	out << "Nome da Farmacia: " << farm.getNome() << endl;
	out << "Morada: " <<  farm.getMorada() << endl;
	out << "Gerente: " << farm.getGerente() << endl;

	return out;
}

void Farmacia::addProductToStock(Produto * prod)
{
	StockItem si(prod, 0);
	stock.push(si);
}

void Farmacia::restoreStock(unsigned int min)
{
	vector<StockItem> temp;

	while(!stock.empty())
	{
		StockItem copy = stock.top();
		stock.pop();
		if(copy.getQuantity() < min)
		{
			copy.setQuantity(min);
			temp.push_back(copy);
		}
		else
		{
			temp.push_back(copy);
			break;
		}
	}

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		stock.push(temp[i]);
	}
}

vector<StockItem> Farmacia::stockWithLessThan(unsigned int ammount)
{
	vector<StockItem> temp;

	while(!stock.empty())
	{
		if(stock.top().getQuantity() < ammount)
		{
			temp.push_back(stock.top());
			stock.pop();
		}
		else
			break;
	}

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		stock.push(temp[i]);
	}

	return temp;
}
