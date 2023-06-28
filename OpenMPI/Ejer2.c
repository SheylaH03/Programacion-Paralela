#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int idProc, nProc, i, tag = 99, primero, tamBloque, flag, tamNombre;
char nombre[30];
MPI_Status status;
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Get_processor_name(nombre, &tamNombre);

    nombre[tamNombre] = '\0';
    int tam = atoi(argv[1]);
    int datos[tam], u = 0;

    /* Calcula el tamaño de las partes a enviar a los otros */
    tamBloque = tam / nProc;
    int max = 0, maximos[nProc];
    if (idProc == nProc - 1)
    {
        
        FILE *f = NULL;
        f = fopen("Archivo1.txt", "r");

        while(feof(f) == 0){
            fscanf(f, "%d", &datos[u]);
            u++;
        } 
        printf("\n");

        /* Envia los bloques de datos los otros procesos*/
        for (i = 0; i < nProc - 1; i++)
        {
            primero = i * tamBloque;
            MPI_Send(&datos[primero], tamBloque, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
        /* determina lo que debo sumar yo (nproc-1) */
        primero = idProc * tamBloque;
        /* efectuo mi suma parcial */
        max = 0;
        for (i = primero; i < tam ; i++)
            if (datos[i] > max){
                max = datos[i];
            }
        printf ("Mi maximo es : %d\n", max);
        maximos[idProc] = max;
            /* obtener las sumas parciales y calcula la total */
        for (i = 0; i < nProc - 1; i++)
        {
            MPI_Recv(&max, 1, MPI_LONG, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            printf("Respondio %d - envio: %d\n", status.MPI_SOURCE, max);

            maximos[status.MPI_SOURCE] = max;
        }

        max = 0;
        for(i  = 0; i < nProc; i++){
            if (maximos[i] > max){
                max = maximos[i];
            }
        }

        printf("El maximo es = %d\n", max);
    }
    else
    {
        /* recibe mi parte */
        MPI_Recv(datos, tamBloque, MPI_LONG, nProc - 1, tag, MPI_COMM_WORLD, &status);
        /* efectua mi suma parcial */
        max = 0;
        for (i = 0; i < tamBloque; i++){
            if (datos[i] > max){
                max = datos[i];
            }
        } 
        /* devuelve mi suma parcial a (nproc - 1) */
        MPI_Send(&max, 1, MPI_LONG, nProc - 1, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}