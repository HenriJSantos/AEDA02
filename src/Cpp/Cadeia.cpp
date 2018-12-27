#include "Cadeia.h"
#include <fstream>
#include <algorithm>
#include <iomanip>

Cadeia::Cadeia(string nome)
{
	this->nome = nome;
}

string Cadeia::getNome() {
	return this->nome;
}

void Cadeia::setNome(string nome) {
	this->nome = nome;
}

void Cadeia::addFarmacia(Farmacia* farm) {
	this->farmacias.push_back(farm);
	sort(this->farmacias.begin(),this->farmacias.end(), Farmacia::compare);
}

void Cadeia::rmFarmacia(string nomeFarm) {
	bool removed;
	for (unsigned int i = 0; i < this->farmacias.size(); i++)
	{
		if (this->farmacias[i]->getNome() == nomeFarm)
		{
			removed = true;
			delete this->farmacias[i];
			this->farmacias.erase(this->farmacias.begin()+i);
		}
	}
	if (!removed)
		throw(NaoExisteFarmacia(nomeFarm));
}

void Cadeia::addFuncionario(Funcionario* func)
{
	this->funcionarios.push_back(func);
	sort(this->funcionarios.begin(),this->funcionarios.end(), Pessoa::compare);
}

void Cadeia::rmFuncionario(unsigned int contribFunc)
{
	bool removed;
	for (unsigned int i = 0; i < this->funcionarios.size(); i++)
	{
		if (this->funcionarios[i]->getNoContribuinte() == contribFunc)
		{
			removed = true;
			delete this->funcionarios[i];
			this->funcionarios.erase(this->funcionarios.begin()+i);
		}
	}
	if (!removed)
		throw(NaoExistePessoa(contribFunc, "Funcionário"));
}

void Cadeia::addCliente(Cliente* cliente)
{
	clientes.insert(cliente);
}

void Cadeia::rmCliente(string nome, unsigned int contribCliente, string distrito)
{
	Cliente tempCliente(nome, "", contribCliente, distrito);
	set<Cliente*, classcomp>::iterator itr;
	itr = clientes.find(&tempCliente);
	if(itr == clientes.end())
		throw(NaoExistePessoa(contribCliente, "Cliente"));
	else
	{
		delete itr;
		this->clientes.erase(itr);
	}
}

void Cadeia::addVenda(Venda* venda)
{
	this->vendas.push_back(venda);
	sort(this->vendas.begin(),this->vendas.end(),Venda::compare);
}

void Cadeia::rmVenda(unsigned int id)
{
	bool removed = false;
	int left = 0, right = this->vendas.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (this->vendas[middle]->getId() < id)
			left = middle + 1;
		else if (id < this->vendas[middle]->getId())
			right= middle - 1;
		else
		{
			removed = true;
			delete this->vendas[middle];
			this->vendas.erase(this->vendas.begin() + middle);
		}
	}
	if(!removed)
		throw(NaoExisteVenda(id));
}

Farmacia* Cadeia::getFarmaciaComNome(string nomeFarm)
{
	int left = 0, right = this->farmacias.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (this->farmacias[middle]->getNome() < nomeFarm)
			left = middle + 1;
		else if (nomeFarm < this->farmacias[middle]->getNome())
			right= middle - 1;
		else
			return this->farmacias[middle]; // encontrou
	}
	throw(NaoExisteFarmacia(nomeFarm));
}

Funcionario* Cadeia::getFuncionarioComNome(string nome)
{
	int left = 0, right = this->funcionarios.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (this->funcionarios[middle]->getNome() < nome)
			left = middle + 1;
		else if (nome < this->funcionarios[middle]->getNome())
			right= middle - 1;
		else
			return this->funcionarios[middle]; // encontrou
	}
	throw(NaoExistePessoa(nome, "Funcionário"));
}

Cliente* Cadeia::getClienteComNoContribuinte(unsigned int noContribuinte)
{
	set<Cliente*, classcomp>::iterator itr;
	for (itr = clientes.begin(); itr != clientes.end(); itr++)
	{
		if ((*itr)->getNoContribuinte() == noContribuinte)
		{
			return *itr;
		}
	}
	throw(NaoExistePessoa(noContribuinte, "Cliente"));
}

Funcionario* Cadeia::getFuncionarioComNoContribuinte(unsigned int noContribuinte)
{
	for (unsigned int i = 0; i < this->funcionarios.size(); i++)
	{
		if (this->funcionarios[i]->getNoContribuinte() == noContribuinte)
		{
			return this->funcionarios[i];
		}
	}
	throw(NaoExistePessoa(noContribuinte, "Funcionario"));
}

Cliente* Cadeia::getClienteComNome(string nome)
{
	set<Cliente*, classcomp>::iterator itr;
	for (itr = clientes.begin(); itr != clientes.end(); itr++)
	{
		if ((*itr)->getNome() == nome)
		{
			return *itr;
		}
	}
	throw(NaoExistePessoa(nome, "Cliente"));
}

