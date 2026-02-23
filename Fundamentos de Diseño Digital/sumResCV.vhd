-- =====================================================
-- Sumador/Restador de 4 bits para GAL22V10
-- Usando componente sumCom
-- Control: Ci = 0 → Suma (A+B)
--          Ci = 1 → Resta (A-B)
-- =====================================================

library ieee;
use ieee.std_logic_1164.all;

entity sumador_restador_4bits is
    port(
        -- Entradas (9 pines totales)
        A: in std_logic_vector(3 downto 0);
        B: in std_logic_vector(3 downto 0);
        Ci: in std_logic;
        
        -- Salidas (5 pines totales)
        S: out std_logic_vector(3 downto 0);
        Co: out std_logic
    );
end sumador_restador_4bits;

architecture estructural of sumador_restador_4bits is
    
    -- ========================================
    -- Declaración del componente sumCom
    -- ========================================
    component sumCom
        port(
            x, y: in std_logic;
            s: out std_logic;
            cs: out std_logic;
            c: in std_logic
        );
    end component;
    
    -- ========================================
    -- Señales internas
    -- ========================================
    signal B_xor: std_logic_vector(3 downto 0);  -- B modificado
    signal carries: std_logic_vector(2 downto 0); -- Acarreos intermedios
    
begin
    
    -- ========================================
    -- Control de operación con XOR
    -- ========================================
    B_xor(0) <= B(0) xor Ci;
    B_xor(1) <= B(1) xor Ci;
    B_xor(2) <= B(2) xor Ci;
    B_xor(3) <= B(3) xor Ci;
    
    -- ========================================
    -- Instanciación de 4 sumadores completos
    -- ========================================
    
    -- Bit 0 (LSB)
    U0: sumCom port map(
        x => A(0),
        y => B_xor(0),
        s => S(0),
        cs => carries(0),
        c => Ci
    );
    
    -- Bit 1
    U1: sumCom port map(
        x => A(1),
        y => B_xor(1),
        s => S(1),
        cs => carries(1),
        c => carries(0)
    );
    
    -- Bit 2
    U2: sumCom port map(
        x => A(2),
        y => B_xor(2),
        s => S(2),
        cs => carries(2),
        c => carries(1)
    );
    
    -- Bit 3 (MSB)
    U3: sumCom port map(
        x => A(3),
        y => B_xor(3),
        s => S(3),
        cs => Co,
        c => carries(2)
    );
    
end estructural;