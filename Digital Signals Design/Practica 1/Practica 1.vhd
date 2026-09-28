library IEEE; 
use IEEE.STD_LOGIC_1164.ALL; 

entity practica1 is 
port (
        A,B,C,D,SEL,REF : in std_logic_vector ( 1 downto 0);
        DISPLAY : out std_logic_vector (6 downto 0)
    );
end entity;

architecture archPractica1 of practica1 is 

signal DATO: std_logic_vector(1 downto 0);
signal I,MA,ME: std_logic;
constant IGUAL : std_logic_vector (6 downto 0) := "0001001";
constant MAYOR : std_logic_vector (6 downto 0) := "0011001";
constant MENOR : std_logic_vector (6 downto 0) := "0001101";

begin
    with SEL select
        DATO <= A when "00",
                B when "01", 
                C when "10",
                D when others;

    process (DATO, REF)
    begin
        I <= '0';
        MA <= '0'; 
        ME <= '0';
        if (DATO > REF) then 
            MA <= '1';
        elsif (DATO < REF) then 
            ME <= '1'; 
        else 
            I <= '1'; 
        end if;
    end process; 

    process (MA,ME)
    begin 
        if(MA = '1') then
            DISPLAY <= MAYOR;
        elsif (ME = '1') then 
            DISPLAY <= MENOR;
        else 
            DISPLAY <= IGUAL;
        end if; 
    end process; 
end archPractica1;