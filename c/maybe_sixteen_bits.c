#include <stdio.h>

int main() {
    unsigned char bytes[2];
    int sum = 0;
    int count = 0;
    FILE *fp=fopen("1988730searlymelt.int.304.448.c", "rb");
    while ( fread(bytes, 2, 1,fp) != 0) {
      int piece = bytes[0] | (bytes[1]<<8);
      sum += piece;
      printf("The piece is %d\n", piece);
      count = count + 1;
    }
    printf("The sum is %d\n", sum);
    printf("the total count is %d\n", count);
    return 0;
}
