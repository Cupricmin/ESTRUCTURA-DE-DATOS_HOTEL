// Reserva.cpp

#include <iostream> // Entrada y salida de datos (cin, cout)
#include <iomanip>  // setw para alinear las tablas
#include <string>   // Manejo de cadenas de texto (std::string)
#include <limits>   // numeric_limits para limpiar el búfer del teclado
#include <cstdlib>  // exit y atoi
#include <cctype>   // isdigit y tolower
#include "Reserva.h"
#include "Habitacion.h" // Para asignar y liberar habitaciones
#include "Cola.h"       // Para sacar de la cola las reservas que ya no corresponden

using namespace std; // Evita anteponer el prefijo std:: antes de los elementos de la librería estándar

// INICIO DE LA LISTA ENLAZADA
Proceso* inicioLista = NULL; // Puntero global a la cabeza de la lista, inicializado como vacío (NULL)

// =====================================================================
// FUNCIONES AUXILIARES DE VALIDACIÓN
// =====================================================================

// Lee un número entero dentro de un rango y repite hasta que sea válido.
int leerNumero(string mensaje, int minimo, int maximo)
{
    int numero; // Variable temporal para almacenar el valor ingresado por el usuario
    do // Se repite mientras la entrada sea inválida o esté fuera de rango
    {
        cout << mensaje; // Imprime la indicación para el usuario

        if (!(cin >> numero)) // La lectura falló (ej. el usuario ingresó letras en lugar de números)
        {
            if (cin.eof()) // Si ya no hay más entrada (Ctrl+Z / fin de archivo) se cierra para no repetir infinitamente
            {
                cout << "\nFin de la entrada. Cerrando el programa.\n";
                exit(0);
            }
            cout << "Error: ingrese un numero valido.\n"; // Mensaje de error por tipo de dato incorrecto
            cin.clear(); // Limpia la bandera de error (failbit) de cin para permitir nuevas lecturas
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta el texto inválido que quedó en el búfer
            numero = minimo - 1; // Valor fuera de rango para que el do-while se repita
        }
        else if (numero < minimo || numero > maximo) // Número correcto pero fuera de los límites
        {
            cout << "Error: ingrese un numero entre "
                 << minimo << " y " << maximo << ".\n";
        }
    } while (numero < minimo || numero > maximo); // Repite si no está en el rango [minimo, maximo]

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el '\n' restante para no afectar los getline posteriores
    return numero; // Devuelve el número validado
}

// Lee un texto no vacío; si soloLetras es true, solo acepta letras y espacios.
string leerTextoValido(string mensaje, bool soloLetras)
{
    string texto;  // Variable para almacenar la cadena ingresada
    bool valido;   // Bandera de control del bucle de validación

    do // Se repite hasta que la entrada cumpla todas las condiciones
    {
        valido = true; // Se asume válido al comenzar cada intento
        cout << mensaje;
        if (!getline(cin, texto)) // Lee la línea completa; si ya no hay entrada, cierra el programa
        {
            cout << "\nFin de la entrada. Cerrando el programa.\n";
            exit(0);
        }

        if (texto.empty()) // El usuario solo presionó Enter
        {
            cout << "Error: el campo no puede estar vacio.\n";
            valido = false;
        }
        else if (soloLetras) // Si se exige solo letras y espacios
        {
            for (int i = 0; i < (int)texto.length(); i++) // Recorre la cadena carácter por carácter
            {
                unsigned char letra = (unsigned char)texto[i]; // Carácter actual
                // Se aceptan A-Z, a-z, espacio y también letras con tilde o ñ (códigos >= 128).
                if (!((letra >= 'A' && letra <= 'Z') ||
                      (letra >= 'a' && letra <= 'z') ||
                      letra == ' ' ||
                      letra >= 128))
                {
                    cout << "Error: ingrese solo letras y espacios.\n";
                    valido = false;
                    break; // Detiene la revisión al encontrar el primer carácter no permitido
                }
            }
        }
    } while (!valido); // Repite mientras no sea válido
    return texto;
}

