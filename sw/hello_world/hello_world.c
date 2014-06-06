#include <stdio.h>

#define SVR_PROC_START_ADDR 5242880
#define SVR_PROC_ID_ADDR 5242884

int main(int argc, char *argv[]){

  int* startPos = (int*) SVR_PROC_START_ADDR;
  int* idPos = (int*) SVR_PROC_ID_ADDR;

  // Get this proc id
  unsigned int thisProc = (*idPos);

  // Print proc id
  printf("Hi from processor MIPS %u!\n", thisProc);

  // Start other proc
  (*startPos) = thisProc+1;

  //exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

