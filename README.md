# Nodo *insertar(Nodo *r, int cod, string nom, double pre)
```cpp
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
```


Explicación técnica (parrafo único y completo):  
Esta función implementa la **inserción recursiva** en un Árbol Binario de Búsqueda (BST). **Necesita**: un puntero `r` al nodo raíz del (sub)árbol donde se va a insertar; un `cod` entero que actúa como clave de ordenación; `nom` y `pre` con los datos que formarán el nuevo `Nodo`. **Cómo funciona (paso a paso)**: primero comprueba la condición base `if (r == NULL)`; eso significa que hemos llegado a la posición correcta en el árbol donde debe ir el nuevo elemento: se crea dinámicamente un `Nodo` con `new Nodo(cod, nom, pre)` y se devuelve ese puntero (esto enlaza el nuevo nodo a su padre en la recursión). Si `r` no es nulo, compara la clave `cod` con `r->codigo`: si `cod < r->codigo` baja recursivamente por la rama izquierda y asigna el resultado a `r->izq` (esto asegura que, si la subllamada crea un nodo nuevo o reestructura algo, el puntero del padre se actualiza correctamente); si `cod > r->codigo` hace lo mismo por la rama derecha. Si `cod == r->codigo` entra en la rama `else` y **no inserta**, solo imprime `El codigo ya existe`, por lo que la función evita duplicados (pero no devuelve un error explícito ni lanza excepción). Al final devuelve siempre `r` — esto permite que la llamada inicial reciba (o conserve) la raíz del árbol actualizado. **Qué muestra / efecto visible**: puede imprimir el mensaje de duplicado y modifica la estructura del árbol añadiendo un nuevo nodo en la hoja correspondiente. **Complejidad**: tiempo promedio O(h) donde h es la altura del árbol; en el peor caso (árbol degenerado, lista) O(n). **Consideraciones de memoria y seguridad**: usa `new` para asignación dinámica; no hay `delete` en este código, por lo que si eliminas nodos no liberados habrá fugas; además `new` puede lanzar `std::bad_alloc` en condiciones extremas. **Recomendaciones**: validar la clave antes de llamar (si quieres), manejar el caso de duplicados devolviendo un flag o lanzando excepción si el flujo lo requiere, y considerar un árbol auto-balanceado (AVL/Red-Black) si necesitas evitar el caso O(n).

---

# Nodo *buscar(Nodo *r, int cod)

```cpp
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
```

Explicación técnica (parrafo único y completo):  
`buscar` es una función recursiva que localiza un nodo por su clave `cod` siguiendo la **propiedad de orden** del BST. **Necesita** el puntero `r` al nodo raíz del (sub)árbol donde comenzar la búsqueda y la clave `cod`. **Cómo funciona**: si `r` es nulo, devuelve `NULL` (caso base: no existe más recorrido, elemento no encontrado). Si `cod == r->codigo` devuelve el propio puntero `r` (nodo encontrado). Si `cod < r->codigo` explora la subrama izquierda llamando recursivamente `buscar(r->izq, cod)`. Si no se cumple ninguna de las anteriores, por eliminación lógica `cod > r->codigo` y explora la rama derecha con `buscar(r->der, cod)`. **Qué devuelve**: un puntero al `Nodo` encontrado o `NULL` si no existe. **Efecto visible**: no modifica la estructura del árbol, solo lee; normalmente se usa después para mostrar datos o validar existencia. **Complejidad**: tiempo O(h) promedio, O(n) en peor caso (árbol degenerado). **Consideraciones**: la función devuelve un puntero crudo al nodo dentro del árbol (aliasing); si luego se elimina o modifica ese nodo, el puntero puede volverse inválido — tener cuidado con la gestión de memoria concurrente. Se podría implementar también de forma iterativa para evitar profundidad de recursión en árboles muy altos.

---

# void mostrarInorden(Nodo *r)

```cpp
void mostrarInorden(Nodo *r) {
  if (r != NULL) {
    mostrarInorden(r->izq);
    cout << "Codigo: " << r->codigo << " | Nombre: " << r->nombre
         << " | Precio: S/" << r->precio << endl;
    mostrarInorden(r->der);
  }
}
```