// Comprueba que el texto tenga el formato AAAA-MM-DD y que sea una fecha real.
bool fechaValida(const string& fecha)
{
    if (fecha.length() != 10 || fecha[4] != '-' || fecha[7] != '-') // Formato: 4 dígitos, guion, 2, guion, 2
        return false;

    for (int i = 0; i < 10; i++) // Todas las demás posiciones deben ser dígitos
    {
        if (i == 4 || i == 7) continue;
        if (!isdigit((unsigned char)fecha[i])) return false;
    }

    int anio = atoi(fecha.substr(0, 4).c_str()); // Convierte las partes del texto a números
    int mes  = atoi(fecha.substr(5, 2).c_str());
    int dia  = atoi(fecha.substr(8, 2).c_str());

    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    if (bisiesto) diasPorMes[1] = 29; // Febrero tiene 29 días en año bisiesto

    if (anio < 2000 || mes < 1 || mes > 12) return false;
    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

// Lee una fecha y repite hasta que tenga formato AAAA-MM-DD y sea válida (RF11).
string leerFecha(string mensaje)
{
    string fecha;
    do
    {
        fecha = leerTextoValido(mensaje, false); // Reutiliza la lectura de texto no vacío
        if (!fechaValida(fecha))
            cout << "Error: fecha invalida. Use el formato AAAA-MM-DD (ej. 2026-11-15).\n";
    } while (!fechaValida(fecha));
    return fecha;
}

// Devuelve true si el texto es uno de los 6 estados permitidos.
bool estadoValido(const string& estado)
{
    return estado == ESTADO_PENDIENTE || estado == ESTADO_CONFIRMADA ||
           estado == ESTADO_EN_ATENCION || estado == ESTADO_FINALIZADA ||
           estado == ESTADO_CANCELADA || estado == ESTADO_NO_PRESENTADO;
}

// Una reserva "activa" (Pendiente, Confirmada o En atencion) mantiene su habitación ocupada.
// Finalizada, Cancelada y No presentado la dejan libre.
bool estadoOcupaHabitacion(const string& estado)
{
    return estado == ESTADO_PENDIENTE || estado == ESTADO_CONFIRMADA ||
           estado == ESTADO_EN_ATENCION;
}

// Convierte la prioridad numérica en texto (1-Alta, 2-Media, 3-Baja).
string textoPrioridad(int prioridad)
{
    if (prioridad == 1) return "Alta";
    if (prioridad == 2) return "Media";
    return "Baja";
}

// Pasa un texto a minúsculas (se usa para buscar por nombre sin importar mayúsculas).
static string aMinusculas(string texto)
{
    for (int i = 0; i < (int)texto.length(); i++)
        texto[i] = (char)tolower((unsigned char)texto[i]);
    return texto;
}

// Pide un número de habitación hasta que esté libre (o ya sea de esa misma reserva).
static int leerHabitacionDisponible(string mensaje, int idReservaActual)
{
    while (true)
    {
        int numero = leerNumero(mensaje, 1, 28); // Valida que esté entre 1 y 28
        NodoHabitacion* hab = buscarHabitacion(numero); // Busca el nodo de esa habitación

        if (hab == NULL || hab->estado == HAB_LIBRE || hab->idReserva == idReservaActual)
            return numero; // Está libre (o ya es de esta reserva): se acepta

        cout << "Error: la habitacion " << numero << " ya esta ocupada por la reserva ID "
             << hab->idReserva << ".\n";
        mostrarHabitacionesDisponibles(); // Ayuda al usuario mostrando las que sí están libres
    }
}

// Libera la habitación de una reserva, solo si de verdad estaba a nombre de esa reserva.
static void soltarHabitacion(Proceso* reserva)
{
    NodoHabitacion* hab = buscarHabitacion(reserva->habitacion);
    if (hab != NULL && hab->idReserva == reserva->id)
        liberarHabitacion(hab->numero);
}

// =====================================================================
// OPERACIONES BÁSICAS DE LA LISTA ENLAZADA
// =====================================================================

// Buscar una reserva por su ID: recorre la lista nodo por nodo.
Proceso* buscarPorID(int id)
{
    Proceso* actual = inicioLista; // Puntero auxiliar apuntando al inicio de la lista

    while (actual != NULL) // Continúa mientras no se alcance el final de la lista
    {
        if (actual->id == id) // ¿El ID del nodo coincide con el buscado?
            return actual; // Devuelve la dirección de memoria del nodo encontrado
        actual = actual->siguiente; // Avanza al siguiente nodo
    }
    return NULL; // Se recorrió toda la lista y no hubo coincidencia
}

// Mostrar los datos de una reserva (recibe el puntero al nodo).
void mostrarReserva(Proceso* reserva)
{
    cout << "\nID: " << reserva->id << endl;
    cout << "Nombre del huesped: " << reserva->nombreHuesped << endl;
    cout << "Habitacion: " << reserva->habitacion;
    NodoHabitacion* hab = buscarHabitacion(reserva->habitacion); // Busca el tipo y la tarifa de la habitación
    if (hab != NULL)
        cout << " (" << hab->tipo << " - S/ " << hab->tarifa << ")";
    cout << endl;
    cout << "Descripcion: " << reserva->descripcion << endl;
    cout << "Estado: " << reserva->estado << endl;
    cout << "Prioridad: ";

    switch (reserva->prioridad) // Convierte la prioridad numérica en texto
    {
        case 1: cout << "Alta"; break;
        case 2: cout << "Media"; break;
        case 3: cout << "Baja"; break;
    }

    cout << endl;
    cout << "Fecha: " << reserva->fecha << endl;
}

// Agrega un nodo ya creado al FINAL de la lista (o como cabeza si la lista está vacía).
void insertarAlFinal(Proceso* nuevo)
{
    nuevo->siguiente = NULL; // El nuevo nodo será el último, así que su siguiente es NULL

    if (inicioLista == NULL) // Lista vacía
    {
        inicioLista = nuevo; // El nuevo nodo pasa a ser la cabeza
    }
    else
    {
        Proceso* actual = inicioLista; // Puntero auxiliar apuntando al inicio
        while (actual->siguiente != NULL) // Recorre hasta quedarse en el último nodo
            actual = actual->siguiente;
        actual->siguiente = nuevo; // Enlaza el último nodo con el nuevo
    }
}

// Cuenta cuántas reservas hay en la lista.
int contarReservas()
{
    int total = 0;
    Proceso* actual = inicioLista;
    while (actual != NULL)
    {
        total++;
        actual = actual->siguiente;
    }
    return total;
}

// Borra con delete todos los nodos de la lista (al cargar datos o al cerrar el programa).
void liberarLista()
{
    while (inicioLista != NULL)
    {
        Proceso* aux = inicioLista;         // Guarda el nodo a borrar
        inicioLista = inicioLista->siguiente; // La cabeza pasa al siguiente nodo
        delete aux;                         // Libera la memoria del nodo
    }
}

// =====================================================================
// OPERACIONES DEL MENÚ
// =====================================================================

// 1. REGISTRAR RESERVA: pide los datos, crea el nodo y lo inserta al final.
// Devuelve el ID registrado (o 0 si no se pudo registrar).
int insertarProceso()
{
    cout << "\n--- REGISTRAR RESERVA ---\n";

    if (contarHabitacionesLibres() == 0) // RF08: no se puede reservar si no hay habitaciones libres
    {
        cout << "No hay habitaciones libres. No se puede registrar una reserva.\n";
        return 0;
    }

    int id;
    Proceso* encontrado; // Puntero auxiliar para detectar IDs duplicados

    // Validar ID y evitar duplicados
    do
    {
        id = leerNumero("Ingrese ID: ", 1, 1000000);
        encontrado = buscarPorID(id); // Busca si el ID ya existe en la lista

        if (encontrado != NULL)
            cout << "Error: el ID ya existe.\n";

    } while (encontrado != NULL); // Repite mientras el ID ya exista

    Proceso* nuevo = new Proceso; // Reserva memoria dinámica (heap) para el nuevo nodo
    nuevo->id = id;

    nuevo->nombreHuesped =
        leerTextoValido("Nombre del huesped: ", true);
    nuevo->habitacion =
        leerHabitacionDisponible("Numero de habitacion (1 a 28): ", id); // Solo acepta habitaciones libres
    nuevo->descripcion =
        leerTextoValido("Descripcion: ", false);
    nuevo->estado = ESTADO_PENDIENTE; // Todo proceso nuevo empieza como "Pendiente"
    nuevo->prioridad =
        leerNumero("Prioridad (1-Alta, 2-Media, 3-Baja): ", 1, 3);
    nuevo->fecha =
        leerFecha("Fecha (AAAA-MM-DD): ");

    asignarHabitacion(nuevo->habitacion, nuevo->id); // Marca la habitación como ocupada por esta reserva
    insertarAlFinal(nuevo); // Enlaza el nodo al final de la lista

    cout << "\nReserva registrada correctamente.\n";
    return id;
}

// 2. BUSCAR RESERVA POR ID
void buscarProcesoID()
{
    cout << "\n--- BUSCAR RESERVA POR ID ---\n";

    if (inicioLista == NULL) // Lista vacía
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000);
    Proceso* reserva = buscarPorID(id); // Dirección del nodo (o NULL si no existe)

    if (reserva != NULL)
        mostrarReserva(reserva);
    else
        cout << "No se encontro una reserva con ese ID.\n";
}

