#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>

int main() {
    long max_files = sysconf(_SC_OPEN_MAX);
    printf("Número máximo de archivos abiertos: %ld\n", max_files);

    struct rlimit limits;
    int success = getrlimit(RLIMIT_NOFILE, &limits);
    if (success == 0) {
        printf("El tamaño máximo de la tabla de descriptores es: %lu\n", limits.rlim_cur);
    } else {
        printf("Error al obtener el tamaño máximo de la tabla de descriptores\n");
    }
    return 0;





}


