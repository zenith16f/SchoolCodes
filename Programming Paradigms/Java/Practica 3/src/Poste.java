public class Poste extends Jugador {
    // Variables
    private String posicion;

    // Constructor
    public Poste(String nombreInput, int edadInput, int numeroInput, String posicionInput) {
        super(nombreInput, edadInput, numeroInput);
        posicion = posicionInput;
    }

    // Methods
    @Override
    public void mostrarInfo() {
        System.out.println("Poste - " + nombre + " #" + numero);
    }
}

