#include <stdio.h> 
#include <unistd.h> 
int main() {
int i, p;
    for (i=0; i<2; i++) {
        p = fork();
	printf("i=%d, p=%d\n", i, p); }
}
