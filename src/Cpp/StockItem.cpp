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


void StockItem::addQuantity(unsigned int quant)
{
	this->quant += quant;
}

bool StockItem::takeQuantity(unsigned int quant)
{
	if (this->quant >= quant)
	{
		this->quant -= quant;
		return true;
	}
	else
		return false;
}

bool StockItem::operator< (const StockItem & si) const
{
	return (this->quant > si.getQuantity());
}
