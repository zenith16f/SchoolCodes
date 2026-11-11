library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Practica4 is
    generic (
        -- Con CLK = 27 MHz:  f_out = 27e6 / (2 * (DIVISOR + 1))
        DIV1 : integer := 13499999;   -- DIVF1:   1 Hz
        DIV2 : integer := 134999;     -- DIVF2: 100 Hz
        DIV3 : integer := 2699999;    -- DIVF3:   5 Hz
        DIV4 : integer := 13499       -- DIVF4:   1 kHz
    );
    port (
        clk : in  std_logic;
        clr : in  std_logic;
        sel : in  std_logic_vector(1 downto 0);
        q   : out std_logic_vector(1 downto 0)
    );
end entity;

architecture ArchPractica4 of Practica4 is

component DIVF is
        generic ( DIVISOR : integer );
        port (
            CLK    : in  std_logic;
            CLR    : in  std_logic;
            CLKOUT : out std_logic
        );
    end component;


    component MUX4x1 is
        port (
            I0, I1, I2, I3 : in  std_logic;
            SEL            : in  std_logic_vector(1 downto 0);
            Y              : out std_logic
        );
    end component;
 
    signal f1, f2, f3, f4 : std_logic;
    signal f_sel          : std_logic;
begin

    
    U_DIVF1: DIVF generic map (DIVISOR => DIV1) port map (CLK => clk, CLR => clr, CLKOUT => f1);
    U_DIVF2: DIVF generic map (DIVISOR => DIV2) port map (CLK => clk, CLR => clr, CLKOUT => f2);
    U_DIVF3: DIVF generic map (DIVISOR => DIV3) port map (CLK => clk, CLR => clr, CLKOUT => f3);
    U_DIVF4: DIVF generic map (DIVISOR => DIV4) port map (CLK => clk, CLR => clr, CLKOUT => f4);

    U_MUX: MUX4x1 port map (I0 => f1, I1 => f2, I2 => f3, I3 => f4, SEL => sel, Y => f_sel);

    q(1) <= f_sel;
    q(0) <= not f_sel;
    
end architecture;