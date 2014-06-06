/**
 * @file      bus.cpp
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
 * @brief     Implements a ac_tlm memory.
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
// Standard includes
// SystemC includes
// ArchC includes

#include "bus.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::bus;

/// Constructor
bus::bus( sc_module_name module_name, int size) :
  sc_module( module_name ),
  DM_port("DM_port", 5242880U),
  supervisor_port("supervisor_port", 5242881U),
  offload_port("offload_port", 5242882U)
{
  target_export = new sc_export< ac_tlm_transport_if >[size];
  /// Binds target_export to the memory
  for (int i=0; i<8; i++) {
    target_export[i]( *this );
  }


}

/// Destructor
bus::~bus() {
  delete [] target_export;
}



