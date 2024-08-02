#include <stdio.h>
#include <stdlib.h>
void print_binary(int num) {
  unsigned int mask =
      1 << ((sizeof(int) * 8) - 1);  // Create a mask to check each bit
  int count = 0;                     // Counter for spacing every 4 bits

  for (; mask > 0; mask >>= 1) {
    if (num & mask)
      printf("1");
    else
      printf("0");

    count++;
    if (count % 4 == 0)  // Add a space every 4 bits
      printf(" ");
  }
  printf("\n");
}

void f(void) {
  int a[4];  // stack value . a  store a pointer to this first element of a
             // array. (no bound detect for stablity or securirty. but very
             // fast.) . 
  int *b = malloc(16);  // mem-heap data box.
  // using a pointer to storage its location addr.(give a way to get and set it
  // )
  int *c;  // a pointer to stack data .
  int i;

  // %p will auto print  its` addr in hex
  printf("1: a = %p, b = %p, c = %p\n", a, b, c);
  printf("1: a_point_to = %p, b_addr = %p, c_point_to = %p\n", a, b, c);

  c = a;  // now we can use indirect ref to original array_a
  for (i = 0; i < 4; i++) {
    a[i] = 100 + i;
  }

  c[0] = 200;
  printf("2: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n", a[0], a[1], a[2],
         a[3]);

  c[1] = 300;  // equal to  *(a + 1)
  *(c + 2) = 301;  
  // this +2 will auto calculate the sizeof each array cell.(offset)
  3 [c] = 302;  // syntax: equivalent way of writing *(c + 3) = 302. (also c[3] )
  printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n", a[0], a[1], a[2],
         a[3]);

  c = c + 1;// c point to next cell:a[1]
  *c = 400;
  printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n", a[0], a[1], a[2],
         a[3]);


  // printf("size of int is %ld \n",sizeof(int));
  // printf("size of char is %ld \n",sizeof(char));
  printf("bin view of a[1]: ");
  print_binary(a[1]);
  // float cast_offset = sizeof(char) / sizeof(int);
  c = (int *)((char *)c + 1); // cast c pointer to 8 bits wide(char type),then
  // offset 1 cell(but 8 bit, 1 byte ),  now c point to a[1+cast_offset]
  // then `recognize`  all data in a[1](but int size cell wide)  as int
  // a[1]: 0000 0000 0000 0000 0000 0001 1001 0000 (400)  <=  data from this side. right to left 
  // c[1] is missing a[1] first 8 bit and dangerously overwrite a[2] first 8 bit
  // printf("a_addr is %p\n",&a);
  // printf("a[1]_addr is %p\n",&a[1]);
  // printf("c_addr is %p\n",&c);
  *c = 500;
  // after *c = 500;
  //                 . first 8 bit ignore
  // a[1]: 0000 0000 0000 0000 0000 0001 1001 0000 (400)
  //    -> 0000 0000 0000 0000 0000 0000 0000 0001
  //                 . overwrite  first 8 bit by new *c
  // a[2]: 0000 0000 0000 0000 0000 0001 0010 1101 (301)
  //    -> 1111 0100 0000 0000 0000 0001 0010 1101
  //       0000 0000 0000 0000 0000 0001 1111 0100 (500)
  // 11111010010010000 (128144)
  // 100000000 (256)
  printf("bin view of new c[1]: ");
  print_binary(c[1]);
  printf("5: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n", a[0], a[1], a[2],
         a[3]);

  b = (int *)a + 1;
  c = (int *)((char *)a + 1);
  printf("6: a = %p, b = %p, c = %p\n", a, b, c);
}



int main(int ac, char **av) {
  f();
  return 0;
}

// a1 11111111111110110110111110000101010100110110100 140727686441396
// c1 11111111111110110110111110000101010100110100000 140727686441376