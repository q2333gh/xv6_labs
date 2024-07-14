#include <stdio.h>
#include <stdlib.h>

void f(void) {
  int a[4];  // stack value . a  store a pointer to this array. (no bound detect
             // for stablity or securirty. but very fast.)
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

  c[1] = 300;
  *(c + 2) = 301;  
  // this +2 will auto calculate the sizeof each array cell.(offset)
  3 [c] = 302;  // syntax: equivalent way of writing *(c + 3) = 302.
  printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n", a[0], a[1], a[2],
         a[3]);

  c = c + 1;
  *c = 400;
  printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n", a[0], a[1], a[2],
         a[3]);

  c = (int *)((char *)c + 1);
  *c = 500;
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