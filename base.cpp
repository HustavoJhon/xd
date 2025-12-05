#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int codigo;
    string nombre;
    int edad;
    Nodo *izq;
    Nodo *der;

    Nodo(int c, string n, int e) {
        codigo = c;
        nombre = n;
        edad = e;
        izq = der = NULL;
    }
};

// Insertar en árbol binario
Nodo* insertar(Nodo* r, int cod, string nom, int edad) {
    if (r == NULL)
        return new Nodo(cod, nom, edad);

    if (cod < r->codigo)
        r->izq = insertar(r->izq, cod, nom, edad);
    else if (cod > r->codigo)
        r->der = insertar(r->der, cod, nom, edad);
    else
        cout << "El codigo ya existe\n";

    return r;
}

// Buscar
Nodo* buscar(Nodo* r, int cod) {
    if (r == NULL)
        return NULL;
    if (cod == r->codigo)
        return r;
    if (cod < r->codigo)
        return buscar(r->izq, cod);
    return buscar(r->der, cod);
}

// Mostrar Inorden
void mostrar(Nodo* r) {
    if (r != NULL) {
        mostrar(r->izq);
        cout << "Codigo: " << r->codigo
             << " | Nombre: " << r->nombre
             << " | Edad: " << r->edad << endl;
        mostrar(r->der);
    }
}

int main() {
    Nodo* raiz = NULL;
    int op;

    do {
        cout << "\nMENU\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Mostrar estudiantes\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            int cod, edad;
            string nom;
            cout << "Codigo: ";
            cin >> cod;
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nom);
            cout << "Edad: ";
            cin >> edad;

            raiz = insertar(raiz, cod, nom, edad);

        } else if (op == 2) {
            if (raiz == NULL)
                cout << "No hay estudiantes\n";
            else
                mostrar(raiz);

        } else if (op == 3) {
            int cod;
            cout << "Codigo a buscar: ";
            cin >> cod;
            Nodo* res = buscar(raiz, cod);

            if (res != NULL) {
                cout << "Encontrado:\n";
                cout << "Nombre: " << res->nombre << endl;
                cout << "Edad: " << res->edad << endl;
            } else {
                cout << "No existe.\n";
            }
        }

    } while (op != 4);

    return 0;
}
