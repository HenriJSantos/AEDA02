#include "Receita.h"
#include <fstream>
#include <ctime>

vector<Receita*> Receita::receitasValidas;

Receita::Receita(Cliente* cliente, string nomeMedico) {
	this->cliente = cliente;
	this->nomeMedico = nomeMedico;
	this->noReceita = this->criarNumeroValido();
	receitasValidas.push_back(this);
}

void Receita::addProduto(Produto* produto) {
	if(produto->passivelReceita())
		this->produtos.push_back(produto);
	else
		throw(NaoPassivelAReceita(produto->getNome()));
}

string Receita::getNoReceita()
{
	return this->noReceita;
}

string Receita::criarNumeroValido()
{
	bool numeroValido = true;
	string numero;
	srand(time(NULL));
	do
	{
		numero = "";
		numeroValido = true;
		for (unsigned int i = 1; i <= 10; i++)
		{
			numero += rand() % 10 + 48; // Criar um numero aleatorio de 10 digitos entre 0 e 9
		}

		for (unsigned int i = 0; i < receitasValidas.size(); i++)
		{
			if (numero == receitasValidas[i]->getNoReceita())
			{
				numeroValido = false;	// Se numero for repetido, descartar numero
			}
		}
	} while (!numeroValido);
	return numero;
}

Receita* Receita::getReceitaComNumero(string noReceita)
{
	int left = 0, right = receitasValidas.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (receitasValidas[middle]->getNoReceita() < noReceita)
			left = middle + 1;
		else if (noReceita < receitasValidas[middle]->getNoReceita())
			right= middle - 1;
		else
			return receitasValidas[middle]; // encontrou
	}
	throw (ReceitaInexistente(noReceita));
}

vector<Produto*> Receita::getProdutos()
{
	return this->produtos;
}

void Receita::printReceita()
{
	string fileName = this->cliente->getNome() + " Receita no. " + (string)this->noReceita;
	ofstream out;
	out.open("Output/Impressora/" + fileName + ".txt");
	out << "Receita nº " << (string)this->getNoReceita() << endl;
	out << "Prescritor: " << this->nomeMedico << endl;
	out << "Paciente: " << this->cliente->getNome() << endl;
	out << "Produtos:\n";
	for (unsigned int i = 0; i < this->produtos.size(); i++)
	{
		out << "   " << this->produtos[i]->getCodigo() << " - " << this->produtos[i]->getNome() << endl;
	}
	out.close();
}

void Receita::removeReceitaComNo(string noReceita)
{
	for (unsigned int i = 0; i < receitasValidas.size(); i++)
	{
		if (receitasValidas[i]->getNoReceita() == noReceita)
		{
			receitasValidas.erase(receitasValidas.begin()+i);
			return;
		}
	}
	throw ReceitaInexistente(noReceita);
}

Receita::~Receita()
{
	removeReceitaComNo(this->getNoReceita());
	delete this;
}
