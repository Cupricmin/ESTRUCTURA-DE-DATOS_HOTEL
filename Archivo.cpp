#include <iostream> // Permite mostrar mensajes.
#include <fstream> // Permite leer y guardar archivos.
#include <string> // Permite trabajar con textos.
#include <cstdlib> // Permite convertir textos a números.
#include "Archivo.h"
#include "Reserva.h" // Permite trabajar con las reservas.
#include "Habitacion.h" // Permite trabajar con las habitaciones.
#include "Cola.h" // Permite trabajar con la cola de reservas.

using namespace std; // Permite usar cout, cin y string sin escribir std::.

// Reemplaza el símbolo separador para evitar errores al guardar.
static string limpiarTexto(string texto)
{
    for (int i = 0; i < (int)texto.length(); i++) // Revisa cada carácter.
    {
        if (texto[i] == '|')
            texto[i] = '/'; // Cambia la barra vertical por una diagonal.
    }

    return texto; // Devuelve el texto corregido.
}

// Comprueba si el texto contiene solo números enteros.
static bool esEntero(const string& texto)
{
    if (texto.empty())
        return false; // Rechaza textos vacíos.

    if (texto.length() > 7)
        return false; // Rechaza textos demasiado largos.

    for (int i = 0; i < (int)texto.length(); i++) // Revisa cada carácter.
    {
        if (texto[i] < '0')
            return false; // Rechaza caracteres anteriores al cero.

        if (texto[i] > '9')
            return false; // Rechaza caracteres posteriores al nueve.
    }

    return true; // Indica que el texto contiene solo números.
}

// Separa una línea en varios campos usando la barra vertical.
static int dividirLinea(const string& linea, string campos[], int maximo)
{
    int cantidad = 0; // Cuenta los campos encontrados.
    size_t inicio = 0; // Indica dónde comienza cada campo.

    while (true)
    {
        if (cantidad >= maximo)
            return maximo + 1; // Indica que hay demasiados campos.

        size_t pos = linea.find('|', inicio); // Busca la siguiente barra vertical.

        if (pos == string::npos) // Comprueba si ya no quedan separadores.
        {
            campos[cantidad++] = linea.substr(inicio); // Guarda el último campo.
            break; // Termina de separar la línea.
        }

        campos[cantidad++] = linea.substr(inicio, pos - inicio); // Guarda el campo encontrado.
        inicio = pos + 1; // Continúa después del separador.
    }

    return cantidad; // Devuelve la cantidad de campos.
}

// Guarda todas las reservas en un archivo.
int guardarReservas()
{
    ofstream archivo(ARCHIVO_RESERVAS.c_str()); // Abre el archivo para guardar los datos.

    if (!archivo.is_open()) // Comprueba si se pudo abrir.
    {
        cout << "Error: no se pudo crear el archivo "
             << ARCHIVO_RESERVAS << ".\n";
        return -1; // Informa que ocurrió un error.
    }

    int guardadas = 0; // Cuenta las reservas guardadas.
    Proceso* actual = inicioLista; // Comienza desde la primera reserva.

    while (actual != NULL) // Recorre todas las reservas.
    {
        // Guarda los datos de la reserva separados por barras verticales.
        archivo << actual->id << "|"
                << limpiarTexto(actual->nombreHuesped) << "|"
                << actual->habitacion << "|"
                << limpiarTexto(actual->descripcion) << "|"
                << actual->estado << "|"
                << actual->prioridad << "|"
                << actual->fecha << "\n";

        guardadas++; // Cuenta la reserva guardada.
        actual = actual->siguiente; // Avanza a la siguiente reserva.
    }

    archivo.close(); // Cierra el archivo.
    return guardadas; // Devuelve la cantidad guardada.
}

