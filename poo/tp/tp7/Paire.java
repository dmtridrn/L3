package tp.tp7;

import java.util.List;

public class Paire<X,Y> {
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
    private void setGauche(X g){
        this.gauche = g;
    }
    private void setDroite(Y d){
        this.droite = d;
    }

    static <U extends Number, V extends Number> Paire<Double, Double> somme(List<Paire<U, V>> aSommer){
        double resGauche = 0;
        double resDroit = 0;
        for(Paire<U, V> elt : aSommer){
            resGauche += elt.getGauche().doubleValue();
            resDroit += elt.getDroite().doubleValue();
        }
        return new Paire<Double,Double>(resGauche,resDroit);
    }

    public static void main(String[] args){
        Paire<? extends Number, ? extends Number> p1 = new Paire<Integer, Integer>(15, 12);
        Paire<? super Integer, ? super Integer> p2 = new Paire<Number, Number>(15, 12);
        p2.setDroite(60);
    }
}

