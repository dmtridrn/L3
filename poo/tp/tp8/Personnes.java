package tp.tp8;

public class Personnes {
    final String nom;
    public Personnes(String nom){
        this.nom = nom;
    }

    @Override
    public String toString(){
        return this.nom;
    }
}
