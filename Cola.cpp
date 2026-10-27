#include <iostream> // Libreria para entrada y salida de datos
#include <string>   // Libreria para usar textos (string)

using namespace std; // Evita escribir std:: antes de comandos como cout y cin

// Estructura que representa cada proceso o solicitud en la cola
struct Proceso
{
    int id;               // ID del proceso
    string nombreHuesped; // Nombre del huesped
    int habitacion;       // Numero de habitacion
    string descripcion;   // Detalle del servicio solicitado
    string estado;        // Estado actual (Pendiente, Atendido)
    int prioridad;        // Nivel de urgencia (1: Alta, 2: Media, 3: Baja)
    string fecha;         // Fecha y hora del registro

    Proceso* siguiente;   // Puntero que apunta al siguiente nodo de la cola
};

// Punteros globales para controlar el inicio y fin de la cola
Proceso* frente = NULL; // Puntero al primer nodo de la cola (inicia vacio)
Proceso* final = NULL;  // Puntero al ultimo nodo de la cola (inicia vacio)

// Declaracion de las funciones que usara el programa
void encolarProceso();   // Agrega un nuevo proceso al final
void atenderProceso();   // Procesa la solicitud al frente de la cola
void desencolarProceso(); // Elimina la primera solicitud
void mostrarCola();      // Muestra la lista de procesos pendientes

// Funcion principal del programa
int main() {
    int opcion; // Variable para guardar la opcion elegida por el usuario

    // Bucle para repetir el menu hasta que el usuario elija salir
    do {
        cout << "\n========================================\n"; 
        cout << "   MODULO DE ATENCION A SOLICITUDES     \n"; 
        cout << "========================================\n"; 
        cout << "1. Registrar nueva solicitud (Encolar)\n";      
        cout << "2. Atender solicitud actual (Atender)\n";      
        cout << "3. Eliminar primera solicitud (Desencolar)\n"; 
        cout << "4. Ver cola de solicitudes pendientes\n";     
        cout << "5. Salir\n";                                   
        cout << "Seleccione una opcion: ";                      // Pide una seleccion al usuario
        cin >> opcion;                                         // Lee y guarda la opcion ingresada

        // Evalua la opcion ingresada por el usuario
        switch (opcion) {
            case 1: // Si eligio la opcion 1
                encolarProceso(); // Llama a la funcion para encolar[cite: 2]
                break;            // Sale del bloque switch
            case 2: // Si eligio la opcion 2
                atenderProceso(); // Llama a la funcion para atender
                break;            // Sale del bloque switch
            case 3: // Si eligio la opcion 3
                desencolarProceso(); // Llama a la funcion para desencolar
                break;               // Sale del bloque switch
            case 4: // Si eligio la opcion 4
                mostrarCola(); // Llama a la funcion para mostrar la cola
                break;         // Sale del bloque switch
            case 5: // Si eligio la opcion 5
                cout << "\nSaliendo del modulo...\n"; // Mensaje de despedida
                break;                                // Sale del bloque switch
            default: // Si eligio una opcion fuera del menu
                cout << "\nOpcion no valida, intenta de nuevo.\n"; // Mensaje de error
                break;                                             // Sale del bloque switch
        }
    } while (opcion != 5); // Continua ejecutandose mientras la opcion no sea 5

    return 0; // Finaliza la ejecucion del programa correctamente
}

// Funcion para agregar un proceso a la cola (siguiendo el diagrama de flujo)
void encolarProceso() {
    Proceso* NuevoNodo = new Proceso(); // Reserva espacio en memoria para el nuevo nodo[cite: 2]

    cout << "\n--- REGISTRAR NUEVA SOLICITUD ---\n"; // Titulo del formulario

    // ENTRADA: Recibir IDProceso
    cout << "Ingrese el ID del Proceso: "; // Pide el ID del proceso en pantalla[cite: 2]
    cin >> NuevoNodo->id;                  // Guarda el ID directamente en el nodo[cite: 2]

    cin.ignore(); // Limpia el salto de linea del teclado
    cout << "Nombre del huesped: "; // Pide el nombre del huesped
    getline(cin, NuevoNodo->nombreHuesped); // Guarda la linea de texto completa con el nombre

    cout << "Numero de habitacion: "; // Pide el numero de habitacion
    cin >> NuevoNodo->habitacion;      // Guarda el numero de habitacion

    cin.ignore(); // Limpia el teclado para leer la siguiente frase
    cout << "Descripcion del servicio: "; // Pide el detalle de la solicitud
    getline(cin, NuevoNodo->descripcion); // Guarda la descripcion del servicio

    cout << "Prioridad (1: Alta, 2: Media, 3: Baja): "; // Pide la prioridad
    cin >> NuevoNodo->prioridad;                         // Guarda el numero de prioridad

    cin.ignore(); // Limpia el teclado antes de la ultima entrada de texto
    cout << "Fecha y Hora: "; // Pide la fecha y hora
    getline(cin, NuevoNodo->fecha); // Guarda el texto de la fecha y hora

    NuevoNodo->estado = "Pendiente"; // Define el estado por defecto como Pendiente

    // PROCESO: NuevoNodo -> siguiente = NULL
    NuevoNodo->siguiente = NULL; // El nuevo nodo apunta a NULL porque ira al final[cite: 2]

    // CONDICIONAL: ¿frente == NULL?
    if (frente == NULL) { // Comprueba si la cola esta actualmente vacia[cite: 2]
        // SI:
        frente = NuevoNodo; // Apunta el puntero frente al nuevo nodo[cite: 2]
        final = NuevoNodo;  // Apunta el puntero final al nuevo nodo[cite: 2]
    } else {
        // NO:
        final->siguiente = NuevoNodo; // El nodo al final actual conecta su puntero al nuevo nodo[cite: 2]
        final = NuevoNodo;            // El puntero final pasa a ser el nuevo nodo recién agregado[cite: 2]
    }

    // SALIDA: Mostrar mensaje "Proceso encolado con exito"
    cout << "\nProceso encolado con exito\n"; // Imprime exactamente el mensaje de exito del diagrama[cite: 2]
}

// Funcion para atender y mostrar la solicitud al frente de la cola
void atenderProceso() {
    // Evalua si no hay elementos en la cola
    if (frente == NULL) {
        cout << "\n[!] No hay solicitudes pendientes por atender.\n"; // Muestra mensaje de cola vacia
        return; // Sale de la funcion inmediatamente
    }

    cout << "\n--- ATENDIENDO SOLICITUD EN FRENTE ---\n"; // Titulo del proceso
    cout << "ID Solicitud  : " << frente->id << "\n";          // Imprime el ID del elemento del frente
    cout << "Huesped       : " << frente->nombreHuesped << "\n"; // Imprime el nombre del huesped
    cout << "Habitacion    : " << frente->habitacion << "\n";    // Imprime la habitacion
    cout << "Descripcion   : " << frente->descripcion << "\n";   // Imprime el detalle del servicio
    cout << "Fecha         : " << frente->fecha << "\n";         // Imprime la fecha de registro

    frente->estado = "Atendido"; // Cambia el valor del estado a Atendido
    cout << "Estado actual : " << frente->estado << "\n"; // Muestra la confirmacion de estado

    cout << "\nSolicitud completada. Retirando de la cola...\n"; // Informa al usuario
    desencolarProceso(); // Elimina el elemento