vector<Funcionario* > Cadeia::getFuncionariosDaFarmacia(Farmacia* farm){

	vector<Funcionario* > funcs;

	for(unsigned int i = 0; i < this->funcionarios.size();i++){
		if(funcionarios.at(i)->getFarmacia() == farm){
			funcs.push_back(funcionarios.at(i));
		}
	}
	return funcs;
}


void Cadeia::exportarCadeia()
{
	string fileName = "Farmácias " + this->nome;
	ofstream out;

	out.open("Output/Cadeias/" + fileName + ".txt");
	out << "Farmacias:\n";
	for (unsigned int i = 0; i < this->farmacias.size(); i++)
	{
		out << "   Farmacia " << this->farmacias[i]->getNome() << ":" << endl;
		out << "      Morada: " << this->farmacias[i]->getMorada() << endl;
		out << "      Gerente: " << this->farmacias[i]->getGerente() << endl << endl;
	}
	out << "Funcionarios:\n";
	for (unsigned int i = 0; i < this->funcionarios.size(); i++)
	{
		out << "   Nome: " << this->funcionarios[i]->getNome() << endl;
		out << "   No. Contribuinte: " << this->funcionarios[i]->getNoContribuinte() << endl;
		out << "   Morada: " << this->funcionarios[i]->getMorada() << endl;
		out << "   Distrito: " << this->funcionarios[i]->getDistrito() << endl;
		out << "   Salário: " << this->funcionarios[i]->getSalario() << endl;
		out << "   Farmácia: " << ((this->funcionarios[i]->getFarmacia() == NULL)? "Nenhuma" : this->funcionarios[i]->getFarmacia()->getNome()) << endl;
		out << "   Cargo: " << this->funcionarios[i]->getCargo() << endl;
		out << "   Password: " << this->funcionarios[i]->getPassword() << endl << endl;
	}
	out << "Clientes:\n";
	set<Cliente*, classcomp>::iterator itr;
	for (itr = clientes.begin(); itr != clientes.end(); itr++)
	{
		out << "   Nome: " << (*itr)->getNome() << endl;
		out << "   No. Contribuinte: " << (*itr)->getNoContribuinte() << endl;
		out << "   Morada: " << (*itr)->getMorada() << endl;
		out << "   Distrito: " << (*itr)->getDistrito() << endl;
		out << "   Historial:" << endl;
		if((*itr)->getHistorial().size()==0){
			out << "     Nenhuma compra efetuada" << endl;
		}
		for(unsigned int j = 0; j < (*itr)->getHistorial().size(); j++){
			out << "     Compra " << (*itr)->getHistorial().at(j)->getId() << ":" << endl;
			out << "       Funcionario: " << (*itr)->getHistorial().at(j)->getFuncionario() << endl;
			out << "       Data: " << (*itr)->getHistorial().at(j)->getData() << endl;
			out << "       Hora: " << (*itr)->getHistorial().at(j)->getHora() << endl;
			out << "       Produtos: " << endl;
			for(unsigned int k=0; k < (*itr)->getHistorial().at(j)->getItens().size(); k++){
				out << "         Produto: " << (*itr)->getHistorial().at(j)->getItens().at(k).getNome() << endl;
				out << "         Quantidade: " << (*itr)->getHistorial().at(j)->getItens().at(k).getQuant() << endl;
				out << "         Preco Unidade: " << (*itr)->getHistorial().at(j)->getItens().at(k).getPrecUnid() << "€" << endl;
				out << "         Iva: " << (*itr)->getHistorial().at(j)->getItens().at(k).getIva() << "%" << endl;
				out << "         Comparticipacao: " << setprecision(2) << fixed << (*itr)->getHistorial().at(j)->getItens().at(k).getCompart() << "€" << endl;
				out << "         Subtotal: " << setprecision(2) << fixed << (*itr)->getHistorial().at(j)->getItens().at(k).getSubtotal() << "€" << endl << endl;
			}
			out << "       Total: " << (*itr)->getHistorial().at(j)->getTotal() << endl;
			out << endl;
		}
	}
	out.close();
}

