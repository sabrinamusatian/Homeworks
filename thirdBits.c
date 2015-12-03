#include <stdio.h>


int thirdBits(void) {
  int x = 36; // 0000 0000 0000 0000 0000 0000 0010 0100
  int y = (x << 6); // 0000 0000 0000 0000 0000 1001 0000 0000
  int z = y + x; // 0000 0000 0000 0000 0000 1001 0010 0100
  return (((z << 12) + z) << 6) + x; // 0010 0100 1001 0010 0100 1001 0010 0100
}

int main()
{
    printf("ThirdBits: %d\n", thirdBits());
    return 0;
}