// 3. BUSCAR RESERVA POR NOMBRE (sin importar mayúsculas y aceptando nombres parciales)
void buscarProcesoNombre()
{
    cout << "\n--- BUSCAR RESERVA POR NOMBRE ---\n";

    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    string nombre = leerTextoValido("Ingrese el nombre del huesped: ", true);
    string buscado = aMinusculas(nombre); // Se compara todo en minúsculas

    Proceso* actual = inicioLista; // Puntero auxiliar para recorrer
    bool encontrado = false;       // Indica si hubo al menos una coincidencia
    while (actual != NULL)
    {
        // find devuelve string::npos si el texto buscado NO está dentro del nombre
        if (aMinusculas(actual->nombreHuesped).find(buscado) != string::npos)
        {
            mostrarReserva(actual);
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    if (!encontrado)
        cout << "No se encontraron reservas para ese huesped.\n";
}

// MOSTRAR TODAS LAS RESERVAS (RF09): recorre la lista e imprime una fila por reserva.
void mostrarReservas()
{
    cout << "\n--- LISTA DE RESERVAS ---\n";

    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return;
    }

    cout << left << setw(9) << "ID" << setw(24) << "Huesped" << setw(6) << "Hab"
         << setw(15) << "Estado" << setw(11) << "Prioridad" << "Fecha" << endl;
    cout << "--------------------------------------------------------------------------\n";

    Proceso* actual = inicioLista;
    int total = 0;
    while (actual != NULL) // Recorre la lista nodo por nodo
    {
        string nombre = actual->nombreHuesped;
        if (nombre.length() > 22) nombre = nombre.substr(0, 22); // Recorta nombres largos para no desalinear

        cout << left << setw(9) << actual->id << setw(24) << nombre
             << setw(6) << actual->habitacion << setw(15) << actual->estado
             << setw(11) << textoPrioridad(actual->prioridad) << actual->fecha << endl;
        total++;
        actual = actual->siguiente;
    }
    cout << "\nTotal de reservas: " << total << endl;
}

// 4. MODIFICAR RESERVA: busca por ID y reemplaza los datos del nodo (sin crear otro nodo).
// Devuelve el ID modificado (o 0 si no se modificó nada).
int modificarProceso()
{
    cout << "\n--- MODIFICAR RESERVA ---\n";
    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return 0;
    }
    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000);
    Proceso* reserva = buscarPorID(id);

    if (reserva == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return 0;
    }
    cout << "\nReserva encontrada.\n";
    mostrarReserva(reserva); // Muestra los datos actuales antes de modificarlos

    bool ocupa = estadoOcupaHabitacion(reserva->estado); // ¿La reserva tiene una habitación ocupada?
    int prioridadAnterior = reserva->prioridad;          // Se guarda para saber si cambió

    reserva->nombreHuesped =
        leerTextoValido("Nuevo nombre del huesped: ", true);

    int nuevaHabitacion;
    if (ocupa) // Si la reserva está activa, la nueva habitación debe estar libre
        nuevaHabitacion = leerHabitacionDisponible("Nueva habitacion (1 a 28): ", reserva->id);
    else       // Si ya terminó (Finalizada, Cancelada...) no ocupa habitación, solo se corrige el dato
        nuevaHabitacion = leerNumero("Nueva habitacion (1 a 28): ", 1, 28);

    reserva->descripcion =
        leerTextoValido("Nueva descripcion: ", false);
    reserva->prioridad =
        leerNumero("Nueva prioridad (1-Alta, 2-Media, 3-Baja): ", 1, 3);
    reserva->fecha =
        leerFecha("Nueva fecha (AAAA-MM-DD): ");

    if (ocupa && nuevaHabitacion != reserva->habitacion) // Si cambió de habitación...
    {
        liberarHabitacion(reserva->habitacion);          // ...libera la anterior
        asignarHabitacion(nuevaHabitacion, reserva->id); // ...y ocupa la nueva
    }
    reserva->habitacion = nuevaHabitacion;

    // Si cambió la prioridad y la reserva está en la cola, se vuelve a ubicar según su nueva prioridad.
    if (prioridadAnterior != reserva->prioridad && estaEnCola(reserva->id))
    {
        quitarDeCola(reserva->id);
        encolarPorID(reserva->id);
    }

    cout << "\nReserva modificada correctamente.\n";
    return id;
}

