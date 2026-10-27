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
int leerNumero(string mensaje, int minimo, int maximo) // Define la función recibiendo el texto a mostrar y los límites numéricos
{
    int numero; // Variable temporal para almacenar el valor ingresado por el usuario
    do // Inicia el bucle que se repetirá mientras la entrada sea inválida o esté fuera de rango
    {
        cout << mensaje; // Imprime en consola la indicación (prompt) para el usuario
        
        if (!(cin >> numero)) // Evalúa si la lectura falló (ej. el usuario ingresó letras en lugar de números)
        {
            cout << "Error: ingrese un numero valido.\n"; // Muestra mensaje de error por tipo de dato incorrecto
            cin.clear(); // Limpia la bandera de error (failbit) del flujo cin para permitir nuevas lecturas
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta todo el texto inválido que quedó en el búfer
            numero = minimo - 1; // Asigna un valor fuera de rango para garantizar que la condición del do-while siga siendo verdadera
        }
        else if (numero < minimo || numero > maximo) // Evalúa si el número es correcto pero está fuera de los límites permitidos
        {
            cout << "Error: ingrese un numero entre " // Muestra mensaje de error especificando el rango aceptado
                 << minimo << " y " << maximo << ".\n";
        }
    } while (numero < minimo || numero > maximo); // Repite el proceso si el número no está en el rango [minimo, maximo]

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el salto de línea ('\n') restante para no afectar lecturas de texto (getline)
    return numero; // Devuelve el número entero completamente validado
}


// Leer texto y validar si contiene solo letras
string leerTextoValido(string mensaje, bool soloLetras) // Declara la función recibiendo el mensaje indicativo y la bandera de validación de letras
{
    string texto; // Variable para almacenar la cadena ingresada por el usuario
    bool valido; // Bandera de control para gestionar la repetición del bucle de validación

    do // Inicia el bucle que se repetirá hasta que la entrada cumpla con todas las condiciones
    {
        valido = true; // Asume inicialmente que el texto es válido al comenzar cada intento
        cout << mensaje; // Imprime en consola la indicación o prompt para el usuario
        getline(cin, texto); // Lee la línea completa de texto desde la consola, incluyendo espacios

        if (texto.empty()) // Evalúa si la cadena está vacía,  el usuario solo presionó la tecla Enter
        {
            cout << "Error: el campo no puede estar vacio.\n"; // Muestra el mensaje de error por campo no completado
            valido = false; // Marca la entrada como no válida para forzar la repetición del bucle
        }
        else if (soloLetras) // Evalúa si está activada la restricción de permitir únicamente letras y espacios
        {
            for (int i = 0; i < texto.length(); i++) // Recorre la cadena carácter por carácter desde la posición 0 hasta el final
            {
                char letra = texto[i]; // Extrae y guarda el carácter actual para su posterior inspección
                if (!((letra >= 'A' && letra <= 'Z') || // Comprueba si el carácter NO es una letra mayúscula,
                      (letra >= 'a' && letra <= 'z') || // NI una letra minúscula,
                      letra == ' '))                   // NI un espacio en blanco
                {
                    cout << "Error: ingrese solo letras y espacios.\n"; // Muestra el mensaje de error por carácter no permitido
                    valido = false; // Marca la entrada como no válida
                    break; // Interrumpe inmediatamente el bucle for al detectar el primer carácter no permitido
                }
            }
        }
    } while (!valido); // Repite el proceso do-while mientras la variable valido sea false
    return texto; // Retorna la cadena de texto completamente validada
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
