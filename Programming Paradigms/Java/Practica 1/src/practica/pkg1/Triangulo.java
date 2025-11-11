/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package practica.pkg1;

/**
 *
 * @author escom
 */
public class Triangulo {
    double baseT,alturaT;
    
    Triangulo(double base, double altura){
        baseT = base;
        alturaT= altura;
    }
    
    double areaTriangulo(){
        return (baseT*alturaT)/2;
    }
}
