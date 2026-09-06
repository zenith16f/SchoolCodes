library ieee;
use ieee.std_logic_1164.all;

entity main is
    port (
        A, B, C, D : in  std_logic_vector(1 downto 0);
        SEL        : in  std_logic_vector(1 downto 0);
        REF        : in  std_logic_vector(1 downto 0);
        SEG        : out std_logic_vector(6 downto 0)
    );
end entity main;

architecture estructural of main is

    component mux4x1_2bit is
        port (
            A, B, C, D : in  std_logic_vector(1 downto 0);
            SEL        : in  std_logic_vector(1 downto 0);
            DATO       : out std_logic_vector(1 downto 0)
        );
    end component;

    component comparador2bit is
        port (
            DATO : in  std_logic_vector(1 downto 0);
            REF  : in  std_logic_vector(1 downto 0);
            COMP : out std_logic_vector(1 downto 0)
        );
    end component;

    component deco_comp_7seg is
        port (
            COMP : in  std_logic_vector(1 downto 0);
            SEG  : out std_logic_vector(6 downto 0)
        );
    end component;

    signal s_dato : std_logic_vector(1 downto 0);
    signal s_comp : std_logic_vector(1 downto 0);

begin
    U1: mux4x1_2bit
        port map (A => A, B => B, C => C, D => D, SEL => SEL, DATO => s_dato);

    U2: comparador2bit
        port map (DATO => s_dato, REF => REF, COMP => s_comp);

    U3: deco_comp_7seg
        port map (COMP => s_comp, SEG => SEG);

end architecture estructural;