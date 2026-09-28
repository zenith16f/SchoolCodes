library ieee;
use ieee.std_logic_1164.all;


entity TareaFlipFlops is
    port (
        -- Inputs Flip Flops
        D           : in  std_logic;
        T           : in  std_logic;
        J, K        : in  std_logic;
        S, R        : in  std_logic;

        -- Flip Flops Share
        CLK         : in  std_logic;
        PRE         : in  std_logic;
        CLR         : in  std_logic;


        -- MUX Inputs
        SEL         : in  STD_LOGIC_VECTOR(1 downto 0);

        -- Outputs
        Q, NQ         : out std_logic
    );
end entity;

architecture archTareaFlipFLops of TareaFlipFlops is
function nextD(D : std_logic) return std_logic is
begin
    return D;
end function;

function nextT(T,Q : std_logic) return std_logic is
begin
    return T xor Q;
end function;

function nextJK(J, K, Q: std_logic) return std_logic is
begin
    return (J and not Q) or (not K and Q);
end function;

function nextSR(S, R ,Q: std_logic) return std_logic is
begin
    return S or (not R and Q);
end function;


signal QD, QT, QJK, QSR : std_logic := '0';
signal busD, busT, busJK, busSR : STD_LOGIC_VECTOR(1 downto 0);
signal muxOut : STD_LOGIC_VECTOR(1 downto 0);

begin
 -- Flip Flop D
 process(CLK, PRE, CLR, D)
 begin
    if PRE = '1' then
        QD <= '1';
    elsif CLR = '1' then
        QD <= '0';
    elsif rising_edge(CLK) then
        QD <= nextD(D);
    end if;
 end process;

 -- Flip Flop T
    process(CLK, PRE, CLR, QT, T)
    begin
        if PRE = '1' then
            QT <= '1';
        elsif CLR = '1' then
            QT <= '0';
        elsif rising_edge(CLK) then
            QT <= nextT(T, QT);
        end if;
    end process;

    -- Flip Flop JK
    process (CLK, PRE, CLR, J, K, QJK)
    begin
        if PRE = '1' then
            QJK <= '1';
        elsif CLR = '1' then
            QJK <= '0';
        elsif rising_edge(CLK) then
            QJK <= nextJK(J, K, QJK);
        end if;
    end process;
    
    -- Flip Flop SR
    process (CLK, PRE, CLR, S, R, QSR)
    begin
        if PRE = '1' then
            QSR <= '1';
        elsif CLR = '1' then
            QSR <= '0';
        elsif rising_edge(CLK) then
            QSR <= nextSR(S, R, QSR);
        end if;
    end process;
    

    -- Flip Flop Outputs
    busD  <= qD  & (not qD);
    busT  <= qT  & (not qT);
    busJK <= qJK & (not qJK);
    busSR <= qSR & (not qSR);

    -- MUX
    with SEL select
        muxOut <= busD  when "00",
                   busT  when "01",
                   busJK when "10",
                   busSR when others;

    Q  <= muxOut(1);
    NQ <= muxOut(0);
end architecture;