// 5. ELIMINAR RESERVA: desconecta el nodo de la lista y libera su memoria.
// Devuelve el ID eliminado (o 0 si no se eliminó nada).
int eliminarProceso()
{
    cout << "\n--- ELIMINAR RESERVA ---\n";

    if (inicioLista == NULL)
    {
        cout << "No hay reservas registradas.\n";
        return 0;
    }

    int id = leerNumero(
        "Ingrese el ID de la reserva que desea eliminar: ",
        1, 1000000
    );

    Proceso* actual = inicioLista; // Puntero auxiliar para recorrer
    Proceso* anterior = NULL;      // Guarda el nodo previo al que se evalúa

    // Buscar el nodo que se desea eliminar
    while (actual != NULL && actual->id != id)
    {
        anterior = actual;          // Guarda el nodo actual como anterior antes de avanzar
        actual = actual->siguiente;
    }
    if (actual == NULL) // Se llegó al final sin encontrar el ID
    {
        cout << "No existe una reserva con ese ID.\n";
        return 0;
    }
    mostrarReserva(actual); // Muestra los datos antes de borrarlo

    // Desconectar el nodo de la lista
    if (anterior == NULL) // El nodo a eliminar es el primero (cabeza)
        inicioLista = actual->siguiente; // La cabeza pasa al segundo nodo
    else // Está en medio o al final
        anterior->siguiente = actual->siguiente; // El nodo anterior "salta" al nodo eliminado

    soltarHabitacion(actual); // Libera la habitación que tenía ocupada
    quitarDeCola(actual->id); // Si estaba en la cola de atención, también se retira

    delete actual; // Libera la memoria dinámica del nodo eliminado

    cout << "\nReserva eliminada correctamente.\n";
    return id;
}

