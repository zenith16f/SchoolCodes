-- Libraries
library ieee;
use ieee.std_logic_1164.all;

-- Entities
entity Comparador is
	Port(
	A1,A0,B1,B0: in std_logic;
	F1,F2,F3: out std_logic
	);
end Comparador;

-- Architectures
architecture ArchComparador of Comparador is
begin
	F1<=(A1 and not B1) or (A0 and (not B1) and (not B0)) or (A1 and A0 and B0);
	F2<=((not A1) and B1) or ((not A1) and (not A0) and B1) or ((not A0) and B1 and B0);
	F3<=(A0 Xnor B0) and (A1 Xnor B1);
end ArchComparador;