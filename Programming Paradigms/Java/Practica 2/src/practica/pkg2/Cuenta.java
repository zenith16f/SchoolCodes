/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package practica.pkg2;

/**
 *
 * @author escom
 */
public class Cuenta {
    protected double saldo;
    
   public Cuenta(double saldoInicial){
        saldo=saldoInicial;
    }
    
    public double consultar(){
        return saldo;
    }
    
    public void depositar(double monto){
        saldo = saldo+monto;
    }
    
    public void retirar(double monto){
        if(monto<saldo){
            saldo = saldo-monto;
            System.out.println("Saldo en la cuenta: "+saldo);
        }else{
            System.out.println("No es posible retirar, fondos insuficientes ");
        }
    }
}
