#include "Funcionario.h"

Funcionario::Funcionario(string nome, string morada, unsigned int noContribuinte, string distrito, unsigned int salario, string password) : Pessoa(nome, morada, noContribuinte, distrito){
	this->salario = salario;
	this->farm = NULL;
	this->cargo = "Funcionario";
	this->password = password;
}

unsigned int Funcionario::getSalario() {
	return this->salario;
}

void Funcionario::setSalario(unsigned int salario) {
	this->salario = salario;
}

Farmacia* Funcionario::getFarmacia() {
	return this->farm;
}

void Funcionario::setFarmacia(Farmacia* farmacia) {
	this->farm = farmacia;
}

string Funcionario::getCargo() {
	return this->cargo;
}

void Funcionario::setCargo(string Cargo) {
	this->cargo = Cargo;
}

string Funcionario::getPassword()
{
	return this->password;
}

void Funcionario::setPassword(string password)
{
	this->password = password;
}

bool Funcionario::operator== (const Funcionario & f) const
{
	if(this->getNoContribuinte() == f.getNoContribuinte())
		return true;
	else
		return false;
}

std::ostream& operator<< (ostream & out, Funcionario & func){
	out << "Nome do Funcionario: " << func.getNome() << endl;
	out << "No. de Contribuinte: " << func.getNoContribuinte() << endl;
	out << "Morada: " << func.getMorada() << endl;
	out << "Distrito: " << func.getDistrito() << endl;
	out << "Salario: " << func.getSalario() << endl;
	if(func.getFarmacia()!=NULL){
		out << "Farmacia de servico: " << func.getFarmacia()->getNome() << endl;
	}
	else{
		out << "Farmacia de servico: " << "Nenhuma" << endl;
	}
	out << "Cargo: " << func.getCargo() << endl;

	return out;
}
