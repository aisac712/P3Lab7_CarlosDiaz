#ifndef PERSONA_H
#define PERSONA_H

#include <vector>           //librería estándar de los vectores
#include <string>

using std::vector;
using std::string;

class Persona {
public:
    Persona(string, string, int);
    Persona(const Persona& orig);
    virtual ~Persona();
    
    string getNombre();
    string getContra();
    int    getLlave();
    vector<string> getRecibidos();
    void addMsj(string);
private:
    string nombre;
    string contra;
    int llave;
    vector<string> mRecibidos;
};

#endif /* PERSONA_H */

