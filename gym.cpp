#include <iostream>
#include <string>
using namespace std;

struct Nodo {
  int codigo;
  string nombre;
  string membresia;
  Nodo *izq;
  Nodo *der;

  Nodo(int c, string n, string m) {
    codigo = c;
    nombre = n;
    membresia = m;
    izq = NULL;
    der = NULL;
  }
};

Nodo *insertar(Nodo *r, int cod, string nom, string mem) {
  if (r == NULL) {
    return new Nodo(cod, nom, mem);
  }
  if (cod < r->codigo) {
    r->izq = insertar(r->izq, cod, nom, mem);
  } else if (cod > r->codigo) {
    r->der = insertar(r->der, cod, nom, mem);
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
  if (cod < r->codigo)
    return buscar(r->izq, cod);

  return buscar(r->der, cod);
}

void mostrarInorden(Nodo *r) {
  if (r != NULL) {
    mostrarInorden(r->izq);
    cout << "Codigo: " << r->codigo
         << " | Nombre: " << r->nombre
         << " | Membresia: " << r->membresia << endl;
    mostrarInorden(r->der);
  }
}

void mostrarArbol(Nodo *r, int nivel) {
  if (r != NULL) {
    mostrarArbol(r->der, nivel + 1);
    for (int i = 0; i < nivel; i++)
      cout << "    ";
    cout << r->codigo << endl;
    mostrarArbol(r->izq, nivel + 1);
  }
}

void limpiarBuffer() {
  cin.clear();
  cin.ignore(10000, '\n');
}

int main() {
  Nodo *raiz = NULL;
  int op;

  do {
    cout << "\nMENU GIMNASIO\n";
    cout << "1. Registrar socio\n";
    cout << "2. Mostrar socios\n";
    cout << "3. Buscar socio\n";
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
      string nom, mem;

      cout << "Codigo del socio: ";
      cin >> cod;

      if (cin.fail()) {
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

      cout << "Tipo de membresia (Mensual / Anual / VIP): ";
      getline(cin, mem);

      raiz = insertar(raiz, cod, nom, mem);
      cout << "\nSocio registrado\n";
    }

    else if (op == 2) {
      if (raiz == NULL)
        cout << "\nNo hay socios registrados\n";
      else
        mostrarInorden(raiz);
    }

    else if (op == 3) {
      int cod;
      cout << "Codigo del socio: ";
      cin >> cod;

      Nodo *res = buscar(raiz, cod);

      if (res != NULL) {
        cout << "Codigo: " << res->codigo << endl;
        cout << "Nombre: " << res->nombre << endl;
        cout << "Membresia: " << res->membresia << endl;
      } else {
        cout << "\nSocio no encontrado\n";
      }
    }

    else if (op == 4) {
      if (raiz == NULL)
        cout << "\nNo hay socios\n";
      else
        mostrarArbol(raiz, 0);
    }

  } while (op != 5);

  return 0;
}
