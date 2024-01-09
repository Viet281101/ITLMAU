#include <stdio.h>

int
main (int argc, char *argv[])
{
  char acc = 0, tmp = 0; // registers
  char mem[16384];       // memory
  int sp = 0;            // stack pointer
  char instr;

  while ((instr = getchar()) != EOF) {
    switch (instr) {
    case 'f' /* False */ : acc = 0;             break;
    case 't' /* True  */ : acc = 1;             break;
    case 's' /* Push  */ : mem[sp++] = acc;     break; // to avoid "p" conflict, "s" as in "store"
    case 'l' /* Pop   */ : acc = mem[--sp];     break; // to avoid "p" conflict, "l" as in "load"
    case 'h' /* Hold  */ : tmp = acc;           break;
    case 'n' /* Nand  */ : acc = !(acc && tmp); break;
    }
  }

  printf("result = %d\n", acc);
  return 0;
}
