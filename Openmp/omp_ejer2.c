// Distrución de tareas con for y uso de variables
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int mayor(float v[], int N, float media){
int i=0, mayores = 0;   

for(i=0; i<N; i++)
   if(v[i]>media) mayores++; 

return mayores;
}

int menor(float v[], int N, float media){
int i=0, menores = 0;   

for(i=0; i<N; i++)
   if(v[i]<media) menores++; 

return menores;
}

int main( int argc, char *argv[] ){

    int i=0, suma=0, mayores=0, menores=0, u = 0;
    float datos[50];
    float media = 0;

    FILE *f = NULL;
    f = fopen("Archivo1.txt", "r");

    while(feof(f) == 0){
        fscanf(f, "%f", &datos[u]);
        u++;
    } 
 
    #pragma omp parallel for private(i) reduction(+:suma)   
        for(i=0;i<u;i++){ 
            suma+=datos[i];
        }

    media = (float)suma/(float)u;


    #pragma omp parallel sections 
    {
    #pragma omp section
    {
        mayores  = mayor(datos,u,media);
            
    }
    #pragma omp section
    {
        menores  = menor(datos,u,media);
    }
    }

    printf("%d valores son mayores a la media\n",mayores);
    printf("%d valores son menores a la media\n",menores);


}