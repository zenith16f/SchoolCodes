#include "logica.h"

void numeracion(int i,int j, int matriz[FILAS][COLUMNAS]){
	matriz[i][j] = (j+1);
}
void numeracionImpar(int i, int j, int matriz[FILAS][COLUMNAS]){
	matriz[i][j] = (2*j)+1;
}
void numeracionPar(int i, int j, int matriz[FILAS][COLUMNAS]){
	matriz[i][j] = 2*(j+1);
}
//Asignacion de elementos a la matriz
void llenarMatriz(int matriz[FILAS][COLUMNAS]){
	for(int i=0; i<FILAS; i++){
		for(int j=0; j<COLUMNAS; j++){
			
			switch(i){
				case 0:
					numeracion(i,j,matriz);
					break;
				case 1:
					numeracionImpar(i,j,matriz);
					break;
				case 2:
					numeracionPar(i,j,matriz);
					break;
				default:
					break;
			}
		}
	}
}