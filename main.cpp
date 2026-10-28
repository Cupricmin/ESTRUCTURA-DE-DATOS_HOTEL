
 // Archivo principal del sistema del Hotel Aloinka.
#include <iostream> // Permite mostrar e ingresar datos.
#include <string> // Permite trabajar con textos.
#include <sstream> // Permite unir textos con numeros.
#include "Reserva.h" // Contiene las funciones de reservas.
#include "Habitacion.h" // Contiene las funciones de habitaciones.
#include "Cola.h" // Contiene las funciones de la cola.
#include "Pila.h" // Contiene las funciones de la pila.
#include "Archivo.h" // Contiene las funciones para guardar y cargar datos.

using namespace std; // Permite usar cout, cin y string sin escribir std::.

// Crea un texto que incluye el ID de una reserva.
static string textoConID(const string& texto, int id)
{
    ostringstream salida; // Guarda el texto que se va a formar.
    salida << texto << " (ID " << id << ")"; // Une el texto con el ID.
    return salida.str(); // Devuelve el texto completo.
}

// Muestra el menu para buscar reservas.
static void menuBuscar()
{
    int opcion; // Guarda la opcion elegida.

    do
    {
        cout << "\n--- BUSCAR RESERVA ---\n";
        cout << "1. Buscar por ID\n";
        cout << "2. Buscar por nombre del huesped\n";
        cout << "3. Mostrar todas las reservas\n";
        cout << "0. Volver\n";

        opcion = leerNumero("Opcion: ", 0, 3); // Pide una opcion valida.

        switch (opcion)
        {
            case 1:
                buscarProcesoID(); // Busca una reserva por su ID.
                break;

            case 2:
                buscarProcesoNombre(); // Busca por el nombre del huesped.
                break;

            case 3:
                mostrarReservas(); // Muestra todas las reservas.
                break;
        }

    } while (opcion != 0); // Repite hasta elegir volver.
}

// Muestra el menu para modificar reservas.
static void menuModificar()
{
    int opcion; // Guarda la opcion elegida.

    do
    {
        cout << "\n--- MODIFICAR RESERVA ---\n";
        cout << "1. Modificar datos de la reserva\n";
        cout << "2. Cambiar estado de la reserva\n";
        cout << "0. Volver\n";

        opcion = leerNumero("Opcion: ", 0, 2); // Pide una opcion valida.

        if (opcion == 1)
        {
            int id = modificarProceso(); // Modifica los datos de una reserva.

            if (id != 0) // Comprueba si se hizo una modificacion.
                apilarOperacion(textoConID("Modificar reserva", id)); // Guarda la operacion en el historial.
        }
        else if (opcion == 2)
        {
            int id = cambiarEstado(); // Cambia el estado de una reserva.

            if (id != 0) // Comprueba si se cambio el estado.
            {
                Proceso* reserva = buscarPorID(id); // Busca la reserva modificada.

                apilarOperacion(textoConID("Cambiar estado de reserva", id) + " a " + reserva->estado); // Guarda el cambio en el historial.
            }
        }

    } while (opcion != 0); // Repite hasta elegir volver.
}

// Muestra el menu para gestionar habitaciones.
static void menuHabitaciones()
{
    int opcion; // Guarda la opcion elegida.

    do
    {
        cout << "\n--- GESTIONAR HABITACIONES ---\n";
        cout << "1. Ver estado de todas las habitaciones\n";
        cout << "2. Ver habitaciones disponibles\n";
        cout << "3. Buscar una habitacion\n";
        cout << "4. Asignar habitacion a una reserva\n";
        cout << "5. Liberar habitacion (check-out)\n";
        cout << "0. Volver\n";

        opcion = leerNumero("Opcion: ", 0, 5); // Pide una opcion valida.

        if (opcion == 1)
        {
            mostrarHabitaciones(); // Muestra todas las habitaciones.
        }
        else if (opcion == 2)
        {
            mostrarHabitacionesDisponibles(); // Muestra las habitaciones libres.
        }
        else if (opcion == 3)
        {
            int numero = leerNumero("Numero de habitacion (1 a 28): ", 1, 28); // Pide el numero de habitacion.
            NodoHabitacion* hab = buscarHabitacion(numero); // Busca la habitacion.

            if (hab != NULL)
                mostrarHabitacion(hab); // Muestra los datos de la habitacion.
            else
                cout << "La habitacion no existe.\n"; // Informa si no existe.
        }
        else if (opcion == 4)
        {
            int idReserva = leerNumero("ID de la reserva: ", 1, 1000000); // Pide el ID de la reserva.
            int numero = leerNumero("Numero de habitacion (1 a 28): ", 1, 28); // Pide la habitacion.

            if (asignarHabitacionAReserva(idReserva, numero)) // Intenta asignar la habitacion.
            {
                ostringstream texto; // Guarda el mensaje de la operacion.
                texto << "Asignar habitacion " << numero << " a la reserva ID " << idReserva; // Forma el mensaje.
                apilarOperacion(texto.str()); // Guarda la operacion en el historial.
            }
        }
        else if (opcion == 5)
        {
            int numero = leerNumero("Numero de habitacion a liberar (1 a 28): ", 1, 28); // Pide la habitacion.
            int id = hacerCheckOut(numero); // Libera la habitacion y obtiene el ID.

            if (id != 0) // Comprueba si se realizo el check-out.
            {
                ostringstream texto; // Guarda el mensaje.
                texto << "Liberar habitacion " << numero << " (check-out de la reserva ID " << id << ")"; // Forma el mensaje.
                apilarOperacion(texto.str()); // Guarda la operacion en el historial.
            }
        }

    } while (opcion != 0); // Repite hasta elegir volver.
}

