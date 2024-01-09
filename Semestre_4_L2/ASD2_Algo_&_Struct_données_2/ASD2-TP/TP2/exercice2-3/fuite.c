
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int fuite() {
    static int* pIntNull;
    static int* pInt;

    pIntNull = malloc(sizeof(int));
    pIntNull = NULL; 
    
    pInt = malloc(sizeof(int));

    // free(pIntNull);
    // free(pInt);
    return 0;
}

int main()
{
    fuite();
    return 0;
}


// $ valgrind gcc -Wall -Wextra fuite.c -o fuite
/*
==5921== Memcheck, a memory error detector
==5921== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5921== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5921== Command: gcc -Wall -Wextra fuite.c -o fuite
==5921== 
==5921== 
==5921== HEAP SUMMARY:
==5921==     in use at exit: 176,487 bytes in 107 blocks
==5921==   total heap usage: 432 allocs, 325 frees, 237,091 bytes allocated
==5921== 
==5921== LEAK SUMMARY:
==5921==    definitely lost: 6,195 bytes in 40 blocks
==5921==    indirectly lost: 82 bytes in 5 blocks
==5921==      possibly lost: 0 bytes in 0 blocks
==5921==    still reachable: 170,210 bytes in 62 blocks
==5921==         suppressed: 0 bytes in 0 blocks
==5921== Rerun with --leak-check=full to see details of leaked memory
==5921== 
==5921== For lists of detected and suppressed errors, rerun with: -s
==5921== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/




// $ valgrind --leak-check=full --show-reachable=yes ./fuite
/*
==7684== Memcheck, a memory error detector
==7684== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7684== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==7684== Command: ./fuite
==7684== 
==7684== 
==7684== HEAP SUMMARY:
==7684==     in use at exit: 8 bytes in 2 blocks
==7684==   total heap usage: 2 allocs, 0 frees, 8 bytes allocated
==7684== 
==7684== 4 bytes in 1 blocks are still reachable in loss record 1 of 2
==7684==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7684==    by 0x109176: fuite (in /home/viet/Documents/Option_Paris8_Informatique/Semestre_2_L2/Algo_&_struct_données_2/ASD2-TP/TP2/exercice2-3/fuite)
==7684==    by 0x109196: main (in /home/viet/Documents/Option_Paris8_Informatique/Semestre_2_L2/Algo_&_struct_données_2/ASD2-TP/TP2/exercice2-3/fuite)
==7684== 
==7684== 4 bytes in 1 blocks are definitely lost in loss record 2 of 2
==7684==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7684==    by 0x10915A: fuite (in /home/viet/Documents/Option_Paris8_Informatique/Semestre_2_L2/Algo_&_struct_données_2/ASD2-TP/TP2/exercice2-3/fuite)
==7684==    by 0x109196: main (in /home/viet/Documents/Option_Paris8_Informatique/Semestre_2_L2/Algo_&_struct_données_2/ASD2-TP/TP2/exercice2-3/fuite)
==7684== 
==7684== LEAK SUMMARY:
==7684==    definitely lost: 4 bytes in 1 blocks
==7684==    indirectly lost: 0 bytes in 0 blocks
==7684==      possibly lost: 0 bytes in 0 blocks
==7684==    still reachable: 4 bytes in 1 blocks
==7684==         suppressed: 0 bytes in 0 blocks
==7684== 
==7684== For lists of detected and suppressed errors, rerun with: -s
==7684== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

*/


