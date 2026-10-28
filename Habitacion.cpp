// Habitacion.cpp
// Maneja las habitaciones del hotel mediante una lista enlazada.

#include <iostream> // Permite mostrar mensajes.
#include <iomanip>  // Permite ordenar las columnas.
#include <string>   // Permite usar textos.
#include "Habitacion.h"

using namespace std;

// Primer nodo de la lista de habitaciones.
NodoHabitacion* inicioHabitaciones = NULL;

// Registra una habitacion al final de la lista.
static void registrarHabitacion(int numero, string tipo, int tarifa)
{
    NodoHabitacion* nueva = new NodoHabitacion; // Crea un nodo.
    nueva->numero = numero; // Guarda el numero.
    nueva->tipo = tipo; // Guarda el tipo.
    nueva->tarifa = tarifa; // Guarda el precio.
    nueva->estado = HAB_LIBRE; // Empieza libre.
    nueva->idReserva = 0; // No tiene reserva.
    nueva->siguiente = NULL; // No apunta a otro nodo.

    // Si la lista esta vacia, agrega el primer nodo.
    if (inicioHabitaciones == NULL)
    {
        inicioHabitaciones = nueva;
    }
    else
    {
        NodoHabitacion* actual = inicioHabitaciones; // Empieza desde el inicio.

        // Busca el ultimo nodo.
        while (actual->siguiente != NULL)
            actual = actual->siguiente;

        actual->siguiente = nueva; // Agrega la nueva habitacion.
    }
}

// Crea las 28 habitaciones del hotel.
void crearHabitaciones()
{
    // Evita crear las habitaciones mas de una vez.
    if (inicioHabitaciones != NULL)
        return;

    // Asigna el tipo y la tarifa de cada habitacion.
    for (int n = 1; n <= 28; n++)
    {
        if (n <= 8)
            registrarHabitacion(n, "Matrimonial", 80);
        else if (n <= 16)
            registrarHabitacion(n, "Doble", 80);
        else if (n <= 23)
            registrarHabitacion(n, "Triple", 120);
        else
            registrarHabitacion(n, "Cuadruple", 160);
    }
}

// Busca una habitacion por su numero.
NodoHabitacion* buscarHabitacion(int numero)
{
    NodoHabitacion* actual = inicioHabitaciones; // Empieza desde el inicio.

    while (actual != NULL)
    {
        // Comprueba si encontro la habitacion.
        if (actual->numero == numero)
            return actual;

        actual = actual->siguiente; // Avanza al siguiente nodo.
    }

    return NULL; // No encontro la habitacion.
}

// Asigna una habitacion a una reserva.
bool asignarHabitacion(int numero, int idReserva)
{
    NodoHabitacion* hab = buscarHabitacion(numero);

    // Comprueba si la habitacion existe.
    if (hab == NULL)
        return false;

    // Evita asignar una habitacion ocupada por otra reserva.
    if (hab->estado == HAB_OCUPADA && hab->idReserva != idReserva)
        return false;

    hab->estado = HAB_OCUPADA; // Marca la habitacion como ocupada.
    hab->idReserva = idReserva; // Guarda el ID de la reserva.

    return true;
}

// Deja una habitacion libre.
bool liberarHabitacion(int numero)
{
    NodoHabitacion* hab = buscarHabitacion(numero);

    // Comprueba si la habitacion existe.
    if (hab == NULL)
        return false;

    hab->estado = HAB_LIBRE; // Cambia el estado a libre.
    hab->idReserva = 0; // Elimina el ID asociado.

    return true;
}

// Muestra los datos de una habitacion.
void mostrarHabitacion(NodoHabitacion* hab)
{
    cout << "\nHabitacion: " << hab->numero << endl;
    cout << "Tipo: " << hab->tipo << endl;
    cout << "Tarifa: S/ " << hab->tarifa << endl;
    cout << "Estado: " << hab->estado << endl;

    // Muestra el ID si tiene una reserva asociada.
    if (hab->idReserva != 0)
        cout << "Reserva asociada (ID): " << hab->idReserva << endl;
}

// Muestra los datos de una habitacion en una fila.
static void imprimirFila(NodoHabitacion* hab)
{
    cout << left << setw(6) << hab->numero
         << setw(14) << hab->tipo
         << setw(12) << hab->tarifa
         << setw(10) << hab->estado;

    // Muestra el ID de la reserva.
    if (hab->idReserva != 0)
        cout << hab->idReserva;
    else
        cout << "-";

    cout << endl;
}

// Muestra los titulos de las columnas.
static void imprimirEncabezado()
{
    cout << left << setw(6) << "Hab"
         << setw(14) << "Tipo"
         << setw(12) << "Tarifa(S/)"
         << setw(10) << "Estado"
         << "Reserva(ID)" << endl;

    cout << "------------------------------------------------------\n";
}

// Muestra todas las habitaciones y su estado.
void mostrarHabitaciones()
{
    cout << "\n--- ESTADO DE LAS HABITACIONES ---\n";

    imprimirEncabezado();

    int libres = 0;
    int ocupadas = 0;

    NodoHabitacion* actual = inicioHabitaciones;

    // Recorre todas las habitaciones.
    while (actual != NULL)
    {
        imprimirFila(actual);

        // Cuenta las habitaciones libres y ocupadas.
        if (actual->estado == HAB_LIBRE)
            libres++;
        else
            ocupadas++;

        actual = actual->siguiente; // Avanza al siguiente nodo.
    }

    cout << "\nLibres: " << libres
         << " | Ocupadas: " << ocupadas << endl;
}

// Muestra solo las habitaciones libres.
void mostrarHabitacionesDisponibles()
{
    cout << "\n--- HABITACIONES DISPONIBLES ---\n";

    // Comprueba si quedan habitaciones libres.
    if (contarHabitacionesLibres() == 0)
    {
        cout << "No hay habitaciones libres.\n";
        return;
    }

    imprimirEncabezado();

    NodoHabitacion* actual = inicioHabitaciones;

    // Recorre la lista y muestra las habitaciones libres.
    while (actual != NULL)
    {
        if (actual->estado == HAB_LIBRE)
            imprimirFila(actual);

        actual = actual->siguiente; // Avanza al siguiente nodo.
    }
}

// Cuenta las habitaciones libres.
int contarHabitacionesLibres()
{
    int libres = 0;
    NodoHabitacion* actual = inicioHabitaciones;

    while (actual != NULL)
    {
        // Aumenta el contador si esta libre.
        if (actual->estado == HAB_LIBRE)
            libres++;

        actual = actual->siguiente; // Avanza al siguiente nodo.
    }

    return libres;
}

// Deja todas las habitaciones libres.
void reiniciarOcupacion()
{
    NodoHabitacion* actual = inicioHabitaciones;

    while (actual != NULL)
    {
        actual->estado = HAB_LIBRE; // Cambia el estado.
        actual->idReserva = 0; // Quita la reserva asociada.

        actual = actual->siguiente; // Avanza al siguiente nodo.
    }
}

// Elimina todos los nodos de la lista.
void borrarHabitaciones()
{
    while (inicioHabitaciones != NULL)
    {
        NodoHabitacion* aux = inicioHabitaciones; // Guarda el nodo actual.
        inicioHabitaciones = inicioHabitaciones->siguiente; // Avanza al siguiente.
        delete aux; // Libera la memoria.
    }
}
