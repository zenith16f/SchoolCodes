public class Suplente extends Jugador {
    // Variables
    private String posicion;

    // Constructor
    public Suplente(String nombreInput, int edadInput, int numeroInput,String posicionInput) {
        super(nombreInput, edadInput, numeroInput);
        posicion = posicionInput;
    }


    // Methods
    @Override
    public void mostrarInfo() {
        System.out.println("Suplente - " + nombre + " #" + numero);
    }
}

