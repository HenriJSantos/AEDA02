#ifndef STOCK_ITEM_H
#define STOCK_ITEM_H

#include "Produto.h"

class StockItem {

private:
	Produto * prod;
	unsigned int quant;
public:
	StockItem(Produto * prod, unsigned int quant);
	void setQuantity(unsigned int quant);
	unsigned int getQuantity() const;
	void addQuantity(unsigned int quant);
	bool takeQuantity(unsigned int quant);
	bool operator< (const StockItem & si) const;
};



#endif /* STOCK_ITEM_H */
