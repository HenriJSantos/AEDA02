#include "Cliente.h"

Cliente::Cliente(string nome, string morada, unsigned int noContribuinte, string distrito) : Pessoa(nome, morada, noContribuinte, distrito) {}

void Cliente::addCompra(Venda* compra) {
	this->historial.push_back(compra);
}

void Cliente::rmCompra(unsigned int idCompra) {
	bool removed;
	for (unsigned int i = 0; i < this->historial.size(); i++)
	{
		if (this->historial[i]->getId() == idCompra)
		{
			removed = true;
			this->historial.erase(this->historial.begin()+i);
		}
	}
	if (!removed)
		throw(CompraInexistente(idCompra));
}

vector<Venda*> Cliente::getHistorial() {
	return this->historial;
}

std::ostream& operator<< (ostream & out, Cliente &cli){
	out << "Nome: " << cli.getNome() << endl;
	out << "No. de Contribuinte: " << cli.getNoContribuinte() << endl;
	out << "Morada: " << cli.getMorada() << endl;
	out << "Distrito: " << cli.getDistrito() << endl;
	return out;
}
