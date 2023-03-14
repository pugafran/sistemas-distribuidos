#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
int main(){

    int * vector = malloc(sizeof(int) * 3);

    int i;

    for(i = 0; i < 3; i++){
        *(vector+i) = i;
        printf("\n%d\n", *(vector+i));

    }

    printf("\nLa gocha pumarín\n");

    for(i = 0; i < 3; i++){
        vector[i] = i;
        printf("\n%d\n", vector[i]);

    }


    return 0;
}