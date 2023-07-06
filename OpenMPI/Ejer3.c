#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int idProc, nProc, i, tag = 99, primero, ultimo, bloque, flag, tamNombre, pmax = 0, nmax = 0, pmin = 0, nmin = 0;
char nombre[30];

MPI_Status status;
int main(int argc, char **argv)
{
    int *max = (int*)malloc(sizeof(int)); 
    int *min = (int*)malloc(sizeof(int)); 
    *min = 10000;
    nombre[tamNombre] = '\0';
    int tam = atoi(argv[1]);
    int datos[tam], u = 0;
    FILE *f = NULL;

    f = fopen("Archivo1.txt", "r");

    while(feof(f) == 0){
        fscanf(f, "%d", &datos[u]);
        u++;

        if(datos[u-1] > *max)
            *max = datos[u-1];
        if(datos[u-1] < *min)
            *min = datos[u-1];
    } 

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Get_processor_name(nombre, &tamNombre);

    /* Calcula el tamaño de las partes a enviar a los otros */

    MPI_Bcast(datos, tam, MPI_INT, 0, MPI_COMM_WORLD);
    // Determina nmeros a sumar
    bloque = tam / nProc;
    if (idProc == nProc - 1)
    {
        primero = (nProc - 1) * bloque;
        ultimo = tam - 1;
    }
    else
    {
        primero = idProc * bloque;
        ultimo = (idProc + 1) * bloque - 1;
    }

    pmax = 0;
    pmin = 0;
    // Computa la busqueda del mayor
    for (i = primero; i <= ultimo; i++){
        if(datos[i] == *max){
            pmax++;
        }
        if (datos[i] == *min){
            pmin++;
        }    
    }

    // printf("El maximo es %d \n", *max);
    // printf("El minimo es %d\n", *min);

    // printf("En el  proceso %d el numero %d aparece %d veces\n", idProc, *max, pmax);
    // printf("En el proceso %d el numero %d aparece %d veces\n", idProc, *min, pmin);

    MPI_Reduce(&pmax, &nmax, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&pmin, &nmin, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (idProc == 0){
        printf("El maximo es %d y aparece %d veces\n", *max, nmax);
        printf("El minimo es %d y aparece %d veces\n", *min, nmin);
    }
    MPI_Finalize();
}