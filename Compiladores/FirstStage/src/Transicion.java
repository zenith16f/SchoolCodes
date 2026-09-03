public class Transicion {
    private char simboloInferior;
    private char simboloSuperior;
    private Estado estadoDestino;

    // Constructors
    public Transicion( char simbolo, Estado estado2) {
        this.estadoDestino = estado2;
        this.simboloInferior = simbolo;
        this.simboloSuperior = simbolo;
    }

    public Transicion(char simboloUno, char simboloDos, Estado estado2) {
        this.estadoDestino = estado2;
        this.simboloInferior = simboloUno;
        this.simboloSuperior = simboloDos;
    }


    // Getters and Setters

    public char getSimboloInferior() {
        return simboloInferior;
    }

    public void setSimboloInferior(char simboloInferior) {
        this.simboloInferior = simboloInferior;
    }

    public char getSimboloSuperior() {
        return simboloSuperior;
    }

    public void setSimboloSuperior(char simboloSuperior) {
        this.simboloSuperior = simboloSuperior;
    }

    public Estado getEstadoDestino() {
        return estadoDestino;
    }

    public void setEstadoDestino(Estado estadoDestino) {
        this.estadoDestino = estadoDestino;
    }
}
