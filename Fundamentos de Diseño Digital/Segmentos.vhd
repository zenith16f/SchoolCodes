--Libraries
library IEEE;
use IEEE.std_logic_1164.all;

-- Entities
ENTITY segmentosGate IS
	PORT (
		A,B,C,D: IN std_logic;
		Fa,Fb,Fc,Fd,Fe,Ff,Fg: OUT std_logic
		);
END segmentosGate;

-- Architectures
ARCHITECTURE segmentosBehavior OF segmentosGate IS
BEGIN
	Fa<= ((NOT B) AND (NOT D)) OR (B AND C) OR ((NOT A) AND C) OR ((NOT A) AND B AND D) OR (A AND (NOT B ) AND (NOT C) ) OR (A AND (NOT D));
	Fb<= ((NOT B) AND (NOT D)) OR ((NOT A) AND C AND D) OR ((NOT A) AND (NOT C) AND (NOT D)) OR ((NOT B) AND (NOT C)) OR (A AND (NOT C) AND D);
	Fc<= ((NOT A) AND B) OR (A AND (NOT B)) OR ((NOT C) AND D) OR ((NOT A) AND (NOT C)) OR ((NOT A) AND D);
	Fd<= (A AND (NOT C)) OR (B AND C AND (NOT D)) OR ((NOT A) AND (NOT B) AND (NOT D)) OR ((NOT B) AND C AND D) OR (B AND (NOT C) AND D);
	Fe<= ((NOT B) AND (NOT D)) OR (A AND C) OR (A AND B) OR (C AND (NOT D));
	Ff<= (A AND C) OR (A AND (NOT B)) OR (B AND (NOT D)) OR ((NOT A) AND B AND (NOT C)) OR ((NOT C) AND (NOT D));
	Fg<= ((NOT A) AND B AND (NOT C)) OR (A AND D) OR (A AND (NOT B)) OR ((NOT B) AND C) OR (C AND (NOT D));
END ARCHITECTURE segmentosBehavior;