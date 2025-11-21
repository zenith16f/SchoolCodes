//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

        // Inicializations
        Equipo myTeam = new Equipo("Zado","Tercera Division");
        Base base = new Base("Marco",21,30,"Base" );
        Ala alaDer = new Ala("Antonio",19,3,"Ala Derecha");
        Ala alaIzq =  new Ala("Lopez",20,24,"Ala Izquierda");
        Poste posteDer = new Poste("Isaac",22,56,"Poste Derecho");
        Poste posteIzq = new Poste("Jhon",20,1,"Poste Izquierdo");
        Suplente suplenteUno  = new Suplente("Doe",21,11,"Suplente A");
        Suplente suplenteDos  = new Suplente("Jane Doe",21,16,"Suplente B");


        // Setters
        myTeam.setBase(base);
        myTeam.setAlaDer(alaDer);
        myTeam.setAlaIzq(alaIzq);
        myTeam.setPosteDer(posteDer);
        myTeam.setPosteIzq(posteIzq);
        myTeam.setSuplenteUno(suplenteUno);
        myTeam.setSuplenteDos(suplenteDos);

        // Show team
        myTeam.mostrarEquipo();

        // Checking if the team is complete
        if (myTeam.equipoCompleto()) {
            System.out.println("El equipo esta completo");
        }else{
            System.out.println("El equipo esta incompleto, consigue jugadores");
        }

    }
}