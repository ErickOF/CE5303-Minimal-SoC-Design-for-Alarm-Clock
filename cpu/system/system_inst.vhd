	component system is
		port (
			clk_clk           : in  std_logic                    := 'X'; -- clk
			reset_reset_n     : in  std_logic                    := 'X'; -- reset_n
			display_h1_export : out std_logic_vector(3 downto 0);        -- export
			display_h0_export : out std_logic_vector(3 downto 0);        -- export
			display_m1_export : out std_logic_vector(3 downto 0);        -- export
			display_m0_export : out std_logic_vector(3 downto 0);        -- export
			display_s1_export : out std_logic_vector(3 downto 0);        -- export
			display_s0_export : out std_logic_vector(3 downto 0)         -- export
		);
	end component system;

	u0 : component system
		port map (
			clk_clk           => CONNECTED_TO_clk_clk,           --        clk.clk
			reset_reset_n     => CONNECTED_TO_reset_reset_n,     --      reset.reset_n
			display_h1_export => CONNECTED_TO_display_h1_export, -- display_h1.export
			display_h0_export => CONNECTED_TO_display_h0_export, -- display_h0.export
			display_m1_export => CONNECTED_TO_display_m1_export, -- display_m1.export
			display_m0_export => CONNECTED_TO_display_m0_export, -- display_m0.export
			display_s1_export => CONNECTED_TO_display_s1_export, -- display_s1.export
			display_s0_export => CONNECTED_TO_display_s0_export  -- display_s0.export
		);

