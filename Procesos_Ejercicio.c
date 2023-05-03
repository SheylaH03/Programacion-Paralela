#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {
    int a = 10, b = 15, c = 0, estado;
    int hijo=fork();

    if (hijo==0){
        c = a+b;
        exit(c);
    }
    else{
        wait(&estado);

        if(WIFEXITED(estado)){
            c = WEXITSTATUS(estado);
            printf("El primedio es: %d", c/2);
        }
    }
    return 0;
}
