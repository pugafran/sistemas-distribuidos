#include <windows.h>
#include <stdio.h>

int main() {
    DWORD max_files;
    BOOL success = GetMaximumFileCount(&max_files);
    if (success) {
        printf("El tamaño máximo de la tabla de descriptores es: %lu\n", max_files);
    } else {
        printf("Error al obtener el tamaño máximo de la tabla de descriptores\n");
    }
    return 0;
}
