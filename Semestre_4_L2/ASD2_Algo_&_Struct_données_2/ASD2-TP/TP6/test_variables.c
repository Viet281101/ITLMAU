
#include <stdio.h>
#include <stdlib.h>

struct ma_struct {
  int a;
  int b;
  struct ma_struct* c;
};

int main() {
  int var_int = 3;
  float var_float = 3.14;
  char var_char = 'A';
  char var_string[] = "Hello";
  long int var_long_int = 1234567890;
  char var_string2[] = "World";
  int* var_p_int = malloc(sizeof(int));
  int** var_pp_int = malloc(sizeof(int*));
  int var_array[5] = {1, 2, 3, 4, 5};
  struct ma_struct var_struct;
  struct ma_struct* var_p_struct = malloc(sizeof(struct ma_struct));

  // Print variable information
  printf("Variable Information:\n");
  printf("var_int:\nValue: %d\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_int, sizeof(var_int), &var_int, sizeof(&var_int));
  printf("var_float:\nValue: %f\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_float, sizeof(var_float), &var_float, sizeof(&var_float));
  printf("var_char:\nValue: %c\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_char, sizeof(var_char), &var_char, sizeof(&var_char));
  printf("var_string:\nValue: %s\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_string, sizeof(var_string), &var_string, sizeof(&var_string));
  printf("var_long_int:\nValue: %ld\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_long_int, sizeof(var_long_int), &var_long_int, sizeof(&var_long_int));
  printf("var_string2:\nValue: %s\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_string2, sizeof(var_string2), &var_string2, sizeof(&var_string2));
  printf("var_p_int:\nValue: %p\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_p_int, sizeof(var_p_int), &var_p_int, sizeof(&var_p_int));
  printf("var_pp_int:\nValue: %p\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_pp_int, sizeof(var_pp_int), &var_pp_int, sizeof(&var_pp_int));
  printf("var_array:\nValue: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", var_array[i]);
  }
  printf("\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", sizeof(var_array), &var_array, sizeof(&var_array));
  printf("var_struct:\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", sizeof(var_struct), &var_struct, sizeof(&var_struct));
  printf("var_p_struct:\nValue: %p\nSize: %lu bytes\nAddress: %p\nAddress Size: %lu bytes\n", var_p_struct, sizeof(var_p_struct), &var_p_struct, sizeof(&var_p_struct));

  return 0;
}

