#include "offload.h"
#include <endian.h>

using user::offload;

/// Constructor
offload::offload( sc_module_name module_name, int k) :
  sc_module( module_name ),
  target_export("iport")
{

  target_export( *this );

   /// Initialize memory vector
  memory = new uint8_t[ 1 ];
  memory[0]=0;
}

/// Destructor
offload::~offload() {
     delete [] memory;
}


ac_tlm_rsp_status offload::writem( const uint32_t &a , const uint32_t &d )
{
  if (a == 5242876) {
      int j;
      int global_x = be32toh(d);
      long local_x;
      int ans = 0;
      //printf("   offload>> numero a ser calculado: %d\n", global_x);

      int LENGTH = 2000000;
      for(j=0;j<LENGTH;j++){
          // different cpu processes a certain range of bits. i.e, cpu0 processes 1~16 bits, cpu1 processes 17~32 bits 
          local_x = global_x;
          if(local_x){
              do{
                  ans++;
              }while (0 != (local_x = local_x&(local_x-1))) ;
          }
      }
      //printf("   offload>> numero de bits: %d\n", ans);
      ans = htobe32(ans);
      *((uint32_t *) &memory[a]) = *((uint32_t *) &ans);     
  }
  return SUCCESS;
}

ac_tlm_rsp_status offload::readm( const uint32_t &a , uint32_t &d )
{
    *((uint32_t *) &d) = *((uint32_t *) &memory[a]);
    return SUCCESS;
}