// Muestra el menu de atencion de solicitudes.
static void menuCola()
{
    int opcion; // Guarda la opcion elegida.

    do
    {
        cout << "\n========================================\n";
        cout << "   MODULO DE ATENCION A SOLICITUDES     \n";
        cout << "========================================\n";
        cout << "1. Registrar nueva solicitud (Encolar)\n";
        cout << "2. Atender solicitud actual (Atender)\n";
        cout << "3. Eliminar primera solicitud (Desencolar)\n";
        cout << "4. Ver cola de solicitudes pendientes\n";
        cout << "0. Volver\n";

        opcion = leerNumero("Seleccione una opcion: ", 0, 4); // Pide una opcion valida.
        int id = 0; // Guarda el ID de la reserva.

        switch (opcion)
        {
            case 1:
                id = encolarProceso(); // Agrega una solicitud a la cola.

                if (id != 0)
                    apilarOperacion(textoConID("Encolar reserva", id)); // Guarda la operacion.

                break;

            case 2:
                id = atenderProceso(); // Atiende la primera solicitud.

                if (id != 0)
                    apilarOperacion(textoConID("Atender reserva", id)); // Guarda la operacion.

                break;

            case 3:
                id = desencolarProceso(); // Elimina la primera solicitud.

                if (id != 0)
                    apilarOperacion(textoConID("Desencolar reserva", id)); // Guarda la operacion.

                break;

            case 4:
                mostrarCola(); // Muestra las solicitudes pendientes.
                break;
        }

    } while (opcion != 0); // Repite hasta elegir volver.
}

// Muestra el historial de operaciones.
static void menuHistorial()
{
    int opcion; // Guarda la opcion elegida.

    do
    {
        cout << "\n--- HISTORIAL DE OPERACIONES ---\n";
        cout << "1. Ver historial completo\n";
        cout << "2. Ver ultima operacion\n";
        cout << "3. Eliminar ultimo registro del historial\n";
        cout << "0. Volver\n";

        opcion = leerNumero("Opcion: ", 0, 3); // Pide una opcion valida.

        switch (opcion)
        {
            case 1:
                mostrarHistorial(); // Muestra todas las operaciones.
                break;

            case 2:
                mostrarTope(); // Muestra la ultima operacion guardada.
                break;

            case 3:
                desapilarOperacion(); // Elimina la ultima operacion.
                break;
        }

    } while (opcion != 0); // Repite hasta elegir volver.
}

// Guarda las reservas en el archivo.
static void guardarDatos()
{
    int total = guardarReservas(); // Guarda las reservas y obtiene la cantidad.

    if (total >= 0) // Comprueba si se guardaron los datos.
    {
        cout << "\nDatos guardados: " << total << " reserva(s) en " << ARCHIVO_RESERVAS << ".\n";

        ostringstream texto; // Guarda el mensaje del historial.
        texto << "Guardar datos (" << total << " reservas)"; // Forma el mensaje.
        apilarOperacion(texto.str()); // Guarda la operacion en el historial.
    }
}

