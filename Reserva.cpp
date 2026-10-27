```cpp
// Reserva Fredy
// Reserva Fredy
#include <iostream> // Incluye la librería estándar para operaciones de entrada y salida de datos (cin, cout)
#include <string>   // Incluye la librería para el manejo de cadenas de texto (std::string)
#include <limits>   // Incluye la librería para obtener información sobre tipos de datos y limpiar el búfer (numeric_limits)

using namespace std; // Evita anteponer el prefijo std:: antes de los elementos de la librería estándar
// ESTRUCTURA DE LA RESERVA
struct Proceso // Define la estructura (nodo) que almacenará los datos de cada reserva en la lista enlazada
{
    int id;               // Almacena el número entero que identifica de forma única la reserva
    string nombreHuesped; // Almacena el nombre y apellido del huésped registrado
    int habitacion;      // Almacena el número asignado a la habitación del hotel
    string descripcion;   // Almacena los detalles, notas o tipo de habitación reservada
    string estado;        // Almacena la etapa actual del flujo de la reserva (ej. Pendiente, Completado)
    int prioridad;     // Almacena el nivel de urgencia o prioridad asignado (1-Alta, 2-Media, 3-Baja)
    string fecha;         // Almacena la fecha de la reserva en formato de cadena (AAAA-MM-DD)
    Proceso* siguiente;   // Puntero de autorreferencia que almacena la dirección de memoria del siguiente nodo
};

// INICIO DE LA LISTA ENLAZADA
Proceso* inicioLista = NULL; // Declara la variable global puntero a la cabeza de la lista, inicializada como vacía (NULL)

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
Proceso* buscarPorID(int id) // Declara la función que recibe el ID buscado y retorna un puntero de tipo Proceso (dirección de memoria)
{
    Proceso* actual = inicioLista; // Inicializa un puntero auxiliar apuntando al inicio (cabeza) de la lista enlazada

    while (actual != NULL) // Inicia el bucle de recorrido que continuará mientras no se alcance el final de la lista
    {
        if (actual->id == id) // Evalúa si el ID del nodo en la posición actual coincide con el ID buscado
            return actual; // Retorna inmediatamente la dirección de memoria del nodo encontrado y finaliza la función
        actual = actual->siguiente; // Avanza el puntero auxiliar al siguiente nodo de la lista enlazada
    }
    return NULL; // Retorna NULL si se recorrió toda la lista y no se encontró ninguna coincidencia
}


// Mostrar los datos de una reserva
void mostrarReserva(Proceso* reserva) // Declara la función que recibe por parámetro la dirección de memoria (puntero) de la reserva a imprimir
{
    cout << "\nID: " << reserva->id << endl; // Imprime un salto de línea inicial y el valor del ID accediendo al campo id mediante el operador flecha (->)
    cout << "Nombre del huesped: " 
         << reserva->nombreHuesped << endl; // Imprime la etiqueta y la cadena con el nombre del huésped registrado
    cout << "Habitacion: " << reserva->habitacion << endl; // Imprime la etiqueta y el número de habitación asignada
    cout << "Descripcion: " << reserva->descripcion << endl; // Imprime la etiqueta y la descripción adicional asociada a la reserva
    cout << "Estado: " << reserva->estado << endl; // Imprime la etiqueta y el estado actual (ej. Pendiente, En proceso, Completado, Cancelado)
    cout << "Prioridad: "; // Imprime la etiqueta previa para mostrar posteriormente la versión en texto de la prioridad

    switch (reserva->prioridad) // Evalúa la propiedad numérica de la prioridad (1, 2 o 3)
    {
        case 1: cout << "Alta"; break; // Si el valor es 1, imprime "Alta" y sale del bloque switch mediante break
        case 2: cout << "Media"; break; // Si el valor es 2, imprime "Media" y sale del bloque switch mediante break
        case 3: cout << "Baja"; break; // Si el valor es 3, imprime "Baja" y sale del bloque switch mediante break
    }

    cout << endl; // Imprime un salto de línea final para separar el texto de la prioridad del siguiente campo
    cout << "Fecha: " << reserva->fecha << endl; // Imprime la etiqueta y la fecha registrada para la reserva
}


// 1. REGISTRAR RESERVA
void insertarProceso() // Declara la función principal para crear e insertar una nueva reserva en la lista enlazada
{
    cout << "\n--- REGISTRAR RESERVA ---\n"; // Imprime un salto de línea y el título del encabezado en consola
    int id; // Variable local para almacenar temporalmente el ID leido antes de asignarlo al nodo
    Proceso* encontrado; // Puntero auxiliar para almacenar el resultado de la búsqueda por ID y verificar duplicados

    // Validar ID y evitar duplicados
    do // Inicia el bucle de validación para garantizar que el ID ingresado sea único
    {
        id = leerNumero("Ingrese ID: ", 1, 1000000); // Solcita y valida que el ID ingresado esté en el rango numérico permitido
        encontrado = buscarPorID(id); // Invoca la función de búsqueda para verificar si el ID ya está registrado en algún nodo

        if (encontrado != NULL) // Si la función no retorna NULL, significa que el ID ya existe dentro de la lista
            cout << "Error: el ID ya existe.\n"; // Muestra un mensaje de advertencia informando la duplicidad del ID

    } while (encontrado != NULL); // Repite el bucle mientras el ID ingresado ya exista en la lista enlazada

    Proceso* nuevo = new Proceso; // Reserva dinámicamente un bloque de memoria en el heap para la nueva estructura tipo Proceso
    nuevo->id = id; // Asigna el ID validado al campo id del nodo recién creado

    nuevo->nombreHuesped = 
        leerTextoValido("Nombre del huesped: ", true); // Lee y valida que el nombre no esté vacío y contenga solo letras y espacios
    nuevo->habitacion = 
        leerNumero("Numero de habitacion (1 a 28): ", 1, 28); // Lee y valida que el número de habitación esté estrictamente entre 1 y 28
    nuevo->descripcion = 
        leerTextoValido("Descripcion: ", false); // Lee la descripción asegurando que el campo no se envíe vacío
    nuevo->estado = "Pendiente"; // Asigna el estado inicial por defecto "Pendiente" al registro de la reserva
    nuevo->prioridad = 
        leerNumero("Prioridad (1-Alta, 2-Media, 3-Baja): ", 1, 3); // Lee y limita el rango numérico de prioridad entre 1 y 3
    nuevo->fecha = 
        leerTextoValido("Fecha (AAAA-MM-DD): ", false); // Captura y valida la fecha ingresada como cadena de texto no vacía

    // Insertar al final de la lista
    nuevo->siguiente = NULL; // Asigna NULL al puntero siguiente del nuevo nodo, indicando que será el último de la lista

    if (inicioLista == NULL) // Evalúa si la lista enlazada se encuentra actualmente vacía (sin nodos registrados)
    {
        inicioLista = nuevo; // Asigna el nuevo nodo como la cabeza o inicio de la lista enlazada
    }
    else // Si la lista ya cuenta con uno o más elementos registrados
    {
        Proceso* actual = inicioLista; // Crea e inicializa un puntero auxiliar apuntando al inicio de la lista

        while (actual->siguiente != NULL) // Recorre la lista enlazada deteniéndose exactamente en el último nodo existente
            actual = actual->siguiente; // Desplaza el puntero auxiliar al nodo subsiguiente
        actual->siguiente = nuevo; // Enlaza el puntero siguiente del último nodo hacia la dirección de memoria del nuevo nodo
    }
    cout << "\nReserva registrada correctamente.\n"; // Muestra mensaje de confirmación tras insertar exitosamente el registro
}

// 2. BUSCAR RESERVA POR ID
void buscarProcesoID() // Declara la función para consultar y mostrar una reserva específica buscando por su ID
{
    cout << "\n--- BUSCAR RESERVA POR ID ---\n"; // Imprime un salto de línea y el título del encabezado en consola

    if (inicioLista == NULL) // Evalúa si la lista enlazada está vacía (sin reservas registradas)
    {
        cout << "No hay reservas registradas.\n"; // Muestra un mensaje informando que no existen registros en el sistema
        return; // Interrumpe y sale inmediatamente de la función al no haber datos que buscar
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000); // Solicita y valida que el ID ingresado sea un entero entre 1 y 1000000
    Proceso* reserva = buscarPorID(id); // Invoca la función auxiliar para obtener la dirección de memoria del nodo asociado al ID

    if (reserva != NULL) // Evalúa si la búsqueda retornó un puntero válido (reserva encontrada)
        mostrarReserva(reserva); // Invoca la función auxiliar para imprimir en pantalla todos los datos formateados de la reserva
    else // Se ejecuta si la búsqueda retornó NULL (no se encontró coincidencia)
        cout << "No se encontro una reserva con ese ID.\n"; // Muestra un mensaje de advertencia indicando la ausencia del registro
}

// 3. BUSCAR RESERVA POR NOMBRE
void buscarProcesoNombre() // Declara la función para buscar y listar todas las reservas asociadas al nombre de un huésped
{
    cout << "\n--- BUSCAR RESERVA POR NOMBRE ---\n"; // Imprime el encabezado visual de la sección en consola

    if (inicioLista == NULL) // Evalúa si la lista enlazada se encuentra completamente vacía
    {
        cout << "No hay reservas registradas.\n"; // Informa al usuario que no existen registros cargados en memoria
        return; // Interrumpe y finaliza inmediatamente la ejecución de la función
    }

    string nombre = leerTextoValido(
        "Ingrese el nombre del huesped: ", true
    ); // Solicita y valida que la entrada de texto no esté vacía y contenga únicamente letras y espacios

    Proceso* actual = inicioLista; // Crea e inicializa un puntero auxiliar apuntando a la cabeza de la lista
    bool encontrado = false; // Inicializa una bandera booleana para registrar si existe al menos una coincidencia
    while (actual != NULL) // Recorre secuencialmente la lista enlazada nodo por nodo hasta el final
    {
        if (actual->nombreHuesped == nombre) // Compara si el nombre del nodo actual coincide con el nombre buscado
        {
            mostrarReserva(actual); // Invoca la función auxiliar para imprimir todos los datos del nodo coincidente
            encontrado = true; // Cambia la bandera a true indicando que se halló al menos un registro
        }
        actual = actual->siguiente; // Avanza el puntero auxiliar al siguiente nodo de la lista enlazada
    }
    if (!encontrado) // Evalúa si la bandera permaneció en false al culminar el recorrido completo
        cout << "No se encontraron reservas para ese huesped.\n"; // Muestra mensaje indicando la ausencia de coincidencias
}

// 4. MODIFICAR RESERVA
void modificarProceso() // Declara la función para buscar y actualizar los campos de una reserva existente
{
    cout << "\n--- MODIFICAR RESERVA ---\n"; // Imprime el encabezado de la sección en la consola
    if (inicioLista == NULL) // Evalúa si la lista enlazada está vacía (sin registros cargados)
    {
        cout << "No hay reservas registradas.\n"; // Notifica al usuario que no existen datos que se puedan modificar
        return; // Interrumpe y finaliza la ejecución de la función de inmediato
    }
    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000); // Solicita y valida el ID de la reserva a modificar dentro del rango aceptado
    Proceso* reserva = buscarPorID(id); // Obtiene la dirección de memoria del nodo mediante la función auxiliar de búsqueda

    if (reserva == NULL) // Evalúa si el puntero es NULL (no se encontró ninguna reserva asociada a ese ID)
    {
        cout << "No existe una reserva con ese ID.\n"; // Muestra un mensaje de error indicando la inexistencia del registro
        return; // Sale de la función al no haber nodo que actualizar
    }
    cout << "\nReserva encontrada.\n"; // Muestra un mensaje indicando que el registro fue localizado exitosamente
    mostrarReserva(reserva); // Imprime los datos actuales del nodo antes de realizar la modificación

    reserva->nombreHuesped = 
        leerTextoValido("Nuevo nombre del huesped: ", true); // Solicita el nuevo nombre, validando que no esté vacío y contenga solo letras/espacios
    reserva->habitacion = 
        leerNumero("Nueva habitacion (1 a 28): ", 1, 28); // Lee y valida que la nueva habitación esté estrictamente dentro del rango de 1 a 28
    reserva->descripcion = 
        leerTextoValido("Nueva descripcion: ", false); // Captura la nueva descripción asegurando que no se ingrese una cadena vacía
    reserva->prioridad = 
        leerNumero("Nueva prioridad (1-Alta, 2-Media, 3-Baja): ", 1, 3); // Lee y valida la nueva prioridad en la escala del 1 al 3
    reserva->fecha = 
        leerTextoValido("Nueva fecha (AAAA-MM-DD): ", false); // Captura la nueva fecha en texto validando que no quede el campo en blanco

    cout << "\nReserva modificada correctamente.\n"; // Notifica al usuario que los cambios fueron aplicados con éxito en la memoria
}
// 5. ELIMINAR RESERVA
void eliminarProceso() // Declara la función para localizar, desconectar y liberar la memoria de una reserva por su ID
{
    cout << "\n--- ELIMINAR RESERVA ---\n"; // Imprime el encabezado visual de la sección en la consola

    if (inicioLista == NULL) // Evalúa si la lista enlazada está vacía (sin registros para eliminar)
    {
        cout << "No hay reservas registradas.\n"; // Notifica al usuario que no existen datos almacenados
        return; // Interrumpe y finaliza inmediatamente la ejecución de la función
    }

    int id = leerNumero(
        "Ingrese el ID de la reserva que desea eliminar: ",
        1, 1000000
    ); // Solicita y valida que el ID ingresado se encuentre en el rango de 1 a 1000000

    Proceso* actual = inicioLista; // Puntero auxiliar inicializado en la cabeza para recorrer la lista enlazada
    Proceso* anterior = NULL; // Puntero auxiliar para rastrear el nodo previo al nodo que se evaluará

    // Buscar el nodo que se desea eliminar
    while (actual != NULL && actual->id != id) // Avanza por la lista mientras no llegue al final Y no haya encontrado el ID buscado
    {
        anterior = actual; // Guarda la dirección del nodo actual como el nodo anterior antes de avanzar
        actual = actual->siguiente; // Desplaza el puntero auxiliar al siguiente nodo de la lista
    }
    if (actual == NULL) // Evalúa si se recorrió toda la lista hasta el final sin encontrar el ID buscado
    {
        cout << "No existe una reserva con ese ID.\n"; // Muestra un mensaje informando que el registro no existe
        return; // Finaliza la función al no haber nodo que eliminar
    }
    mostrarReserva(actual); // Imprime los datos del nodo localizado antes de proceder a borrarlo
    // Desconectar el nodo de la lista
    if (anterior == NULL) // Evalúa si el nodo a eliminar es el primero de la lista (cabeza)
        inicioLista = actual->siguiente; // Actualiza la cabeza de la lista hacia el segundo nodo
    else // Se ejecuta si el nodo a eliminar está en una posición intermedia o al final
        anterior->siguiente = actual->siguiente; // Reconecta el puntero siguiente del nodo anterior omitiendo el nodo actual

    delete actual; // Libera físicamente la memoria dinámica asignada al nodo eliminado mediante el operador delete

    cout << "\nReserva eliminada correctamente.\n"; // Notifica al usuario la confirmación del borrado exitoso
}
// 6. CAMBIAR ESTADO DE RESERVA
void cambiarEstado() // Declara la función para actualizar únicamente el estado del flujo de una reserva existente
{
    cout << "\n--- CAMBIAR ESTADO DE RESERVA ---\n"; // Imprime el encabezado visual de la sección en la consola

    if (inicioLista == NULL) // Evalúa si la lista enlazada está vacía (sin registros almacenados)
    {
        cout << "No hay reservas registradas.\n"; // Notifica al usuario que no existen datos registrados
        return; // Interrumpe y finaliza inmediatamente la ejecución de la función
    }

    int id = leerNumero("Ingrese el ID de la reserva: ", 1, 1000000); // Solicita y valida que el ID ingresado esté en el rango de 1 a 1000000

    Proceso* reserva = buscarPorID(id); // Obtiene la dirección de memoria del nodo correspondiente mediante la función auxiliar de búsqueda

    if (reserva == NULL) // Evalúa si la búsqueda devolvió NULL (reserva no encontrada)
    {
        cout << "No existe una reserva con ese ID.\n"; // Muestra un mensaje informando la inexistencia del registro
        return; // Finaliza la ejecución al no haber nodo que actualizar
    }

    cout << "\nHuesped: " << reserva->nombreHuesped << endl; // Muestra el nombre del huésped de la reserva encontrada
    cout << "Estado actual: " << reserva->estado << endl; // Muestra el estado en el que se encuentra actualmente la reserva

    cout << "\nSeleccione el nuevo estado:\n"; // Imprime el menú de opciones para la actualización del estado
    cout << "1. Pendiente\n"; // Opción 1: Estado inicial o en espera
    cout << "2. En proceso\n"; // Opción 2: Estado activo o en atencion
    cout << "3. Completado\n"; // Opción 3: Estado finalizado exitosamente
    cout << "4. Cancelado\n"; // Opción 4: Estado anulado

    int opcion = leerNumero("Opcion: ", 1, 4); // Lee y valida que la opción seleccionada esté estrictamente entre 1 y 4

    switch (opcion) // Evalúa la opción ingresada para asignar la cadena de texto correspondiente al atributo estado
    {
        case 1: reserva->estado = "Pendiente"; break; // Asigna "Pendiente" si la opción fue 1 y sale del switch
        case 2: reserva->estado = "En proceso"; break; // Asigna "En proceso" si la opción fue 2 y sale del switch
        case 3: reserva->estado = "Completado"; break; // Asigna "Completado" si la opción fue 3 y sale del switch
        case 4: reserva->estado = "Cancelado"; break; // Asigna "Cancelado" si la opción fue 4 y sale del switch
    }

    cout << "\nEstado actualizado correctamente.\n"; // Confirma al usuario que el cambio de estado se realizó con éxito
    cout << "Nuevo estado: " << reserva->estado << endl; // Muestra en consola el nuevo valor asignado al campo estado
}
