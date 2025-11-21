public class Ala extends Jugador {
    // Variables
    private String posicion;

    // Constructor
    public Ala(String nombreInput, int edadInput, int numeroInput, String posicionInput) {
        super(nombreInput, edadInput, numeroInput);
        posicion = posicionInput;
    }

    // Methods
    @Override
    public void mostrarInfo() {
        System.out.println("Ala - " + nombre + " #" + numero);
    }
}

