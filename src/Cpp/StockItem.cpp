#include "StockItem.h"
using namespace std;

StockItem::StockItem(Produto * prod, unsigned int quant)
{
	this->prod = prod;
	this->quant = quant;
}

void StockItem::setQuantity(unsigned int quant)
{
	this->quant = quant;
}

unsigned int StockItem::getQuantity() const
{
	return this->quant;
}

Produto * StockItem::getProduct()
{
	return this->prod;
}


void StockItem::addQuantity(unsigned int quant)
{
	this->quant += quant;
}

void StockItem::takeQuantity(unsigned int quant)
{
	if (this->quant >= quant)
	{
		this->quant -= quant;
		return;
	}
	else
		throw(StockInsuficiente(this->prod));
}

bool StockItem::operator< (const StockItem & si) const
{
	return (this->quant > si.getQuantity());
}

std::ostream& operator<< (ostream & out, StockItem &si){
	out << "Produto e quantidade:" << si.getProduct()->getCodigo() << "-" << si.getProduct()->getNome() << " " << si.getQuantity() << endl;
    return out;
}
