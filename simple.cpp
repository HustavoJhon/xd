#include <iostream>
#include <string>
using namespace std;

struct Nodo {
  int codigo;
  string nombre;
  double precio;
  Nodo *izq;
  Nodo *der;

  Nodo(int c, string n, double p) {
    codigo = c;
    nombre = n;
    precio = p;
    izq = NULL;
    der = NULL;
  }
};

Nodo *insertar(Nodo *r, int cod, string nom, double pre) {
  if (r == NULL) {
    return new Nodo(cod, nom, pre);
  }
  if (cod < r->codigo) {
    r->izq = insertar(r->izq, cod, nom, pre);
  } else if (cod > r->codigo) {
    r->der = insertar(r->der, cod, nom, pre);
  } else {
    cout << "\nEl codigo ya existe\n";
  }
  return r;
}

Nodo *buscar(Nodo *r, int cod) {
  if (r == NULL)
    return NULL;
  if (cod == r->codigo)
    return r;
  if (cod < r->codigo) {
    return buscar(r->izq, cod);
  }
  return buscar(r->der, cod);
}

void mostrarInorden(Nodo *r) {
  if (r != NULL) {
    mostrarInorden(r->izq);
    cout << "Codigo: " << r->codigo << " | Nombre: " << r->nombre
         << " | Precio: S/" << r->precio << endl;
    mostrarInorden(r->der);
  }
}

void mostrarArbol(Nodo *r, int nivel) {
  if (r != NULL) {
    mostrarArbol(r->der, nivel + 1);
    for (int i = 0; i < nivel; i++) {
      cout << "    ";
    }
    cout << r->codigo << endl;
    mostrarArbol(r->izq, nivel + 1);
  }
}

bool validarNumero(int num) { return num > 0; }

bool validarPrecio(double pre) { return pre >= 0; }

void limpiarBuffer() {
  cin.clear();
  cin.ignore(10000, '\n');
}

int main() {
  Nodo *raiz = NULL;
  int op;

  do {
    cout << "\nMENU\n";
    cout << "1. Agregar producto\n";
    cout << "2. Mostrar productos\n";
    cout << "3. Buscar producto\n";
    cout << "4. Ver arbol\n";
    cout << "5. Salir\n";
    cout << "Opcion: ";
    cin >> op;

    if (cin.fail()) {
      limpiarBuffer();
      cout << "\nIngrese un numero valido\n";
      continue;
    }

    if (op == 1) {
      int cod;
      string nom;
      double pre;

      cout << "Codigo: ";
      cin >> cod;

      if (cin.fail() || !validarNumero(cod)) {
        limpiarBuffer();
        cout << "\nCodigo invalido\n";
        continue;
      }

      if (buscar(raiz, cod) != NULL) {
        cout << "\nEl codigo ya existe\n";
        continue;
      }

      cin.ignore();
      cout << "Nombre: ";
      getline(cin, nom);

      if (nom.empty()) {
        cout << "\nEl nombre no puede estar vacio\n";
        continue;
      }

      cout << "Precio: ";
      cin >> pre;

      if (cin.fail() || !validarPrecio(pre)) {
        limpiarBuffer();
        cout << "\nPrecio invalido\n";
        continue;
      }

      raiz = insertar(raiz, cod, nom, pre);
      cout << "\nProducto agregado\n";
    } else if (op == 2) {
      if (raiz == NULL) {
        cout << "\nNo hay productos\n";
      } else {
        mostrarInorden(raiz);
      }
    } else if (op == 3) {
      if (raiz == NULL) {
        cout << "\nNo hay productos\n";
        continue;
      }

      int cod;
      cout << "Codigo: ";
      cin >> cod;

      if (cin.fail()) {
        limpiarBuffer();
        cout << "\nCodigo invalido\n";
        continue;
      }

      Nodo *res = buscar(raiz, cod);

      if (res != NULL) {
        cout << "Codigo: " << res->codigo << endl;
        cout << "Nombre: " << res->nombre << endl;
        cout << "Precio: S/" << res->precio << endl;
      } else {
        cout << "\nProducto no encontrado\n";
      }
    } else if (op == 4) {
      if (raiz == NULL) {
        cout << "\nNo hay productos\n";
      } else {
        mostrarArbol(raiz, 0);
      }
    } else if (op == 5) {
      cout << "\nSaliendo...\n";
    } else {
      cout << "\nOpcion invalida\n";
    }

  } while (op != 5);

  return 0;
}
