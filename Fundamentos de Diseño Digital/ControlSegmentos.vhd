-- Libraries
library IEEE;
USE IEEE.std_logic_1164.all;

-- Entities
ENTITY controlSegmentoGate IS
    PORT (
        A,B,C,D: IN std_logic;
        control: IN std_logic;
        output: OUT std_logic_vector(6 DOWNTO 0)
    );
END controlSegmentoGate;

-- Architectures
ARCHITECTURE controlSegmentoBehavior OF controlSegmentoGate IS
    SIGNAL inputVector: std_logic_vector(3 DOWNTO 0);
    SIGNAL Fa, Fb, Fc, Fd, Fe, Ff, Fg: std_logic;

BEGIN
    inputVector <= A & B & C & D;

    -- Proceso principal de control
    PROCESS(inputVector, control)
    BEGIN
        IF control = '1' THEN
            -- BCD a 7 segmentos
            Fa <= ((NOT A) AND C) OR ((NOT A) AND B AND C) OR (A AND (NOT B) AND (NOT C)) OR ((NOT B) AND (NOT C) AND (NOT D));
            Fb <= ((NOT B) AND (NOT C)) OR ((NOT A) AND (NOT C) AND (NOT D)) OR ((NOT A) AND (NOT B)) OR ((NOT A) AND C AND D);
            Fc <= ((NOT B) AND (NOT C)) OR ((NOT A) AND B) OR ((NOT A) AND D);
            Fd <= (A AND (NOT C) AND (NOT D)) OR ((NOT A) AND B AND (NOT C) AND D) OR ((NOT A) AND (NOT B) AND C) OR ((NOT A) AND C AND (NOT D)) OR (A AND (NOT B) AND (NOT C));
            Fe <= ((NOT B) AND (NOT C) AND (NOT D)) OR ((NOT A) AND C AND (NOT D));
            Ff <= (A AND (NOT B) AND (NOT C)) OR ((NOT B) AND (NOT C) AND (NOT D)) OR ((NOT A) AND B AND(NOT C)) OR ((NOT A) AND B AND (NOT D));
            Fg <= (B AND (NOT C)) OR A OR ((NOT B) AND C);
        ELSE
            -- BIN a 7 segmentos
            Fa <= ((NOT B) AND (NOT D)) OR (A AND C) OR (A AND (NOT B) AND (NOT C)) OR ((NOT B) AND (NOT C) AND (NOT D));
            Fb <= ((NOT A) AND B AND (NOT C)) OR (A AND (NOT C)) OR ((NOT A) AND (NOT B) AND C AND D) OR ((NOT A) AND C AND (NOT D));
            Fc <= ((NOT A) AND (NOT D)) OR (B AND (NOT C)) OR ((NOT B) AND C AND (NOT D)) OR (B AND C AND (NOT D));
            Fd <= (A AND B) OR ((NOT C) AND D) OR ((NOT B) AND (NOT C) AND (NOT D)) OR (C AND (NOT D));
            Fe <= (C AND (NOT D)) OR ((NOT A) AND (NOT B));
            Ff <= ((NOT A) AND C) OR ((NOT B) AND (NOT C)) OR (A AND (NOT D)) OR ((NOT A) AND B AND (NOT D));
            Fg <= ((NOT A) AND B AND C) OR (A AND (NOT D)) OR (C AND (NOT D)) OR (B AND (NOT D));
        END IF;
    END PROCESS;

    -- Asignar output
    output <= Fg & Ff & Fe & Fd & Fc & Fb & Fa;

END controlSegmentoBehavior;