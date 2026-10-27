
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ===== ESTRUCTURA DEL NODO =====

struct Nodo
{
    string nombre;
    Nodo* siguiente;
};

// Punteros de la cola
Nodo* frente = nullptr;
Nodo* finalCola = nullptr;

// ===== FUNCIONES =====

void encolar()
{
    string nombre;

    cout << "\nIngrese el nombre del cliente: ";
    getline(cin, nombre);

    if (nombre.empty())
    {
        cout << "El nombre no puede estar vacio.\n";
        return;
    }

    // Crear nuevo nodo dinamicamente
    Nodo* nuevo = new Nodo;
    nuevo->nombre = nombre;
    nuevo->siguiente = nullptr;

    // Si la cola esta vacia
    if (frente == nullptr)
    {
        frente = nuevo;
        finalCola = nuevo;
    }
    else
    {
        // Agregar al final de la cola
        finalCola->siguiente = nuevo;
        finalCola = nuevo;
    }

    cout << "Cliente agregado a la cola correctamente.\n";
}

void atenderCliente()
{
    if (frente == nullptr)
    {
        cout << "\nNo hay clientes en espera.\n";
        return;
    }

    // Guardar el nodo que se eliminara
    Nodo* auxiliar = frente;

    cout << "\nAtendiendo al cliente: "
         << auxiliar->nombre << endl;

    // Avanzar el frente
    frente = frente->siguiente;

    // Si la cola queda vacia
    if (frente == nullptr)
    {
        finalCola = nullptr;
    }

    // Liberar memoria
    delete auxiliar;

    cout << "Cliente atendido correctamente.\n";
}

void mostrarCola()
{
    if (frente == nullptr)
    {
        cout << "\nLa cola esta vacia.\n";
        return;
    }

    Nodo* actual = frente;
    int posicion = 1;

    cout << "\n--- CLIENTES EN ESPERA ---\n";

    while (actual != nullptr)
    {
        cout << posicion << ". "
             << actual->nombre << endl;

        actual = actual->siguiente;
        posicion++;
    }
}

void liberarCola()
{
    while (frente != nullptr)
    {
        Nodo* auxiliar = frente;
        frente = frente->siguiente;
        delete auxiliar;
    }

    finalCola = nullptr;
}

// ===== MENU DE ATENCION =====

void menuCola()
{
    int opcion;

    do
    {
        cout << "\n==============================\n";
        cout << "       COLA DE ATENCION\n";
        cout << "==============================\n";
        cout << "1. Registrar cliente\n";
        cout << "2. Atender cliente\n";
        cout << "3. Mostrar cola\n";
        cout << "0. Regresar al menu principal\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            cout << "Opcion invalida.\n";
            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );

        switch (opcion)
        {
            case 1:
                encolar();
                break;

            case 2:
                atenderCliente();
                break;

            case 3:
                mostrarCola();
                break;

            case 0:
                cout << "Regresando al menu principal...\n";
                break;

            default:
                cout << "Opcion incorrecta.\n";
        }

    } while (opcion != 0);
}

// ===== MENU PRINCIPAL =====

void menuPrincipal()
{
    int opcion;

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
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            cout << "Opcion invalida.\n";
            continue;
        }

        switch (opcion)
        {
            case 1:
                cout << "\nRegistrar reserva\n";
                break;

            case 2:
                cout << "\nBuscar reserva\n";
                break;

            case 3:
                cout << "\nModificar reserva\n";
                break;

            case 4:
                cout << "\nEliminar reserva\n";
                break;

            case 5:
                cout << "\nGestion de habitaciones\n";
                break;

            case 6:
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                menuCola();
                break;

            case 7:
                cout << "\nHistorial de operaciones\n";
                break;

            case 8:
                cout << "\nDatos guardados\n";
                break;

            case 9:
                cout << "\nDatos cargados\n";
                break;

            case 0:
                cout << "\nCerrando sistema...\n";
                break;

            default:
                cout << "\nOpcion incorrecta.\n";
        }

    } while (opcion != 0);
}

// ===== PROGRAMA PRINCIPAL =====

int main()
{
    menuPrincipal();

    // Liberar memoria dinamica antes de terminar
    liberarCola();

    return 0;
}