// Cambia el estado de una reserva y mantiene coherentes las habitaciones y la cola.
// Devuelve false si el cambio no se puede hacer (por ejemplo, su habitación ya fue tomada).
bool aplicarEstado(Proceso* reserva, const string& nuevoEstado)
{
    bool ocupabaAntes = estadoOcupaHabitacion(reserva->estado); // ¿Tenía habitación ocupada?
    bool ocupaAhora = estadoOcupaHabitacion(nuevoEstado);       // ¿Y con el nuevo estado?

    if (ocupaAhora && !ocupabaAntes) // Ejemplo: de "No presentado" vuelve a "Pendiente"
    {
        if (!asignarHabitacion(reserva->habitacion, reserva->id)) // Necesita su habitación otra vez
        {
            cout << "No se puede cambiar el estado: la habitacion " << reserva->habitacion
                 << " ya esta ocupada por otra reserva.\n";
            return false;
        }
    }
    else if (!ocupaAhora && ocupabaAntes) // Ejemplo: pasa a "Finalizada" o "Cancelada"
    {
        soltarHabitacion(reserva); // Libera la habitación para futuras reservas
    }

    reserva->estado = nuevoEstado; // Aplica el nuevo estado

    // Una reserva que ya está en atención o terminó no debe seguir esperando en la cola.
    if (nuevoEstado == ESTADO_EN_ATENCION || !ocupaAhora)
        quitarDeCola(reserva->id);

    return true;
}

// 6. CAMBIAR ESTADO DE RESERVA (sigue el algoritmo CambiarEstadoProceso del informe).
// Devuelve el ID de la reserva si se cambió el estado, o 0 si no.
int cambiarEstado()
{
    cout << "\n--- CAMBIAR ESTADO DE RESERVA ---\n";

    if (inicioLista == NULL) // Paso 1 del algoritmo: lista vacía
    {
        cout << "No hay reservas registradas.\n";
        return 0;
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000);
    Proceso* reserva = buscarPorID(id); // Paso 3: busca el proceso por ID

    if (reserva == NULL) // Paso 4: no se encontró
    {
        cout << "No existe una reserva con ese ID.\n";
        return 0;
    }

    cout << "\nHuesped: " << reserva->nombreHuesped << endl;
    cout << "Estado actual: " << reserva->estado << endl;

    // Paso 5: un proceso cerrado ya no puede cambiar de estado
    if (reserva->estado == ESTADO_FINALIZADA || reserva->estado == ESTADO_CANCELADA)
    {
        cout << "El proceso ya fue cerrado y no puede cambiar de estado.\n";
        return 0;
    }

    cout << "\nSeleccione el nuevo estado:\n";
    cout << "1. Pendiente\n";
    cout << "2. Confirmada\n";
    cout << "3. En atencion\n";
    cout << "4. Finalizada\n";
    cout << "5. Cancelada\n";
    cout << "6. No presentado\n";

    int opcion = leerNumero("Opcion: ", 1, 6); // Paso 2: solo se pueden elegir estados válidos

    string nuevoEstado;
    switch (opcion) // Convierte la opción en el texto del estado
    {
        case 1: nuevoEstado = ESTADO_PENDIENTE; break;
        case 2: nuevoEstado = ESTADO_CONFIRMADA; break;
        case 3: nuevoEstado = ESTADO_EN_ATENCION; break;
        case 4: nuevoEstado = ESTADO_FINALIZADA; break;
        case 5: nuevoEstado = ESTADO_CANCELADA; break;
        case 6: nuevoEstado = ESTADO_NO_PRESENTADO; break;
    }

    if (nuevoEstado == reserva->estado)
    {
        cout << "La reserva ya tiene ese estado.\n";
        return 0;
    }

    string estadoAnterior = reserva->estado;
    if (!aplicarEstado(reserva, nuevoEstado)) // Paso 6: actualiza el estado (y habitación/cola si hace falta)
        return 0;

    cout << "\nEstado actualizado de " << estadoAnterior << " a " << reserva->estado << ".\n";
    return id;
}

