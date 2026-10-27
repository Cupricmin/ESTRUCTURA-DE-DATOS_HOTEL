```cpp
// Reserva Fredy

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ESTRUCTURA DE LA RESERVA
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

// INICIO DE LA LISTA ENLAZADA
Proceso* inicioLista = NULL;


// FUNCIONES AUXILIARES DE VALIDACION
// Leer un numero entero dentro de un rango
int leerNumero(string mensaje, int minimo, int maximo)
{
    int numero;
    do
    {
        cout << mensaje;
        if (!(cin >> numero))
        {
            cout << "Error: ingrese un numero valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            numero = minimo - 1;
        }
        else if (numero < minimo || numero > maximo)
        {
            cout << "Error: ingrese un numero entre "
                 << minimo << " y " << maximo << ".\n";
        }

    } while (numero < minimo || numero > maximo);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return numero;
}


// Leer texto y validar si contiene solo letras
string leerTextoValido(string mensaje, bool soloLetras)
{
    string texto;
    bool valido;
    do
    {
        valido = true;
        cout << mensaje;
        getline(cin, texto);
        
        if (texto.empty())
        {
            cout << "Error: el campo no puede estar vacio.\n";
            valido = false;
        }
        else if (soloLetras)
        {
            for (int i = 0; i < texto.length(); i++)
            {
                char letra = texto[i];
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
    return texto;
}


// Buscar una reserva por su ID
Proceso* buscarPorID(int id)
{
    Proceso* actual = inicioLista;
    while (actual != NULL)
    {
        if (actual->id == id)
            return actual;
        actual = actual->siguiente;
    }

    return NULL;
}


// Mostrar los datos de una reserva
void mostrarReserva(Proceso* reserva)
{
    cout << "\nID: " << reserva->id << endl;
    cout << "Nombre del huesped: "
         << reserva->nombreHuesped << endl;
    cout << "Habitacion: " << reserva->habitacion << endl;
    cout << "Descripcion: " << reserva->descripcion << endl;
    cout << "Estado: " << reserva->estado << endl;
    cout << "Prioridad: ";

    switch (reserva->prioridad)
    {
        case 1: cout << "Alta"; break;
        case 2: cout << "Media"; break;
        case 3: cout << "Baja"; break;
    }
    cout << endl;
    cout << "Fecha: " << reserva->fecha << endl;
}


// 1. REGISTRAR RESERVA
void insertarProceso()
{
    cout << "\n--- REGISTRAR RESERVA ---\n";
    int id;
    Proceso* encontrado;

    // Validar ID y evitar duplicados
    do
    {
        id = leerNumero("Ingrese ID: ", 1, 1000000);
        encontrado = buscarPorID(id);
        if (encontrado != NULL)
            cout << "Error: el ID ya existe.\n";

    } while (encontrado != NULL);

    Proceso* nuevo = new Proceso;
    nuevo->id = id;

    nuevo->nombreHuesped =
        leerTextoValido("Nombre del huesped: ", true);
    nuevo->habitacion =
        leerNumero("Numero de habitacion (1 a 28): ", 1, 28);
    nuevo->descripcion =
        leerTextoValido("Descripcion: ", false);
    nuevo->estado = "Pendiente";
    nuevo->prioridad =
        leerNumero("Prioridad (1-Alta, 2-Media, 3-Baja): ", 1, 3);
    nuevo->fecha =
        leerTextoValido("Fecha (AAAA-MM-DD): ", false);

    // Insertar al final de la lista
    nuevo->siguiente = NULL;
    
    if (inicioLista == NULL)
    {
        inicioLista = nuevo;
    }
    else
    {
        Proceso* actual = inicioLista;
        while (actual->siguiente != NULL)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    cout << "\nReserva registrada correctamente.\n";
}


// 2. BUSCAR RESERVA POR ID
void buscarProcesoID()
{
    cout << "\n--- BUSCAR RESERVA POR ID ---\n";
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000);
    Proceso* reserva = buscarPorID(id);

    if (reserva != NULL)
        mostrarReserva(reserva);
    else
        cout << "No se encontro una reserva con ese ID.\n";
}


// 3. BUSCAR RESERVA POR NOMBRE
void buscarProcesoNombre()
{
    cout << "\n--- BUSCAR RESERVA POR NOMBRE ---\n";

    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }
    string nombre = leerTextoValido(
        "Ingrese el nombre del huesped: ", true
    );

    Proceso* actual = inicioLista;
    bool encontrado = false;

    while (actual != NULL)
    {
        if (actual->nombreHuesped == nombre)
        {
            mostrarReserva(actual);
            encontrado = true;
        }

        actual = actual->siguiente;
    }

    if (!encontrado)
        cout << "No se encontraron reservas para ese huesped.\n";
}


// 4. MODIFICAR RESERVA
void modificarProceso()
{
    cout << "\n--- MODIFICAR RESERVA ---\n";
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000);
    Proceso* reserva = buscarPorID(id);

    if (reserva == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return;
    }

    cout << "\nReserva encontrada.\n";
    mostrarReserva(reserva);
    reserva->nombreHuesped =
        leerTextoValido("Nuevo nombre del huesped: ", true);
    reserva->habitacion =
        leerNumero("Nueva habitacion (1 a 28): ", 1, 28);
    reserva->descripcion =
        leerTextoValido("Nueva descripcion: ", false);
    reserva->prioridad =
        leerNumero("Nueva prioridad (1-Alta, 2-Media, 3-Baja): ", 1, 3);
    reserva->fecha =
        leerTextoValido("Nueva fecha (AAAA-MM-DD): ", false);
    cout << "\nReserva modificada correctamente.\n";
}


// 5. ELIMINAR RESERVA
void eliminarProceso()
{
    cout << "\n--- ELIMINAR RESERVA ---\n";
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }
    int id = leerNumero(
        "Ingrese el ID de la reserva que desea eliminar: ",
        1, 1000000
    );
    Proceso* actual = inicioLista;
    Proceso* anterior = NULL;
    
    // Buscar el nodo que se desea eliminar
    while (actual != NULL && actual->id != id)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return;
    }
    mostrarReserva(actual);

    // Desconectar el nodo de la lista
    if (anterior == NULL)
        inicioLista = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    delete actual;

    cout << "\nReserva eliminada correctamente.\n";
}

// 6. CAMBIAR ESTADO DE RESERVA
void cambiarEstado()
{
    cout << "\n--- CAMBIAR ESTADO DE RESERVA ---\n";
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000);

    Proceso* reserva = buscarPorID(id);
    if (reserva == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return;
    }

    cout << "\nHuesped: " << reserva->nombreHuesped << endl;
    cout << "Estado actual: " << reserva->estado << endl;
    cout << "\nSeleccione el nuevo estado:\n";
    cout << "1. Pendiente\n";
    cout << "2. En proceso\n";
    cout << "3. Completado\n";
    cout << "4. Cancelado\n";

    int opcion = leerNumero("Opcion: ", 1, 4);

    switch (opcion)
    {
        case 1: reserva->estado = "Pendiente"; break;
        case 2: reserva->estado = "En proceso"; break;
        case 3: reserva->estado = "Completado"; break;
        case 4: reserva->estado = "Cancelado"; break;
    }

    cout << "\nEstado actualizado correctamente.\n";
    cout << "Nuevo estado: " << reserva->estado << endl;
}
```
