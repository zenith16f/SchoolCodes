
public class Equipo {
    // Variables
    private String nombre, categoria;

    // Team composition
    private Base base;
    private Ala alaDer;
    private Ala alaIzq;
    private Poste posteDer;
    private Poste posteIzq;
    private Suplente suplenteUno;
    private Suplente suplenteDos;

    // Constructor
    public Equipo(String nombreInput, String categoriaInput) {
        nombre = nombreInput;
        categoria = categoriaInput;
    }

    // Getters and Setters
    // Setters
    public void setBase(Base base) {
        this.base = base;
    }

    public void setAlaDer(Ala alaDer) {
        this.alaDer = alaDer;
    }

    public void setAlaIzq(Ala alaIzq) {
        this.alaIzq = alaIzq;
    }

    public void setPosteDer(Poste posteDer) {
        this.posteDer = posteDer;
    }

    public void setPosteIzq(Poste posteIzq) {
        this.posteIzq = posteIzq;
    }

    public void setSuplenteUno(Suplente suplenteUno) {
        this.suplenteUno = suplenteUno;
    }

    public void setSuplenteDos(Suplente suplenteDos) {
        this.suplenteDos = suplenteDos;
    }


    // Getters
    public Base getBase() {
        return base;
    }

    public Ala getAlaDer() {
        return alaDer;
    }

    public Ala getAlaIzq() {
        return alaIzq;
    }

    public Poste getPosteDer() {
        return posteDer;
    }

    public Poste getPosteIzq() {
        return posteIzq;
    }

    public Suplente getSuplenteUno() {
        return suplenteUno;
    }

    public Suplente getSuplenteDos() {
        return suplenteDos;
    }

    // Methods
    public void mostrarEquipo() {
        System.out.println("=== Nombre: " + nombre + " Categoria: " + categoria + " ===");

        if (base != null) {
            base.mostrarInfo();
        } else {
            System.out.println("Base sin asignar");
        }
        if (alaDer != null) {
            alaDer.mostrarInfo();
        } else {
            System.out.println("Ala Derecha sin asignar");
        }

        if (alaIzq != null) {
            alaIzq.mostrarInfo();
        } else {
            System.out.println("Ala Izquierda sin asignar");
        }

        if (posteDer != null) {
            posteDer.mostrarInfo();
        } else {
            System.out.println("Poste Derecho sin asignar");
        }

        if (posteIzq != null) {
            posteIzq.mostrarInfo();
        } else {
            System.out.println("Poste Izquierdo sin asignar");
        }

        if (suplenteUno != null) {
            suplenteUno.mostrarInfo();
        } else {
            System.out.println("Suplente Uno sin asignar");
        }

        if (suplenteDos != null) {
            suplenteDos.mostrarInfo();
        } else {
            System.out.println("Suplente Dos sin asignar");
        }
    }

    public Boolean equipoCompleto() {
        return base != null && alaDer != null && alaIzq != null && posteDer != null && posteIzq != null && suplenteUno != null && suplenteDos != null;
    }
}
