// Cola.cpp
// Maneja la cola de reservas usando nodos y punteros.
// Las reservas con mayor prioridad se atienden primero.

#include <iostream> // Permite mostrar mensajes.
#include <string>   // Permite usar textos.
#include "Cola.h"
#include "Reserva.h"

using namespace std; // Evita escribir std::.

// Punteros que controlan la cola.
NodoCola* frente = NULL; // Primer nodo de la cola.
NodoCola* final = NULL;  // Ultimo nodo de la cola.

// Busca la prioridad de una reserva.
static int prioridadDe(int id)
{
    Proceso* reserva = buscarPorID(id);

    if (reserva == NULL)
        return 3; // Si no existe, usa prioridad baja.

    return reserva->prioridad;
}

// Revisa si una reserva ya esta en la cola.
bool estaEnCola(int id)
{
    NodoCola* actual = frente; // Empieza desde el primer nodo.

    while (actual != NULL)
    {
        if (actual->idProceso == id)
            return true; // La reserva ya esta en la cola.

        actual = actual->siguiente; // Avanza al siguiente nodo.
    }

    return false; // No encontro la reserva.
}

// Agrega una reserva segun su prioridad.
bool encolarPorID(int id)
{
    Proceso* reserva = buscarPorID(id);

    if (reserva == NULL)
        return false; // No existe la reserva.

    NodoCola* nuevo = new NodoCola(); // Crea un nuevo nodo.
    nuevo->idProceso = id;            // Guarda el ID.
    nuevo->siguiente = NULL;          // No apunta a otro nodo.

    int prioridad = reserva->prioridad; // Guarda la prioridad.

    // Si la cola esta vacia, el nodo ocupa ambos extremos.
    if (frente == NULL)
    {
        frente = nuevo;
        final = nuevo;
    }
    // Si tiene mayor prioridad, pasa al primer lugar.
    else if (prioridadDe(frente->idProceso) > prioridad)
    {
        nuevo->siguiente = frente;
        frente = nuevo;
    }
    else
    {
        // Busca donde colocar la reserva.
        NodoCola* actual = frente;

        while (actual->siguiente != NULL)
        {
            if (prioridadDe(actual->siguiente->idProceso) > prioridad)
                break;

            actual = actual->siguiente; // Avanza al siguiente nodo.
        }

        // Coloca el nodo en la posicion encontrada.
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;

        // Actualiza el ultimo nodo si corresponde.
        if (nuevo->siguiente == NULL)
            final = nuevo;
    }

    return true; // La reserva se agrego correctamente.
}

// Pide el ID y agrega la reserva a la cola.
int encolarProceso()
{
    cout << "\n--- REGISTRAR NUEVA SOLICITUD (ENCOLAR) ---\n";

    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas. Primero registre una reserva.\n";
        return 0;
    }

    // Lee el ID de la reserva.
    int id = leerNumero("Ingrese el ID del Proceso: ", 1, 1000000);
    Proceso* reserva = buscarPorID(id);

    if (reserva == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return 0;
    }

    // Solo acepta reservas pendientes o confirmadas.
    if (reserva->estado != ESTADO_PENDIENTE
        && reserva->estado != ESTADO_CONFIRMADA)
    {
        cout << "Solo se pueden encolar reservas Pendientes o Confirmadas. Estado actual: "
             << reserva->estado << ".\n";
        return 0;
    }

    // Evita agregar la misma reserva dos veces.
    if (estaEnCola(id))
    {
        cout << "Ese proceso ya esta en la cola.\n";
        return 0;
    }

    encolarPorID(id); // Agrega la reserva a la cola.

    // Busca el turno que ocupa la reserva.
    int turno = 1;
    NodoCola* actual = frente;

    while (actual != NULL)
    {
        if (actual->idProceso == id)
            break;

        actual = actual->siguiente;
        turno++;
    }

    // Muestra el turno asignado.
    cout << "\nProceso encolado con exito (turno #" << turno << ").\n";

    return id;
}

