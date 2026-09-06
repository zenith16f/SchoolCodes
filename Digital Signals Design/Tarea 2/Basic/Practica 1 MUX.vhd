library ieee;
use ieee.std_logic_1164.all;

entity mux4x1_2bit is
    port (
        A, B, C, D : in  std_logic_vector(1 downto 0);
        SEL        : in  std_logic_vector(1 downto 0);
        DATO       : out std_logic_vector(1 downto 0)
    );
end entity mux4x1_2bit;

architecture concurrente of mux4x1_2bit is
begin
    with SEL select
        DATO <= A when "00",
                B when "01",
                C when "10",
                D when others;
end architecture concurrente;