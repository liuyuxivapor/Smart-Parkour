#
# SoC Based on Cortex-M0 simulation make file
# 
#-----------------------------------------------------------------------------
#
#  Configurations
#

# Simulator type 
SIMULATOR  = verilator

# RTL source
RTL_SRC = $(wildcard ../RTL/*.v)

# verilator option
WARE_IGNORE = --Wno-width --Wno-stmtdly --Wno-initialdly --Wno-combdly --Wno-unoptflat --Wno-pinmissing
VERILATOR_OPTIONS = -DSIMULATION --top-module Cortex_M0_Soc --cc --trace $(WARE_IGNORE)
VERILATOR_VC_OPTIONS = -f ./verilator.vc

.PHONY: compile run sim all gtk compile_verilator sim_verilator run_verilator 
# ------- Simulator redirect -----------

compile : compile_$(SIMULATOR)

run     : run_$(SIMULATOR)

sim     : sim_$(SIMULATOR)

all     : all_$(SIMULATOR)

gtk		:
	gtkwave.exe `wslpath -m ~`/vcd_file/VCortex_M0_Soc/mcutest.vcd &
# ------- verilator -----------
CXX	:= g++
CPP_SRC := ./sim_main.cpp ./sim_uart.cpp
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V|grep VERILATOR_ROOT | head -1 | sed -e " s/^.*=\s*//"')
VROOT   := $(VERILATOR_ROOT)
INCS	:= -I./obj_dir/ -I$(VROOT)/include 
FLAGS	:= -Wall -Og -g -DROOT_VERILATOR -lpthread
GFXFLAGS:= $(FLAGS) `pkg-config gtkmm-3.0 --cflags`
GFXLIBS := `pkg-config gtkmm-3.0 --libs`
CFLAGS  :=  $(GFXFLAGS)
# Compile RTL
compile_verilator : 
	verilator $(VERILATOR_OPTIONS) $(VERILATOR_VC_OPTIONS)

obj_dir:  $(RTL_SRC)
	make compile_verilator --no-print-directory

obj_dir/VCortex_M0_Soc__ALL.a: obj_dir/VCortex_M0_Soc.mk obj_dir
	make -C obj_dir -f VCortex_M0_Soc.mk VCortex_M0_Soc__ALL.a
obj_dir/verilated.o: obj_dir/VCortex_M0_Soc.mk | obj_dir
	@if [ ! -d obj_dir ] ; then \
	  make compile_verilator --no-print-directory; \
	fi
		make -C obj_dir -f VCortex_M0_Soc.mk verilated.o
obj_dir/verilated_vcd_c.o: obj_dir/VCortex_M0_Soc.mk | obj_dir
	@if [ ! -d obj_dir ] ; then \
	  make compile_verilator --no-print-directory; \
	fi
		make -C obj_dir -f VCortex_M0_Soc.mk verilated_vcd_c.o
sim__lcd: 
	verilator -DUNITTEST -CFLAGS -std=c++11 --cc -exe ./sim_lcd/display_controller.v --top-module display_controller ./sim_lcd/sim_lcd.cpp
	make -C obj_dir -f Vdisplay_controller.mk
	./obj_dir/Vdisplay_controller

sim__buzzer:
	xxd -r -p ../Software/keil/buzzer_music.txt ../Software/keil/buzzer_music.hex

sim_main:
	make sim_verilator --no-print-directory

sim_verilator : obj_dir/sim_main.o obj_dir/sim_uart.o obj_dir/VCortex_M0_Soc__ALL.a obj_dir/verilated.o obj_dir/verilated_vcd_c.o
	make sim__lcd sim__buzzer
	g++ -std=c++11 $(CFLAGS) $^ $(GFXLIBS) -o ./sim_main

obj_dir/sim_main.o: ./sim_main.cpp ./testbench.h ./sim_uart.h
obj_dir/sim_uart.o: ./sim_main.cpp ./sim_uart.h

obj_dir/%.o: ./%.cpp | obj_dir
	$(CXX) $(CFLAGS) $(INCS) -c $< -o $@

run_verilator : sim_main
	./sim_main -c 20000 -p 0

all_verilator : 
	make run_verilator

# Remove RTL compile files, log files, software compile files
clean : 
	@if [ -d work ] ; then \
	  rm -rf work ; \
	fi
	@if [ -e tarmac0.log ] ; then \
	  rm tarmac0.log ; \
	fi
	@if [ -e tarmac1.log ] ; then \
	  rm tarmac1.log ; \
	fi
	@if [ -e vsim.wlf ] ; then \
	  rm vsim.wlf ; \
	fi
	@if [ -e image.hex ] ; then \
	  rm image.hex ; \
	fi
	@if [ -e bootloader.hex ] ; then \
	  rm bootloader.hex ; \
	fi
	@if [ -e compile_mti.log ] ; then \
	  rm  compile_mti.log ; \
	fi
	@if [ -e compile_vcs.log ] ; then \
	  rm  compile_vcs.log ; \
	fi
	@if [ -e compile_nc.log ] ; then \
	  rm  compile_nc.log ; \
	fi
	@if [ -e transcript ] ; then \
	  rm  transcript ; \
	fi
	@if [ -e simv ] ; then \
	  rm  simv ; \
	fi
	@if [ -d csrc ] ; then \
	  rm -rf csrc ; \
	fi
	@if [ -d simv.daidir ] ; then \
	  rm -rf simv.daidir ; \
	fi
	@if [ -e inter.vpd ] ; then \
	  rm -rf inter.vpd ; \
	fi
	@if [ -e quit.do ] ; then \
	  rm -rf quit.do ; \
	fi
	@if [ -e ucli.key ] ; then \
	  rm -rf ucli.key ; \
	fi
	@if [ -d DVEfiles ] ; then \
	  rm -rf DVEfiles ; \
	fi
	@if [ -d INCA_libs ] ; then \
	  rm -rf INCA_libs ; \
	fi
	@if [ -d cov_work ] ; then \
	  rm -rf cov_work ; \
	fi
	@if [ -e hdl.var ] ; then \
	  rm -rf hdl.var ; \
	fi
	@if [ -e ncelab.args ] ; then \
	  rm -rf ncelab.args ; \
	fi
	@if [ -e ncvlog.args ] ; then \
	  rm -rf ncvlog.args ; \
	fi
	@if [ -e ncsim.args ] ; then \
	  rm -rf ncsim.args ; \
	fi
	@if [ -e ncprep.log ] ; then \
	  rm -rf ncprep.log ; \
	fi
	@if [ -e ncelab.log ] ; then \
	  rm -rf ncelab.log ; \
	fi
	@if [ -e ncvlog.log ] ; then \
	  rm -rf ncvlog.log ; \
	fi
	@if [ -e ncsim.log ] ; then \
	  rm -rf ncsim.log ; \
	fi
	@if [ -e run.tcl ] ; then \
	  rm -rf run.tcl ; \
	fi
	@if [ -e RUN_NC ] ; then \
	  rm -rf RUN_NC ; \
	fi
	@if [ -e ncsim.key ] ; then \
	  rm -rf ncsim.key ; \
	fi
	@if [ -e cds.lib ] ; then \
	  rm -rf cds.lib ; \
	fi
	@rm -f *.vcd *.log
	@rm -f *.hex
	@rm -rf obj_dir logs
	@if [ -e sim_main ] ; then \
	  rm -rf sim_main ; \
	fi