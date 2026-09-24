# Estructuras de Datos y Algoritmos II

Prácticas en C de la asignatura Estructuras de Datos y Algoritmos II. Cada carpeta corresponde a un tema y tiene su propio `makefile`. Parte del código (cabeceras, programas de prueba y algunas funciones auxiliares) venía dado por el profesorado; el resto son las funciones que había que implementar en cada sesión.

## Temas

### 1. Árboles binarios (`ArbolesBinarios/`)

Árbol binario genérico con nodos de tipo `char`.

- Recorridos en preorden, inorden, postorden y amplitud (este último usa una cola).
- Funciones recursivas: altura, número de nodos, nodos hoja, nodos internos, nodos con un único hijo, máximo y mínimo, sustituir un valor, árbol especular, y comprobar si dos árboles son similares o equivalentes.
- Construcción de un árbol de expresión a partir de una expresión en notación postfija (usando una pila) y evaluación de ese árbol.

```bash
make ejercicio1   # recorridos
make ejercicio3   # árbol de expresión
```

### 2. Montículo binario (`MonticuloBinario/monticuloBinario/`)

Montículo de mínimos sobre un vector de 100 posiciones: insertar, eliminar el mínimo, incrementar y decrementar una clave, comprobar si un vector es un montículo, crear un montículo a partir de un vector y ordenar con heapsort. Todo se apoya en el filtrado ascendente y el filtrado descendente.

```bash
make prueba1
make prueba2
```

El fuente está guardado como `montiulo.c`, pero el `makefile` espera `monticulo.c`, así que hay que renombrarlo antes de compilar.

### 3. Conjuntos disjuntos (`Conjuntos Disjuntos/`)

Tres representaciones de una partición de 16 elementos con las operaciones `crea`, `buscar` y `unir`:

- `rMatrices/`: vector de representantes.
- `rListas/`: listas enlazadas.
- `rArboles/`: bosque de árboles, con unión sin criterio, unión por altura y unión por tamaño.

```bash
make cMatrices
make cListas
make cArboles
```

### 4. Grafos (`Grafos/`)

Grafos representados con listas de adyacencia (máximo 20 vértices).

- Ejercicio 1: recorridos en profundidad y en amplitud.
- Ejercicio 2: ordenación topológica, en dos versiones.
- Ejercicio 3: caminos mínimos en grafos no ponderados y algoritmo de Dijkstra en grafos ponderados, con la reconstrucción del camino y su coste.
- Ejercicio 4: árbol de expansión de coste mínimo con Prim y Kruskal.

Los ficheros `resultadoEj*.txt` guardan la salida de cada ejercicio.

```bash
make ejercicio1
make ejercicio2
```

Para usar el montículo en Dijkstra o Prim hay que añadir `monticulo.o` al enlazado y renombrar su `tipoElemento` a `tipoElementoM`, porque choca con el de la cola. En el `makefile` están indicados los cambios.

### 5. Árboles binarios de búsqueda (`ArbolesBinariosBusqueda/`)

Inserción, búsqueda y eliminación en un ABB. El ejercicio 1 guarda claves enteras y el ejercicio 3 añade a cada nodo una cadena de hasta 20 caracteres. Se elige una u otra versión compilando con `-DEJERCICIO1` o `-DEJERCICIO3`.

```bash
make pruebaEj1
make pruebaEj3
```

### 6. Memoria secundaria (`MemoriaSecundaria/`)

Ficheros de alumnos (DNI, nombre, apellidos y provincia) guardados en disco.

- `Secuencial/`: lectura, búsqueda e inserción en un fichero secuencial.
- `Dispersion/`: fichero organizado por dispersión con cubos de 5 registros, 20 cubos en el área primaria y 4 de desborde.

### 7. Trabajo de memoria secundaria (`TrabajoMemoriaSecundaria/`)

Trabajo de la asignatura (el enunciado está en `MS2026.pdf`). Hace una librería de dispersión genérica que sirve tanto para alumnos como para asignaturas; el tipo de registro se elige al compilar con `-DALUM` o `-DASIG`.

- Crear el fichero hash a partir de un fichero de datos, con área de desborde y control de densidad.
- Buscar y modificar registros (provincia de un alumno, créditos de una asignatura).
- Acceso por número de expediente mediante un índice con búsqueda binaria (organización secuencial indexada).

La estructura es `src/` para los fuentes, `include/` para las cabeceras, `lib/` para los objetos, `datos/` para los ficheros de entrada y `resultados/` para las salidas.

```bash
cd TrabajoMemoriaSecundaria/bin
make genAlumnosH
make genAsignaturasH
make modAlumnoH
make modAsigH
```

## Compilación

Hace falta `gcc` y `make`. Cada tema se compila desde su carpeta con el objetivo que corresponda. Algunos `.o` y ejecutables compilados se subieron al repositorio; si dan problemas, basta con borrarlos (`make limpiar` o `make clean`) y volver a compilar.

## Notas para el examen

Apuntes que fui tomando sobre las preguntas que suelen caer:

- Grafos: qué hay que modificar en el montículo para poder usarlo en Prim.
- Árboles binarios de búsqueda:
  - En las funciones del ABB la raíz se pasa como puntero por referencia, porque hay que modificar los campos `izq` y `der`.
  - Es habitual que pregunten el pseudocódigo de eliminación (diapositiva 30 de los apuntes). Cuando el nodo tiene dos hijos se sustituye por el nodo más a la derecha del subárbol izquierdo o por el más a la izquierda del subárbol derecho.
  - Hay que tener en cuenta el caso en que el nodo a eliminar solo tiene hijo izquierdo.
  - En el ejercicio 3 cambian las funciones de insertar y eliminar respecto al ejercicio 1. Si el puenteo está bien hecho, el resultado tiene que coincidir con el del ejercicio 1.
  - Revisar el enunciado para responder la pregunta del ejercicio 2.
