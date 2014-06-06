#include "supervisor.h"

using user::supervisor;

/// Constructor
supervisor::supervisor( sc_module_name module_name, int size) :
  sc_module( module_name ),
  target_export("iport")
{
  num_processors = 0;
  /// Initialize memory vector
  int k = 128;
  memory = new uint8_t[ k ];
  for(k=k-1;k>0;k--) memory[k]=0;
  target_export( *this );

  processorList = new mips1_p[size];
  for (int i=0; i<size; i++) {
    processorList[i] = NULL;
  }

}

/// Destructor
supervisor::~supervisor() {
  delete [] memory;
}

void supervisor::addProcessor (mips1* processor) {
  processorList[num_processors] = processor;
  num_processors++;
}


ac_tlm_rsp_status supervisor::writem( const uint32_t &a , const uint32_t &d )
{
  uint32_t actualAddress = a-5242880;
  if (actualAddress >= 0) {
    if(d < num_processors) {
      processorList[d]->ac_wait_sig = 0;
    }
  }
  return SUCCESS;
}

ac_tlm_rsp_status supervisor::readm( const uint32_t &a , uint32_t &d )
{
  return SUCCESS;
}

