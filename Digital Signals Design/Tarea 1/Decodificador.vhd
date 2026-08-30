entity bcd_7seg is
    port (
        bcd : in  bit_vector(3 downto 0);  -- 0000 a 1001 (0-9)
        a, b, c, d, e, f, g : out bit
    );
end entity bcd_7seg;

architecture comportamiento of bcd_7seg is
    signal segmentos : bit_vector(6 downto 0); -- orden: a b c d e f g
begin
    with bcd select
        segmentos <= "1111110" when "0000", -- 0
                      "0110000" when "0001", -- 1
                      "1101101" when "0010", -- 2
                      "1111001" when "0011", -- 3
                      "0110011" when "0100", -- 4
                      "1011011" when "0101", -- 5
                      "1011111" when "0110", -- 6
                      "1110000" when "0111", -- 7
                      "1111111" when "1000", -- 8
                      "1111011" when "1001", -- 9
                      "0000000" when others;  -- apagado (entradas no válidas)

    a <= segmentos(6);
    b <= segmentos(5);
    c <= segmentos(4);
    d <= segmentos(3);
    e <= segmentos(2);
    f <= segmentos(1);
    g <= segmentos(0);
end architecture comportamiento;