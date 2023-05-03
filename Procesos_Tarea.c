#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    int estado;
    float b = 0, suma = 0;
    int hijo=fork();

    if (hijo==0){
        
        for(int i=2; i <= atoi(argv[1])+1; i++){
            suma += atof(argv[i]);
        }
        
        exit(suma);
    }
    else{
        wait(&estado);

        if(WIFEXITED(estado)){
            suma = WEXITSTATUS(estado);
            printf("El primedio es: %f", suma/atoi(argv[1]));
        }
    }
    return 0;
}