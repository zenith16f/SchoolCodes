// Includes
#include <stdio.h>
#include <math.h>
// Constants
#define N 5

// Preguntar Function
float preguntar(int i)
{
    float calificacion;
    printf("Ingresa la calificacion del alumno %d: ", i);
    scanf("%f", &calificacion);
    return calificacion;
}

// Inicializar function
void inicializar(float arr[N])
{

    int alumno;
    for (int i = 0; i < N; i++)
    {
        alumno = (i + 1);
        float dato = preguntar(alumno);
        arr[i] = dato;
    }
}

// Suma Function
float Suma(float arr[N])
{
    float suma;
    for (int i = 0; i < N; i++)
    {
        suma += +arr[i];
    }
    return suma;
}

// Promedio Function
void Promedio(float arr[N])
{
    float suma = Suma(arr);
    float promedio;

    promedio = suma / N;
    printf("El promedio de las calificacion es: %.2f \n", promedio);
}

// Desviacion Estandar Function
void desviacionEstandar(float arr[N])
{
    float desviacion, acumulado, suma, tot;
    suma = Suma(arr)/N;
    for (int i = 0; i < N; i++)
    {
        acumulado += arr[i] - suma;
    }

    tot = powf(2, acumulado); 

    desviacion = sqrt(tot / N);

    printf("La desviacion estandar es: %.2f \n", desviacion);
}

// Mostrar function
void mostrar(float arr[N])
{
    for (int i = 0; i < N; i++)
    {
        // Output
        printf("Calificacion %d : %.2f \n", i + 1, arr[i]);
    }
}

// Main function
int main(void)
{
    // Variables
    float calif[N];

    // Function Calling
    inicializar(calif);
    mostrar(calif);
    Promedio(calif);
    desviacionEstandar(calif);
}
