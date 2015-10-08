#include <stdio.h>


int thirdBits(void) {
  int x = 73; // 0000 0000 0000 0000 0000 0000 0100 1001
  int y = (x << 9); // 0000 0000 0000 0000 1001 0010 0000 0000
  int z = y + x; // 0000 0000 0000 0000 1001 0010 0100 1001
  return ((z << 18) + z); // 0100 1001 0010 0100 1001 0010 0100 1001
}

int main()
{
    printf("ThirdBits: %d\n",thirdBits());
    return 0;
}
