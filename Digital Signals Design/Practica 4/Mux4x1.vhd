library ieee;
use ieee.std_logic_1164.all;

entity MUX4x1 is
    port (
        I0, I1, I2, I3 : in  std_logic;
        SEL            : in  std_logic_vector(1 downto 0);
        Y              : out std_logic
    );
end entity;

architecture ArchMUX of MUX4x1 is
begin
    with SEL select
        Y <= I0 when "00",
             I1 when "01",
             I2 when "10",
             I3 when others;
end architecture;