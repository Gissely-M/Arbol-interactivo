#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include <functional>

using namespace std;

// Definición de la estructura del nodo (versión genérica con plantilla)
template <typename T>
struct Nodo {
    T valor;
    Nodo* izquierdo;
    Nodo* derecho;
    int nivel;
    
    Nodo(T val, int lvl) : valor(val), izquierdo(nullptr), derecho(nullptr), nivel(lvl) {}
};

// Función para crear el árbol interactivamente con validación de entrada
template <typename T>
void crearArbol(Nodo<T>* &raiz, int nivelActual, int profundidadMaxima) {
    if (nivelActual > profundidadMaxima) {
        cout << "No se puede anadir este nodo. Se ha alcanzado la profundidad maxima (" << profundidadMaxima << ")." << endl;
        return;
    }
    
    T valor;
    bool entradaValida = false;
    while (!entradaValida) {
        cout << "\nIngrese el valor para el nodo del nivel " << nivelActual << ": ";
        if (cin >> valor) {
            entradaValida = true;
        } else {
            cout << "Entrada no válida. Por favor ingrese un valor compatible con el tipo seleccionado." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    raiz = new Nodo<T>(valor, nivelActual);
    
    cout << "Nodo creado en el nivel " << nivelActual << " de " << profundidadMaxima << " niveles maximos.\n" << endl;
    
    if (nivelActual == profundidadMaxima) {
        cout << "Este nodo esta en el nivel maximo permitido. No puedes anadir mas valores." << endl;
        return;
    }
    
    char respuesta;
    bool respuestaValida = false;
    
    do {
        cout << "¿Desea crear un hijo izquierdo para " << valor << "? (s/n): ";
        cin >> respuesta;
        
        if (respuesta == 's' || respuesta == 'S' || respuesta == 'n' || respuesta == 'N') {
            respuestaValida = true;
        } else {
            cout << "Respuesta inválida. Por favor ingrese 's' o 'n'." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!respuestaValida);
    
    if (respuesta == 's' || respuesta == 'S') {
        cout << "Creando hijo izquierdo (nivel " << nivelActual + 1 << "):" << endl;
        crearArbol(raiz->izquierdo, nivelActual + 1, profundidadMaxima);
    }
    
    respuestaValida = false;
    
    do {
        cout << "¿Desea crear un hijo derecho para " << valor << "? (s/n): ";
        cin >> respuesta;
        
        if (respuesta == 's' || respuesta == 'S' || respuesta == 'n' || respuesta == 'N') {
            respuestaValida = true;
        } else {
            cout << "Respuesta inválida. Por favor ingrese 's' o 'n'." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!respuestaValida);
    
    if (respuesta == 's' || respuesta == 'S') {
        cout << "Creando hijo derecho (nivel " << nivelActual + 1 << "):" << endl;
        crearArbol(raiz->derecho, nivelActual + 1, profundidadMaxima);
    }
}

// Función para calcular la altura real del árbol
template <typename T>
int calcularAltura(Nodo<T>* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    
    int alturaIzquierda = calcularAltura(raiz->izquierdo);
    int alturaDerecha = calcularAltura(raiz->derecho);
    
    return max(alturaIzquierda, alturaDerecha) + 1;
}

// Función para mostrar el árbol en orden de nivel (BFS)
template <typename T>
void mostrarArbolPorNiveles(Nodo<T>* raiz) {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }
    
    queue<Nodo<T>*> cola;
    cola.push(raiz);
    
    int nivelActual = 1;
    int nodosEnNivelActual = 1;
    int nodosEnSiguienteNivel = 0;
    
    cout << "\nArbol por niveles:" << endl;
    cout << "Nivel " << nivelActual << ": ";
    
    while (!cola.empty()) {
        Nodo<T>* nodoActual = cola.front();
        cola.pop();
        nodosEnNivelActual--;
        
        cout << nodoActual->valor << " ";
        
        if (nodoActual->izquierdo != nullptr) {
            cola.push(nodoActual->izquierdo);
            nodosEnSiguienteNivel++;
        }
        
        if (nodoActual->derecho != nullptr) {
            cola.push(nodoActual->derecho);
            nodosEnSiguienteNivel++;
        }
        
        if (nodosEnNivelActual == 0) {
            if (!cola.empty()) {
                nivelActual++;
                nodosEnNivelActual = nodosEnSiguienteNivel;
                nodosEnSiguienteNivel = 0;
                cout << "\nNivel " << nivelActual << ": ";
            }
        }
    }
    cout << endl;
}

// Función para contar el número total de nodos
template <typename T>
int contarNodos(Nodo<T>* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    return 1 + contarNodos(raiz->izquierdo) + contarNodos(raiz->derecho);
}

// Función para mostrar el árbol en recorrido en orden
template <typename T>
void mostrarEnOrden(Nodo<T>* raiz) {
    if (raiz != nullptr) {
        mostrarEnOrden(raiz->izquierdo);
        cout << raiz->valor << " ";
        mostrarEnOrden(raiz->derecho);
    }
}

// Función para verificar y mostrar la información de niveles
template <typename T>
void verificarNiveles(Nodo<T>* raiz, int profundidadMaxima) {
    int alturaReal = calcularAltura(raiz);
    int totalNodos = contarNodos(raiz);
    int nodosMaximosPosibles = (1 << profundidadMaxima) - 1;
    
    cout << "\n           Informacion de niveles" << endl;
    cout << "Profundidad maxima configurada: " << profundidadMaxima << " niveles" << endl;
    cout << "Altura real del arbol construido: " << alturaReal << " niveles" << endl;
    cout << "Total de nodos creados: " << totalNodos << endl;
    cout << "Máximo de nodos posibles para " << profundidadMaxima << " niveles: " << nodosMaximosPosibles << endl;
    
    if (alturaReal < profundidadMaxima) {
        cout << "Nota: El arbol no alcanzo la profundidad maxima configurada." << endl;
    } else if (alturaReal == profundidadMaxima) {
        cout << "Nota: El arbol alcanzo exactamente la profundidad maxima configurada." << endl;
    }
}

// Función para buscar un valor, contar repeticiones y mostrar sus rutas
bool buscarYMostrarRuta(Nodo<int>* nodo, int valor, string ruta, int& contador) {
    if (nodo == nullptr) return false;
    
    bool encontrado = false;
    if (nodo->valor == valor) {
        cout << "Ruta encontrada: " << ruta << endl;
        contador++;
        encontrado = true;
    }
    
    bool izq = buscarYMostrarRuta(nodo->izquierdo, valor, ruta + " -> Izq", contador);
    bool der = buscarYMostrarRuta(nodo->derecho, valor, ruta + " -> Der", contador);
    
    return encontrado || izq || der;
}

// Buscar el menor valor en el árbol
template <typename T>
void buscarMenorValor(Nodo<T>* raiz, T& menor) {
    if (!raiz) return;
    if (raiz->valor < menor) menor = raiz->valor;
    buscarMenorValor(raiz->izquierdo, menor);
    buscarMenorValor(raiz->derecho, menor);
}

// Buscar el mayor valor en el árbol
template <typename T>
void buscarMayorValor(Nodo<T>* raiz, T& mayor) {
    if (!raiz) return;
    if (raiz->valor > mayor) mayor = raiz->valor;
    buscarMayorValor(raiz->izquierdo, mayor);
    buscarMayorValor(raiz->derecho, mayor);
}


// Funcion auxiliar para buscar un valor y guardar la ruta
template <typename T>
bool buscarValorConRuta(Nodo<T>* raiz, T valorBuscado, vector<T>& ruta) {
    if (raiz == nullptr) return false;

    ruta.push_back(raiz->valor);
    
    if (raiz->valor == valorBuscado) return true;

    if (buscarValorConRuta(raiz->izquierdo, valorBuscado, ruta)) return true;
    if (buscarValorConRuta(raiz->derecho, valorBuscado, ruta)) return true;

    ruta.pop_back(); // Si no está en este camino, eliminarlo
    return false;
}

// Funcion para recorrer la ruta interactivamente
template <typename T>
void recorrerRutaInteractiva(const vector<T>& ruta) {
    if (ruta.empty()) {
        cout << "No hay ruta para mostrar." << endl;
        return;
    }

    int posicion = 0;
    char opcion;
    do {
        cout << "\nValor actual: " << ruta[posicion] << endl;
        
        if (posicion < ruta.size() - 1)
            cout << "Siguiente valor en la ruta (S)" << endl;
        if (posicion > 0)
            cout << "Valor anterior en la ruta (A)" << endl;
        cout << "Salir (X)" << endl;
        
        cout << "Opcion: ";
        cin >> opcion;
        
        if (opcion == 'S' || opcion == 's') {
            if (posicion < ruta.size() - 1)
                posicion++;
            else
                cout << "Ya estas en el ultimo valor." << endl;
        } else if (opcion == 'A' || opcion == 'a') {
            if (posicion > 0)
                posicion--;
            else
                cout << "Ya estas en el primer valor." << endl;
        }
        
    } while (opcion != 'X' && opcion != 'x');
}

template <typename T>
void buscarYMostrarTodasLasRutas(Nodo<T>* raiz, T valorBuscado) {
    vector<vector<T>> rutas;  // Todas las rutas encontradas

    function <void(Nodo<T>*, vector<T>)> dfs = [&](Nodo<T>* nodo, vector<T> rutaActual) {
        if (!nodo) return;

        rutaActual.push_back(nodo->valor);

        if (nodo->valor == valorBuscado)
            rutas.push_back(rutaActual);

        dfs(nodo->izquierdo, rutaActual);
        dfs(nodo->derecho, rutaActual);
    };

    dfs(raiz, {});

    if (rutas.empty()) {
        cout << "El valor no fue encontrado en el arbol.\n";
        return;
    }

    cout << "\nSe encontraron " << rutas.size() << " ruta(s) para el valor " << valorBuscado << ":\n";
    for (size_t i = 0; i < rutas.size(); ++i) {
        cout << "Ruta " << (i + 1) << ": ";
        for (size_t j = 0; j < rutas[i].size(); ++j) {
            cout << rutas[i][j];
            if (j < rutas[i].size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    char elegir;
    do {
        cout << "\n¿Deseas recorrer alguna ruta interactivamente? (s/n): ";
        cin >> elegir;
    } while (elegir != 's' && elegir != 'S' && elegir != 'n' && elegir != 'N');

    if (elegir == 's' || elegir == 'S') {
        int indice;
        do {
            cout << "Ingresa el numero de la ruta a recorrer (1 a " << rutas.size() << "): ";
            cin >> indice;
        } while (indice < 1 || indice > (int)rutas.size());

        recorrerRutaInteractiva(rutas[indice - 1]);
    }
}

template <typename T>
void encontrarRutaMenor(Nodo<T>* raiz, vector<T>& ruta) {
    Nodo<T>* actual = raiz;
    while (actual) {
        ruta.push_back(actual->valor);
        if (actual->derecho)
            actual = actual->derecho;
        else
            break;
    }
}

template <typename T>
void encontrarRutaMayor(Nodo<T>* raiz, vector<T>& ruta) {
    Nodo<T>* actual = raiz;
    while (actual) {
        ruta.push_back(actual->valor);
        if (actual->derecho)
            actual = actual->derecho;
        else
            break;
    }
}


// Función para liberar memoria
template <typename T>
void liberarMemoria(Nodo<T>* raiz) {
    if (raiz != nullptr) {
        liberarMemoria(raiz->izquierdo);
        liberarMemoria(raiz->derecho);
        delete raiz;
    }
}

int main() {
    cout << "        ARBOL INTERACTIVO" << endl;
    int profundidadMaxima;

    cout << "Ingrese la profundidad maxima del arbol (numero de niveles): " << endl;
    while (!(cin >> profundidadMaxima) || profundidadMaxima <= 0) {
        cout << "Entrada invalida. Ingrese un numero positivo para la profundidad: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int tipoValor;
    cout << "Elija el tipo de valores para el arbol:" << endl;
    cout << "1. Enteros (int)" << endl;
    cout << "2. Cadenas de texto (string)" << endl;
    cout << "Opcion: ";
    while (!(cin >> tipoValor) || (tipoValor != 1 && tipoValor != 2)) {
        cout << "Opcion invalida. Ingrese 1 o 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (tipoValor == 1) {
        Nodo<int>* raiz = nullptr;
        cout << "\nCreando arbol con valores enteros..." << endl;
        cout << "\nProfundidad maxima configurada: " << profundidadMaxima << " niveles" << endl;
        crearArbol(raiz, 1, profundidadMaxima);

        mostrarArbolPorNiveles(raiz);

        cout << "\nRecorrido inorden: ";
        mostrarEnOrden(raiz);
        cout << endl;

        verificarNiveles(raiz, profundidadMaxima);

        char menuOpcion;
        do {
            cout << "\n      MENU" << endl;
            cout << "1. La cantidad de veces que se repite y su ruta (Tu escribes el valor)." << endl;
            cout << "2. La cantidad de veces que se repite y su ruta (El menor valor)." << endl;
            cout << "3. La cantidad de veces que se repite y su ruta (El mayor valor)." << endl;
            cout << "4. Salir" << endl;
            cout << "Opcion: ";
            cin >> menuOpcion;

            switch (menuOpcion) {
                case '1': {
                    int buscarValor;
                    cout << "Ingresa el valor a buscar: ";
                    cin >> buscarValor;
                    int contador = 0;
                    cout << "\nBuscando valor " << buscarValor << " en el arbol...\n";
                    if (!buscarYMostrarRuta(raiz, buscarValor, "Raiz", contador)) {
                        cout << "El valor no se encontro en el arbol." << endl;
                    } else {
                        cout << "Total de veces encontrado: " << contador << endl;
                    }
                    // Validar la entrada del valor buscado
                    while (cin.fail()) {
                        cout << "Entrada invalida. Intenta de nuevo: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> buscarValor;
                    }
                    buscarYMostrarTodasLasRutas(raiz, buscarValor);
                    break;
                }
case '2': {
    if (!raiz) break;
    int menor = raiz->valor;
    buscarMenorValor(raiz, menor);
    int contador = 0;
    cout << "\nMenor valor encontrado: " << menor << endl;
    buscarYMostrarRuta(raiz, menor, "Raiz", contador);
    cout << "Total de veces que aparece: " << contador << endl;
    vector<int> rutaMenor;
    encontrarRutaMenor(raiz, rutaMenor);
    cout << "\nRuta al valor menor: ";
    for (size_t i = 0; i < rutaMenor.size(); ++i) {
        cout << rutaMenor[i];
        if (i < rutaMenor.size() - 1)
            cout << " ---> ";
    }
    cout << endl;
    recorrerRutaInteractiva(rutaMenor); // Permitir al usuario recorrer la ruta interactivamente
    break;
}
case '3': {
    if (!raiz) break;
    int mayor = raiz->valor;
    buscarMayorValor(raiz, mayor);
    int contador = 0;
    cout << "\nMayor valor encontrado: " << mayor << endl;
    buscarYMostrarRuta(raiz, mayor, "Raiz", contador);
    cout << "Total de veces que aparece: " << contador << endl;
    vector<int> rutaMayor;
    encontrarRutaMayor(raiz, rutaMayor);
    cout << "\nRuta al valor mayor: ";
    for (size_t i = 0; i < rutaMayor.size(); ++i) {
        cout << rutaMayor[i];
        if (i < rutaMayor.size() - 1)
            cout << " ---> ";
    }
    cout << endl;
    recorrerRutaInteractiva(rutaMayor); // Permitir al usuario recorrer la ruta interactivamente
    break;
}
                case '4':
                    cout << "Saliendo del menu..." << endl;
                    break;
                default:
                    cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        } while (menuOpcion != '4');
		
        liberarMemoria(raiz);

    } else if (tipoValor == 2) {
        Nodo<string>* raiz = nullptr;
        cout << "\nCreando arbol con valores de texto..." << endl;
        cout << "\nProfundidad maxima configurada: " << profundidadMaxima << " niveles" << endl;
        crearArbol(raiz, 1, profundidadMaxima);

        mostrarArbolPorNiveles(raiz);

        cout << "\nRecorrido en 'orden': ";
        mostrarEnOrden(raiz);
        cout << endl;

        verificarNiveles(raiz, profundidadMaxima);
        liberarMemoria(raiz);
    }

    cout << "\nPrograma finalizado." << endl;
    return 0;
}