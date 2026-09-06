library ieee;
use ieee.std_logic_1164.all;

entity deco is
    port (
        COMP : in  std_logic_vector(1 downto 0);
        SEG  : out std_logic_vector(6 downto 0)  -- orden: a b c d e f g
    );
end entity deco;

architecture comportamiento of deco is
begin
    with COMP select
        SEG <= "0001001" when "00", -- igual  =
               "0001101" when "01", -- mayor  >
               "0011001" when "10", -- menor  <
               "0000000" when others;
end architecture comportamiento;