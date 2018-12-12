#include "ItemVenda.h"
#include <iomanip>

ItemVenda::ItemVenda(string codigoProduto, unsigned int quant, unsigned int iva, float precUnid, bool receitado) {
	this->prod = Produto::getProdutoComCodigo(codigoProduto);
	this->quant = quant;
	this->iva = iva;
	this->precUnid = precUnid;
	this->compart = receitado? quant*this->prod->getTaxaDesc()*precUnid*0.01 : 0;
	this->subtotal = quant*precUnid*(1+0.01*iva)-this->compart;
}

ItemVenda::ItemVenda(string codigoProduto, unsigned int quant, unsigned int iva, float precUnid, float compart, float subtotal) {

	this->prod = Produto::getProdutoComCodigo(codigoProduto);
	this->quant = quant;
	this->iva = iva;
	this->precUnid = precUnid;
	this->compart = compart;
	this->subtotal = subtotal;
}

string ItemVenda::getCodigo(){
	return prod->getCodigo();
}

string ItemVenda::getNome(){
	return prod->getNome();
}

unsigned int ItemVenda::getQuant(){
	return this->quant;
}

unsigned int ItemVenda::getIva(){
	return this->iva;
}

float ItemVenda::getPrecUnid(){
	return this->precUnid;
}

float ItemVenda::getCompart(){
	return this->compart;
}

float ItemVenda::getSubtotal(){
	return this->subtotal;
}

std::ostream& operator<< (ostream & in, ItemVenda & item)
{
	in << "Produto: " << item.prod->getNome() << endl;
	in << "Quantidade: " << item.quant << endl;
	in << "Preco Unidade: " << setprecision(2) << fixed << item.precUnid << "€\n";
	in << "IVA: " << item.iva << "%" << endl;
	in << "Comparticao: " << setprecision(2) << fixed << item.compart << "€\n" << endl;
	in << "Subtotal: " << setprecision(2) << fixed << item.subtotal << "€\n";
	return in;
}
