#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include "C:\\Users\ccoel\\OneDrive\\Escritorio\\Progra I\\Bim 2\\src\output\\ccLib.h"

using namespace std;

const string NOMBRE_CLAUDIA_COELLO = "Claudia Coello Gabriela Toapanta";
const string CEDULA_CLAUDIA_COELLO = "1726416892";
const string ARCHIVO_CLAUDIA_COELLO = "C:\\Users\\ccoel\\OneDrive\\Escritorio\\Progra I\\Bim 2\\src\\output\\output\\ccNumero.txt";

struct ccNumero
{
    string ccNumero;
};

struct CCNodo
{
    string ccDato;
    CCNodo* siguiente;
};

void ccPop(CCNodo*& ccPila)
{
    if (ccPila != nullptr)
    {
        CCNodo* nodoAEliminar = ccPila;
        ccPila = ccPila->siguiente;
        delete nodoAEliminar;
    }
}

void ccMostrarPila(CCNodo* ccPila)
{
    CCNodo* aux = ccPila;
    while (aux != nullptr)
    {
        cout << setColor(green);
        mostrarPorcentaje();
        //cout << "\t   " << ccPila->ccDato.capacidadBelica << ",  " << ccPila->ccDato.geolocalizacion << ",   " << ccPila->ccDato.tipoArsenal << endl;
        cout << "\t" << aux->ccDato << endl;
        aux = aux->siguiente;
    }
    
}

void ccPush(CCNodo*& ccPila, const string& ccDato)
{
    CCNodo* nuevoNodo = new CCNodo;
    nuevoNodo->ccDato = ccDato;
    nuevoNodo->siguiente = ccPila;
    ccPila = nuevoNodo;
}

bool ccReadArchivo(string ccNombreArchivo)
{
    ifstream f;
    string line;
    CCNodo* pila = nullptr;
    try
    {
        f.open(ccNombreArchivo);
        if (!f.is_open())
        {
            cout << "Error al abrir el archivo " << ccNombreArchivo << endl;
            return false;
        }

        int lineNumber = 0;

        while (getline(f, line))
        {

            ccPush(pila, line); // Agregar línea a la pila
            lineNumber++;

            lineNumber++;
        }

        f.close();

        // Mostrar datos de la pila
        ccMostrarPila(pila);

        // Limpiar la pila
        while (pila != nullptr)
        {
            ccPop(pila);
        }

        return true;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

int main()
{

    cout << "[+] Informacion del compilador lite para numeros" << endl
         << "Developer-Nombre : " << NOMBRE_CLAUDIA_COELLO << endl
         << "Developer-Cedula : " << CEDULA_CLAUDIA_COELLO << endl;
    ccReadArchivo(ARCHIVO_CLAUDIA_COELLO);
    

    return 0;
}