// Carga las reservas desde el archivo.
static void cargarDatos()
{
    cout << "\nSe reemplazaran las reservas actuales por las del archivo.\n";

    int confirmar = leerNumero("1. Continuar  2. Cancelar: ", 1, 2); // Pide confirmar la carga.

    if (confirmar == 2)
        return; // Regresa si se cancela.

    int total = cargarReservas(); // Carga las reservas del archivo.

    if (total < 0)
    {
        cout << "No se encontro el archivo " << ARCHIVO_RESERVAS << ". Primero guarde los datos (opcion 8).\n";
        return; // Termina si no encuentra el archivo.
    }

    cout << "\nDatos cargados: " << total << " reserva(s) recuperadas de " << ARCHIVO_RESERVAS << ".\n";

    ostringstream texto; // Guarda el mensaje del historial.
    texto << "Cargar datos (" << total << " reservas)"; // Forma el mensaje.
    apilarOperacion(texto.str()); // Guarda la operacion en el historial.
}

// Muestra el menu principal del hotel.
static void menuPrincipal()
{
    int opcion; // Guarda la opcion elegida.

    do
    {
        cout << "\n==============================\n";
        cout << "       HOTEL ALOINKA\n";
        cout << " SISTEMA DE GESTION DE PROCESOS\n";
        cout << "==============================\n";

        cout << "1. Registrar reserva\n";
        cout << "2. Buscar reserva\n";
        cout << "3. Modificar reserva\n";
        cout << "4. Eliminar reserva\n";
        cout << "5. Gestionar habitaciones\n";
        cout << "6. Cola de atencion\n";
        cout << "7. Historial de operaciones\n";
        cout << "8. Guardar datos\n";
        cout << "9. Cargar datos\n";
        cout << "0. Salir\n";

        opcion = leerNumero("\nSeleccione una opcion: ", 0, 9); // Pide una opcion del 0 al 9.
        int id; // Guarda el ID de la reserva modificada.

        switch (opcion)
        {
            case 1:
                id = insertarProceso(); // Registra una reserva.

                if (id != 0)
                    apilarOperacion(textoConID("Registrar reserva", id)); // Guarda la operacion.

                break;

            case 2:
                menuBuscar(); // Abre el menu de busqueda.
                break;

            case 3:
                menuModificar(); // Abre el menu de modificacion.
                break;

            case 4:
                id = eliminarProceso(); // Elimina una reserva.

                if (id != 0)
                    apilarOperacion(textoConID("Eliminar reserva", id)); // Guarda la operacion.

                break;

            case 5:
                menuHabitaciones(); // Abre el menu de habitaciones.
                break;

            case 6:
                menuCola(); // Abre el menu de atencion.
                break;

            case 7:
                menuHistorial(); // Abre el historial.
                break;

            case 8:
                guardarDatos(); // Guarda los datos.
                break;

            case 9:
                cargarDatos(); // Carga los datos.
                break;

            case 0:
                cout << "\nCerrando sistema...\n"; // Muestra el mensaje de salida.
                break;
        }

    } while (opcion != 0); // Repite hasta elegir salir.
}

// Funcion principal del programa.
int main()
{
    crearHabitaciones(); // Crea las 28 habitaciones del hotel.

    // Carga las reservas guardadas si el archivo existe.
    int cargadas = cargarReservas();

    if (cargadas >= 0)
    {
        cout << "Se recuperaron " << cargadas << " reserva(s) de " << ARCHIVO_RESERVAS << ".\n";

        ostringstream texto; // Guarda el mensaje del historial.
        texto << "Cargar datos al iniciar (" << cargadas << " reservas)"; // Forma el mensaje.
        apilarOperacion(texto.str()); // Guarda la operacion.
    }

    menuPrincipal(); // Muestra el menu principal.

    // Pregunta si se desean guardar los datos antes de salir.
    cout << "\nDesea guardar los datos antes de salir?\n";

    int guardar = leerNumero("1. Si  2. No: ", 1, 2); // Pide la respuesta.

    if (guardar == 1)
    {
        int total = guardarReservas(); // Guarda las reservas.

        if (total >= 0)
            cout << "Datos guardados: " << total << " reserva(s) en " << ARCHIVO_RESERVAS << ".\n";
    }

    // Libera la memoria usada por las estructuras.
    liberarLista(); // Libera la lista de reservas.
    liberarCola(); // Libera la cola.
    liberarPila(); // Libera la pila.
    borrarHabitaciones(); // Libera la lista de habitaciones.

    return 0; // Termina el programa.
}

