#include "supervisor.h"
#include "endian.h"

using user::supervisor;

/// Constructor
supervisor::supervisor( sc_module_name module_name, int size) :
  sc_module( module_name ),
  target_export("iport")
{
  num_processors = 0;

  /// Initialize memory vector
  int k = 4;
  memory = new int[ k ];
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
  int actualAddress = (a-5242880)/4;

  int val = be32toh(d);

  if (actualAddress < 0) return SUCCESS;

  if (actualAddress == 0) {
    if(val < num_processors) {
      processorList[val]->ac_wait_sig = 0;
    }
  } else if (actualAddress < 4) {
    memory[actualAddress] = val;
  }
  return SUCCESS;
}

ac_tlm_rsp_status supervisor::readm( const uint32_t &a , uint32_t &d )
{
  int actualAddress = (a-5242880)/4;

  *((uint32_t *) &d) = (uint32_t) htobe32(memory[actualAddress]);

  // PROC COUNT & MUTEX
  // ANY ADDRESS OVER 0 INCREASES ON READ
  // ONLY FIRST GET 0 -> MUTEX
  // WRITE 0 TO UNLOCK
  // EVERYONE ELSE GETS A DIFFERENT (INCREASING) NUMBER
  if (actualAddress > 0) {
    memory[actualAddress]++;
  }
  return SUCCESS;
}

