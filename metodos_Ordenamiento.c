#include "metodos_Ordenamiento.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int buscar_menor(const int arr[], int n, int inicio)
{
    int pos_menor = inicio;

    for (int i = inicio + 1; i < n; i++) {
        if (arr[i] < arr[pos_menor]) {
            pos_menor = i;
        }
    }

    return pos_menor;
}

static void intercambiar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int particionar(int arr[], int bajo, int alto)
{
    int pivote = arr[alto];
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (arr[j] <= pivote) {
            i++;
            intercambiar(&arr[i], &arr[j]);
        }
    }

    intercambiar(&arr[i + 1], &arr[alto]);
    return i + 1;
}

int *Data(int size)
{
    if (size <= 0) {
        return NULL;
    }

    if ((size_t)size > (size_t)-1 / sizeof(int)) {
        return NULL;
    }

    int *arr = malloc((size_t)size * sizeof(*arr));
    if (arr == NULL) {
        return NULL;
    }

    static int semilla_inicializada = 0;
    if (!semilla_inicializada) {
        srand((unsigned int)time(NULL));
        semilla_inicializada = 1;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000 + 1;
    }

    return arr;
}

int *get_array_data(int size)
{
    return Data(size);
}

int *burbuja(int arr[], int n, int *pasadas)
{
    int total_pasadas = 0;

    for (int i = 0; arr != NULL && n > 1 && i < n - 1; i++) {
        int hubo_intercambio = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                intercambiar(&arr[j], &arr[j + 1]);
                hubo_intercambio = 1;
            }
        }

        total_pasadas++;
        if (!hubo_intercambio) {
            break;
        }
    }

    if (pasadas != NULL) {
        *pasadas = total_pasadas;
    }

    return arr;
}

int *seleccion(int arr[], int n, int *pasadas)
{
    int total_pasadas = 0;

    for (int i = 0; arr != NULL && n > 1 && i < n - 1; i++) {
        int pos_menor = buscar_menor(arr, n, i);
        intercambiar(&arr[i], &arr[pos_menor]);
        total_pasadas++;
    }

    if (pasadas != NULL) {
        *pasadas = total_pasadas;
    }

    return arr;
}

int *insercion(int arr[], int n)
{
    if (arr == NULL || n < 2) {
        return arr;
    }

    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = clave;
    }

    return arr;
}

void quicksort(int arr[], int bajo, int alto)
{
    if (arr == NULL || bajo >= alto) {
        return;
    }

    int pivote = particionar(arr, bajo, alto);
    quicksort(arr, bajo, pivote - 1);
    quicksort(arr, pivote + 1, alto);
}

static void mezclar(int arr[], int inicio, int medio, int fin)
{
    int longitud_izq = medio - inicio + 1;
    int longitud_der = fin - medio;
    int *izquierda = malloc((size_t)longitud_izq * sizeof(*izquierda));
    int *derecha = malloc((size_t)longitud_der * sizeof(*derecha));

    if (izquierda == NULL || derecha == NULL) {
        free(izquierda);
        free(derecha);
        return;
    }

    memcpy(izquierda, arr + inicio, (size_t)longitud_izq * sizeof(*izquierda));
    memcpy(derecha, arr + medio + 1, (size_t)longitud_der * sizeof(*derecha));

    int i = 0;
    int j = 0;
    int k = inicio;
    while (i < longitud_izq && j < longitud_der) {
        if (izquierda[i] <= derecha[j]) {
            arr[k++] = izquierda[i++];
        } else {
            arr[k++] = derecha[j++];
        }
    }
    while (i < longitud_izq) arr[k++] = izquierda[i++];
    while (j < longitud_der) arr[k++] = derecha[j++];

    free(izquierda);
    free(derecha);
}

static void mergesort_recursivo(int arr[], int inicio, int fin)
{
    if (inicio >= fin) return;
    int medio = inicio + (fin - inicio) / 2;
    mergesort_recursivo(arr, inicio, medio);
    mergesort_recursivo(arr, medio + 1, fin);
    mezclar(arr, inicio, medio, fin);
}

int *mergesort(int arr[], int n)
{
    if (arr != NULL && n > 1) {
        mergesort_recursivo(arr, 0, n - 1);
    }
    return arr;
}

static void heapificar(int arr[], int n, int raiz)
{
    int mayor = raiz;
    int izquierdo = 2 * raiz + 1;
    int derecho = 2 * raiz + 2;

    if (izquierdo < n && arr[izquierdo] > arr[mayor]) mayor = izquierdo;
    if (derecho < n && arr[derecho] > arr[mayor]) mayor = derecho;

    if (mayor != raiz) {
        intercambiar(&arr[raiz], &arr[mayor]);
        heapificar(arr, n, mayor);
    }
}

void heapSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;
    for (int i = n / 2 - 1; i >= 0; i--) heapificar(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        intercambiar(&arr[0], &arr[i]);
        heapificar(arr, i, 0);
    }
}

void shellSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;
    for (int espacio = n / 2; espacio > 0; espacio /= 2) {
        for (int i = espacio; i < n; i++) {
            int temporal = arr[i];
            int j = i;
            while (j >= espacio && arr[j - espacio] > temporal) {
                arr[j] = arr[j - espacio];
                j -= espacio;
            }
            arr[j] = temporal;
        }
    }
}

void countingSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;

    int minimo = arr[0], maximo = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minimo) minimo = arr[i];
        if (arr[i] > maximo) maximo = arr[i];
    }
    if ((long long)maximo - minimo > 100000000LL) {
        quicksort(arr, 0, n - 1);
        return;
    }

    int rango = maximo - minimo + 1;
    int *conteo = calloc((size_t)rango, sizeof(*conteo));
    int *resultado = malloc((size_t)n * sizeof(*resultado));
    if (conteo == NULL || resultado == NULL) {
        free(conteo);
        free(resultado);
        return;
    }

    for (int i = 0; i < n; i++) conteo[arr[i] - minimo]++;
    for (int i = 1; i < rango; i++) conteo[i] += conteo[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        resultado[conteo[arr[i] - minimo] - 1] = arr[i];
        conteo[arr[i] - minimo]--;
    }
    memcpy(arr, resultado, (size_t)n * sizeof(*arr));
    free(conteo);
    free(resultado);
}

void radixSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;

    uint32_t *transformado = malloc((size_t)n * sizeof(*transformado));
    int *resultado = malloc((size_t)n * sizeof(*resultado));
    if (transformado == NULL || resultado == NULL) {
        free(transformado);
        free(resultado);
        return;
    }

    for (int i = 0; i < n; i++) {
        transformado[i] = (uint32_t)arr[i] ^ UINT32_C(0x80000000);
    }

    uint32_t salida[n < 1 ? 1 : n];
    for (unsigned byte = 0; byte < 4; byte++) {
        unsigned desplazamiento = byte * 8;
        int conteo[256] = {0};
        for (int i = 0; i < n; i++) {
            conteo[(transformado[i] >> desplazamiento) & 255]++;
        }
        int acumulado = 0;
        for (int i = 0; i < 256; i++) {
            int cantidad = conteo[i];
            conteo[i] = acumulado;
            acumulado += cantidad;
        }
        for (int i = 0; i < n; i++) {
            unsigned digito = (transformado[i] >> desplazamiento) & 255;
            salida[conteo[digito]++] = transformado[i];
        }
        memcpy(transformado, salida, (size_t)n * sizeof(*transformado));
    }

    for (int i = 0; i < n; i++) {
        resultado[i] = (int)((uint32_t)transformado[i] ^ UINT32_C(0x80000000));
    }
    memcpy(arr, resultado, (size_t)n * sizeof(*arr));
    free(resultado);
    free(transformado);
}

void cocktailSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;
    int inicio = 0, fin = n - 1;

    while (inicio <= fin) {
        int intercambio = 0;
        for (int i = inicio; i < fin; i++) {
            if (arr[i] > arr[i + 1]) {
                intercambiar(&arr[i], &arr[i + 1]);
                intercambio = 1;
            }
        }
        if (!intercambio) break;
        fin--;

        intercambio = 0;
        for (int i = fin; i > inicio; i--) {
            if (arr[i] < arr[i - 1]) {
                intercambiar(&arr[i], &arr[i - 1]);
                intercambio = 1;
            }
        }
        if (!intercambio) break;
        inicio++;
    }
}

void combSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;
    int espacio = n;
    int ordenado = 0;

    while (espacio > 1 || !ordenado) {
        espacio = (espacio * 10) / 13;
        if (espacio < 1) espacio = 1;
        ordenado = 1;
        for (int i = 0; i + espacio < n; i++) {
            if (arr[i] > arr[i + espacio]) {
                intercambiar(&arr[i], &arr[i + espacio]);
                ordenado = 0;
            }
        }
    }
}

void gnomeSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i - 1] <= arr[i]) {
            i++;
        } else {
            intercambiar(&arr[i], &arr[i - 1]);
            i--;
        }
    }
}

void bucketSort(int arr[], int n)
{
    if (arr == NULL || n < 2) return;

    int minimo = arr[0], maximo = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minimo) minimo = arr[i];
        if (arr[i] > maximo) maximo = arr[i];
    }
    if (minimo == maximo) return;

    int numero_buckets = n;
    int *baldes = calloc((size_t)numero_buckets, sizeof(*baldes));
    int **buckets = calloc((size_t)numero_buckets, sizeof(*buckets));
    if (baldes == NULL || buckets == NULL) {
        free(baldes);
        free(buckets);
        return;
    }

    for (int i = 0; i < n; i++) {
        long indice = ((long)arr[i] - minimo) * (numero_buckets - 1) /
                      ((long)maximo - minimo);
        baldes[indice]++;
    }
    for (int i = 0; i < numero_buckets; i++) {
        if (baldes[i] > 0) {
            buckets[i] = malloc((size_t)baldes[i] * sizeof(int));
            if (buckets[i] == NULL) {
                for (int j = 0; j < i; j++) free(buckets[j]);
                free(baldes);
                free(buckets);
                return;
            }
        }
    }

    int *posiciones = calloc((size_t)numero_buckets, sizeof(*posiciones));
    if (posiciones == NULL) {
        for (int i = 0; i < numero_buckets; i++) free(buckets[i]);
        free(baldes);
        free(buckets);
        return;
    }
    for (int i = 0; i < n; i++) {
        long indice = ((long)arr[i] - minimo) * (numero_buckets - 1) /
                      ((long)maximo - minimo);
        buckets[indice][posiciones[indice]++] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < numero_buckets; i++) {
        if (baldes[i] > 0) {
            insercion(buckets[i], baldes[i]);
            for (int j = 0; j < baldes[i]; j++) arr[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    free(posiciones);
    free(baldes);
    free(buckets);
}

void imprimirArreglo(const int arr[], int n)
{
    if (arr == NULL) return;
    for (int i = 0; i < n; i++) printf("%d%s", arr[i], i + 1 < n ? " " : "");
    printf("\n");
}

int arregloOrdenado(const int arr[], int n)
{
    if (arr == NULL) return 0;
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}
