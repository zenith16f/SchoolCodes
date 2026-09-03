import com.sun.nio.sctp.PeerAddressChangeNotification;

import java.util.ArrayList;

public class AFN {
    public static final char EPSILON = '\u03B5';

    private ArrayList<Character> alfabeto;
    private Estado estadoInicial;
    private ArrayList<Estado> estadosAccept;
    private ArrayList<Estado> estadosAFN;

    // Functions
    public AFN CrearBasico(char simbolo) {
        AFN f = new AFN();
        Estado estado1, estado2;
        Transicion transicion;
        estado1 = new Estado();
        estado2 = new Estado();
        transicion = new Transicion(simbolo, estado2);
        estado1.getTransciciones().add(transicion);
        estado2.setEstadoAccept(true);
        f.estadoInicial = estado1;
        f.estadosAccept.add(estado2);
        f.estadosAFN.add(estado1);
        f.estadosAFN.add(estado2);
        f.alfabeto.add(simbolo);

        return f;
    }

    public AFN CrearBasico2(char simboloUno, char simboloDos) {
        AFN f = new AFN();
        Estado estado1, estado2;
        Transicion transicion;
        estado1 = new Estado();
        estado2 = new Estado();
        transicion = new Transicion(simboloUno, simboloDos, estado2);
        estado1.getTransciciones().add(transicion);
        estado2.setEstadoAccept(true);
        f.estadoInicial = estado1;
        f.estadosAccept.add(estado2);
        f.estadosAFN.add(estado1);
        f.estadosAFN.add(estado2);
        for (char a = simboloUno; a <= simboloDos; a++) {
            f.alfabeto.add(a);
        }

        return f;
    }

    public AFN UnirAFN(AFN f2) {
        Estado estadoUno, estadoDos;
        estadoUno = new Estado();
        estadoDos = new Estado();
        estadoUno.getTransciciones().add(new Transicion(EPSILON, this.estadoInicial));
        estadoUno.getTransciciones().add(new Transicion(EPSILON, f2.estadoInicial));
        for (Estado estado : this.estadosAccept) {
            estado.getTransciciones().add(new Transicion(EPSILON, estadoDos));
            estado.setEstadoAccept(false);
        }

        for (Estado estado : f2.estadosAccept) {
            estado.getTransciciones().add(new Transicion(EPSILON, estadoDos));
            estado.setEstadoAccept(false);
        }

        estadoDos.setEstadoAccept(true);
        ListUtils.Union(this.estadosAFN, f2.estadosAFN);
        this.estadosAFN.add(estadoUno);
        this.estadosAFN.add(estadoDos);
        this.estadosAccept.clear();
        this.estadosAccept.add(estadoDos);
        this.estadoInicial = estadoUno;
        ListUtils.Union(this.alfabeto, f2.alfabeto);
        f2 = null;

        return this;
    }

    public AFN Concatenar(AFN f2) {
        for (Estado estado : this.estadosAccept) {
            for (Transicion transicion : f2.estadoInicial.getTransciciones()) {
                estado.getTransciciones().add(transicion);
                estado.setEstadoAccept(false);
            }
        }

        ListUtils.Union(this.estadosAFN, f2.estadosAFN);
        this.estadosAFN.remove(f2.estadoInicial);
        this.estadosAccept.clear();
        ListUtils.Union(this.estadosAccept, f2.estadosAccept);
        ListUtils.Union(this.alfabeto, f2.alfabeto);

        return this;
    }

    public AFN CerraduraPositiva() {
        Estado estadoUno = new Estado();
        Estado estadoDos = new Estado();
        estadoUno.getTransciciones().add(new Transicion(EPSILON, this.estadoInicial));

        for (Estado estado : this.estadosAccept) {
            estado.getTransciciones().add(new Transicion(EPSILON, estadoDos));
            estado.getTransciciones().add(new Transicion(EPSILON, this.estadoInicial));
            estado.setEstadoAccept(false);
        }

        this.estadosAFN.add(estadoUno);
        this.estadosAFN.add(estadoDos);
        this.setEstadoInicial(estadoUno);
        this.estadosAccept.clear();
        this.estadosAccept.add(estadoDos);

        return this;
    }

    public AFN CerraduraKleene() {
        this.CerraduraPositiva();

        for (Estado estado : this.estadosAccept) {
            this.estadoInicial.getTransciciones().add(new Transicion(EPSILON, estado));
        }
        ;

        return this;
    }

    public AFN OpOpcional() {
        Estado estadoUno = new Estado();
        Estado estadoDos = new Estado();

        estadoDos.setEstadoAccept(true);
        estadoUno.getTransciciones().add(new Transicion(EPSILON, this.estadoInicial));

        for (Estado estado : this.estadosAccept) {
            estado.getTransciciones().add(new Transicion(EPSILON, estadoDos));
            estado.setEstadoAccept(false);
        }

        estadoUno.getTransciciones().add(new Transicion(EPSILON, estadoDos));
        this.estadosAFN.add(estadoUno);
        this.estadosAFN.add(estadoDos);
        this.setEstadoInicial(estadoUno);
        this.estadosAccept.clear();
        this.estadosAccept.add(estadoDos);

        return this;

    }


    // Getters and Setters
    public ArrayList<Character> getAlfabeto() {
        return alfabeto;
    }

    public void setAlfabeto(ArrayList<Character> alfabeto) {
        this.alfabeto = alfabeto;
    }

    public Estado getEstadoInicial() {
        return estadoInicial;
    }

    public void setEstadoInicial(Estado estadoInicial) {
        this.estadoInicial = estadoInicial;
    }

    public ArrayList<Estado> getEstadosAccept() {
        return estadosAccept;
    }

    public void setEstadosAccept(ArrayList<Estado> estadosAccept) {
        this.estadosAccept = estadosAccept;
    }

    public ArrayList<Estado> getEstadosAFN() {
        return estadosAFN;
    }

    public void setEstadosAFN(ArrayList<Estado> estadosAFN) {
        this.estadosAFN = estadosAFN;
    }
}
