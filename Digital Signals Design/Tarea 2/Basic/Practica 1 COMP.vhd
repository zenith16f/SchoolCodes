library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;  -- necesaria para comparar como magnitud, no bit a bit

entity comparador2bit is
    port (
        DATO : in  std_logic_vector(1 downto 0);
        REF  : in  std_logic_vector(1 downto 0);
        COMP : out std_logic_vector(1 downto 0)  -- "00"=igual, "01"=mayor, "10"=menor
    );
end entity comparador2bit;

architecture secuencial of comparador2bit is
begin
    process(DATO, REF)
    begin
        if unsigned(DATO) = unsigned(REF) then
            COMP <= "00";
        elsif unsigned(DATO) > unsigned(REF) then
            COMP <= "01";
        else
            COMP <= "10";
        end if;
    end process;
end architecture secuencial;