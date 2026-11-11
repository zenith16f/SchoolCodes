library IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE. STD_LOGIC_UNSIGNED. ALL;

entity Practica2 is 
port ( CLK,CLR,PRE,D,T,J,K,S,R: in std_logic; 
       SEL: in std_logic_vector(1 downto 0);
       CLKOUT: INOUT STD_LOGIC;
       Q: inout std_logic_vector(1 downto 0)
      );
end entity;

architecture ArchPractica2 of Practica2 is 
SIGNAL CONTADOR: STD_LOGIC_VECTOR (24 DOWNTO 0):=(OTHERS=>'0');
CONSTANT DIVISOR: INTEGER:= 27000000;
begin 

PROCESS (CLK)
BEGIN
IF RISING_EDGE(CLK) THEN
       IF (CONTADOR=DIVISOR) THEN
      CONTADOR<=(OTHERS =>'0');
      CLKOUT<= NOT CLKOUT;
      ELSE
     CONTADOR<=CONTADOR + 1;
     END IF;
END IF;
END PROCESS;

process (CLKOUT,CLR,PRE,D,T,J,K,S,R,SEL)
begin
if(CLR='0')then
    Q<="01";
elsif rising_edge (CLKOUT) then 
if(PRE='1') then 
    Q<="10";
else 
case SEL is
--FlipFlop D
when "00" =>
    Q(1)<=D;
    Q(0)<= not D; 
--FlipFlop T
when "01" =>
    Q(1)<= ((not t) and Q(1)) or (T and Q(0));
    Q(0)<= not (((not t) and Q(1)) or (T and Q(0)));
--FlipFlop JK
when "10" =>
    Q(1)<=((not K) and Q(1)) or (J and Q(0));
    Q(0)<= not (((not K) and Q(1)) or (J and Q(0)));
--FlipFlop SR
when others =>
if(S='1' and R='1') then 
    Q(1)<= '1';
    Q(0)<='1';
else 
    Q(1)<=S or ((not R) and Q(1));
    Q(0)<=not (S or ((not R) and Q(1)));
end if;
end case;
end if; 
end if; 
end process; 
end ArchPractica2;