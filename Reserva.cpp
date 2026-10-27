#Reserva Fredy

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Estructura que va alamcenar los datos de la reserva
struct Proceso
{
    int id;
    string nombreHuesped;
    int habitacion;
    string descripcion;
    string estado;
    int prioridad;
    string fecha;

    Proceso* siguiente;
};

// Inicio de la lista enlazada
Proceso* inicioLista = NULL;

// Declaracion de las funciones principales
void insertarProceso();
void buscarProcesoID();
void buscarProcesoNombre();
void modificarProceso();
void eliminarProceso();
void cambiarEstado();


// Funciones que utiliza principal
void registrarReserva();
void buscarReserva();



























