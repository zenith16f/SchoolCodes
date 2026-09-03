import java.util.ArrayList;

public class Estado {
    private int idEstado;
    private boolean estadoAccept;
    private ArrayList<Transicion> transciciones;

    private static int ContadorEstado = 0;

    // Getters and Setters

    public int getIdEstado() {
        return idEstado;
    }

    public void setIdEstado(int idEstado) {
        this.idEstado = idEstado;
    }

    public boolean isEstadoAccept() {
        return estadoAccept;
    }

    public void setEstadoAccept(boolean estadoAccept) {
        this.estadoAccept = estadoAccept;
    }

    public ArrayList<Transicion> getTransciciones() {
        return transciciones;
    }

    public void setTransciciones(ArrayList<Transicion> transciciones) {
        this.transciciones = transciciones;
    }

    public static int getContadorEstado() {
        return ContadorEstado;
    }

    public static void setContadorEstado(int contadorEstado) {
        ContadorEstado = contadorEstado;
    }
}
