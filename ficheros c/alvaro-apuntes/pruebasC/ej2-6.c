#include <stdio.h>

int main(){
    int *p_i = NULL;   // Se declara pero no se inicializa
	
    if(p_i!=NULL){
    	*p_i = 100;	// erroneamente dereferencio el puntero
    }
}
