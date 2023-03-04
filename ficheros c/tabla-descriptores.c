#include <unistd.h>
#include <stdio.h>

int main() {
    long max_files = sysconf(_SC_OPEN_MAX);
    printf("Número máximo de archivos abiertos: %ld\n", max_files);
    return 0;
}
