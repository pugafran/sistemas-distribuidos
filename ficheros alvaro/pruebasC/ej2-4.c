#include <stdio.h>

void main()
{
    char   c = 'a';
    int    i = 100;
    double z = 0.0;

    int j = 3;

    //Punteros
    char *p_c = &c;

    printf("Tamaño de c: %lu\n", sizeof(c));
    printf("Tamaño de i: %lu\n", sizeof(i));
    printf("Tamaño de z: %lu\n", sizeof(z));
    printf("Dirección de c: %p\n", &c);
    printf("Dirección de i: %p\n", &i);
    printf("Dirección de z: %p\n", &z);
    printf("Tamaño de la dirección de c: %lu\n", sizeof(&c));
    printf("Tamaño de la dirección de i: %lu\n", sizeof(&i));
    printf("Tamaño de la dirección de z: %lu\n", sizeof(&z));
}