Explicación técnica (parrafo único y completo):  
`mostrarInorden` realiza un **recorrido en-orden** (left-root-right) del árbol, lo que garantiza que los nodos se procesen **ordenados por la clave** (`codigo`) si el árbol cumple la propiedad BST. **Necesita**: el puntero `r` al nodo raíz del (sub)árbol a imprimir. **Cómo funciona**: es recursiva — primero llama a sí misma con `r->izq` (procesar subárbol izquierdo completamente), luego ejecuta la línea que imprime los campos del nodo actual (`codigo`, `nombre`, `precio`) en la salida estándar, y por último recorre `r->der`. El `if (r != NULL)` actúa como caso base, evitando llamadas sobre punteros nulos. **Qué muestra**: en la consola lista cada nodo en orden ascendente por código, una línea por nodo con formato legible. **Complejidad**: O(n) tiempo para visitar n nodos; O(h) espacio en la pila por la recursión (altura h). **Calidad/propiedades**: adecuado para obtener un "catálogo" ordenado; si el árbol no está balanceado la recursión puede consumir mucha pila; si se desea salida paginada o filtrada habría que añadir control adicional. **Recomendaciones**: si trabajas con grandes volúmenes, considera implementación iterativa con stack explícito o recorrido que genere resultados paginados; para internacionalización o formatos monetarios más precisos, usa formatos/locale apropiados en lugar de concatenar `S/` directo.

---

# void mostrarArbol(Nodo *r, int nivel)

```cpp
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
```

Explicación técnica (parrafo único y completo):  
`mostrarArbol` es una rutina visual que imprime la **estructura** del árbol en consola en forma vertical, con indentación que refleja la profundidad de cada nodo. **Necesita**: `r` como puntero al nodo raíz del (sub)árbol y `nivel` (entero) que indica la profundidad actual — normalmente se llama con `nivel = 0` desde la raíz. **Cómo funciona (lógica de orden)**: recorre primero la rama derecha (`mostrarArbol(r->der, nivel + 1)`), luego imprime `nivel` veces un bloque de espacios `" "` para indentar, después imprime `r->codigo` y termina recorriendo la rama izquierda (`mostrarArbol(r->izq, nivel + 1)`). Ese orden (derecha → raíz → izquierda) hace que **los nodos con claves mayores** aparezcan arriba en la salida y los menores abajo, produciendo una vista tipo "rotada 90° a la izquierda" del árbol: la raíz está más a la izquierda, la derecha del árbol aparece por encima y la izquierda por debajo. **Qué muestra**: únicamente el campo `codigo` por línea (podrías añadir nombre/precio si quieres), con niveles de sangría que visualizan la jerarquía y la relación padre-hijo. **Complejidad**: O(n) tiempo para imprimir todos los nodos, y espacio de pila O(h) por recursión. **Propiedades y utilidad**: es útil para depuración y para que una persona comprenda la forma global del árbol (si está balanceado o es degenerado). **Limitaciones**: la salida en consola es rudimentaria — no es un gráfico real; la anchura de indentación fija puede provocar líneas muy largas en árboles profundos; además, solo muestra el `codigo` (podrías enriquecer la salida). **Recomendación**: si necesitas una vista más completa, imprime también `nombre` y `precio` junto al `codigo` o exporta la estructura a un formato que pueda graficarse (Graphviz dot). Para árboles muy profundos considera una versión iterativa o limitar la profundidad impresa.

---

# Ejemplo rápido (traza) — para entender mejor cómo interactúan

Imagina insertas los códigos en este orden: `50, 30, 70, 20, 40`.

- `insertar(50)` crea raíz 50;
    
- `insertar(30)` se coloca a la izquierda de 50;
    
- `insertar(70)` a la derecha de 50;
    
- `insertar(20)` a la izquierda de 30;
    
- `insertar(40)` a la derecha de 30.
    
- `mostrarInorden` imprimirá: `20, 30, 40, 50, 70` (orden ascendente por `codigo`).
    
- `buscar(40)` recorre 50 → izquierda(30) → derecha(40) → devuelve el nodo 40.
    
- `mostrarArbol(raiz,0)` mostrará una salida tipo:
    

      ```cpp
        70
    50
        40
    30
        20

      ```

(la indentación y el orden reflejan derecha-arriba, izquierda-abajo).

---

# Riesgos, mejoras y buenas prácticas (resumen)

- **Fugas de memoria**: cada `new` debe emparejarse con un `delete` cuando elimines nodos; considera un destructor recursivo o gestionar con smart pointers (`unique_ptr`) para seguridad.
    
- **Recursión profunda**: en árboles degenerados la profundidad puede ser O(n) y agotar la pila; podrías cambiar a versiones iterativas o usar árboles balanceados.
    
- **Duplicados**: ahora sólo se imprime un mensaje; si necesitas control, devuelve un booleano o lanza una excepción.
    
- **Robustez**: valida entradas antes de insertar (rangos, tipos).
    
- **Escalabilidad**: si vas a usar muchos nodos, piensa en árboles balanceados (AVL, Red-Black) o estructuras persistentes.
    

---