package tp.tp8;

import java.util.function.Consumer;

public class Test {
    
    public static void main(String[] args){
        MaListe<Personne> maliste = new MaListe<>();
        Personne p1 = new Personne("riri");
        Personne p2 = new Personne("titi");
        Personne p3 = new Personne("pipi");

        maliste.add(p1);
        maliste.add(p2);
        maliste.add(p3);

        Consumer<MaListe<Personne>> afficheur = liste -> {
            int cpt = 1;
            for(Personne p : liste) {
                System.out.println(cpt + ": " + p);
                cpt++;
            }
        };
        
        afficheur.accept(maliste);

        
    }
}

