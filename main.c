#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "metodos_Ordenamiento.h"

static void mostrar_menu(void)
{
    printf("\nMETODOS DE ORDENAMIENTO\n");
    printf(" 1. Burbuja\n");
    printf(" 2. Seleccion\n");
    printf(" 3. Insercion\n");
    printf(" 4. QuickSort\n");
    printf(" 5. MergeSort\n");
    printf(" 6. HeapSort\n");
    printf(" 7. ShellSort\n");
    printf(" 8. RadixSort\n");
    printf(" 9. CountingSort\n");
    printf("10. CocktailSort\n");
    printf("11. CombSort\n");
    printf("12. GnomeSort\n");
    printf("13. BucketSort\n");
    printf(" 0. Salir\n");
}

int main(void)
{
    int opcion, tamanio;

    do {
        mostrar_menu();
        printf("Opcion: ");
        if (scanf("%d", &opcion) != 1) return 1;
        if (opcion == 0) break;
        if (opcion < 1 || opcion > 13) {
            printf("Opcion invalida.\n");
            continue;
        }

        printf("Cantidad de elementos: ");
        if (scanf("%d", &tamanio) != 1 || tamanio < 1) {
            printf("Tamanio invalido.\n");
            continue;
        }

        int *datos = Data(tamanio);
        if (datos == NULL) {
            fprintf(stderr, "No se pudo crear el arreglo.\n");
            return 1;
        }

        printf("Original: ");
        imprimirArreglo(datos, tamanio);
        clock_t inicio = clock();
        int pasadas = 0;

        switch (opcion) {
            case 1: burbuja(datos, tamanio, &pasadas); break;
            case 2: seleccion(datos, tamanio, &pasadas); break;
            case 3: insercion(datos, tamanio); break;
            case 4: quicksort(datos, 0, tamanio - 1); break;
            case 5: mergesort(datos, tamanio); break;
            case 6: heapSort(datos, tamanio); break;
            case 7: shellSort(datos, tamanio); break;
            case 8: radixSort(datos, tamanio); break;
            case 9: countingSort(datos, tamanio); break;
            case 10: cocktailSort(datos, tamanio); break;
            case 11: combSort(datos, tamanio); break;
            case 12: gnomeSort(datos, tamanio); break;
            case 13: bucketSort(datos, tamanio); break;
        }

        clock_t fin = clock();
        printf("Ordenado: ");
        imprimirArreglo(datos, tamanio);
        printf("Estado: %s\n", arregloOrdenado(datos, tamanio) ? "correcto" : "incorrecto");
        printf("Tiempo: %.6f segundos\n", (double)(fin - inicio) / CLOCKS_PER_SEC);
        free(datos);
    } while (1);

    return 0;
}
