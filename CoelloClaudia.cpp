#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

const string NOMBRE_CLAUDIA_COELLO = "Claudia Coello Gabriela Toapanta";
const string CEDULA_CLAUDIA_COELLO = "1726416892";
const string ARCHIVO_CLAUDIA_COELLO = "C:\\Users\\ccoel\\OneDrive\\Escritorio\\Progra I\\Bim 2\\src\\output\\output\\ccNumero.txt";
const string ALFA_CLAUDIA_COELLO = "+-123456789.,";

int const TNumero = 10;
int const TE = -1;
enum Estado { q0, q1, q2, q3, q4 };

int const MT_CLAUDIA_COELLO[5][6] =
{
    /* +   -   S   N      .    ,    */
    {q1,  q1,  q4,  q1,   q4,   q4},  // Estado q0 (inicio)
    {q4,  q4,  q4,  q1,   q2,   q2},  // Estado q1 (parte entera)
    {q4,  q4,  q4,  q3,   q4,   q4},  // Estado q2 (parte decimal)
    {q4,  q4,  q4,  q3,   q4,   q4},  // Estado q3 (parte decimal, aceptación)
    {q4,  q4,  q4,  q4,   q4,   q4}   // Estado q4 (estado de error)
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
        cout << aux->ccDato << endl;
        aux = aux->siguiente;
    }
}

int getIndiceAlfa(char c)
{
    int index = ALFA_CLAUDIA_COELLO.find(c);
    if (index >= 0)
        return index;
    return TE;
}

void ccPush(CCNodo*& ccPila, const string& ccDato)
{
    CCNodo* nuevoNodo = new CCNodo;
    nuevoNodo->ccDato = ccDato;
    nuevoNodo->siguiente = ccPila;
    ccPila = nuevoNodo;
}

void ccValidar(string ccPalabra, CCNodo*& ccPila, int& numerosValidos)
{
    int q = 0, l = 0;
    string numeroActual = "";

    for (auto &&c : ccPalabra)
    {
        l = getIndiceAlfa(c);
        q = MT_CLAUDIA_COELLO[q][l];

        if (q == TNumero)
        {
            numeroActual += c;
        }   
        else if (q == TE)
        {
            cout << "ERROR" << endl;
            break;
        }
    }

    if (!numeroActual.empty())
    {
        ccPush(ccPila, numeroActual);
        numerosValidos++;
    }
}

bool ccReadArchivo(string ccNombreArchivo, CCNodo*& ccPila, int& numerosValidos)
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

        while (!f.eof())
        {
            getline(f, line);

            ccValidar(line, ccPila, numerosValidos);

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
    int numerosValidos = 0;
    
    if (ccReadArchivo(ARCHIVO_CLAUDIA_COELLO, pila, numerosValidos))
    {
        cout << "Lineas validas en la pila:" << endl;
        ccMostrarPila(pila);
    }

    cout << "[+] Informacion del compilador lite para numeros" << endl
         << "Developer-Nombre : " << NOMBRE_CLAUDIA_COELLO << endl
         << "Developer-Cedula : " << CEDULA_CLAUDIA_COELLO << endl
         << "Valores Validos: " << numerosValidos << endl;

    // Limpia la pila de memoria
    while (pila != nullptr)
    {
        ccPop(pila);
    }

    return 0;
}
