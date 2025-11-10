package tp.tp7;

import java.util.List;

public class Paire<X,Y>{
    public X gauche;
    public Y droite;

    public Paire(X gauche, Y droite){
        this.gauche = gauche;
        this.droite = droite;
    }

    public X getGauche(){
        return this.gauche;
    }
    public Y getDroite(){
        return this.droite;
    }
    public void setGauche(X g){
        this.gauche = g;
    }
    public void setDroite(Y d){
        this.droite = d;
    }

    static <U extends Number, V extends Number> Paire<Double, Double> somme(List<Paire<U, V>> aSommer){
        Double g = 0.0;
        Double d = 0.0;
        for(Paire<U,V> e : aSommer){
            g += e.gauche.doubleValue();
            d += e.droite.doubleValue();
        }
        return new Paire<>(g, d);
    }
}