/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package practica.pkg2;

/**
 *
 * @author escom
 */
public class Practica2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       Cuenta cuenta = new Cuenta(1000);
       CuentaDeAhorros cuentaAhorros = new CuentaDeAhorros(1000,0.3);
       CuentaDeCheques cuentaCheques = new CuentaDeCheques(1000,200);
       
        System.out.println("EL saldo inicial dela cuenta de ahorros: "+cuentaAhorros.consultar());
        System.out.println("El saldo Inicial de la cuenta de cheques: "+cuentaCheques.consultar());
        System.out.println("SAldo de la cuenta de ahorros en un mes: "+cuentaAhorros.consultar());
        cuentaCheques.retirar(1100);
        cuentaCheques.retirar(150);
    }
    
}
