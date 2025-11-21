/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package practica.pkg2;

/**
 *
 * @author escom
 */
public class CuentaDeAhorros extends Cuenta{
    private double tasaInteres;
    private int contador;
    
 
    public CuentaDeAhorros (double saldoInicial, double tasaInteresInput){
        super(saldoInicial) ;
        tasaInteres=tasaInteresInput;
        contador=0;
    }
    
    @Override
    public double consultar(){
   if(contador==0){
       contador+=1;
       return saldo;
   }
   
        saldo = saldo +(tasaInteres*contador*saldo);
        contador+=1;
   
        return saldo;
    }
    
}
