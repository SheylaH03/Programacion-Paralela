// Distrución de tareas con for y uso de variables
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int triangularInferior(int datos[5][5], int x, int y){
    int suma = 0;

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(j>i){
                suma += datos[i][j];
            }
        }
    }
    return suma;

}

int triangularSuperior(int datos[5][5], int x, int y){
    int suma = 0;

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(j<i){
                suma += datos[i][j];
            }
        }
    }
    return suma;
}

int Diagonal(int datos[5][5], int x, int y){
    int suma = 0;

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(j == i){
                suma += datos[i][j];
            }
        }
    }
    return suma;
}



int main( int argc, char *argv[] ){

    int datos[5][5], x=0, y = 0, superior = 0, inferior = 0, diagonal = 0;

    FILE *f = NULL;
    f = fopen("Archivo2.txt", "r");

    while(feof(f) == 0){
        fscanf(f, "%d", &datos[x][y]);    
        y++;
        if(y == 5){
            y = 0;
            x++;
        }
    } 
    if(y == 0) y = 5;

    #pragma omp parallel sections 
    {
        #pragma omp section
        {
            diagonal = Diagonal(datos, x, y);
            printf("La suma de la diagonal es %d \n", diagonal);
                
        }
        #pragma omp section
        {
            superior = triangularSuperior(datos, x, y);
            printf("La suma de la Triangular Superios es %d \n", superior);
            
        }
        #pragma omp section
        {
            inferior = triangularInferior(datos, x, y);
            printf("La suma de la Triangular Inferior es %d \n", inferior);
            
        }
    }

    


}