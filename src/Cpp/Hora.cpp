#include "Hora.h"
#include <time.h>
#include <iomanip>

Hora::Hora(unsigned int h, unsigned int m, unsigned int s) {
	this->hora = h;
	this->minuto = m;
	this->segundo = s;
}

Hora::Hora() {
	time_t currentTime;
	time(&currentTime);
	struct tm *myTime = localtime(&currentTime);
	this->hora=myTime->tm_hour;
	this->minuto=myTime->tm_min;
	this->segundo=myTime->tm_sec;
}

unsigned int Hora::getHora(){
	return this->hora;
}

void Hora::setHora(unsigned int h){
	this->hora = h;
}

unsigned int Hora::getMinutos(){
	return this->minuto;
}

void Hora::setMinutos(unsigned int m){
	this->minuto = m;
}

unsigned int Hora::getSegundos(){
	return this->segundo;
}

void Hora::setSegundos(unsigned int s){
	this->segundo = s;
}

ostream & operator<<(ostream & o, const Hora & h){
	o << setfill('0') << setw(2) << h.hora << ":" << h.minuto << ":" << h.segundo;
	return o;
}
