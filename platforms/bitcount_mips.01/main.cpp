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
#include  "supervisor.h"
#include  "offload.h"

using user::ac_tlm_mem;
using user::bus;
using user::supervisor;
using user::offload;

int sc_main(int ac, char *av[])
{

  int num_processors = 8;

  mips1_p* processorList;
  processorList = new mips1_p[num_processors];

  //!  ISA simulator
  mips1 mips1_proc1("mips1");
  mips1 mips1_proc2("mips2");
  mips1 mips1_proc3("mips3");
  mips1 mips1_proc4("mips4");
  mips1 mips1_proc5("mips5");
  mips1 mips1_proc6("mips6");
  mips1 mips1_proc7("mips7");
  mips1 mips1_proc8("mips8");

  processorList[0] = &mips1_proc1;
  processorList[1] = &mips1_proc2;
  processorList[2] = &mips1_proc3;
  processorList[3] = &mips1_proc4;
  processorList[4] = &mips1_proc5;
  processorList[5] = &mips1_proc6;
  processorList[6] = &mips1_proc7;
  processorList[7] = &mips1_proc8;

  ac_tlm_mem mem("mem");

  bus membus("bus",num_processors);

  supervisor visor("supervisor", num_processors);
  for (int i=0; i<num_processors; i++) {
    visor.addProcessor(processorList[i]);
  }
  offload off("offload");

#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
  ac_trace("mips1_proc2.trace");
#endif 


  for (int i=0; i<num_processors; i++) {
    processorList[i]->DM_port(membus.target_export[i]);
  }

  membus.DM_port(mem.target_export);
  membus.supervisor_port(visor);
  membus.offload_port(off);

  char av1[128];
  strcpy(av1, av[1]);

  mips1_proc1.init(ac, av);
  cerr << endl;

  strcpy(av[1],av1);

  for (int i=1; i<num_processors; i++) {
    strcpy(av[1],av1);
    processorList[i]->init(ac, av);
    processorList[i]->ac_wait_sig = 1;
    cerr << endl;
  }

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