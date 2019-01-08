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
	 * @return Produto do item
	 */
	Produto * getProduct();
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
	void takeQuantity(unsigned int quant);

	/**
	 * @brief Overload do operador "<" para comparar o stock na fila de prioridade
	 * @param si StockItem a comparar
	 * @return "true" se o stock existente for menor que o stock de "si"
	 */

	bool operator< (const StockItem & si) const;

	/**
	 * @brief Overload do operator << (para display no ecra)
	 * @param out Output stream
	 * @param si StockItem a mostrar
	 * @return StockItem e respetiva informacao
	 */
	friend std::ostream& operator<< (ostream & out, StockItem &si);
};

class StockInsuficiente {
	/**
	 * @brief Identificador do produto
	 */
	Produto * prod;
public:
	/**
	 * @brief Construtor da classe "StockInsuficiente" (excecao)
	 * @param prod Identificador do produto sem stock suficiente
	 */
	StockInsuficiente(Produto * prod) {this->prod = prod;}
	/**
	 * @return Identificador do produto inexistente
	 */
	Produto * getProd() {return this->prod;}
};



#endif /* STOCK_ITEM_H */
