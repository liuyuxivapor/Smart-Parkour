#include <verilated.h>
#include <iostream>
#include <fstream>
#include "VCortex_M0_Soc.h"
#include "testbench.h"
#include "sim_uart.h"
#include "cxxopts.hpp"
using namespace std;

// Global Variable
unsigned long sim_cycle = 15000; // 仿真周期数
bool trace = false;
bool running_trace = false;
int port = 2333;
#define MAX_CYCLE 9999999999

class TB_Cortex_M0_Soc : public TESTBENCH<VCortex_M0_Soc>
{
public:
  UARTSIM m_uart;
  int uart0;
  bool m_running_trace;

public:
  TB_Cortex_M0_Soc(bool running_trace, int port, unsigned long count, bool wave) : m_uart(port), TESTBENCH<VCortex_M0_Soc>(count, wave)
  {
    m_running_trace = running_trace;
    uart0 = 1;
    m_uart.setup(16); // 16 means baudrate for simulation
    opentrace("E:/ciciec/arm/Smart-Parkour/sim/mcutest.vcd");
  }
  void tick(void)
  {
    
    uart0 = m_uart((m_core->TXD));
    m_core->RXD = uart0;
    if (m_running_trace && (!m_trace))
    {
      if (m_uart.check_fifo("!@#$"))
      {
        trace = true;
        opentrace("E:/ciciec/arm/Smart-Parkour/sim/mcutest.vcd");
      }
    }
    TESTBENCH<VCortex_M0_Soc>::tick();
  }

  bool on_tick(void)
  {
    tick();
    if (done())
      exit(0);
    return true;
  }
};

int main(int argc, char **argv)
{
  // arguments init
  cxxopts::Options options("sim_main", "Verilator Simulation.");
  options
      .set_width(70)
      .set_tab_expansion()
      .allow_unrecognised_options()
      .add_options()("c,cycle", "Simulation cycles", cxxopts::value<unsigned long>())("p,port", "Uart TCP port, 0 means stdio", cxxopts::value<int>())("t,trace", "Simulation trace", cxxopts::value<bool>())("r,running_trace", "Simulation running trace", cxxopts::value<bool>())("l,lcd", "Enable LCD simulation,240*320", cxxopts::value<bool>())("h,help", "Print help");
  // arguments parse
  auto result = options.parse(argc, argv);
  if (result.count("help"))
  {
    std::cout << options.help({"", "Group"}) << std::endl;
    exit(0);
  }
  try
  {
    sim_cycle = result["cycle"].as<unsigned long>();
    if (sim_cycle == 0)
      sim_cycle = MAX_CYCLE;
    trace = result["trace"].as<bool>();
    running_trace = result["running_trace"].as<bool>();
    port = result["port"].as<int>();
    if (port > 65535)
      port = 0;
  }
  catch (const cxxopts::OptionException &e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }

  TB_Cortex_M0_Soc *top = new TB_Cortex_M0_Soc(running_trace, port, sim_cycle, trace & (!running_trace));

  top->reset();
  while (!top->done())
  {
    top->tick();
  }
  top->close();
  delete top;
  exit(0);
  return 0;
}