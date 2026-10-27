////Reserva Fredy

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


////////////BUSCAR POR A HUESPED POR ID
void buscarProcesoID()
{
    int idBuscar;
    bool valido = true;

    cout << "\n--- BUSCAR RESERVA POR ID ---\n";

    // Verificar si la lista esta vacia
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    // Validar que el ID ingresado sea un numero positivo
    do
    {
        valido = true;
        cout << "Ingrese el ID de la reserva: ";

        if (!(cin >> idBuscar) || idBuscar <= 0)
        {
            cout << "Error: ingrese un ID numerico mayor que 0.\n";

            cin.clear();
            cin.ignore(10000, '\n');

            valido = false;
        }

    } while (!valido);

    // Recorrer la lista enlazada buscando el ID
    Proceso* actual = inicioLista;

    while (actual != NULL)
    {
        if (actual->id == idBuscar)
        {
            cout << "\nReserva encontrada:\n";
            cout << "ID: " << actual->id << endl;
            cout << "Nombre del huesped: " << actual->nombreHuesped << endl;
            cout << "Habitacion: " << actual->habitacion << endl;
            cout << "Descripcion: " << actual->descripcion << endl;
            cout << "Estado: " << actual->estado << endl;

            cout << "Prioridad: ";

            if (actual->prioridad == 1)
                cout << "Alta" << endl;
            else if (actual->prioridad == 2)
                cout << "Media" << endl;
            else
                cout << "Baja" << endl;

            cout << "Fecha: " << actual->fecha << endl;

            return;
        }

        actual = actual->siguiente;
    }

    // Si termina el recorrido y no encuentra el ID
    cout << "\nNo se encontro una reserva con el ID "
         << idBuscar << ".\n";
}
 //////// BUSCAR POR NOMBRE 


