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


//// PROCESO QUE REGISTRA LA RESERVA
void insertarProceso()
{
    Proceso* nuevo = new Proceso;
    int numero;
    bool valido;

    cout << "--- REGISTRAR RESERVA ---";

    // Validar el ID
    do
    {
        valido = true;
        cout << "Ingrese ID: ";

        if (!(cin >> numero) || numero <= 0)
        {
            cout << "Error: ingrese un numero mayor que 0.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            valido = false;
        }
        else
        {
            // Comprobar si el ID ya existe
            Proceso* actual = inicioLista;

            while (actual != NULL)
            {
                if (actual->id == numero)
                {
                    cout << "Error: el ID ya existe.\n";
                    valido = false;
                    break;
                }

                actual = actual->siguiente;
            }
        }

    } while (!valido);

    nuevo->id = numero;
    cin.ignore(10000, '\n');

    // VALIDAR EL NOMBRE DEL HUESPED
    do
    {
        valido = true;
        cout << "Nombre del huesped: ";
        getline(cin, nuevo->nombreHuesped);

        if (nuevo->nombreHuesped.empty())
        {
            cout << "Error: el nombre no puede estar vacio.\n";
            valido = false;
        }
        else
        {
            for (int i = 0; i < nuevo->nombreHuesped.length(); i++)
            {
                char letra = nuevo->nombreHuesped[i];

                if (!((letra >= 'A' && letra <= 'Z') ||
                      (letra >= 'a' && letra <= 'z') ||
                      letra == ' '))
                {
                    cout << "Error: ingrese solo letras y espacios.\n";
                    valido = false;
                    break;
                }
            }
        }

    } while (!valido);

    // Validar el numero de habitacion
    do
    {
        valido = true;
        cout << "Numero de habitacion (1 a 28): ";

        if (!(cin >> numero) || numero < 1 || numero > 28)
        {
            cout << "Error: ingrese una habitacion del 1 al 28.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            valido = false;
        }

    } while (!valido);

    nuevo->habitacion = numero;
    cin.ignore(10000, '\n');

    // Registrar la descripcion de prioridad
    do
    {
        cout << "Descripcion: ";
        getline(cin, nuevo->descripcion);

        if (nuevo->descripcion.empty())
        {
            cout << "Error: la descripcion no puede estar vacia.\n";
        }

    } while (nuevo->descripcion.empty());

    // Asignar el estado inicial
    nuevo->estado = "Pendiente";

    // Validar la prioridad
    do
    {
        valido = true;
        cout << "Prioridad (1-Alta, 2-Media, 3-Baja): ";

        if (!(cin >> numero) || numero < 1 || numero > 3)
        {
            cout << "Error: ingrese 1, 2 o 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            valido = false;
        }

    } while (!valido);

    nuevo->prioridad = numero;
    cin.ignore(10000, '\n');

    // Validar que la fecha no este vacia
    do
    {
        cout << "Fecha (AAAA-MM-DD): ";
        getline(cin, nuevo->fecha);

        if (nuevo->fecha.empty())
        {
            cout << "Error: la fecha no puede estar vacia.\n";
        }

    } while (nuevo->fecha.empty());

    // Preparar el enlace del nuevo nodo
    nuevo->siguiente = NULL;

    // Insertar el nodo al final de la lista
    if (inicioLista == NULL)
    {
        inicioLista = nuevo;
    }
    else
    {
        Proceso* actual = inicioLista;

        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }

    cout << "\nReserva registrada correctamente.\n";
}




























