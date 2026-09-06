library ieee;
use ieee.std_logic_1164.all;

package pkg_comparador is
    -- Patrones de 7 segmentos (cátodo común, orden a-b-c-d-e-f-g)
    constant SEG_IGUAL : std_logic_vector(6 downto 0) := "0001001"; -- =
    constant SEG_MAYOR : std_logic_vector(6 downto 0) := "0001101"; -- >
    constant SEG_MENOR : std_logic_vector(6 downto 0) := "0011001"; -- <
    constant SEG_OFF   : std_logic_vector(6 downto 0) := "0000000"; -- apagado

    -- Códigos internos del resultado del comparador
    constant COMP_IGUAL : std_logic_vector(1 downto 0) := "00";
    constant COMP_MAYOR : std_logic_vector(1 downto 0) := "01";
    constant COMP_MENOR : std_logic_vector(1 downto 0) := "10";
end package pkg_comparador;