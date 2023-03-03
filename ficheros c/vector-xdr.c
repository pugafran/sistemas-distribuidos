#include <stdio.h>
#include <sys/types.h>


typedef struct {
u_int VariosEnteros_len; 
int *VariosEnteros_val;
} VariosEnteros;

int main(){

    VariosEnteros v;
    v.VariosEnteros_val = NULL;
    // ...
    xdr_VariosEnteros(&operacion, &v);
    // Podemos acceder ya a sus elementos
    // v.VariosEnteros_len <-- Cuántos son
    // v.VariosEnteros_val[i] <-- Cada uno de ellos
    // Liberar
    xdr_free((xdrproc_t) xdr_VariosEnteros, &v);





    return 0;

}