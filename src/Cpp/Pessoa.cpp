#include "Pessoa.h"

Pessoa::Pessoa(string nome, string morada, unsigned int noContribuinte) {
	this->nome = nome;
	this->morada = morada;
	this->noContribuinte = noContribuinte;
}

string Pessoa::getNome() const{
	return this->nome;
}

void Pessoa::setNome(string Nome) {
	this->nome = nome;
}

string Pessoa::getMorada() const{
	return this->morada;
}

void Pessoa::setMorada(string Morada) {
	this->morada = morada;
}

unsigned int Pessoa::getNoContribuinte() const{
	return this->noContribuinte;
}

void Pessoa::setNoContribuinte(unsigned int No_Contribuinte) {
	this->noContribuinte = noContribuinte;
}

bool Pessoa::compare (Pessoa * p1, Pessoa * p2)
{
	if (p1->getNome() < p2->getNome())
		return true;
	else
		return false;
}
