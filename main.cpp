#include <iostream>
#include <string>

using namespace std;

void registrarReserva();
void buscarReserva();

void mostrarHabitaciones();

void encolar();

void apilar();


// ===== FUNCIONES DEL SISTEMA =====

// Muestra el menú principal del hotel.
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

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;


        switch(opcion)
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
                cout << "\nGestion habitaciones\n";
                break;

            case 6:
                cout << "\nCola de atencion\n";
                break;

            case 7:
                cout << "\nHistorial\n";
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
                cout << "\nOpcion incorrecta\n";
        }


    }while(opcion != 0);

}


// ===== PROGRAMA PRINCIPAL =====

int main()
{
    menuPrincipal();

    return 0;
}
