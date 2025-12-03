library IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

--Entities
ENTITY segmentosGate IS 
    PORT (
        A,B,C,D: IN std_logic;
        Fa,Fb,Fc,Fd,Fe,Ff,Fg: OUT std_logic
        );
END segmentosGate;

-- Architectures
ARCHITECTURE segmentosBehavior OF segmentosGate IS
BEGIN
    Fa <= ((NOT B) AND (NOT D)) OR A OR C OR (B AND D);
    Fb <= (NOT B) OR ((NOT C ) AND (NOT D)) OR (C AND D);
    Fc <= (NOT C ) OR D OR B;
    Fd <= (C AND (NOT D)) OR A OR ((NOT B) AND (NOT D)) OR (B AND (NOT C) AND D) OR ((NOT B) AND C);
    Fe <= (C AND (NOT D)) OR ((NOT B) AND (NOT D));
    Ff <= ((NOT C) AND (NOT D)) OR (B AND (NOT C)) OR (B AND (NOT D)) OR A;
    Fg<= (B AND (NOT C)) OR A OR (B AND (NOT C)) OR ((NOT B) AND C);
END ARCHITECTURE segmentosBehavior;