// Retira la primera reserva de la cola.
int desencolarProceso()
{
    // Revisa si hay reservas en la cola.
    if (frente == NULL)
    {
        cout << "\n[!] La cola esta vacia, no hay procesos para desencolar.\n";
        return 0;
    }

    NodoCola* aux = frente; // Guarda el primer nodo.
    int idRetirado = aux->idProceso; // Guarda su ID.

    frente = frente->siguiente; // Avanza al siguiente nodo.

    // Si no quedan nodos, actualiza el final.
    if (frente == NULL)
        final = NULL;

    cout << "\nProceso desencolado con exito. ID #" << idRetirado << ".\n";

    delete aux; // Libera la memoria del nodo.

    return idRetirado;
}

// Atiende la primera reserva de la cola.
int atenderProceso()
{
    // Revisa si hay reservas por atender.
    if (frente == NULL)
    {
        cout << "\n[!] No hay solicitudes pendientes por atender.\n";
        return 0;
    }

    cout << "\n--- ATENDIENDO SOLICITUD EN FRENTE ---\n";

    int id = frente->idProceso; // Obtiene el primer ID.
    Proceso* reserva = buscarPorID(id); // Busca la reserva.

    // Muestra los datos de la reserva.
    if (reserva != NULL)
        mostrarReserva(reserva);

    desencolarProceso(); // Retira la reserva de la cola.

    // Cambia el estado de la reserva.
    if (reserva != NULL)
    {
        aplicarEstado(reserva, ESTADO_EN_ATENCION);
        cout << "Estado actual : " << reserva->estado << "\n";
    }

    cout << "\nSolicitud atendida y retirada de la cola.\n";

    return id;
}

// Muestra todas las reservas de la cola.
void mostrarCola()
{
    // Revisa si hay elementos para mostrar.
    if (frente == NULL)
    {
        cout << "\n[!] La cola esta vacia.\n";
        return;
    }

    NodoCola* actual = frente; // Empieza desde el primer nodo.
    int turno = 1; // Cuenta los turnos.

    cout << "\n========================================\n";
    cout << "     SOLICITUDES PENDIENTES EN COLA     \n";
    cout << "========================================\n";

    // Recorre todos los nodos de la cola.
    while (actual != NULL)
    {
        cout << "Turno #" << turno << " | ID #" << actual->idProceso << "\n";

        Proceso* reserva = buscarPorID(actual->idProceso);

        // Muestra los datos si la reserva existe.
        if (reserva != NULL)
        {
            cout << "  - Huesped    : " << reserva->nombreHuesped << "\n";
            cout << "  - Habitacion : " << reserva->habitacion << "\n";
            cout << "  - Servicio   : " << reserva->descripcion << "\n";
            cout << "  - Prioridad  : " << textoPrioridad(reserva->prioridad) << "\n";
            cout << "  - Fecha      : " << reserva->fecha << "\n";
            cout << "  - Estado     : " << reserva->estado << "\n";
        }

        cout << "----------------------------------------\n";

        actual = actual->siguiente; // Pasa al siguiente nodo.
        turno++; // Aumenta el turno.
    }
}

// Quita una reserva de la cola usando su ID.
bool quitarDeCola(int id)
{
    NodoCola* actual = frente; // Nodo que se revisa.
    NodoCola* anterior = NULL; // Nodo anterior.

    // Busca la reserva que se quiere quitar.
    while (actual != NULL)
    {
        if (actual->idProceso == id)
            break;

        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL)
        return false; // No encontro la reserva.

    // Si es el primer nodo, mueve el frente.
    if (anterior == NULL)
        frente = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    // Actualiza el final si se elimino el ultimo nodo.
    if (actual == final)
        final = anterior;

    delete actual; // Libera la memoria del nodo.

    return true;
}

// Libera la memoria de todos los nodos.
void liberarCola()
{
    while (frente != NULL)
    {
        NodoCola* aux = frente; // Guarda el primer nodo.
        frente = frente->siguiente; // Avanza al siguiente.
        delete aux; // Elimina el nodo guardado.
    }

    final = NULL; // Deja la cola vacia.
}
