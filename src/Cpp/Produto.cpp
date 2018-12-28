#include "Produto.h"
#include <ctime>
#include <fstream>
#include <algorithm>

vector<Produto*> Produto::produtos;

bool Produto::compare(Produto * p1, Produto * p2)
{
	if (p1->getCodigo() < p2->getCodigo())
		return true;
	else
		return false;
}

Produto::Produto(string nome, float preco, string descricao) {
	this->nome = nome;
	this->preco = preco;
	this->descricao = descricao;
}

Produto::Produto(string codigo, string nome, float preco, string descricao) {
	this->nome = nome;
	this->preco = preco;
	this->descricao = descricao;
	this->codigo = codigo;
}

bool Produto::adquirivelSemReceita(){
	return true;
}

string Produto::getNome(){
	return this->nome;
}

string Produto::getCodigo(){
	return this->codigo;
}

string Produto::getDescricao(){
	return this->descricao;
}

float Produto::getPreco(){
	return this->preco;
}

unsigned int Produto::getIva(){
	if(this->getCodigo().substr(0,1) == "M")
		return 6;
	else
		return 23;
}

void Produto::setDescricao(string descricao){
	this->descricao = descricao;
}

void Produto::setNome(string nome){
	this->nome = nome;
}

void Produto::setPreco(float preco){
	this->preco = preco;
}

void Produto::setCodigo(string codigo){
	this->codigo = codigo;
}

void Produto::setProdutos(vector<Produto*> prods){
	produtos = prods;
}

vector<Produto*> Produto::getProdutos()
{
	return produtos;
}

void Produto::removeProdutoComCodigo(string codigo){

	for(unsigned int i = 0; i < produtos.size(); i++){
		if(produtos.at(i)->getCodigo() == codigo){
			delete produtos.at(i);
			produtos.erase(produtos.begin()+i);
			return;
		}
	}

	throw (ProdutoInexistente(codigo));

}

Produto* Produto::getProdutoComCodigo(string codigo){
	int left = 0, right = produtos.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (produtos[middle]->getCodigo() < codigo)
			left = middle + 1;
		else if (codigo < produtos[middle]->getCodigo())
			right= middle - 1;
		else
			return produtos[middle]; // encontrou
	}
	throw (ProdutoInexistente(codigo));
}

Produto* Produto::getProdutoComNome(string nome){
	for (unsigned int i = 0; i < produtos.size(); i++)
	{
		if (produtos[i]->getNome() == nome)
		{
			return produtos[i];
		}
	}
	throw (ProdutoInexistente(nome));
}

Produto::~Produto()
{
	removeProdutoComCodigo(this->codigo);
	delete this;
}
