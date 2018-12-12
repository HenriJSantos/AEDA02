#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "import_export.h"
#include "Produto.h"
#include "Medicamento.h"
#include "MedicamentoPassReceita.h"
#include "Outro.h"
#include "Funcionario.h"
#include "Cliente.h"
#include "Venda.h"
#include "ItemVenda.h"

void exportarProdutos()
{
	sort(Produto::produtos.begin(),Produto::produtos.end(), Produto::compare);
	ofstream out;
	out.open("Output/Produtos.txt");
	for (unsigned int i = 0; i < Produto::produtos.size(); i++)
	{
		out << "Código: " << Produto::produtos[i]->getCodigo() << endl;
		out << "Nome: " << Produto::produtos[i]->getNome() << endl;
		out << "Preço: " << Produto::produtos[i]->getPreco() << endl;
		out << "Descricao: " << Produto::produtos[i]->getDescricao() << endl;
		char codeIdentifier = Produto::produtos[i]->getCodigo()[0];
		switch(codeIdentifier)
		{
		case 'M':
			if(Produto::produtos[i]->passivelReceita())
			{
				out << "Tipo: Medicamento Passível a Receita" << endl;
				out << "Taxa de Desconto: " << Produto::produtos[i]->getTaxaDesc() << "%" << endl;
				out << "Adquirível sem receita: " << (Produto::produtos[i]->adquirivelSemReceita()? "Sim" : "Não") << endl;
			}
			else
				out << "Tipo: Medicamento" << endl;
			break;
		case 'O':
			out << "Tipo: Outro" << endl;
			break;
		}
		out << endl;
	}
	out.close();
}

void importarProdutos()
{
	ifstream in;
	in.open("Output/Produtos.txt");
	if (in.is_open())
	{
		while(!in.eof())
		{
			string tempInput;

			string codigo;
			getline(in,codigo);
			if (codigo == "")
				break;
			codigo = codigo.substr(8,5);

			string nome;
			getline(in, nome);
			nome = nome.substr(6);

			getline(in,tempInput);
			tempInput = tempInput.substr(7);
			float preco = stof(tempInput);

			string descricao;
			getline(in,descricao);
			descricao = descricao.substr(11);

			string tipo;
			getline(in,tipo);
			tipo = tipo.substr(6);

			if (tipo == "Medicamento")
			{
				Medicamento* p = new Medicamento(codigo, nome, preco, descricao);
				if ((unsigned int)stoi(codigo.substr(1)) > Medicamento::getProxCodigo()-1)
					Medicamento::setProxCodigo(stoi(codigo.substr(1))+1);
				Produto::produtos.push_back(p);
			}
			else if (tipo == "Outro")
			{
				if ((unsigned int)stoi(codigo.substr(1)) > Outro::getProxCodigo()-1)
					Outro::setProxCodigo(stoi(codigo.substr(1))+1);

				Outro* p = new Outro(codigo, nome, preco, descricao);
				Produto::produtos.push_back(p);
			}
			else if (tipo == "Medicamento Passível a Receita")
			{
				if ((unsigned int)stoi(codigo.substr(1)) > Medicamento::getProxCodigo()-1)
					Medicamento::setProxCodigo(stoi(codigo.substr(1))+1);

				getline(in,tempInput);
				tempInput = tempInput.substr(18,tempInput.size()-19);
				unsigned int taxaDesc = stoi(tempInput);

				getline(in, tempInput);
				tempInput = tempInput.substr(24);
				bool adquirivelSemReceita;
				if (tempInput == "Sim")
					adquirivelSemReceita = true;
				else
					adquirivelSemReceita = false;

				MedicamentoPassReceita* p = new MedicamentoPassReceita(codigo, nome, preco, descricao, taxaDesc, adquirivelSemReceita);
				Produto::produtos.push_back(p);
			}
			sort(Produto::produtos.begin(),Produto::produtos.end(), Produto::compare);
			getline(in, tempInput);
		}
	}
	in.close();
}
