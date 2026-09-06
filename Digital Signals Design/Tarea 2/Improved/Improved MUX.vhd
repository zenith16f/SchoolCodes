library ieee;
use ieee.std_logic_1164.all;

entity mux4x1_gen is
    generic (
        N : integer := 2  -- ancho de bits configurable
    );
    port (
        A, B, C, D : in  std_logic_vector(N-1 downto 0);
        SEL        : in  std_logic_vector(1 downto 0);
        DATO       : out std_logic_vector(N-1 downto 0)
    );
end entity mux4x1_gen;

architecture concurrente of mux4x1_gen is
begin
    with SEL select
        DATO <= A when "00",
                B when "01",
                C when "10",
                D when others;
end architecture concurrente;