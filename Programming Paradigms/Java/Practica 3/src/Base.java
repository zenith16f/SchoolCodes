public class Base extends Jugador {
    // Variables
    private String posicion;

    // Constructor
    public Base(String nombreInput, int edadInput, int numeroInput, String posicionInput) {
        super(nombreInput, edadInput, numeroInput);
        posicion = posicionInput;
    }

    // Methods
    @Override
    public void mostrarInfo() {
        System.out.println("Base - " + nombre + " #" + numero);
    }
}

