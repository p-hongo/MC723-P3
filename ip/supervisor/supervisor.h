//////////////////////////////////////////////////////////////////////////////

#ifndef supervisor_H_
#define supervisor_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"
#include "../../processors/mips1/mips1.H"

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

typedef mips1* mips1_p;

/// Namespace to isolate memory from ArchC
namespace user
{


  class supervisor :
    public sc_module,
    public ac_tlm_transport_if // Using ArchC TLM protocol
  {
    public:

      /// Exposed port with ArchC interface
      sc_export< ac_tlm_transport_if > target_export;
      /// Internal write
      ac_tlm_rsp_status writem( const uint32_t & , const uint32_t & );
      /// Internal read
      ac_tlm_rsp_status readm( const uint32_t & , uint32_t & );

      /**
       * Implementation of TLM transport method that
       * handle packets of the protocol doing apropriate actions.
       * This method must be implemented (required by SystemC TLM).
       * @param request is a received request packet
       * @return A response packet to be send
       */
      ac_tlm_rsp transport( const ac_tlm_req &request ) {

        ac_tlm_rsp response;

        switch( request.type ) {
          case READ :     // Packet is a READ one
#ifdef DEBUG  // Turn it on to print transport level messages
            cout << response.data << endl;
#endif
            response.status = readm( request.addr , response.data );
            break;
          case WRITE:     // Packet is a WRITE
#ifdef DEBUG
            cout << request.data << endl;
#endif
            response.status = writem( request.addr , request.data );
            break;
          default :
            response.status = ERROR;
            break;
        }

        return response;
      }



      supervisor( sc_module_name module_name, int size);

      ~supervisor();

      void addProcessor (mips1* processor);

    private:
      int *memory;
      mips1_p* processorList;
      int num_processors;


  };

};

#endif //supervisor_H_
