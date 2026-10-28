// Pila.cpp

#include <iostream> // Permite mostrar mensajes.
#include <string>   // Permite usar textos.
#include "Pila.h"

using namespace std;

// Puntero al ultimo nodo de la pila.
NodoPila* tope = NULL;

// Pila auxiliar para mostrar el historial.
static NodoPila* topeAuxiliar = NULL;

// Pasa un nodo de una pila a otra.
static void moverNodo(NodoPila*& origen, NodoPila*& destino)
{
    NodoPila* nodo = origen; // Guarda el nodo actual.
    origen = nodo->siguiente; // Avanza la pila de origen.
    nodo->siguiente = destino; // Enlaza el nodo con el destino.
    destino = nodo; // Actualiza el tope del destino.
}

// Agrega una operacion al tope de la pila.
void apilarOperacion(const string& operacion)
{
    NodoPila* nuevo = new NodoPila; // Crea un nodo.
    nuevo->operacion = operacion; // Guarda la operacion.
    nuevo->siguiente = tope; // Enlaza con el antiguo tope.
    tope = nuevo; // Actualiza el tope.

    cout << "[Historial] Operacion apilada: " << operacion << endl;
}

// Retira la operacion que esta en el tope.
bool desapilarOperacion()
{
    // Comprueba si la pila esta vacia.
    if (tope == NULL)
    {
        cout << "Error: la pila esta vacia, no hay operaciones para desapilar.\n";
        return false;
    }

    NodoPila* aux = tope; // Guarda el nodo que se retirara.
    string texto = aux->operacion; // Guarda el texto de la operacion.
    tope = tope->siguiente; // Actualiza el tope.
    delete aux; // Libera la memoria del nodo.

    cout << "Operacion desapilada con exito: " << texto << endl;

    return true;
}

// Muestra la ultima operacion sin retirarla.
void mostrarTope()
{
    // Comprueba si hay operaciones.
    if (tope == NULL)
    {
        cout << "\nEl historial esta vacio.\n";
        return;
    }

    cout << "\nUltima operacion realizada: " << tope->operacion << endl;
}

// Muestra el historial sin cambiar el orden de la pila.
void mostrarHistorial()
{
    cout << "\n--- HISTORIAL DE OPERACIONES (la mas reciente primero) ---\n";

    // Comprueba si hay operaciones guardadas.
    if (tope == NULL)
    {
        cout << "El historial esta vacio.\n";
        return;
    }

    int numero = 1;

    // Muestra las operaciones y las pasa a la pila auxiliar.
    while (tope != NULL)
    {
        cout << numero << ". " << tope->operacion << endl;
        moverNodo(tope, topeAuxiliar);
        numero++;
    }

    // Devuelve las operaciones a la pila principal.
    while (topeAuxiliar != NULL)
    {
        moverNodo(topeAuxiliar, tope);
    }
}

// Elimina todos los nodos de la pila.
void liberarPila()
{
    while (tope != NULL)
    {
        NodoPila* aux = tope; // Guarda el nodo actual.
        tope = tope->siguiente; // Avanza al siguiente nodo.
        delete aux; // Libera la memoria.
    }
}
