#include <stdio.h>
#include <mpi.h>
#include <string.h>

int idproc;
int main (int argc, char** argv){
    char arch[4][40];

    strcpy(arch[0], argv[1]);
    strcpy(arch[1], argv[2]);
    strcpy(arch[2], argv[3]);
    strcpy(arch[3], argv[4]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idproc);

    float datos[50], min = 10000, max = 0, suma = 0;
    int u = 0;

    FILE *f = NULL;
    f = fopen(arch[idproc], "r");

    while(feof(f) == 0){
        fscanf(f, "%f", &datos[u]);
        u++;
    } 

    for(int i=0;i<u;i++){ 
        suma+=datos[i];
        if(datos[i] <= min){
            min = datos[i];
        }
        if(datos[i] >= max){
            max = datos[i];
        }
    }
    fclose(f);

    char Archivo[50];
    strcat(strcpy(Archivo,"Salida "),arch[idproc]);
    f = fopen(Archivo, "w");

    fprintf(f,"El minimo  del archivo %s es %f \n", arch[idproc], min);
    fprintf(f,"El maximo  del archivo %s es %f \n", arch[idproc], max);
    fprintf(f,"El promedio  del archivo %s es %f \n", arch[idproc], suma/u);

    fclose(f);

    MPI_Finalize();
}
