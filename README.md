# Metodos de ordenamiento en C

Biblioteca en C con implementaciones de 13 algoritmos para ordenar arreglos de
enteros en orden ascendente. Incluye un programa interactivo para probar cada
metodo.

## Metodos incluidos

- Burbuja (`burbuja`)
- Seleccion (`seleccion`)
- Insercion (`insercion`)
- QuickSort (`quicksort`)
- MergeSort (`mergesort`)
- HeapSort (`heapSort`)
- ShellSort (`shellSort`)
- RadixSort (`radixSort`)
- CountingSort (`countingSort`)
- CocktailSort (`cocktailSort`)
- CombSort (`combSort`)
- GnomeSort (`gnomeSort`)
- BucketSort (`bucketSort`)

## Archivos

- `metodos_Ordenamiento.h`: declaraciones de la biblioteca.
- `metodos_Ordenamiento.c`: implementaciones y funciones auxiliares.
- `main.c`: menu interactivo para generar y ordenar arreglos aleatorios.
- `Makefile`: compilacion del programa de prueba.

## Requisitos

Se necesita GCC (u otro compilador compatible con C11) y GNU Make.

## Compilar y ejecutar

Desde la raiz del repositorio:

```sh
make
./ordenamiento
```

El menu permite elegir el algoritmo y la cantidad de elementos. El programa
muestra el arreglo original, el resultado, si quedo ordenado correctamente y el
tiempo medido. Para eliminar el ejecutable:

```sh
make clean
```

## Usar la biblioteca

Incluye el encabezado y compila tu programa junto con
`metodos_Ordenamiento.c`:

```c
#include <stdio.h>
#include "metodos_Ordenamiento.h"

int main(void)
{
    int datos[] = {8, 3, 7, 1, 5};
    int cantidad = (int)(sizeof datos / sizeof datos[0]);

    quicksort(datos, 0, cantidad - 1);
    imprimirArreglo(datos, cantidad);
    return arregloOrdenado(datos, cantidad) ? 0 : 1;
}
```

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic ejemplo.c metodos_Ordenamiento.c -o ejemplo
```

Los algoritmos ordenan el arreglo recibido directamente. En `quicksort`, los
limites `bajo` y `alto` son indices inclusivos. `burbuja` y `seleccion`
aceptan un tercer argumento opcional para devolver el numero de pasadas.
`Data` y `get_array_data` reservan un arreglo aleatorio que el llamador debe
liberar con `free`.

CountingSort usa QuickSort como alternativa cuando el rango de valores es
demasiado grande para contar eficientemente.
