package tp.tp7;

import java.util.NoSuchElementException;

public class Optionnel<T> {
    private T elem;
    @SuppressWarnings("rawtypes")
    private static Optionnel VIDE = new Optionnel<>(null);

    private Optionnel(T elem){
        this.elem = elem;
    }

    public static <T> Optionnel<T> de(T elt){
        if(elt == null){
            throw new IllegalArgumentException();
        }
        return new Optionnel<>(elt);
    }

    @SuppressWarnings("unchecked")
    public static <T> Optionnel<T> vide(){
        return VIDE;
    }

    boolean estVide(){
        return elem == null;
    }

    T get(){
        if(this.elem == null){
            throw new NoSuchElementException();
        }
        return elem;
    }

    T ouSinon(T sinon){
        return estVide() ? sinon : elem;
    }
}

