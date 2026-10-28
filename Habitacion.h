
 // Habitacion.h
// Este archivo contiene la estructura y las funciones de las habitaciones del hotel Aloinka.

#ifndef HABITACION_H
#define HABITACION_H

#include <string> // Permite trabajar con textos usando string.

// Estos son los dos estados que pueden tener las habitaciones.
const std::string HAB_LIBRE = "Libre";
const std::string HAB_OCUPADA = "Ocupada";

// Esta estructura guarda los datos de una habitación.
// Cada NodoHabitacion representa una habitación de la lista enlazada.
struct NodoHabitacion
{
    int numero;                 // Guarda el número de la habitación, del 1 al 28.
    std::string tipo;           // Guarda el tipo: Matrimonial, Doble, Triple o Cuádruple.
    int tarifa;                 // Guarda el precio por noche en soles.
    std::string estado;         // Indica si la habitación está Libre u Ocupada.
    int idReserva;              // Guarda el ID de la reserva que ocupa la habitación.
                                // Si está libre, el ID de la reserva es 0.
    NodoHabitacion* siguiente;  // Apunta al siguiente nodo de la lista enlazada.
};

// Esta función crea y registra las 28 habitaciones del hotel.
void crearHabitaciones();

// Busca una habitación usando su número.
// Devuelve un puntero a la habitación si la encuentra.
// Si no existe, devuelve NULL.
NodoHabitacion* buscarHabitacion(int numero);

// Asigna una habitación a una reserva.
// Recibe el número de la habitación y el ID de la reserva.
// Devuelve true si se realiza la asignación y false si no se puede.
bool asignarHabitacion(int numero, int idReserva);

// Busca una habitación y trata de dejarla libre.
// Devuelve true si se libera correctamente y false si no se logra.
bool liberarHabitacion(int numero);

// Muestra los datos de una sola habitación.
// Recibe un puntero a la habitación que se quiere mostrar.
void mostrarHabitacion(NodoHabitacion* hab);

// Muestra todas las habitaciones del hotel con sus datos y estados.
void mostrarHabitaciones();

// Muestra solamente las habitaciones que están libres.
void mostrarHabitacionesDisponibles();

// Cuenta las habitaciones que están libres.
// Devuelve la cantidad como un número entero.
int contarHabitacionesLibres();

// Deja todas las habitaciones en estado Libre.
// Se utiliza antes de cargar los datos guardados en el archivo.
void reiniciarOcupacion();

// Elimina los nodos de la lista enlazada y libera la memoria utilizada.
// Se utiliza al cerrar el programa para no dejar memoria ocupada.
void borrarHabitaciones();

// Finaliza la protección para evitar que este archivo se incluya varias veces.
#endif

