package annale2017;

import java.util.function.Function;
import java.util.function.Supplier;

public sealed interface Soit<G,D> {

    //fonction d'instance
    boolean isGauche();
    G getGaucheOr(G or);
    G getGaucheOrElse(Supplier<G> orElse);
    <V> V match(Function<G, V> fg, Function<D, V> fd);

    //fabrique statiques
    static <G,D> Soit<G,D> gauche(G valeur){
        return new Gauche<>(valeur);
    }

    static <G,D> Soit<G,D> droite(D valeur){
        return new Droite<>(valeur);
    }

    //classes
    
    record Gauche<G,D>(G valeur) implements Soit<G,D> {

        public boolean isGauche(){
            return true;
        }

        public G getGaucheOr(G or){
            return valeur;
        }

        public G getGaucheOrElse(Supplier<G> orElse){
            return valeur;
        }

        public <V> V match(Function<G, V> fg, Function<D, V> fd){
            return fg.apply(valeur);
        }
    }
    
    record Droite<G,D>(D valeur) implements Soit<G,D> {

        public boolean isGauche(){
            return false;
        }

        public G getGaucheOr(G or){
            return or;
        }

        public G getGaucheOrElse(Supplier<G> orElse){
            return orElse.get();
        }

        public <V> V match(Function<G, V> fg, Function<D, V> fd){
            return fd.apply(valeur);
        }
    }
}
