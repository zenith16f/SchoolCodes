#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo de matriz dispersa
typedef struct Nodo
{
    int fila;
    int columna;
    int valor;
    struct Nodo *sig;
} Nodo;

// Crear un nuevo nodo
Nodo *crear_nodo(int fila, int columna, int valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->fila = fila;
    nuevo->columna = columna;
    nuevo->valor = valor;
    nuevo->sig = NULL;
    return nuevo;
}

// Insertar nodo al final
void insertar_nodo(Nodo **cab, int fila, int columna, int valor)
{
    Nodo *nuevo = crear_nodo(fila, columna, valor);
    if (*cab == NULL)
    {
        *cab = nuevo;
        return;
    }
    Nodo *p = *cab;
    while (p->sig != NULL)
    {
        p = p->sig;
    }
    p->sig = nuevo;
}

// Capturar valores no nulos
void capturar_matriz(Nodo **matriz, int filas, int columnas, int numero)
{
    int cantidad;
    printf("\nCuantos valores no nulos tiene la matriz %d? ", numero);
    scanf("%d", &cantidad);

    for (int i = 0; i < cantidad; i++)
    {
        int f, c, v;
        printf("\nIntroduce las coordenadas del valor no nulo y separalos con espacios (renglon, columna, valor): ");
        fflush(stdout);
        scanf("%d %d %d", &f, &c, &v);

        // Se restan 1 a los indices para trabajar en base 0 internamente
        f -= 1;
        c -= 1;

        if (f >= 0 && f < filas && c >= 0 && c < columnas)
        {
            insertar_nodo(matriz, f, c, v);
        }
        else
        {
            printf("\nCoordenadas fuera de rango. Intenta de nuevo.\n");
            i--;
        }
    }
}

// Imprimir matriz completa.
void imprimir_matriz(Nodo *matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            Nodo *p = matriz;
            int valor = 0;
            while (p != NULL)
            {
                if (p->fila == i && p->columna == j)
                {
                    valor = p->valor;
                    break;
                }
                p = p->sig;
            }
            printf("%3d ", valor);
        }
        printf("\n");
    }
}

// Multiplicación de matrices dispersas con diferente dimensión
Nodo *multiplicar_matrices(Nodo *a, Nodo *b, int m1, int n1, int m2, int n2)
{
    if (n1 != m2)
    {
        printf("\nNo se puede multiplicar: dimensiones incompatibles.\n");
        return NULL;
    }

    Nodo *resultado = NULL;

    for (int i = 0; i < m1; i++)
    {
        for (int k = 0; k < n2; k++)
        {
            int suma = 0;

            for (int j = 0; j < n1; j++)
            {
                int val_a = 0, val_b = 0;
                Nodo *pa = a, *pb = b;

                while (pa != NULL)
                {
                    if (pa->fila == i && pa->columna == j)
                    {
                        val_a = pa->valor;
                        break;
                    }
                    pa = pa->sig;
                }

                while (pb != NULL)
                {
                    if (pb->fila == j && pb->columna == k)
                    {
                        val_b = pb->valor;
                        break;
                    }
                    pb = pb->sig;
                }

                suma += val_a * val_b;
            }

            if (suma != 0)
            {
                insertar_nodo(&resultado, i, k, suma);
            }
        }
    }

    return resultado;
}

void main()
{
    Nodo *matriz1 = NULL, *matriz2 = NULL;
    int m1, n1, m2, n2;

    printf("Filas de la primera matriz: ");
    scanf("%d", &m1);
    printf("Columnas de la primera matriz: ");
    scanf("%d", &n1);
    printf("\nFilas de la segunda matriz: ");
    scanf("%d", &m2);
    printf("Columnas de la segunda matriz: ");
    scanf("%d", &n2);

    printf("\nCaptura de la primera matriz:\n");
    capturar_matriz(&matriz1, m1, n1, 1);

    printf("\nCaptura de la segunda matriz:\n");
    capturar_matriz(&matriz2, m2, n2, 2);

    Nodo *resultado = multiplicar_matrices(matriz1, matriz2, m1, n1, m2, n2);
    if (resultado != NULL){
        printf("\nResultado de la multiplicacion:\n");
        imprimir_matriz(resultado, m1, n2);
    }
    else{
        printf("\nLa multiplicacion resulto en una matriz con puros ceros.\n");
    }
}
