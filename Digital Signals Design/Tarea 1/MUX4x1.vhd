library ieee;
use ieee.std_logic_1164.all;

entity mux4x1 is
    port (
        I0, I1, I2, I3 : in  std_logic;
        S               : in  std_logic_vector(1 downto 0); -- S(1)=S1, S(0)=S0
        Y               : out std_logic
    );
end entity mux4x1;

architecture concurrente of mux4x1 is
begin
    -- Selected signal assignment (concurrente): evalúa S y asigna la entrada correspondiente
    with S select
        Y <= I0 when "00",
             I1 when "01",
             I2 when "10",
             I3 when others;  -- cubre "11" y evita el error de "no todos los casos cubiertos"
end architecture concurrente;