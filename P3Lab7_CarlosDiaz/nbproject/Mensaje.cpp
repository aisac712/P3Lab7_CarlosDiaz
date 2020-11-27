#include "Mensaje.h"
#include <vector>           //librería estándar de los vectores
#include <string>

using std::vector;
using std::string;
using std::to_string;

Mensaje::Mensaje() {
}

Mensaje::Mensaje(const Mensaje& orig) {
}

Mensaje::~Mensaje() {
}

int Mensaje::getLlave(){
    return llave;
}

void Mensaje::setContenido(string mensaje){
    this->contenido=mensaje;
}

string Mensaje::getContenido(){
    return contenido;
}