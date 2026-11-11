library IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE. STD_LOGIC_UNSIGNED. ALL;

entity PRAC3 is 
port ( CLK,CLR, E: in std_logic; 
       Y: out std_logic;
       CLKOUT: INOUT STD_LOGIC;
       Q: inout std_logic_vector(7 downto 0)
      );
end entity;

architecture A_PRAC3 of PRAC3 is 

SIGNAL CONTADOR: STD_LOGIC_VECTOR (24 DOWNTO 0):=(OTHERS=>'0');
CONSTANT DIVISOR: INTEGER:= 270000;
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

PROCESS (CLKOUT,CLR)
variable j0,k0,j1,k1,j2,k2,j3,k3,j4,k4,j5,k5,j6,k6,j7,k7 : STD_LOGIC;
begin 
if(CLR='0')then
Q(0)<='0';
Q(1)<='0';
Q(2)<='0';
Q(3)<='0';
Q(4)<='0';
Q(5)<='0';
Q(6)<='0';
Q(7)<='0';
elsif rising_edge(CLKOUT) then
if(E='1') then 
--FF 0 
j0:=E;
k0:=E;
Q(0) <= ((not k0) and Q(0)) or (j0 and (not Q(0)));
--FF 1 
j1:=E and Q(0);
k1:=E and Q(0);
Q(1) <= ((not k1) and Q(1)) or (j1 and (not Q(1)));
--FF 2 
j2:=E and Q(1) and Q(0);
k2:=E and Q(1) and Q(0);
Q(2) <= ((not k2) and Q(2)) or (j2 and (not Q(2)));
--FF 3 
j3:=E and Q(2) and Q(1) and Q(0);
k3:=E and Q(2) and Q(1) and Q(0);
Q(3) <= ((not k3) and Q(3)) or (j3 and (not Q(3)));
--FF 4 
j4:=E and Q(3) and Q(2) and Q(1) and Q(0);
k4:=E and Q(3) and Q(2) and Q(1) and Q(0);
Q(4) <= ((not k4) and Q(4)) or (j4 and (not Q(4)));
--FF 5 
j5:=E and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
k5:=E and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
Q(5) <= ((not k5) and Q(5)) or (j5 and (not Q(5)));
--FF 6 
j6:=E and Q(5) and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
k6:=E and Q(5) and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
Q(6) <= ((not k6) and Q(6)) or (j6 and (not Q(6)));
--FF 7 
j7:=E and Q(6) and Q(5) and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
k7:=E and Q(6) and Q(5) and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
Q(7) <= ((not k7) and Q(7)) or (j7 and (not Q(7)));
y <= E and Q(7) and Q(6) and Q(5) and Q(4) and Q(3) and Q(2) and Q(1) and Q(0);
end if;
end if; 
END PROCESS; 

end A_PRAC3;