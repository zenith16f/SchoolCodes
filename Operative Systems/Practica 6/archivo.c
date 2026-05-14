#include "archivo.h"
#include "semaforo.h"

void formatoMensaje(pid_t cliente,char frase[], FILE *archivo){
    char frase_formato[MAX_FRASE];
    snprintf(frase_formato, sizeof(frase_formato), "[%d] Escribio: ", (int)cliente);
    strcat(frase_formato, frase);
    strcat(frase_formato, "\n");
    int longitud_frase = strlen(frase_formato);
    fwrite(frase_formato, sizeof(char), longitud_frase, archivo);

}

int guardarFrase(pid_t cliente, char frase[]){
    /*
    Crear archivo para añadir los datos al final del archivo
    o en su caso crear el archivofrases
    */
    FILE *archivo = fopen("frases.txt", "a");
    if(archivo!=NULL){
        formatoMensaje(cliente, frase, archivo);
        fclose(archivo);
        return 0;
    }
    else return 1;
}

/*Verifica si ya hay datos en el archivo*/
long historial(){
    long marcador;
    FILE *archivo = fopen("frases.txt", "r");
    if(archivo != NULL){
        fseek(archivo, 0, SEEK_END);
        marcador = ftell(archivo);
        fclose(archivo);
    }
    return marcador;
}

long imprimirFrases(long cursor_actual){
    char buffer[MAX_FRASE + 50];
    FILE *archivo = fopen("frases.txt", "r");

    if(archivo != NULL){
        fseek(archivo, cursor_actual, SEEK_SET);
        while(fgets(buffer,sizeof(buffer), archivo)){
            printf("[Hilo lector] Frase: %s\n", buffer);
        }
        cursor_actual = ftell(archivo);
        fclose(archivo);      
    }
    return cursor_actual;
}
