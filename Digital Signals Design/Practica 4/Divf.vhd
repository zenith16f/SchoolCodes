library ieee;
use ieee.std_logic_1164.all;

entity Divf is
    generic (
        divisor: integer := 13499999
    );
    port (
        CLK   : in std_logic;
        CLR : in std_logic;
        clkout : out std_logic
        
    );
end entity;

architecture archDivf of Divf is
    signal contador : integer range 0 to divisor := 0;
    signal clk_i : std_logic := '0';

begin

    process (clk,CLR)
    begin
      if (CLR = '0') then
            contador <= 0;
            clk_i    <= '0';
        elsif rising_edge(CLK) then
            if (contador = DIVISOR) then
                contador <= 0;
                clk_i    <= not clk_i;
            else
                contador <= contador + 1;
            end if;
        end if;
    end process;

    CLKOUT <= clk_i;

end architecture;