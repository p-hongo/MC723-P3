#include "offload.h"
#include <endian.h>

using user::offload;

/// Constructor
offload::offload( sc_module_name module_name) :
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
      int resp = 1;
      int x = be32toh(d);
      printf(">>%d\n", x);
      for(int i = 1; i <=x; ++i) resp *= i;
      //if( *((uint32_t *) &d) == 0) 
      //printf("LOLOLOLOLOLOLOLOL\n");
      printf("--%d\n", resp);

  }
  return SUCCESS;
}

ac_tlm_rsp_status offload::readm( const uint32_t &a , uint32_t &d )
{
  return SUCCESS;
}

