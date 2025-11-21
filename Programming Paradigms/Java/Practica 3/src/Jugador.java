public class Jugador {
    // Variables
    protected String nombre;
    protected int numero, edad;

    // Constructor
    public Jugador(String nombreInput, int edadInput, int numeroInput) {
        nombre = nombreInput;
        edad = edadInput;
        numero = numeroInput;
    }

    public void mostrarInfo(){
        System.out.println("Nombre: " + nombre + ", Número: " + numero + ", Edad: " + edad);
    }
}
