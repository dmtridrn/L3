package ratexpr;

import java.util.List;

public sealed interface Rat permits Symbol, EmptySet, Epsilon, Union, Append, Star{

    /* les méthodes d’instance */
    boolean containsUnit();

    Rat derivee(char symbol);

    boolean contains(String word);

    /* les fabriques statiques */
    public static Rat symbol(char s) {
        return new Symbol(s);
    }

    public static Rat emptySet() {
        return new EmptySet();
    }

    public static Rat epsilon() {
        return new Epsilon();
    }

    public static Rat append(Rat a, Rat b) {
        return new Append(a, b);
    }

    public static Rat union(Rat a, Rat b) {
        return new Union(a, b);
    }

    public static Rat star(Rat a) {
        return new Star(a);
    }

}
