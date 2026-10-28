// Pila.h
// Módulo de PILA: historial de operaciones del sistema (LIFO), hecho con nodos y punteros.
#ifndef PILA_H
#define PILA_H

#include <string>

// Nodo de la pila: guarda el texto de una operación y apunta al nodo de abajo.
struct NodoPila
{
    std::string operacion; // Descripción de la acción realizada
    NodoPila* siguiente;   // Puntero al nodo que está debajo en la pila
};

// Apila (push) una nueva operación en el tope del historial.
void apilarOperacion(const std::string& operacion);

// Desapila (pop) la última operación registrada. Devuelve false si la pila estaba vacía.
bool desapilarOperacion();

// Muestra solo la última operación (la que está en el tope).
void mostrarTope();

// Muestra todo el historial, de la operación más reciente a la más antigua.
void mostrarHistorial();

// Libera con delete todos los nodos de la pila (al cerrar el programa).
void liberarPila();

#endif
