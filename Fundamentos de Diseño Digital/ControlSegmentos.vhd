-- Libraries
library IEEE;
use IEEE.std_logic_1164.all;

-- Entity
ENTITY controlSegmentoGate IS
    PORT (
        A,B,C,D: IN std_logic;
        control: IN std_logic;
        Fa, Fb, Fc, Fd, Fe, Ff, Fg: OUT std_logic
    );
END controlSegmentoGate;

-- Architecture
ARCHITECTURE controlSegmentoBehavior OF controlSegmentoGate IS
    SIGNAL input: std_logic_vector(4 DOWNTO 0);
BEGIN
    input <= control & A & B & C & D;
    
    -- Segmento A
    Fa <= '1' when input="10000" else  -- BCD: 0
          '1' when input="10010" else  -- BCD: 2
          '1' when input="10011" else  -- BCD: 3
          '1' when input="10101" else  -- BCD: 5
          '1' when input="10110" else  -- BCD: 6
          '1' when input="10111" else  -- BCD: 7
          '1' when input="11000" else  -- BCD: 8
          '1' when input="11001" else  -- BCD: 9
          '1' when input="00000" else  -- BIN: 0
          '1' when input="00010" else  -- BIN: 2
          '1' when input="00011" else  -- BIN: 3
          '1' when input="00101" else  -- BIN: 5
          '1' when input="00110" else  -- BIN: 6
          '1' when input="00111" else  -- BIN: 7
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01001" else  -- BIN: 9
          '1' when input="01010" else  -- BIN: 10
          '1' when input="01100" else  -- BIN: 12
          '1' when input="01110" else  -- BIN: 14
          '1' when input="01111" else  -- BIN: 15
          '0';
    
    -- Segmento B
    Fb <= '1' when input="10000" else  -- BCD: 0
          '1' when input="10001" else  -- BCD: 1
          '1' when input="10010" else  -- BCD: 2
          '1' when input="10011" else  -- BCD: 3
          '1' when input="10100" else  -- BCD: 4
          '1' when input="10111" else  -- BCD: 7
          '1' when input="11000" else  -- BCD: 8
          '1' when input="11001" else  -- BCD: 9
          '1' when input="00000" else  -- BIN: 0
          '1' when input="00001" else  -- BIN: 1
          '1' when input="00010" else  -- BIN: 2
          '1' when input="00011" else  -- BIN: 3
          '1' when input="00100" else  -- BIN: 4
          '1' when input="00111" else  -- BIN: 7
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01001" else  -- BIN: 9
          '1' when input="01010" else  -- BIN: 10
          '1' when input="01101" else  -- BIN: 13
          '0';
    
    -- Segmento C
    Fc <= '1' when input="10000" else  -- BCD: 0
          '1' when input="10001" else  -- BCD: 1
          '1' when input="10011" else  -- BCD: 3
          '1' when input="10100" else  -- BCD: 4
          '1' when input="10101" else  -- BCD: 5
          '1' when input="10110" else  -- BCD: 6
          '1' when input="10111" else  -- BCD: 7
          '1' when input="11000" else  -- BCD: 8
          '1' when input="11001" else  -- BCD: 9
          '1' when input="00000" else  -- BIN: 0
          '1' when input="00001" else  -- BIN: 1
          '1' when input="00010" else  -- BIN: 2
          '1' when input="00011" else  -- BIN: 3
          '1' when input="00100" else  -- BIN: 4
          '1' when input="00101" else  -- BIN: 5
          '1' when input="00110" else  -- BIN: 6
          '1' when input="00111" else  -- BIN: 7
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01001" else  -- BIN: 9
          '1' when input="01010" else  -- BIN: 10
          '1' when input="01011" else  -- BIN: 11
          '1' when input="01101" else  -- BIN: 13
          '0';
    
    -- Segmento D
    Fd <= '1' when input="10000" else  -- BCD: 0
          '1' when input="10010" else  -- BCD: 2
          '1' when input="10011" else  -- BCD: 3
          '1' when input="10101" else  -- BCD: 5
          '1' when input="10110" else  -- BCD: 6
          '1' when input="11000" else  -- BCD: 8
          '1' when input="11001" else  -- BCD: 9
          '1' when input="00000" else  -- BIN: 0
          '1' when input="00010" else  -- BIN: 2
          '1' when input="00011" else  -- BIN: 3
          '1' when input="00101" else  -- BIN: 5
          '1' when input="00110" else  -- BIN: 6
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01001" else  -- BIN: 9
          '1' when input="01011" else  -- BIN: 11
          '1' when input="01100" else  -- BIN: 12
          '1' when input="01101" else  -- BIN: 13
          '1' when input="01110" else  -- BIN: 14
          '0';
    
    -- Segmento E
    Fe <= '1' when input="10000" else  -- BCD: 0
          '1' when input="10010" else  -- BCD: 2
          '1' when input="10110" else  -- BCD: 6
          '1' when input="11000" else  -- BCD: 8
          '1' when input="00000" else  -- BIN: 0
          '1' when input="00010" else  -- BIN: 2
          '1' when input="00110" else  -- BIN: 6
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01010" else  -- BIN: 10
          '1' when input="01011" else  -- BIN: 11
          '1' when input="01100" else  -- BIN: 12
          '1' when input="01101" else  -- BIN: 13
          '1' when input="01110" else  -- BIN: 14
          '1' when input="01111" else  -- BIN: 15
          '0';
    
    -- Segmento F
    Ff <= '1' when input="10000" else  -- BCD: 0
          '1' when input="10100" else  -- BCD: 4
          '1' when input="10101" else  -- BCD: 5
          '1' when input="10110" else  -- BCD: 6
          '1' when input="11000" else  -- BCD: 8
          '1' when input="11001" else  -- BCD: 9
          '1' when input="00000" else  -- BIN: 0
          '1' when input="00100" else  -- BIN: 4
          '1' when input="00101" else  -- BIN: 5
          '1' when input="00110" else  -- BIN: 6
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01001" else  -- BIN: 9
          '1' when input="01010" else  -- BIN: 10
          '1' when input="01011" else  -- BIN: 11
          '1' when input="01100" else  -- BIN: 12
          '1' when input="01110" else  -- BIN: 14
          '1' when input="01111" else  -- BIN: 15
          '0';
    
    -- Segmento G
    Fg <= '1' when input="10010" else  -- BCD: 2
          '1' when input="10011" else  -- BCD: 3
          '1' when input="10100" else  -- BCD: 4
          '1' when input="10101" else  -- BCD: 5
          '1' when input="10110" else  -- BCD: 6
          '1' when input="11000" else  -- BCD: 8
          '1' when input="11001" else  -- BCD: 9
          '1' when input="11010" else  -- BCD: 10
          '1' when input="11011" else  -- BCD: 11
          '1' when input="11100" else  -- BCD: 12
          '1' when input="11101" else  -- BCD: 13
          '1' when input="11110" else  -- BCD: 14
          '1' when input="11111" else  -- BCD: 15
          '1' when input="00010" else  -- BIN: 2
          '1' when input="00011" else  -- BIN: 3
          '1' when input="00100" else  -- BIN: 4
          '1' when input="00101" else  -- BIN: 5
          '1' when input="00110" else  -- BIN: 6
          '1' when input="01000" else  -- BIN: 8
          '1' when input="01001" else  -- BIN: 9
          '1' when input="01010" else  -- BIN: 10
          '1' when input="01011" else  -- BIN: 11
          '1' when input="01101" else  -- BIN: 13
          '1' when input="01110" else  -- BIN: 14
          '1' when input="01111" else  -- BIN: 15
          '0';

END controlSegmentoBehavior;