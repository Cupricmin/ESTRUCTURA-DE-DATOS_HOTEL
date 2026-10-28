// Reserva.h: archivo de cabecera del módulo de reservas.
#ifndef RESERVA_H // Evita que este archivo se incluya varias veces.
#define RESERVA_H // Define la protección del archivo de cabecera.

#include <string> // Permite utilizar el tipo de dato string.

// Define los seis estados posibles de una reserva.
const std::string ESTADO_PENDIENTE = "Pendiente"; // La reserva está pendiente de atención.
const std::string ESTADO_CONFIRMADA = "Confirmada"; // La reserva ha sido confirmada.
const std::string ESTADO_EN_ATENCION = "En atencion"; // La reserva está siendo atendida.
const std::string ESTADO_FINALIZADA = "Finalizada"; // La atención de la reserva terminó.
const std::string ESTADO_CANCELADA = "Cancelada"; // La reserva fue cancelada.
const std::string ESTADO_NO_PRESENTADO = "No presentado"; // El huésped no se presentó.

// Define la estructura del nodo que almacena los datos de una reserva.
struct Proceso
{
    int id; // Guarda el identificador único de la reserva.
    std::string nombreHuesped; // Guarda el nombre y apellido del huésped.
    int habitacion; // Guarda el número de habitación asignada, del 1 al 28.
    std::string descripcion; // Guarda los detalles o notas de la reserva.
    std::string estado; // Guarda el estado actual de la reserva.
    int prioridad; // Guarda la prioridad: 1 alta, 2 media o 3 baja.
    std::string fecha; // Guarda la fecha de la reserva en formato AAAA-MM-DD.
    Proceso* siguiente; // Apunta al siguiente nodo de la lista enlazada.
}; // Finaliza la definición de la estructura Proceso.

// Declara el puntero inicial de la lista, definido en Reserva.cpp.
extern Proceso* inicioLista; // Permite acceder a la lista desde otros archivos.

// Declara las funciones auxiliares para validar y leer datos.
int leerNumero(std::string mensaje, int minimo, int maximo); // Lee un número dentro de un rango permitido.
std::string leerTextoValido(std::string mensaje, bool soloLetras); // Lee y valida un texto.
std::string leerFecha(std::string mensaje); // Lee una fecha ingresada por el usuario.
bool fechaValida(const std::string& fecha); // Comprueba si la fecha tiene un formato válido.
bool estadoValido(const std::string& estado); // Comprueba si el estado pertenece a los estados permitidos.
bool estadoOcupaHabitacion(const std::string& estado); // Comprueba si el estado implica ocupar una habitación.
std::string textoPrioridad(int prioridad); // Convierte el número de prioridad en texto.

// Declara las operaciones principales de la lista enlazada.
Proceso* buscarPorID(int id); // Busca una reserva por su identificador.
void mostrarReserva(Proceso* reserva); // Muestra los datos de una reserva.
void insertarAlFinal(Proceso* nuevo); // Inserta un nuevo nodo al final de la lista.
int contarReservas(); // Cuenta la cantidad de reservas registradas.
void liberarLista(); // Libera la memoria dinámica utilizada por la lista.

// Declara las funciones que utiliza el menú del sistema.
int insertarProceso(); // Registra una nueva reserva y devuelve su ID o cero si no se realiza.
void buscarProcesoID(); // Permite buscar una reserva por su identificador.
void buscarProcesoNombre(); // Permite buscar reservas por el nombre del huésped.
void mostrarReservas(); // Muestra las reservas registradas.
int modificarProceso(); // Modifica una reserva y devuelve el ID afectado o cero si no hay cambios.
int eliminarProceso(); // Elimina una reserva y devuelve el ID afectado o cero si no se elimina.
int cambiarEstado(); // Cambia el estado de una reserva y devuelve el ID afectado o cero si no hay cambios.

// Declara las funciones que conectan las reservas con las habitaciones y la cola.
bool aplicarEstado(Proceso* reserva, const std::string& nuevoEstado); // Aplica un nuevo estado a una reserva.
bool asignarHabitacionAReserva(int idReserva, int numeroHabitacion); // Asigna una habitación a una reserva.
int hacerCheckOut(int numeroHabitacion); // Registra la salida asociada a una habitación.

// Finaliza la protección del archivo de cabecera.
#endif // RESERVA_H
