#include<stdio.h>
#include<string.h>
#define LIM 100
typedef struct {
    int fila;
    int columna;
}Posicion;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1}; 
typedef struct st{
    Posicion pila[LIM];
    int tope;
} Pila;
void imprimirL(char laberinto[LIM][LIM], int filas) {
    for (int i = 0; i < filas; i++) {
        printf("%s\n", laberinto[i]);
    }
}
int vacia(Pila *p){
    return p->tope == 0;
}
void push(Pila *p, Posicion f){
    p->pila[++(p->tope)] = f; 
}

Posicion pop(Pila *p){
    return p->pila[(p->tope)--];
}

void res(char laberinto[LIM][LIM], Posicion (*bq)(char [LIM][LIM], int, int), int f, int c) {
    Pila p;
    p.tope = 0;

    Posicion ini = bq(laberinto, f,c);
    push(&p, ini);

    while (!vacia(&p)) {
        Posicion a = pop(&p);
        int fila = a.fila;
        int columna = a.columna;

        if (laberinto[fila][columna] == 'S') {
            printf("Salida en %d %d\n", fila, columna);
            laberinto[fila][columna] = '.'; 
            break;
        }

        if (laberinto[fila][columna] != 'E') { 
            laberinto[fila][columna] = '.';
        }

        for (int i = 0; i < 4; i++) {
            int fila2 = fila + dx[i]; // Aqui va al este
            int columna2 = columna + dy[i]; // Aqui al norte
            if (fila2 >= 0 && fila2 < f && columna2 >= 0 && columna2 < c 
                 && (laberinto[fila2][columna2] == 'C' || laberinto[fila2][columna2] == 'S')) {
                Posicion avanza = {fila2, columna2};
                push(&p, avanza);
            }
        }
    }

    printf("Solucion:\n");
    imprimirL(laberinto, f);
}
void resBacktracking(char laberinto[LIM][LIM], Posicion (*bq)(char [LIM][LIM], int, int), int f, int c) {
    Pila p;
    p.tope = 0;

    Posicion ini = bq(laberinto, f, c);
    push(&p, ini);

    while (!vacia(&p)) {
        Posicion a = pop(&p);
        int fila = a.fila;
        int columna = a.columna;
        if (laberinto[fila][columna] == 'S') {
            printf("Salida encontrada en (%d, %d)\n", fila, columna);
            laberinto[fila][columna] = '.'; 
            break;
        }
        if (laberinto[fila][columna] != 'E') {
            laberinto[fila][columna] = '.'; 
        }
        int caminos = 0; 
        for (int i = 0; i < 4; i++) {
            int fila2 = fila + dx[i];
            int columna2 = columna + dy[i];
            if (fila2 >= 0 && fila2 < f && columna2 >= 0 && columna2 < c &&
                (laberinto[fila2][columna2] == 'C' || laberinto[fila2][columna2] == 'S')) {
                Posicion avanza = {fila2, columna2};
                push(&p, avanza); 
                caminos++;
            }
        }     
        if (caminos == 0) {
            laberinto[fila][columna] = 'C'; 
        }
    }

    printf("Solución:\n");
    imprimirL(laberinto, f);
}
Posicion bqIni(char laberinto[LIM][LIM], int filas, int columnas){
    for(int i =0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if(laberinto[i][j] == 'E'){
                Posicion ini = {i,j};
                return ini;
            }
        }
    }
    Posicion nF = {-1,-1};
    return nF;
}
int main(){
    char laberinto[LIM][LIM];
    int fila = 0;
    FILE *f = fopen("laberinto.txt",  "r");
    if(f==NULL){
        printf("No hay archivo\n");
        return 1;
    }
    while(fgets(laberinto[fila], LIM, f) != NULL){
        laberinto[fila][strcspn(laberinto[fila],"\n")] ='\0';
        fila++;
    }
    fclose(f);
    printf("cargado\n");
    imprimirL(laberinto, fila);
    resBacktracking(laberinto,bqIni,  fila, strlen(laberinto[0]));

    return 0;
}
