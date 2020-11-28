#include <iostream>
#include <vector>           //librería estándar de los vectores
#include <string>           //librería estándar de las cadenas
#include <bits/stdc++.h>    //para hacer string to charArray
#include <math.h>           //para usar la funcion ceil() q redondea al entero mayor
#include <sstream>          //parsear string a int en mi token:                 en [0] está destinatario; en[1] el mensaje encriptado; y en [2] la llave

#include "nbproject/Persona.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::to_string;

//prototipo de funciones
//bool estadoRegistro(vector<Persona>, int, string, string);      //identifica si un usuario está registrado en el feisbu
string encriptamiento(bool, string, int);

int main(int argc, char** argv) {
    int op = 0, sizeV=0;
    vector<Persona*> pRegistrados;                                  //almacena los usuarios registrados en el sistema
    
    
    while(op!=3){
        cout << "   FEISBU CRÍPTICO" << endl;
        cout << "1. Registrarse" << endl;
        cout << "2. Ingresar" << endl;
        cout << "3. Salir" << endl;
        cout << "" << endl;
        cout << "Ingresa opción: ";
        cin  >> op;
        
        cout << "" <<  endl;
        switch(op){
            case 1: {
                string nombre="", contra="";
                cout << "   SIGN IN" << endl;
                cout << "Ingresar nombre: ";
                cin >> nombre;
                cout << "Ingresar contraseña: ";
                cin >> contra;
                
                int llave = (1) + rand()%((15+1) - (1));
                cout << "Llave de encriptación: " << to_string(llave) << endl;
                
                Persona* temp = new Persona(nombre, contra, llave);
                
                cout <<  temp->getNombre() << "*" << endl;
                
                //Persona temp(nombre, contra, llave);
                
                pRegistrados.push_back(temp);
                //cout << pRegistrados[0] -> getNombre() << " n" << endl;
                //cout << to_string(pRegistrados.size()) << "*" << endl;
                sizeV++;
                
                cout << "Cuenta creada exitosamente" << endl;
            } break;
            case 2: {
                string nombre="", contra="";
                cout << "   LOG IN" << endl;
                cout << "Ingresar nombre: ";
                cin >> nombre;
                cout << "Ingresar contraseña: ";
                cin >> contra;
                
                //buscar usuario entre los registrados
                bool reg = false;
                int posUser = 0;
                for(int i=0; i<pRegistrados.size(); i++){
                    if(pRegistrados[i]->getNombre()==nombre && pRegistrados[i]->getContra()==contra){
                        reg = true;
                        posUser = i;                                            //VARIABLE IMPORTANTE: ES LA POSICIóN (dentro del vector) DE LA PERSONA QUE SE LOGEO
                        break;
                    }
                }
                
                if(reg){
                    int op2 = 0;
                    cout << "Bienvenido " << pRegistrados[posUser]->getNombre() << endl;
                    while(op2!=4){
                        cout << "1. Enviar mensaje" << endl;
                        cout << "2. Ver mensajes" << endl;
                        cout << "3. Ver mi llave" << endl;
                        cout << "4. Salir" << endl;
                        cout << "" << endl;
                        cout << "Ingresa opción: ";
                        cin >> op2;
                        switch(op2){
                            case 1: {
                                int posDestinatario=0;
                                string mensaje="";
                                cout << "USUARIOS EN EL SISTEMA" << endl;
                                for(int i=0; i<pRegistrados.size(); i++){
                                    cout << i << ".- " << pRegistrados[i]->getNombre() << endl;
                                }
                                
                                cout << "¿A quién le vas a enviar el mensaje?: ";
                                cin >> posDestinatario;
                                while(posDestinatario<0 || posDestinatario>=pRegistrados.size()){
                                    cin >> posDestinatario;
                                }
                                
                                cout << "Mensaje: ";
                                cin >> mensaje;
                                
                                //cout << to_string(pRegistrados[posDestinatario]->getLlave());
                                int llave = pRegistrados[posDestinatario]->getLlave();
                                string mensajeEncriptado = encriptamiento(true, mensaje, llave);
                                cout << "Mensaje encriptado = " << mensajeEncriptado << endl;
                                
                                string lineaUsuario = "Mensaje de " + pRegistrados[posUser]->getNombre() +"#";
                                lineaUsuario += mensajeEncriptado + "#";
                                lineaUsuario += to_string( pRegistrados[posDestinatario]->getLlave() )+"#";
                                
                                pRegistrados[posDestinatario]->addMsj(lineaUsuario);
                                
                                cout << "Mensaje enviado correctamente a " << pRegistrados[posDestinatario]->getNombre() << endl;
                            } break;
                            case 2: {
                                int msjVer=0;
                                cout << "MENSAJES RECIBIDOS" << endl;
                                for(int i=0; i< (pRegistrados[posUser]->getRecibidos().size()); i++){
                                    
                                    string lineaUsuario = pRegistrados[posUser]->getRecibidos().at(i);                      //El mensajese ve: Mensaje de aisoc#hola#3
                                    vector<string> tokensMensaje;
                                    
                                    for (auto j = strtok(&lineaUsuario[0], "#"); j != NULL; j = strtok(NULL, "#")){         //uso tokens envés de objetos jeje
                                        tokensMensaje.push_back(j);                                                         //en [0] está destinatario; [1] el mensaje encriptado; [2] la llave
                                    }
                                    
                                    cout << i << ".- " << tokensMensaje[0] << " " << tokensMensaje[1] << endl;;                                        //imprime: hola
                                }
                                cout << "" << endl;
                                if(pRegistrados[posUser]->getRecibidos().size()!=0){
                                    cout << "Ingrese posición del mensaje a ver: ";
                                    cin >> msjVer;

                                    string lineaUsuario = pRegistrados[posUser]->getRecibidos().at(msjVer);
                                    vector<string> tokensMensaje;

                                    for (auto j = strtok(&lineaUsuario[0], "#"); j != NULL; j = strtok(NULL, "#")){         //uso tokens envés de objetos jeje
                                        tokensMensaje.push_back(j);
                                    }

                                    std::stringstream intLlave(tokensMensaje[2]);
                                    int llave = 0; 
                                    intLlave >> llave; 

                                    string msjDesencriptado = encriptamiento(false, tokensMensaje[1], llave);     //en [0] está destinatario; [1] el mensaje encriptado; [2] la llave
                                    cout << "El mensaje dice: " << msjDesencriptado << endl;
                                    cout << "" << endl;
                                } else
                                    cout << "No tenés mensajes por mostrar" << endl;
                                
                            } break;
                            case 3: {
                                cout << "Mi llave es: " << pRegistrados[posUser]->getLlave() << endl;;
                            } break;
                            case 4: {
                                cout << "Nos vemos " << endl;
                                reg = false;
                            } break;
                            default: 
                                cout << "Opción no válida" << endl;
                        }
                    }
                } else{
                    cout << "Usuario o contraseña incorrectos. O usuario no registrado" << endl;
                }
            } break;
            case 3: {
                cout << "Nos vemos amigou" << endl;
            } break;
            default: 
                cout << "Opción no válida. Intentá de nuevo." << endl;
        }
        cout << "" <<  endl;
    }
            
    return 0;
}

