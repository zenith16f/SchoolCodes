library ieee;
use ieee.std_logic_1164.all;

entity comparador3bit is
    port (
        A, B  : in  std_logic_vector(2 downto 0);
        mayor : out std_logic;
        menor : out std_logic;
        igual : out std_logic
    );
end entity comparador3bit;

architecture secuencial of comparador3bit is
begin
    process(A, B)
    begin
        if A > B then
            mayor <= '1';
            menor <= '0';
            igual <= '0';
        elsif A < B then
            mayor <= '0';
            menor <= '1';
            igual <= '0';
        else
            mayor <= '0';
            menor <= '0';
            igual <= '1';
        end if;
    end process;
end architecture secuencial;