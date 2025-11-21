/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package practica.pkg2;

/**
 *
 * @author escom
 */
public class CuentaDeCheques extends Cuenta{
    
    private double sobregiro;
    
    public CuentaDeCheques(double saldoInicial,double sobregiroInput){
        super(saldoInicial);
        sobregiro=sobregiroInput;
    }
    
    public CuentaDeCheques(double saldoInicial){
        super(saldoInicial);
    }
    
    @Override
    public void retirar(double monto){
        System.out.println("REtirar de la cuenta de cheuqes: "+monto);
        if(monto<(saldo+sobregiro)){
            saldo = saldo-monto;
        System.out.println("Saldo de la ce¿uenta de cheques: "+saldo);
    }
        else{
            System.out.println("No es posible retirar, saldo insuficiente");
        }
    }
}