/*bool estadoRegistro(vector<Persona> registrados, int sizeV, string nombre, string contra){
    cout <<  ((Persona) registrados[0]).getNombre() ;
    
    
    for(int i=0; i<sizeV; i++){
        if(((Persona) registrados.at(i)).getNombre()==nombre && ((Persona) registrados.at(i)).getContra()==contra){
            return true;
            i = sizeV;
        } else {
            return false;
        }
    }
}*/

string encriptamiento(bool encriptar, string mensaje, int llave){
    string mensaje2 = "";
    if(llave==0){
        return mensaje;
    } else{
        if(encriptar){
            
            //int llaveOriginal = llave;
            
            for(int i=0; i< ceil( (double)mensaje.size()/ (double)llave); i++){
                //cout << std::to_string( ceil( (double)mensaje.size()/ (double)llave) ) << endl;
                string cadenaReducida="";
                if(i==0){
                    //cout << mensaje.substr(0, llave) << endl;
                    cadenaReducida = mensaje.substr(0, llave);
                    
                } else {
                    //cout << mensaje.substr(llave*i, llaveOriginal) << endl;
                    cadenaReducida = mensaje.substr(llave*i, llave);
                }
                char char_array[cadenaReducida.length() + 1];
                strcpy(char_array, cadenaReducida.c_str());

                for(int j=0; j<cadenaReducida.length(); j++){
                    if(i%2==1)
                        char_array[j] = char_array[j]-llave;
                    else if(i%2==0)
                        char_array[j] = char_array[j]+llave;
                    
                    mensaje2+=char_array[j];
                }

                for(int i=0; i<cadenaReducida.length(); i++){
                    //cout << char_array[i] << " ";
                }
                //cout << "" << endl;
                
            }
            
            return encriptamiento(true, mensaje2, llave-1);
        } else{
            
            for(int i=0; i<ceil( (double)mensaje.size()/ (double)llave); i++){
                string cadenaReducida="";
                if(i==0){
                    //cout << mensaje.substr(0, llave) << endl;
                    cadenaReducida = mensaje.substr(0, llave);
                    
                } else {
                    //cout << mensaje.substr(llave*i, llaveOriginal) << endl;
                    cadenaReducida = mensaje.substr(llave*i, llave);
                }
                char char_array[cadenaReducida.length() + 1];
                strcpy(char_array, cadenaReducida.c_str());

                for(int j=0; j<cadenaReducida.length(); j++){
                    if(i%2==1)
                        char_array[j] = char_array[j]+llave;
                    else if(i%2==0)
                        char_array[j] = char_array[j]-llave;
                    
                    mensaje2+=char_array[j];
                }

                for(int i=0; i<cadenaReducida.length(); i++){
                    //cout << char_array[i] << " ";
                }
                //cout << "" << endl;
                
            }
            
            return encriptamiento(false, mensaje2, llave-1);
        }
        
        
    }
    
    
}