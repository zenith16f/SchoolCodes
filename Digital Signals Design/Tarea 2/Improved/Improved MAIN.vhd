library ieee;
use ieee.std_logic_1164.all;

entity top_comparador is
    generic (
        N            : integer := 2;
        USAR_REGISTRO : boolean := true  -- true = salida sincronizada, false = combinacional pura
    );
    port (
        clk        : in  std_logic;
        A, B, C, D : in  std_logic_vector(N-1 downto 0);
        SEL        : in  std_logic_vector(1 downto 0);
        REF        : in  std_logic_vector(N-1 downto 0);
        SEG        : out std_logic_vector(6 downto 0)
    );
end entity top_comparador;

architecture estructural of top_comparador is

    component mux4x1_gen is
        generic ( N : integer := 2 );
        port (
            A, B, C, D : in  std_logic_vector(N-1 downto 0);
            SEL        : in  std_logic_vector(1 downto 0);
            DATO       : out std_logic_vector(N-1 downto 0)
        );
    end component;

    component comparador_gen is
        generic ( N : integer := 2 );
        port (
            DATO : in  std_logic_vector(N-1 downto 0);
            REF  : in  std_logic_vector(N-1 downto 0);
            COMP : out std_logic_vector(1 downto 0)
        );
    end component;

    component deco_comp_7seg is
        port (
            COMP : in  std_logic_vector(1 downto 0);
            SEG  : out std_logic_vector(6 downto 0)
        );
    end component;

    signal s_dato     : std_logic_vector(N-1 downto 0);
    signal s_comp      : std_logic_vector(1 downto 0);
    signal s_seg_comb  : std_logic_vector(6 downto 0);
    signal s_seg_reg   : std_logic_vector(6 downto 0) := (others => '0');

begin
    U1: mux4x1_gen
        generic map (N => N)
        port map (A => A, B => B, C => C, D => D, SEL => SEL, DATO => s_dato);

    U2: comparador_gen
        generic map (N => N)
        port map (DATO => s_dato, REF => REF, COMP => s_comp);

    U3: deco_comp_7seg
        port map (COMP => s_comp, SEG => s_seg_comb);

    -- Registro opcional: solo se sintetiza si USAR_REGISTRO = true
    gen_reg: if USAR_REGISTRO generate
        process(clk)
        begin
            if rising_edge(clk) then
                s_seg_reg <= s_seg_comb;
            end if;
        end process;
        SEG <= s_seg_reg;
    end generate gen_reg;

    gen_comb: if not USAR_REGISTRO generate
        SEG <= s_seg_comb;
    end generate gen_comb;

end architecture estructural;