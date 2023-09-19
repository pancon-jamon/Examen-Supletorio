
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include "C:\\Users\\ccoel\\OneDrive\\Escritorio\\Progra I\\Bim 2\\src\\output\\ccLib.h"

using namespace std;

const string NOMBRE_CLAUDIA_COELLO = "Claudia Coello Gabriela Toapanta";
const string CEDULA_CLAUDIA_COELLO = "1726416892";
const string ARCHIVO_CLAUDIA_COELLO = "C:\\Users\\ccoel\\OneDrive\\Escritorio\\Progra I\\Bim 2\\src\\output\\output\\ccNumero.txt";
string const ALFA = "+-123456789.,";

int const TNumero = 10;
int const TE = -1;

int const MT_CLAUDIA_COELLO[5][5] =
{        /* +   -   S   N      .    ,    */
    /*q0*/{0,  0,  1,   -1,  -1},  // Estado q0 (inicio)
    /*q1*/{-1, -1, 1,   2,    2},  // Estado q1 (parte entera)
    /*q2*/{-1, -1,  3,  -1,  -1},  // Estado q2 (parte decimal)
    /*q3*/{-1, -1,  3,  -1, -1,},  // Estado q3 (parte decimal, aceptación)
    /*q4*/{-1,  -1, TNumero,  -1}   // Estado q4 (signo después del inicio)
};


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
        cout << "\t" << aux->ccDato << endl;
        aux = aux->siguiente;
    }
}

int getIndiceAlfa(char c)
{
    int index = ALFA.find(c);
    if (index >= 0)
        return index;
    return TE;
}

tuple<bool, CCNodo*> ccValidar(string ccPalabra)
{
    int q = 0, l = 0;
    bool esValido = true;
    CCNodo* pila = nullptr;

    for (auto &&c : ccPalabra)
    {
        l = getIndiceAlfa(c);
        q = MT_CLAUDIA_COELLO[q][l];

        if (q == TE)
        {
            cout << setColor(red) << "ERROR" << endl;
            esValido = false;
            break;
        }
    }

    return make_tuple(esValido, pila);
}

void ccPush(CCNodo*& ccPila, const string& ccDato)
{
    CCNodo* nuevoNodo = new CCNodo;
    nuevoNodo->ccDato = ccDato;
    nuevoNodo->siguiente = ccPila;
    ccPila = nuevoNodo;
}

bool ccReadArchivo(string ccNombreArchivo, CCNodo*& ccPila)
{
    ifstream f;
    string line;
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
            if (line.empty()) continue; // Saltar líneas vacías
            bool esValido;
            CCNodo* pilaTemporal = nullptr;
            tie(esValido, pilaTemporal) = ccValidar(line);
            
            if (esValido)
            {
                ccPush(ccPila, line);
            }
            else
            {
                // Manejar el caso de líneas no válidas si es necesario
            }

            lineNumber++;
        }

        f.close();

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
    CCNodo* pila = nullptr;
    
    if (ccReadArchivo(ARCHIVO_CLAUDIA_COELLO, pila))
    {
        cout << "Lineas validas en la pila:" << endl;
        ccMostrarPila(pila);
    }

    cout << setColor(gris) << "[+] Informacion del compilador lite para numeros" << endl
         << "Developer-Nombre : " << NOMBRE_CLAUDIA_COELLO << endl
         << "Developer-Cedula : " << CEDULA_CLAUDIA_COELLO << endl;

    return 0;
}
