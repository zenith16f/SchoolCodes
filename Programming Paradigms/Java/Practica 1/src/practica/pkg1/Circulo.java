/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package practica.pkg1;

/**
 *
 * @author escom
 */
public class Circulo {
    double radio;
    
    Circulo(double radioInput){
        radio =radioInput;
    }
    
    double areaCirculo(){
        return Math.PI* Math.pow(radio,2);
    }
}
