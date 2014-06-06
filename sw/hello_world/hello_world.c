#include <stdio.h>

int main(int argc, char *argv[]){

  int* startPos = 5242880;
  int* idPos = 5242884;

  // Get this proc id
  unsigned int thisProc = (*idPos);
  printf("Hi from processor MIPS %u!\n", thisProc);

  // Start other proc
  (*startPos) = thisProc+1;

  //exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

