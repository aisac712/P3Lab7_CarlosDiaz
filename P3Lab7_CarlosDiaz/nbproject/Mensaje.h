#ifndef MENSAJE_H
#define MENSAJE_H

#include <vector>           //librería estándar de los vectores
#include <string>

using std::vector;
using std::string;
using std::to_string;

class Mensaje {
public:
    Mensaje();
    Mensaje(const Mensaje& orig);
    virtual ~Mensaje();
    
    int    getLlave();
    void   setContenido(string);
    string getContenido();
private:
    int llave;
    string contenido;
};

#endif /* MENSAJE_H */

