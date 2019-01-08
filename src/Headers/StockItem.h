#ifndef STOCK_ITEM_H
#define STOCK_ITEM_H

#include "Produto.h"

class StockItem {

private:
	/**
	 * @brief Apontador para um produto
	 */
	Produto * prod;
	/**
	 * @brief Quantidade de produto (unidades em stock)
	 */
	unsigned int quant;
public:
	/**
	 * @brief Construtor da classe "StockItem"
	 * @param prod Apontador para o produto
	 * @param quant Quantidade de produto (unidades em stock)
	 */
	StockItem(Produto * prod, unsigned int quant);
	/**
	 * @brief Atribui uma quantidade ao produto
	 * @param quant Quantidade de produto (unidades em stock)
	 */
	void setQuantity(unsigned int quant);
	/**
	 * @return Quantidade de produto (unidades em stock)
	 */
	unsigned int getQuantity() const;
	/**
	 * @brief Adiciona a quantidade dada como parametro ao stock
	 * @param quant Quantidade de produto (unidades em stock)
	 */
	void addQuantity(unsigned int quant);
	/**
	 * @brief Retira a quantidade dada como parametro ao stock
	 * @param quant Quantidade de produto (unidades em stock)
	 * @return "true" se a quantidade existente for igual ao superior a dada como parametro, "false" caso contrario
	 */
	bool takeQuantity(unsigned int quant);

	/**
	 * @brief Overload do operador "<" para comparar o stock na fila de prioridade
	 * @param si StockItem a comparar
	 * @return "true" se o stock existente for menor que o stock de "si"
	 */
	bool operator< (const StockItem & si) const;
};



#endif /* STOCK_ITEM_H */
