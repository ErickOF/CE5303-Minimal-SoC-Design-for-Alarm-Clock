# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force C:/Users/Edgar/Documents/Introduccion_Embebidos/Project2/CE5303-Minimal-SoC-Design-for-Alarm-Clock/cpu/software/alarm_clock/mem_init/hdl_sim/system_RAM.dat ./ 
file copy -force C:/Users/Edgar/Documents/Introduccion_Embebidos/Project2/CE5303-Minimal-SoC-Design-for-Alarm-Clock/cpu/software/alarm_clock/mem_init/system_RAM.hex ./ 
