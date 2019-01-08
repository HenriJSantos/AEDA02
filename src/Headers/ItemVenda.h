#ifndef ITEMVENDA_H
#define ITEMVENDA_H

#include <iostream>
#include <vector>
#include "Produto.h"

using namespace std;

class ItemVenda {

private:
	/**
	 * @brief Apontador para um produto
	 */
	Produto* prod;
	/**
	 * @brief Quantidade de produto - quantas unidades se comprou
	 */
	unsigned int quant;
	/**
	 * @brief IVA aplicavel ao produto
	 */
	unsigned int iva;
	/**
	 * @brief Preco por unidade
	 */
	float precUnid;
	/**
	 * @brief Comparticipacao aplicavel ao produto
	 */
	float compart;
	/**
	 * @brief Preco a pagar, com IVA e comparticipacao aplicados
	 */
	float subtotal;

public:
	/**
	 * @brief Construtor da classe "ItemVenda"
	 * @param codigoProduto Codigo do produto
	 * @param quant Unidades de produto
	 * @param iva IVA aplicavel ao produto
	 * @param precUnid Preco do produto, por unidade
	 * @param receitado Produto com receita ou nao
	 */
	ItemVenda(string codigoProduto, unsigned int quant, unsigned int iva, float precUnid, bool receitado);

	/**
	 * @brief Construtor da classe "ItemVenda"
	 * @param codigoProduto Codigo do produto
	 * @param quant Unidades de produto
	 * @param iva IVA aplicavel ao produto
	 * @param precUnid Preco do produto, por unidade
	 * @param compart Comparticipacao aplicavel ao produto
	 * @param subtotal Total a pagar, com IVA e comparticipacao incluidos
	 */
	ItemVenda(string codigoProduto, unsigned int quant, unsigned int iva, float precUnid, float compart, float subtotal);

	/**
	 * @return Codigo do produto
	 */
	string getCodigo();

	/**
	 * @return Nome do produto
	 */
	string getNome();

	/**
	 * @return Unidades de produto
	 */
	unsigned int getQuant();

	/**
	 * @return IVA aplicavel ao produto
	 */
	unsigned int getIva();

	/**
	 * @return Preco do produto, por unidade
	 */
	float getPrecUnid();

	/**
	 * @return Comparticipacao aplicavel ao produto
	 */
	float getCompart();

	/**
	 * @return Total a pagar, com IVA e comparticipacao incluidos
	 */
	float getSubtotal();

	 /**
	 * @brief Overload do operator <<
	 * @param in Output stream para dar display a compra
	 * @param item Item a guardar na output stream
	 * @return Compra efetuada, com o nome do produto, quantidade, preco por unidade, IVA, comparticipacao e subtotal
	 */
	friend std::ostream& operator<< (ostream & in, ItemVenda & item);

};

#endif