// Lee el archivo y recupera las reservas guardadas.
int cargarReservas()
{
    ifstream archivo(ARCHIVO_RESERVAS.c_str()); // Abre el archivo para leer los datos.

    if (!archivo.is_open())
        return -1; // Termina si no se pudo abrir el archivo.

    liberarLista(); // Elimina las reservas que estaban en memoria.
    liberarCola(); // Vacía la cola anterior.
    reiniciarOcupacion(); // Deja libres todas las habitaciones.

    string linea; // Guarda cada línea leída.
    int cargadas = 0; // Cuenta las reservas recuperadas.
    int omitidas = 0; // Cuenta las líneas con errores.

    while (getline(archivo, linea)) // Lee una línea cada vez.
    {
        // Elimina el carácter extra que puede aparecer en archivos de Windows.
        if (!linea.empty())
        {
            if (linea[linea.length() - 1] == '\r')
                linea.erase(linea.length() - 1);
        }

        if (linea.empty())
            continue; // Ignora las líneas vacías.

        string campos[7]; // Guarda los siete datos de cada reserva.

        if (dividirLinea(linea, campos, 7) != 7)
        {
            omitidas++; // Cuenta la línea incorrecta.
            continue; // Pasa a la siguiente línea.
        }

        // Comprueba que los datos tengan el formato esperado.
        bool datosValidos = true;

        if (!esEntero(campos[0]))
            datosValidos = false; // Comprueba el ID.

        if (!esEntero(campos[2]))
            datosValidos = false; // Comprueba el número de habitación.

        if (!esEntero(campos[5]))
            datosValidos = false; // Comprueba la prioridad.

        if (campos[1].empty())
            datosValidos = false; // Comprueba el nombre.

        if (campos[3].empty())
            datosValidos = false; // Comprueba la descripción.

        if (!estadoValido(campos[4]))
            datosValidos = false; // Comprueba el estado.

        if (!fechaValida(campos[6]))
            datosValidos = false; // Comprueba la fecha.

        if (!datosValidos)
        {
            omitidas++; // Cuenta el registro incorrecto.
            continue; // Pasa al siguiente registro.
        }

        int id = atoi(campos[0].c_str()); // Convierte el ID a número.
        int habitacion = atoi(campos[2].c_str()); // Convierte la habitación a número.
        int prioridad = atoi(campos[5].c_str()); // Convierte la prioridad a número.

        // Comprueba que los números estén dentro de los rangos permitidos.
        bool rangoValido = true;

        if (id < 1)
            rangoValido = false;

        if (id > 1000000)
            rangoValido = false;

        if (habitacion < 1)
            rangoValido = false;

        if (habitacion > 28)
            rangoValido = false;

        if (prioridad < 1)
            rangoValido = false;

        if (prioridad > 3)
            rangoValido = false;

        if (buscarPorID(id) != NULL)
            rangoValido = false; // Evita registrar IDs repetidos.

        if (!rangoValido)
        {
            omitidas++; // Cuenta el registro incorrecto.
            continue; // Pasa al siguiente registro.
        }

        // Comprueba si la reserva necesita ocupar una habitación.
        if (estadoOcupaHabitacion(campos[4]))
        {
            if (!asignarHabitacion(habitacion, id))
            {
                omitidas++; // Cuenta la reserva que no pudo asignarse.
                continue; // Pasa al siguiente registro.
            }
        }

        Proceso* nuevo = new Proceso; // Crea espacio para la reserva.
        nuevo->id = id; // Guarda el ID.
        nuevo->nombreHuesped = campos[1]; // Guarda el nombre.
        nuevo->habitacion = habitacion; // Guarda la habitación.
        nuevo->descripcion = campos[3]; // Guarda la descripción.
        nuevo->estado = campos[4]; // Guarda el estado.
        nuevo->prioridad = prioridad; // Guarda la prioridad.
        nuevo->fecha = campos[6]; // Guarda la fecha.

        insertarAlFinal(nuevo); // Agrega la reserva a la lista.
        cargadas++; // Cuenta la reserva recuperada.
    }

    archivo.close(); // Cierra el archivo.

    if (omitidas > 0)
    {
        cout << "Aviso: se omitieron " << omitidas
             << " linea(s) con datos invalidos.\n";
    }

    return cargadas; // Devuelve la cantidad de reservas recuperadas.
}
