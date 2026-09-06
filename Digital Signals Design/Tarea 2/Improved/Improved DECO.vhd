library ieee;
use ieee.std_logic_1164.all;
use work.pkg_comparador.all;

entity deco_comp_7seg is
    port (
        COMP : in  std_logic_vector(1 downto 0);
        SEG  : out std_logic_vector(6 downto 0)
    );
end entity deco_comp_7seg;

architecture comportamiento of deco_comp_7seg is
begin
    with COMP select
        SEG <= SEG_IGUAL when COMP_IGUAL,
               SEG_MAYOR when COMP_MAYOR,
               SEG_MENOR when COMP_MENOR,
               SEG_OFF   when others;
end architecture comportamiento;