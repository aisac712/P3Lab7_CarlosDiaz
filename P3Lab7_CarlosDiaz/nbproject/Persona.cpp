#include "Persona.h"
#include <vector>           //librería estándar de los vectores
#include <string>

using std::vector;
using std::string;
using std::to_string;

Persona::Persona(string nombre, string contra, int llave) {
    this->nombre = nombre;
    this->contra = contra;
    this->llave = llave;
    //this->mRecibidos = mRecibidos;
}

Persona::Persona(const Persona& orig) {
    //nada
}

Persona::~Persona() {
    //nada
}

string Persona::getNombre(){
    return nombre;
}

string Persona::getContra(){
    return contra;
}

int Persona::getLlave(){
    return llave;
}

vector<string> Persona::getRecibidos(){
    return mRecibidos;
}

void Persona::addMsj(string msj){
    mRecibidos.push_back(msj);
}
