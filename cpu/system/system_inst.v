	system u0 (
		.clk_clk              (<connected-to-clk_clk>),              //           clk.clk
		.display_h0_export    (<connected-to-display_h0_export>),    //    display_h0.export
		.display_h1_export    (<connected-to-display_h1_export>),    //    display_h1.export
		.display_m0_export    (<connected-to-display_m0_export>),    //    display_m0.export
		.display_m1_export    (<connected-to-display_m1_export>),    //    display_m1.export
		.display_s0_export    (<connected-to-display_s0_export>),    //    display_s0.export
		.display_s1_export    (<connected-to-display_s1_export>),    //    display_s1.export
		.reset_reset_n        (<connected-to-reset_reset_n>),        //         reset.reset_n
		.alarm_export         (<connected-to-alarm_export>),         //         alarm.export
		.btn_set_alarm_export (<connected-to-btn_set_alarm_export>), // btn_set_alarm.export
		.btn_up_export        (<connected-to-btn_up_export>),        //        btn_up.export
		.btn_down_export      (<connected-to-btn_down_export>)       //      btn_down.export
	);

