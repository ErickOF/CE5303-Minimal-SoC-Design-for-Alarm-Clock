// system_tb.v

// Generated using ACDS version 18.1 625

`timescale 1 ps / 1 ps
module system_tb (
	);

	wire        system_inst_clk_bfm_clk_clk;                 // system_inst_clk_bfm:clk -> [system_inst:clk_clk, system_inst_reset_bfm:clk]
	wire        system_inst_alarm_export;                    // system_inst:alarm_export -> system_inst_alarm_bfm:sig_export
	wire  [0:0] system_inst_btn_down_bfm_conduit_export;     // system_inst_btn_down_bfm:sig_export -> system_inst:btn_down_export
	wire  [0:0] system_inst_btn_set_bfm_conduit_export;      // system_inst_btn_set_bfm:sig_export -> system_inst:btn_set_export
	wire  [0:0] system_inst_btn_up_bfm_conduit_export;       // system_inst_btn_up_bfm:sig_export -> system_inst:btn_up_export
	wire  [3:0] system_inst_display_h0_export;               // system_inst:display_h0_export -> system_inst_display_h0_bfm:sig_export
	wire  [3:0] system_inst_display_h1_export;               // system_inst:display_h1_export -> system_inst_display_h1_bfm:sig_export
	wire  [3:0] system_inst_display_m0_export;               // system_inst:display_m0_export -> system_inst_display_m0_bfm:sig_export
	wire  [3:0] system_inst_display_m1_export;               // system_inst:display_m1_export -> system_inst_display_m1_bfm:sig_export
	wire  [3:0] system_inst_display_s0_export;               // system_inst:display_s0_export -> system_inst_display_s0_bfm:sig_export
	wire  [3:0] system_inst_display_s1_export;               // system_inst:display_s1_export -> system_inst_display_s1_bfm:sig_export
	wire  [0:0] system_inst_swc_activate_bfm_conduit_export; // system_inst_swc_activate_bfm:sig_export -> system_inst:swc_activate_export
	wire  [0:0] system_inst_swc_sel_bfm_conduit_export;      // system_inst_swc_sel_bfm:sig_export -> system_inst:swc_sel_export
	wire        system_inst_reset_bfm_reset_reset;           // system_inst_reset_bfm:reset -> system_inst:reset_reset_n

	system system_inst (
		.alarm_export        (system_inst_alarm_export),                    //        alarm.export
		.btn_down_export     (system_inst_btn_down_bfm_conduit_export),     //     btn_down.export
		.btn_set_export      (system_inst_btn_set_bfm_conduit_export),      //      btn_set.export
		.btn_up_export       (system_inst_btn_up_bfm_conduit_export),       //       btn_up.export
		.clk_clk             (system_inst_clk_bfm_clk_clk),                 //          clk.clk
		.display_h0_export   (system_inst_display_h0_export),               //   display_h0.export
		.display_h1_export   (system_inst_display_h1_export),               //   display_h1.export
		.display_m0_export   (system_inst_display_m0_export),               //   display_m0.export
		.display_m1_export   (system_inst_display_m1_export),               //   display_m1.export
		.display_s0_export   (system_inst_display_s0_export),               //   display_s0.export
		.display_s1_export   (system_inst_display_s1_export),               //   display_s1.export
		.reset_reset_n       (system_inst_reset_bfm_reset_reset),           //        reset.reset_n
		.swc_activate_export (system_inst_swc_activate_bfm_conduit_export), // swc_activate.export
		.swc_sel_export      (system_inst_swc_sel_bfm_conduit_export)       //      swc_sel.export
	);

	altera_conduit_bfm system_inst_alarm_bfm (
		.sig_export (system_inst_alarm_export)  // conduit.export
	);

	altera_conduit_bfm_0002 system_inst_btn_down_bfm (
		.sig_export (system_inst_btn_down_bfm_conduit_export)  // conduit.export
	);

	altera_conduit_bfm_0002 system_inst_btn_set_bfm (
		.sig_export (system_inst_btn_set_bfm_conduit_export)  // conduit.export
	);

	altera_conduit_bfm_0002 system_inst_btn_up_bfm (
		.sig_export (system_inst_btn_up_bfm_conduit_export)  // conduit.export
	);

	altera_avalon_clock_source #(
		.CLOCK_RATE (50000000),
		.CLOCK_UNIT (1)
	) system_inst_clk_bfm (
		.clk (system_inst_clk_bfm_clk_clk)  // clk.clk
	);

	altera_conduit_bfm_0003 system_inst_display_h0_bfm (
		.sig_export (system_inst_display_h0_export)  // conduit.export
	);

	altera_conduit_bfm_0003 system_inst_display_h1_bfm (
		.sig_export (system_inst_display_h1_export)  // conduit.export
	);

	altera_conduit_bfm_0003 system_inst_display_m0_bfm (
		.sig_export (system_inst_display_m0_export)  // conduit.export
	);

	altera_conduit_bfm_0003 system_inst_display_m1_bfm (
		.sig_export (system_inst_display_m1_export)  // conduit.export
	);

	altera_conduit_bfm_0003 system_inst_display_s0_bfm (
		.sig_export (system_inst_display_s0_export)  // conduit.export
	);

	altera_conduit_bfm_0003 system_inst_display_s1_bfm (
		.sig_export (system_inst_display_s1_export)  // conduit.export
	);

	altera_avalon_reset_source #(
		.ASSERT_HIGH_RESET    (0),
		.INITIAL_RESET_CYCLES (50)
	) system_inst_reset_bfm (
		.reset (system_inst_reset_bfm_reset_reset), // reset.reset_n
		.clk   (system_inst_clk_bfm_clk_clk)        //   clk.clk
	);

	altera_conduit_bfm_0002 system_inst_swc_activate_bfm (
		.sig_export (system_inst_swc_activate_bfm_conduit_export)  // conduit.export
	);

	altera_conduit_bfm_0002 system_inst_swc_sel_bfm (
		.sig_export (system_inst_swc_sel_bfm_conduit_export)  // conduit.export
	);

endmodule
