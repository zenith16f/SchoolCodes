library ieee;
use ieee.std_logic_1164.all;

entity sumCom is
    port(
        x, y: in std_logic;
        s: out std_logic;
        cs: out std_logic;
        c: in std_logic
    );
end sumCom;

architecture codigo of sumCom is
begin
    s <= (x xor y xor c);
    cs <= (x and y) or (c and (x or y));
end codigo;