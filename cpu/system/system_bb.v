
module system (
	alarm_export,
	btn_down_export,
	swc_sel_export,
	btn_set_export,
	btn_up_export,
	clk_clk,
	display_h0_export,
	display_h1_export,
	display_m0_export,
	display_m1_export,
	display_s0_export,
	display_s1_export,
	reset_reset_n,
	swc_activate_export);	

	output		alarm_export;
	input		btn_down_export;
	input		swc_sel_export;
	input		btn_set_export;
	input		btn_up_export;
	input		clk_clk;
	output	[3:0]	display_h0_export;
	output	[3:0]	display_h1_export;
	output	[3:0]	display_m0_export;
	output	[3:0]	display_m1_export;
	output	[3:0]	display_s0_export;
	output	[3:0]	display_s1_export;
	input		reset_reset_n;
	input		swc_activate_export;
endmodule
