#include <time.h>
#include <iomanip>
#include "Data.h"

Data::Data(unsigned int d, unsigned int m, unsigned int a) {
	this->dia=d;
	this->mes=m;
	this->ano=a;
}

Data::Data() {
	time_t currentTime;
	time(&currentTime);
	struct tm *myTime = localtime(&currentTime);
	this->dia=myTime->tm_mday;
	this->mes=myTime->tm_mon+1;
	this->ano=myTime->tm_year+1900;
}

unsigned int Data::getDia() {
	return this->dia;
}

void Data::setDia(unsigned int d) {
	this->dia = d;
}

unsigned int Data::getMes() {
	return this->mes;
}

void Data::setMes(unsigned int m) {
	this->mes = m;
}

unsigned int Data::getAno() {
	return this->ano;
}

void Data::setAno(unsigned int a) {
	this->ano = a;
}

ostream & operator<<(ostream & o, const Data & d) {
	o << setfill('0') << setw(2) << d.dia << "/" << setfill('0') << setw(2) << d.mes << "/" << setfill('0') << setw(2) << d.ano;
	return o;
}
