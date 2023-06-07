// Distrución de tareas con for y uso de variables
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main( int argc, char *argv[] ){

    int i=0, N=10, suma=0, idHilo;
    int datos[50], u=0;

    FILE *f = NULL;
    f = fopen(argv[1], "r");

    while(feof(f) == 0){
        fscanf(f, "%d", &datos[u]);
        u++;
    } 

    int num = atoi(argv[2]);

    int sumaind[num];

    for(i=0; i<num; i++){
        sumaind[i] = 0;
    }


    #pragma omp parallel for shared(sumaind) private(i, idHilo) num_threads(num)

        for(i = 0; i < u; i++ ) {
            idHilo = omp_get_thread_num(); 
            sumaind[idHilo]+=datos[i];
        }

    for(i=0; i<num; i++){
        suma += sumaind[i];
        printf(" la suma del hilo %d es: %d \n", i, sumaind[i]);
    }

   printf(" la suma es: %d \n", suma);
   printf(" el promedio es: %d \n", suma/u);


 return 0;
}
