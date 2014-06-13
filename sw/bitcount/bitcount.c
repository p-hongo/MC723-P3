#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 2000000
#define PROCESSORS 8

#define SVR_PROC_START_ADDR 5242880
#define SVR_PROC_ID_ADDR 5242884
#define SVR_PROC_LOCK_ADDR_0 5242888
#define SVR_PROC_LOCK_ADDR_1 5242892

int ns[PROCESSORS];
static long int x;
static int terminou;
static int sum;

int getLock (int lockNumber) {
  // Pega o lock ou trava até pegar
  int* lockPos = lockNumber ? (int*) SVR_PROC_LOCK_ADDR_0 : (int*) SVR_PROC_LOCK_ADDR_1;
  while ((*lockPos) != 0) ;
}

int freeLock (int lockNumber) {
   // Libera o lock
  int* lockPos = lockNumber ? (int*) SVR_PROC_LOCK_ADDR_0 : (int*) SVR_PROC_LOCK_ADDR_1;
  (*lockPos) = 0;
}

int bit_count(int myID){
  int ans = 0, j;
  char* str = malloc(30);
  sprintf(str,"%X",x);

  int bit_length = strlen(str);

  int bit_start = bit_length/PROCESSORS*myID;
  int bit_end = bit_length/PROCESSORS*(1+myID) + (myID+1==PROCESSORS && bit_length%PROCESSORS!=0? bit_length%PROCESSORS : 0);
  char* local_str = (char*) malloc(bit_length+1);
  strncpy(local_str,str+bit_start,bit_end-bit_start);
  local_str[bit_length] = '\0';

  unsigned long global_x = strtol(local_str, NULL, 16);
  long local_x;

  getLock(0);

  // Realiza operação usando offload
  unsigned int * sup = (unsigned int*) (5242880-4);
  (*sup) = global_x;
  int retValue = (*sup);

  freeLock(0);

  return retValue;
}

int main(int argc, char *argv[]){

  //unsigned long int inputs[LENGTH];
  int i=0;

  unsigned long int n = 1234567890;//atol(*++argv);*/

  int* startPos = (int*) SVR_PROC_START_ADDR;
  int* idPos = (int*) SVR_PROC_ID_ADDR;

  // Get this proc id
  unsigned int thisProc = (*idPos);
  int result = 0;

  switch(thisProc){
    case 0:
      //Primeiro processador inicializara os dados a serem computados
      x = n;
      terminou = 0;
      sum = 0;
      for(i=1; i<8; ++i)
        (*startPos) = thisProc+i;

    default:
      result = bit_count(thisProc);
      getLock(1);
      sum += result;
      ++terminou;
      freeLock(1);
      break;
  }    

  if(thisProc == 0){
    while(terminou < 8) ;
    printf("%d times %ld contains %d bit set\n", LENGTH, n, sum);
  }


  // exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

