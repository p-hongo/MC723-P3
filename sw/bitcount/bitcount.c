#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 2000000
#define PROCESSORS 8

#define SVR_PROC_START_ADDR 5242880
#define SVR_PROC_ID_ADDR 5242884

int ns[PROCESSORS];
static long int x;
static int terminou;
static int sum;

int bit_count(int myID){
    int ans = 0, j;
    char* str = malloc(30);
    sprintf(str,"%X",x);
    
    int bit_length = strlen(str);
    
    int bit_start = bit_length/PROCESSORS*myID;
    int bit_end = bit_length/PROCESSORS*(1+myID) + (myID+1==PROCESSORS && bit_length%PROCESSORS!=0? bit_length%PROCESSORS : 0);
    //printf(">>> %s %d %d %d\n", str, bit_length, bit_start, bit_end);
    char* local_str = (char*) malloc(bit_length+1);
    strncpy(local_str,str+bit_start,bit_end-bit_start);
    local_str[bit_length] = '\0';
    //printf(">>> %s\n", local_str);
    unsigned long global_x = strtol(local_str, NULL, 16);
    long local_x;
    //chama periferico para offload
    unsigned int * sup = 5242880-4;
    (*sup) = global_x;
    
    //codigo que foi passado para offload
    //  for(j=0;j<LENGTH;j++){
    //    // different cpu processes a certain range of bits. i.e, cpu0 processes 1~16 bits, cpu1 processes 17~32 bits 
    //    local_x = global_x;
    //    if(local_x){
    //        do{
    //            ans++;
    //        }while (0 != (local_x = local_x&(local_x-1))) ;
    //    }
    //  }
    return (*sup);
}

int main(int argc, char *argv[]){

    //unsigned long int inputs[LENGTH];
    int i=0;
    
    unsigned long int n = 1234567890;//atol(*++argv);*/
    
    int* startPos = (int*) SVR_PROC_START_ADDR;
    int* idPos = (int*) SVR_PROC_ID_ADDR;

    // Get this proc id
    unsigned int thisProc = (*idPos);

    // Print proc id
    //printf("Hi from processor MIPS %u!\n", thisProc);

    switch(thisProc){
    case 0:
        //Primeiro processador inicializara os dados a serem computados
        x = n;
        terminou = 0;
        sum = 0;
        sum += bit_count(thisProc);
        for(i=1; i<8; ++i)
        (*startPos) = thisProc+i;
        ++terminou;
        break;
        
    default:
        sum += bit_count(thisProc);
        ++terminou;
        break;
    }    
    
    if(thisProc == 0){
        while(terminou < 8) ;//printf("%d\n", terminou);
        printf("%d times %ld contains %d bit set\n", LENGTH, n, sum);
    }


    //exit(0); // To avoid cross-compiler exit routine
    return 0; // Never executed, just for compatibility
}

