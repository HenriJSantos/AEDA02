#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <vector>

using namespace std;

class Produto {

private:
	static vector<Produto*> produtos;
	string codigo;
	string nome;
	float preco;
	string descricao;

public:
	/**
	 * @brief Construtor da classe "Produto"
	 * @param nome Nome do produto
	 * @param preco Preco do produto
	 * @param descricao Breve descricao da funcionalidade do produto
	 */
	Produto(string nome, float preco, string descricao);

	/**
	 * @brief Construtor da classe "Produto"
	 * @param codigo Codigo do produto
	 * @param nome Nome do produto
	 * @param preco Preco do produto
	 * @param descricao Breve descricao da funcionalidade do produto
	 */
	Produto(string codigo, string nome, float preco, string descricao);

	/**
	 * @return "true" se o produto e adquirivel sem receita medica, "false" caso contrario
	 */
	virtual bool adquirivelSemReceita();

	/**
	 * @return Nome do produto
	 */
	string getNome();

	/**
	 * @return Codigo do produto
	 */
	string getCodigo();

	/**
	 * @return Descricao do produto
	 */
	string getDescricao();

	/**
	 * @return Preco do produto
	 */
	float getPreco();

	/**
	 * @return IVA aplicavel ao produto
	 */
	unsigned int getIva();

	/**
	 * @brief Atribui um nome ao produto
	 * @param nome Nome a atribuir ao produto
	 */
	void setNome(string nome);

	/**
	 * @brief Atribui uma descricao ao produto
	 * @param descricao Descricao a atribuir ao produto
	 */
	void setDescricao(string descricao);

	/**
	 * @brief Atribui um preco ao produto
	 * @param preco Preco a atribuir ao produto
	 */
	void setPreco(float preco);

	/**
	 * @brief Atribui um codigo ao produto
	 * @param codigo Codigo a atribuir ao produto
	 */
	void setCodigo(string codigo);

	/**
	 * @return "false" - o produto nao e passivel a receita medica
	 */
	virtual bool passivelReceita() {return false;}

	/**
	 * @return "0" - a taxa de desconto aplicavel a este produto e 0
	 */
	virtual unsigned int getTaxaDesc() {return 0;}

	/**
	 * @brief Remove um produto com o codigo indicado
	 * @param codigo Codigo do produto a remover
	 */
	static void removeProdutoComCodigo(string codigo);

	/**
	 * @brief Compara dois produtos, para os organizar por ordem crescente
	 * @param Apontador para o primeiro produto a comparar (p1)
	 * @param Apontador para o segundo produto a comparar(p2)
	 * @return "true" se o codigo de p1 for menor que p2, "false" caso contrario
	 */
	static bool compare(Produto * p1, Produto * p2);

	/**
	 * @param codigo Codigo do produto
	 * @return Produto com o codigo dado como parametro
	 */
	static Produto* getProdutoComCodigo(string codigo);

	/**
	 * @return Vetor de produtos da cadeia
	 */
	static vector<Produto*> getProdutos();

	/**
	 * @brief Altera o vetor de produtos
	 * @param prods Novo vetor de produtos
	 */
	static void setProdutos(vector<Produto*> prods);

	/**
	 * @param nome Nome do produto
	 * @return Produto com o nome dado como parametro
	 */
	static Produto* getProdutoComNome(string nome);

	/**
	 * @brief Exporta produtos para um ficheiro de texto
	 */
	friend void exportarProdutos();

	/**
	 * @brief Importa produtos de um ficheiro de texto para o programa
	 */
	friend void importarProdutos();

	/**
	 * @brief Destrutor da classe "Produto"
	 */
	virtual ~Produto();
};

class OverflowCodigos
{
private:
	string categoria;
public:
	/**
	 * @brief Construtor da classe "OverflowCodigos" (excecao)
	 * @brief E lancada quando existem mais de 9999 produtos e nao e possivel atribuir codigos validos
	 * @param categoria Categoria do produto - se e medicamento ou outro
	 */
	OverflowCodigos(string categoria) {this->categoria = categoria;}
	/**
	 * @return Categoria do produto cujo codigo nao pode ser criado
	 */
	string getCategoria() {return this->categoria;}
};

class NaoPassivelAReceita
{
private:
	string nomeProduto;
public:
	/**
	 * @brief Construtor da classe "NaoPassivelAReceita" (excecao)
	 * @param nome Nome do produto que nao e passivel a receita
	 */
	NaoPassivelAReceita(string nome) {this->nomeProduto = nome;}

	/**
	 * @return Nome do produto que nao e passivel a receita
	 */
	string getNomeProduto() {return this->nomeProduto;}
};

class ProdutoInexistente
{
private:
	string codigo;
public:
	/**
	 * @brief Construtor da classe "ProdutoInexistente" (excecao)
	 * @param codigo Codigo do produto inexistente
	 */
	ProdutoInexistente(string codigo) {this->codigo = codigo;}

	/**
	 * @return Codigo do produto inexistente
	 */
	string getCodigo() {return this->codigo;}
};

#endif
