#include <stdio.h>
#include <omp.h>

int main (int argc, char * argv[]){

    float Datos[4];

    #pragma omp parallel
    {
        int IdHilo = omp_get_thread_num(); 

        FILE *f = NULL;
		f = fopen(argv[IdHilo+1], "r");

        float aux = 0, menor = -5;

		while(feof(f) == 0){
			fscanf(f, "%f", &aux);
			if(aux < menor || menor == -5){
                menor = aux;
            }
		} 

        Datos[IdHilo] = menor;
    }

    printf(" %f, %f, %f, %f \n", Datos[0], Datos[1], Datos[2], Datos[3]);

    return 0;
}