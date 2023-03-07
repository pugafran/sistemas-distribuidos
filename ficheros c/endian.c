#include <stdio.h>

int main() {
   unsigned int num = 0x12345678;
   char *ptr = (char*)&num;

   printf("Valor original: 0x%x\n", num);

   if (*ptr == 0x78) {
      printf("El sistema es little endian.\n");
   } else {
      printf("El sistema es big endian.\n");
   }

   return 0;
}

