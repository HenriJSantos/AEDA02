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

void Farmacia::vendeItem(Produto * prod, unsigned int quant)
{
	vector<StockItem> temp;
	bool found = false;

	while(!stock.empty())
	{
		StockItem copy = stock.top();
		stock.pop();
		if(copy.getProduct() == prod)
		{
			copy.takeQuantity(quant);
			found = true;
			temp.push_back(copy);
			break;
		}
		else
		{
			temp.push_back(copy);
		}
	}

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		stock.push(temp[i]);
	}

	if(!found)
		throw(StockInexistente(prod));
}

void Farmacia::restoreStock(unsigned int ammount)
{
	vector<StockItem> temp;

	while(!stock.empty())
	{
		StockItem copy = stock.top();
		if(copy.getQuantity() < ammount)
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

void Farmacia::addStock(Produto* prod, unsigned int quant){

	priority_queue<StockItem> tempStock = stock;
	vector<StockItem> removedItems;
	StockItem item(prod,0);
	bool added = false;

	while(!tempStock.empty()){
		item = tempStock.top();
		tempStock.pop();
		if(item.getProduct() == prod){
			item.addQuantity(quant);
			added = true;
			removedItems.push_back(item);
			break;
		}
		else{
			removedItems.push_back(item);
		}
	}

	if(!added){
		throw(StockInexistente(prod));
	}
	for(unsigned int i = 0; i < removedItems.size(); i++){
		tempStock.push(removedItems.at(i));
	}
	stock = tempStock;
}
