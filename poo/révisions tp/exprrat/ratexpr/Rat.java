package ratexpr;

import java.util.List;

public interface Rat {

    /* les méthodes d’instance */
    boolean containsUnit();

    Rat derivee(char symbol);

    boolean contains(String word);

    /* les fabriques statiques */
    public static Rat symbol(char s) {
        return null; /* compléter ! */
    }

    public static Rat emptySet() {
        return null; /* compléter ! */
    }

    public static Rat epsilon() {
        return null; /* compléter ! */
    }

    public static Rat append(Rat a, Rat b) {
        return null; /* compléter ! */
    }

    public static Rat union(Rat a, Rat b) {
        return null; /* compléter ! */
    }

    public static Rat star(Rat a) {
        return null; /* compléter ! */
    }

}
