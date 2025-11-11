/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package practica.pkg1;

/**
 *
 * @author escom
 */
public class Practica1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // Initialization
        Triangulo triangulo = new Triangulo(3.0,5.0);
        Cuadrado cuadrado = new Cuadrado (10.0);
        Circulo circulo = new Circulo(5.0);
        
        // Functions
        double areaTriangulo = triangulo.areaTriangulo();
        double areaCuadrado = cuadrado.areaCuadrado();
        double areaCirculo = circulo.areaCirculo();
        
        // Output
        System.out.println("El area del triangulo es: " + areaTriangulo);
        System.out.println("El area del cuadrado es: "+areaCuadrado);
        System.out.println("El area del circulo es: "+areaCirculo);
    }
    
}