// =====================================================================
// INTEGRACIÓN CON HABITACIONES
// =====================================================================

// Asigna (o cambia) la habitación de una reserva activa, verificando que esté libre (RF07 y RF08).
// Devuelve true solo si se hizo el cambio.
bool asignarHabitacionAReserva(int idReserva, int numeroHabitacion)
{
    Proceso* reserva = buscarPorID(idReserva);
    if (reserva == NULL)
    {
        cout << "No existe una reserva con ese ID.\n";
        return false;
    }
    if (!estadoOcupaHabitacion(reserva->estado)) // Una reserva cerrada ya no puede ocupar habitación
    {
        cout << "La reserva esta en estado '" << reserva->estado
             << "' y ya no puede ocupar una habitacion.\n";
        return false;
    }
    if (reserva->habitacion == numeroHabitacion)
    {
        cout << "La reserva ya tiene asignada esa habitacion.\n";
        return false;
    }

    NodoHabitacion* hab = buscarHabitacion(numeroHabitacion);
    if (hab == NULL)
    {
        cout << "La habitacion no existe.\n";
        return false;
    }
    if (hab->estado == HAB_OCUPADA) // RF08: se verifica la disponibilidad antes de asignar
    {
        cout << "La habitacion " << numeroHabitacion << " ya esta ocupada por la reserva ID "
             << hab->idReserva << ".\n";
        return false;
    }

    soltarHabitacion(reserva);                        // Libera la habitación anterior
    asignarHabitacion(numeroHabitacion, idReserva);   // Ocupa la nueva
    reserva->habitacion = numeroHabitacion;           // Actualiza el dato dentro del nodo de la reserva

    cout << "Habitacion " << numeroHabitacion << " asignada a la reserva ID " << idReserva << ".\n";
    return true;
}

// Check-out: libera una habitación ocupada y finaliza su reserva.
// Devuelve el ID de la reserva finalizada (o 0 si no se hizo nada).
int hacerCheckOut(int numeroHabitacion)
{
    NodoHabitacion* hab = buscarHabitacion(numeroHabitacion);
    if (hab == NULL)
    {
        cout << "La habitacion no existe.\n";
        return 0;
    }
    if (hab->estado == HAB_LIBRE)
    {
        cout << "La habitacion " << numeroHabitacion << " ya esta libre.\n";
        return 0;
    }

    int id = hab->idReserva;
    Proceso* reserva = buscarPorID(id);
    if (reserva == NULL) // Caso raro: habitación ocupada por una reserva que ya no existe
    {
        liberarHabitacion(numeroHabitacion);
        return id;
    }
    if (reserva->estado != ESTADO_EN_ATENCION) // El check-out solo aplica a huéspedes que están en el hotel
    {
        cout << "La reserva ID " << id << " esta en estado '" << reserva->estado
             << "'. El check-out solo se hace con reservas 'En atencion'.\n"
             << "Use 'Cambiar estado' (Cancelada o No presentado) para liberar esa habitacion.\n";
        return 0;
    }

    aplicarEstado(reserva, ESTADO_FINALIZADA); // Finaliza la reserva y libera la habitación
    cout << "Check-out realizado. Habitacion " << numeroHabitacion
         << " liberada y reserva ID " << id << " finalizada.\n";
    return id;
}