void buscarProcesoNombre()
{
    string nombreBuscar;
    bool valido;

    cout << "\n--- BUSCAR RESERVA POR NOMBRE ---\n";

    // Verificar si hay reservas registradas
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    // Validar que el nombre no este vacio y contenga letras y espacios
    do
    {
        valido = true;

        cout << "Ingrese el nombre del huesped: ";
        cin.ignore(10000, '\n');
        getline(cin, nombreBuscar);

        if (nombreBuscar.empty())
        {
            cout << "Error: el nombre no puede estar vacio.\n";
            valido = false;
        }
        else
        {
            for (int i = 0; i < nombreBuscar.length(); i++)
            {
                char letra = nombreBuscar[i];

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

    // Recorrer la lista enlazada
    Proceso* actual = inicioLista;
    bool encontrado = false;

    while (actual != NULL)
    {
        if (actual->nombreHuesped == nombreBuscar)
        {
            cout << "\nReserva encontrada:\n";
            cout << "ID: " << actual->id << endl;
            cout << "Nombre del huesped: " << actual->nombreHuesped << endl;
            cout << "Habitacion: " << actual->habitacion << endl;
            cout << "Descripcion: " << actual->descripcion << endl;
            cout << "Estado: " << actual->estado << endl;

            cout << "Prioridad: ";

            if (actual->prioridad == 1)
                cout << "Alta" << endl;
            else if (actual->prioridad == 2)
                cout << "Media" << endl;
            else
                cout << "Baja" << endl;

            cout << "Fecha: " << actual->fecha << endl;

            encontrado = true;
        }

        actual = actual->siguiente;
    }

    // Informar si no se encontro ninguna coincidencia
    if (!encontrado)
    {
        cout << "\nNo se encontraron reservas para el huesped: "
             << nombreBuscar << ".\n";
    }
}


///////////// MODIFICAR DATOS DE HUESPED 

void modificarProceso()
{
    int idBuscar;
    int numero;
    bool valido;

    cout << "\n--- MODIFICAR RESERVA ---\n";

    // Verificar si existen reservas
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    // Validar el ID de la reserva
    do
    {
        valido = true;
        cout << "Ingrese el ID de la reserva que desea modificar: ";

        if (!(cin >> idBuscar) || idBuscar <= 0)
        {
            cout << "Error: ingrese un ID numerico mayor que 0.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            valido = false;
        }

    } while (!valido);

    cin.ignore(10000, '\n');

    // Buscar la reserva en la lista
    Proceso* actual = inicioLista;

    while (actual != NULL && actual->id != idBuscar)
    {
        actual = actual->siguiente;
    }

    // Verificar si se encontro la reserva
    if (actual == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return;
    }

    cout << "\nReserva encontrada.\n";
    cout << "Huesped actual: " << actual->nombreHuesped << endl;
    cout << "Habitacion actual: " << actual->habitacion << endl;

    // Modificar el nombre del huesped
    do
    {
        valido = true;

        cout << "\nIngrese el nuevo nombre del huesped: ";
        getline(cin, actual->nombreHuesped);

        if (actual->nombreHuesped.empty())
        {
            cout << "Error: el nombre no puede estar vacio.\n";
            valido = false;
        }
        else
        {
            for (int i = 0; i < actual->nombreHuesped.length(); i++)
            {
                char letra = actual->nombreHuesped[i];

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

    // Modificar el numero de habitacion
    do
    {
        valido = true;
        cout << "Ingrese la nueva habitacion (1 a 28): ";

        if (!(cin >> numero) || numero < 1 || numero > 28)
        {
            cout << "Error: ingrese una habitacion del 1 al 28.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            valido = false;
        }

    } while (!valido);

    actual->habitacion = numero;
    cin.ignore(10000, '\n');

    // Modificar la descripcion
    do
    {
        cout << "Ingrese la nueva descripcion: ";
        getline(cin, actual->descripcion);

        if (actual->descripcion.empty())
        {
            cout << "Error: la descripcion no puede estar vacia.\n";
        }

    } while (actual->descripcion.empty());

    // Modificar la prioridad
    do
    {
        valido = true;
        cout << "Nueva prioridad (1-Alta, 2-Media, 3-Baja): ";

        if (!(cin >> numero) || numero < 1 || numero > 3)
        {
            cout << "Error: ingrese 1, 2 o 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            valido = false;
        }

    } while (!valido);

    actual->prioridad = numero;
    cin.ignore(10000, '\n');

    // Modificar la fecha
    do
    {
        cout << "Ingrese la nueva fecha (AAAA-MM-DD): ";
        getline(cin, actual->fecha);

        if (actual->fecha.empty())
        {
            cout << "Error: la fecha no puede estar vacia.\n";
        }

    } while (actual->fecha.empty());

    cout << "\nReserva modificada correctamente.\n";
}

//// ELIMIAR RESERVA 

void eliminarProceso()
{
    int idBuscar;
    bool valido = true;

    cout << "\n--- ELIMINAR RESERVA ---\n";

    // Verificar si existen reservas registradas
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    // Validar el ID ingresado
    do
    {
        valido = true;
        cout << "Ingrese el ID de la reserva que desea eliminar: ";

        if (!(cin >> idBuscar) || idBuscar <= 0)
        {
            cout << "Error: ingrese un ID numerico mayor que 0.\n";

            cin.clear();
            cin.ignore(10000, '\n');

            valido = false;
        }

    } while (!valido);

    // Buscar la reserva por su ID
    Proceso* actual = inicioLista;
    Proceso* anterior = NULL;

    while (actual != NULL && actual->id != idBuscar)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Verificar si se encontro la reserva
    if (actual == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return;
    }

    // Mostrar los datos de la reserva encontrada
    cout << "\nReserva encontrada:\n";
    cout << "ID: " << actual->id << endl;
    cout << "Huesped: " << actual->nombreHuesped << endl;
    cout << "Habitacion: " << actual->habitacion << endl;

    // Eliminar el nodo de la lista
    if (anterior == NULL)
    {
        // Eliminar el primer nodo
        inicioLista = actual->siguiente;
    }
    else
    {
        // Eliminar un nodo intermedio o el ultimo
        anterior->siguiente = actual->siguiente;
    }

    // Liberar la memoria utilizada por el nodo
    delete actual;

    cout << "\nReserva eliminada correctamente.\n";
}
 /// CAMBIAR ESTADO

void cambiarEstado()
{
    int idBuscar;
    int opcion;
    bool valido;

    cout << "\n--- CAMBIAR ESTADO DE RESERVA ---\n";

    // Verificar si existen reservas registradas
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    // Validar el ID ingresado
    do
    {
        valido = true;

        cout << "Ingrese el ID de la reserva: ";

        if (!(cin >> idBuscar) || idBuscar <= 0)
        {
            cout << "Error: ingrese un ID numerico mayor que 0.\n";

            cin.clear();
            cin.ignore(10000, '\n');

            valido = false;
        }

    } while (!valido);

    // Buscar la reserva por su ID
    Proceso* actual = inicioLista;

    while (actual != NULL && actual->id != idBuscar)
    {
        actual = actual->siguiente;
    }

    // Verificar si existe la reserva
    if (actual == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return;
    }

    // Mostrar el estado actual
    cout << "\nReserva encontrada.\n";
    cout << "Huesped: " << actual->nombreHuesped << endl;
    cout << "Estado actual: " << actual->estado << endl;

    // Mostrar las opciones de estado
    cout << "\nSeleccione el nuevo estado:\n";
    cout << "1. Pendiente\n";
    cout << "2. En proceso\n";
    cout << "3. Completado\n";
    cout << "4. Cancelado\n";

    // Validar la opcion seleccionada
    do
    {
        valido = true;

        cout << "Opcion: ";

        if (!(cin >> opcion) || opcion < 1 || opcion > 4)
        {
            cout << "Error: seleccione una opcion del 1 al 4.\n";

            cin.clear();
            cin.ignore(10000, '\n');

            valido = false;
        }

    } while (!valido);

    // Actualizar el estado de la reserva
    switch (opcion)
    {
        case 1:
            actual->estado = "Pendiente";
            break;

        case 2:
            actual->estado = "En proceso";
            break;

        case 3:
            actual->estado = "Completado";
            break;

        case 4:
            actual->estado = "Cancelado";
            break;
    }

    cout << "\nEstado actualizado correctamente.\n";
    cout << "Nuevo estado: " << actual->estado << endl;
} 