Cadeia::Cadeia(string nomeFicheiro, string nome)
{
	ifstream in;
	in.open("Output/Cadeias/Farmácias "+nomeFicheiro+".txt");
	string line;
	this->nome = nome;
	if (in.is_open())
	{
		getline(in,line);
		while(getline(in,line) && line != "Funcionarios:")
		{
			string nome = line.substr(12);
			nome.erase(nome.size()-1);

			getline(in,line);
			string morada = line.substr(14);

			getline(in,line);
			string gerente = line.substr(15);

			Farmacia* f = new Farmacia(nome,morada);
			f->setGerente(gerente);
			this->addFarmacia(f);

			getline(in,line);
		}

		while(getline(in,line) && line != "Clientes:")
		{
			string nome = line.substr(9);

			getline(in,line);
			unsigned int noContribuinte = stoi(line.substr(21));

			getline(in,line);
			string morada = line.substr(11);

			getline(in,line);
			string distrito = line.substr(13);

			getline(in,line);
			unsigned int salario = stoi(line.substr(12));

			getline(in,line);
			string nomeFarmacia = line.substr(13);
			Farmacia* f;
			if (nomeFarmacia == "Nenhuma")
				f = NULL;
			else
				f = this->getFarmaciaComNome(nomeFarmacia);

			getline(in,line);
			string cargo = line.substr(10);

			getline(in,line);
			string password = line.substr(13);

			Funcionario* func = new Funcionario(nome, morada, noContribuinte, distrito, salario, password);
			func->setFarmacia(f);
			func->setCargo(cargo);
			this->addFuncionario(func);

			getline(in,line);

		}
		getline(in, line);
		while (!in.eof())
		{
			string nome = line.substr(9);

			getline(in,line);
			unsigned int noContribuinte = stoi(line.substr(21));

			getline(in,line);
			string morada = line.substr(11);

			getline(in,line);
			string distrito = line.substr(13);

			Cliente* cl = new Cliente(nome,morada,noContribuinte, distrito);
			this->addCliente(cl);

			getline(in,line);
			getline(in,line);
			if (line == "     Nenhuma compra efetuada")
				getline(in,line);
			else
			{
				do
				{
					unsigned int idCompra = stoi(line.substr(12,line.size()-13));
					if(Venda::getProxId()-1<idCompra)
						Venda::setProxId(idCompra+1);

					getline(in,line);
					string nomeFunc = line.substr(20);

					getline(in,line);
					string data = line.substr(13);

					getline(in,line);
					string hora = line.substr(13);

					Venda* v = new Venda(nomeFunc,data,hora, idCompra);

					getline(in,line);
					while(getline(in,line) && line.substr(0,13) != "       Total:")
					{
						string nome = line.substr(18);

						getline(in,line);
						unsigned int quant = stoi(line.substr(21));

						getline(in,line);
						float precUnid = stof(line.substr(24,line.size()-25));

						getline(in,line);
						unsigned int iva = stoi(line.substr(14,line.size()-15));

						getline(in,line);
						float compart = stof(line.substr(26,line.size()-27));

						getline(in,line);
						float subtotal = stof(line.substr(19,line.size()-20));

						ItemVenda item(Produto::getProdutoComNome(nome)->getCodigo(), quant, iva, precUnid, compart, subtotal);
						v->loadItem(item);

						getline(in,line);
					}
					float total = stof(line.substr(14,line.size()-15));
					v->setTotal(total);
					cl->addCompra(v);
					this->addVenda(v);
					getline(in,line);
					getline(in,line);
				} while(line.substr(0,11) == "     Compra");
			}
		}
		in.close();
	}
	else
		throw(CadeiaInexistente(nome));
}

Cadeia::~Cadeia()
{
	while(!this->clientes.empty())
	{
		delete *(this->clientes.begin());
		this->clientes.erase(this->clientes.begin());
	}

	while(!this->farmacias.empty())
	{
		delete this->farmacias[0];
		this->farmacias.erase(this->farmacias.begin());
	}

	while(!this->funcionarios.empty())
	{
		delete this->funcionarios[0];
		this->funcionarios.erase(this->funcionarios.begin());
	}

	while(!this->vendas.empty())
	{
		delete this->vendas[0];
		this->vendas.erase(this->vendas.begin());
	}
}

std::ostream& operator<< (ostream & out, Cadeia &cadeia){

	out << "------" << endl;
	out << "Cadeia " << cadeia.nome << endl << endl;
	out << "------" << endl;
	out << "Farmacias da Cadeia:" << endl << endl;
	for(unsigned int i = 0; i<cadeia.farmacias.size(); i++){
		out << *cadeia.farmacias.at(i) << endl;
	}
	out << "Funcionarios da Cadeia:" << endl << endl;
	for(unsigned int i = 0; i<cadeia.funcionarios.size(); i++){
		out << *cadeia.funcionarios.at(i) << endl;
	}
	out << "Clientes da Cadeia:" << endl << endl;
	set<Cliente*, classcomp>::iterator itr;
	for (itr = cadeia.clientes.begin(); itr != cadeia.clientes.end(); itr++)
	{
		out << *itr << endl;
	}
	out << "Vendas da Cadeia:" << endl << endl;
	for(unsigned int i = 0; i<cadeia.vendas.size(); i++){
		out << *cadeia.vendas.at(i) << endl;
	}
	out << "----------------------" << endl;
	out << "Final de visualização." << endl;
	out << "----------------------" << endl;
	return out;
}

