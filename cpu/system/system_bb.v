
module system (
	clk_clk,
	reset_reset_n,
	display_h1_export,
	display_h0_export,
	display_m1_export,
	display_m0_export,
	display_s1_export,
	display_s0_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[3:0]	display_h1_export;
	output	[3:0]	display_h0_export;
	output	[3:0]	display_m1_export;
	output	[3:0]	display_m0_export;
	output	[3:0]	display_s1_export;
	output	[3:0]	display_s0_export;
endmodule
