onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand -group Time -label H1 -radix unsigned /system_tb/system_inst_display_h1_export
add wave -noupdate -expand -group Time -label H0 -radix unsigned /system_tb/system_inst_display_h0_export
add wave -noupdate -expand -group Time -label M1 -radix unsigned /system_tb/system_inst_display_m1_export
add wave -noupdate -expand -group Time -label M0 -radix unsigned /system_tb/system_inst_display_m0_export
add wave -noupdate -expand -group Time -label S1 -radix unsigned /system_tb/system_inst_display_s1_export
add wave -noupdate -expand -group Time -label S0 -radix unsigned /system_tb/system_inst_display_s0_export
add wave -noupdate -expand -group Input -label SET_BUTTON /system_tb/system_inst_btn_set_bfm_conduit_export
add wave -noupdate -expand -group Input -label UP_BUTTON /system_tb/system_inst_btn_up_bfm_conduit_export
add wave -noupdate -expand -group Input -label DOWN_BUTTON /system_tb/system_inst_btn_down_bfm_conduit_export
add wave -noupdate -expand -group Input -label ALARM_SWITCH /system_tb/system_inst_swc_activate_bfm_conduit_export
add wave -noupdate -expand -group Input -label SEL_SWITCH /system_tb/system_inst_swc_sel_bfm_conduit_export
add wave -noupdate -label {ALARM SIGNAL} /system_tb/system_inst_alarm_export
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {4020281361 ps} 0} {{Cursor 2} {5389605381 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {5760604500 ps}
