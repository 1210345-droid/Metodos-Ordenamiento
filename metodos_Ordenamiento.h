#ifndef METODOS_ORDENAMIENTO_H
#define METODOS_ORDENAMIENTO_H

int *Data(int size);
int *get_array_data(int size);
int *burbuja(int arr[], int n, int *pasadas);
int *seleccion(int arr[], int n, int *pasadas);
int *insercion(int arr[], int n);
void quicksort(int arr[], int bajo, int alto);
int *mergesort(int arr[], int n);
void heapSort(int arr[], int n);
void shellSort(int arr[], int n);
void radixSort(int arr[], int n);
void countingSort(int arr[], int n);
void cocktailSort(int arr[], int n);
void combSort(int arr[], int n);
void gnomeSort(int arr[], int n);
void bucketSort(int arr[], int n);
void imprimirArreglo(const int arr[], int n);
int arregloOrdenado(const int arr[], int n);

#endif