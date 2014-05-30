#include "supervisor.h"

using user::supervisor;

/// Constructor
supervisor::supervisor( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{

  target_export( *this );
}

/// Destructor
supervisor::~supervisor() {

}


ac_tlm_rsp_status supervisor::writem( const uint32_t &a , const uint32_t &d )
{
  if (a >= 5242880) {
    if( *((uint32_t *) &d) == 0) printf("HUEHUUEHUEHUEHEUH\n");
  }
  return SUCCESS;
}

ac_tlm_rsp_status supervisor::readm( const uint32_t &a , uint32_t &d )
{
  return SUCCESS;
}

