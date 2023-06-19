// Distrución de tareas con for y uso de variables
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


int main( int argc, char *argv[] ){

    int i=0, suma=0, suma2 = 0;
    int datos[50], u=0;
    float varianza = 0, media = 0, desviacion = 0;

    FILE *f = NULL;
    f = fopen("Archivo1.txt", "r");

    while(feof(f) == 0){
        fscanf(f, "%d", &datos[u]);
        u++;
    } 
 
    #pragma omp parallel for private(i) reduction(+:suma)   
        for(i=0;i<u;i++){ 
            suma+=datos[i];
        }
    printf("El  valor de suma es %d \n",suma);
    media = (float)suma/(float)u;
    printf("El valor de la media es %f \n", media);

    #pragma omp parallel for private(i) reduction(+:suma2)   
        for(i=0;i<u;i++){ 
            suma2+=pow(datos[i]- media,2);
        }
    varianza = (float)suma2/(float)u;
    printf("El valor de la varianza es %f \n", varianza);
    desviacion = sqrt(varianza);
    printf("El valor de la desviacion estandar es %f \n", desviacion);


}