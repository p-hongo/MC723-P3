/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/

// Rodolfo editou aqui
//
const char *project_name="mips1";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include  <systemc.h>
#include  "mips1.H"
#include  "ac_tlm_mem.h"
#include  "bus.h"

using user::ac_tlm_mem;
using user::bus;

int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  mips1 mips1_proc1("mips1");
  mips1 mips1_proc2("mips2");
  ac_tlm_mem mem("mem");
  bus membus("bus");

#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
  ac_trace("mips1_proc2.trace");
#endif 

  mips1_proc1.DM_port(membus.target_export[0]);
  mips1_proc2.DM_port(membus.target_export[1]);
  membus.DM_port(mem.target_export);

  char av1[128];
  strcpy(av1, av[1]);

  mips1_proc1.init(ac, av);
  cerr << endl;

  strcpy(av[1],av1);

  mips1_proc2.init(ac, av);
  mips1_proc2.ac_wait_sig = 1;
  cerr << endl;

  sc_start();

  mips1_proc1.PrintStat();
  cerr << endl;

  mips1_proc2.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  mips1_proc1.ac_sim_stats.time = sc_simulation_time();
  mips1_proc1.ac_sim_stats.print();

  mips1_proc2.ac_sim_stats.time = sc_simulation_time();
  mips1_proc2.ac_sim_stats.print();
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return mips1_proc1.ac_exit_status;
}
