
#ifndef COLA_H
// Verifica si COLA_H todavía no ha sido definido.
// Sirve para evitar que este archivo se incluya varias veces.

#define COLA_H
// Define COLA_H para indicar que este archivo ya fue incluido.
// Así evitamos errores por incluir el mismo archivo repetidamente.

// Nodo de la cola: guarda solo el ID de la reserva en espera.
// Los datos completos están en la lista enlazada de reservas.
// Cada nodo también apunta al siguiente nodo de la cola.

struct NodoCola
// Define una estructura llamada NodoCola.
// Una estructura permite agrupar datos relacionados.

{
    int idProceso;
    // Guarda el número identificador del proceso o reserva.
    // Es int porque el ID es un número entero.

    NodoCola* siguiente;
    // Es un puntero que guarda la dirección del siguiente nodo.
    // Permite conectar los nodos y formar la cola.
};

// Pide un ID y encola esa reserva.
// Devuelve el ID encolado o 0 si no se pudo.

int encolarProceso();
// Declara una función que solicita un ID al usuario
// y agrega ese proceso a la cola.
// Devuelve el ID agregado si tiene éxito; 0 si falla.

// Agrega la reserva a la cola respetando su prioridad.
// Dentro de la misma prioridad, mantiene el orden FIFO.

bool encolarPorID(int id);
// Declara una función que recibe un ID como parámetro.
// Agrega a la cola el proceso correspondiente a ese ID,
// respetando la prioridad que utilice el programa.
// Devuelve true si se agrega correctamente y false si no.

// Atiende la reserva del frente: muestra sus datos,
// la pasa a "En atencion" y la retira de la cola.
// Devuelve el ID atendido o 0 si la cola estaba vacía.

int atenderProceso();
// Declara una función que atiende al primer proceso de la cola.
// Según el comentario, muestra sus datos, cambia su estado
// a "En atencion" y lo retira de la cola.
// Devuelve el ID atendido o 0 si no había procesos.

// Retira el primer elemento de la cola sin atenderlo.
// Devuelve su ID o 0 si estaba vacía.

int desencolarProceso();
// Declara una función que elimina el primer nodo de la cola
// sin realizar el proceso de atención.
// Devuelve el ID que retiró o 0 si la cola estaba vacía.

// Muestra todos los procesos que esperan en la cola,
// desde el frente hasta el final.

void mostrarCola();
// Declara una función que recorre la cola y muestra
// los procesos en el orden en que están esperando.
// void significa que no devuelve ningún valor.

// Devuelve true si el ID está en la cola.

bool estaEnCola(int id);
// Declara una función que busca un ID en la cola.
// Recibe el ID que queremos buscar.
// Devuelve true si lo encuentra y false si no.

// Quita de la cola, en cualquier posición,
// el proceso con ese ID. Devuelve true si estaba.

bool quitarDeCola(int id);
// Declara una función que busca el ID indicado y elimina
// el nodo correspondiente, aunque no esté al frente.
// Devuelve true si lo encontró y eliminó; false si no.

// Libera con delete todos los nodos de la cola.

void liberarCola();
// Declara una función que elimina todos los nodos
// dinámicos de la cola para liberar la memoria.
// No devuelve ningún valor.

#endif
// Finaliza la protección contra inclusiones repetidas.

