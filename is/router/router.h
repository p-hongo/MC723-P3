/**
 * @file      router.h
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Defines a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef router_H_
#define router_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include  "ac_tlm_port.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

/// Namespace to isolate memory from ArchC
namespace user
{

  /// A TLM memory
  class router :
    public sc_module,
    public ac_tlm_transport_if // Using ArchC TLM protocol
  {
    public:
      /// Exposed port with ArchC interface
      sc_export< ac_tlm_transport_if > target_export[8];

      ac_tlm_port DM_port;

      /**
       * Implementation of TLM transport method that
       * handle packets of the protocol doing apropriate actions.
       * This method must be implemented (required by SystemC TLM).
       * @param request is a received request packet
       * @return A response packet to be send
       */
      ac_tlm_rsp transport( const ac_tlm_req &request ) {
        return DM_port->transport(request);
      }


      /**
       * Default constructor.
       *
       * @param k Memory size in kilowords.
       *
       */
      router( sc_module_name module_name);

      /**
       * Default destructor.
       */
      ~router();

    private:

  };

};

#endif //router_H_
