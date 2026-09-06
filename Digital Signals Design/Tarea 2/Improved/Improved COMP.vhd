library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.pkg_comparador.all;

entity comparador_gen is
    generic (
        N : integer := 2
    );
    port (
        DATO : in  std_logic_vector(N-1 downto 0);
        REF  : in  std_logic_vector(N-1 downto 0);
        COMP : out std_logic_vector(1 downto 0)
    );
end entity comparador_gen;

architecture secuencial of comparador_gen is
begin
    process(DATO, REF)
    begin
        if unsigned(DATO) = unsigned(REF) then
            COMP <= COMP_IGUAL;
        elsif unsigned(DATO) > unsigned(REF) then
            COMP <= COMP_MAYOR;
        else
            COMP <= COMP_MENOR;
        end if;
    end process;
end architecture secuencial;