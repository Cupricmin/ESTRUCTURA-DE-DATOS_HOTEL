// Archivo.h

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>

// Nombre del archivo donde se guardan las reservas.
const std::string ARCHIVO_RESERVAS = "reservas.txt";

// Guarda todas las reservas de la lista enlazada en reservas.txt.
// Devuelve la cantidad de reservas guardadas, o -1 si no se pudo crear el archivo.
int guardarReservas();

// Lee reservas.txt y reconstruye la lista enlazada 

int cargarReservas();

#endif
